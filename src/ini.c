#include "ini.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char *trim(char *str) {
    while (*str && isspace((unsigned char)*str))
        str++;
    if (*str == '\0')
        return str;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';
    return str;
}

static char *find_chars_or_comment(char *str, const char *chars) {
    while (*str && !(strchr(chars, *str) || strchr(INI_COMMENT_PREFIXES, *str)))
        str++;
    return str;
}

/* Similar to strncpy, but ensures dest (size bytes) is
NUL-terminated, and doesn't pad with NULs. */
static char *ini_strncpy0(char *dest, const char *src, size_t size) {
    size_t i;
    for (i = 0; i < size - 1 && src[i]; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

size_t ini_parse_file(FILE *file, ini_handler handler, void *userdata) {
    char  line[MAX_LINE], section[MAX_LINE] = "";
    char *start;
    char *end;

    size_t error  = 0;
    size_t lineno = 0;
    while (fgets(line, MAX_LINE, file)) {
        lineno++;

        start = trim(line);

        if (strchr(INI_COMMENT_PREFIXES, *start)) {
            /* start of line comment */
        }

        else if (*start == '[') {
            /* A "[section]" line */
            end = find_chars_or_comment(start + 1, "]");
            if (*end == ']') {
                *end  = '\0';
                start = trim(start + 1);
                ini_strncpy0(section, start, sizeof(section) - 1);
            } else if (!error) {
                error = lineno;
            }
        }

        else if (*start) {
            /* Not a comment, must be a name[=:]value pair */
            end = find_chars_or_comment(start + 1, "=:");
            if (*end == '=' || *end == ':') {
                *end        = '\0';
                char *key   = trim(start);
                char *value = end + 1;

                end = find_chars_or_comment(value, "");
                if (*end)
                    *end = '\0';

                value = trim(value);

                if (!handler(userdata, section, key, value) && !error) {
                    error = lineno;
                }
            } else if (!error) {
                error = lineno;
            }
        }
    }

    return error;
}

size_t ini_parse(const char *filename, ini_handler handler, void *userdata) {
    FILE *file = fopen(filename, "r");
    if (!file)
        return -1;

    size_t error = ini_parse_file(file, handler, userdata);
    fclose(file);
    return error;
}
