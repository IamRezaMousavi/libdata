#include "ini.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char *trim(char *str) {
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';
    return str;
}

static char *find_chars_or_comment(char *str, const char *chars) {
    char *p = str;
    while (*p && !(strchr(chars, *p) || *p == '#' || *p == ';'))
        p++;
    *p = '\0';
    trim(str);
    return p;
}

void parse_ini(const char *filename, ini_handler callback, void *userdata) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open file");
        return;
    }

    char   line[MAX_LINE], section[MAX_LINE] = "";
    char  *linep  = line;
    size_t lineno = 0;
    while (fgets(line, MAX_LINE, file)) {
        lineno++;
        linep = trim(line);
        if (strlen(linep) == 0 || line[0] == ';' || line[0] == '#')
            continue;

        if (*linep == '[') {
            char *end = find_chars_or_comment(line + 1, "]");
            if (end) {
                linep = trim(line + 1);
                strncpy(section, linep, sizeof(section) - 1);
                section[sizeof(section) - 1] = '\0';
            }
        } else {
            char *equals = find_chars_or_comment(line + 1, "=");
            if (equals) {
                char *key   = line;
                char *value = equals + 1;
                key         = trim(key);
                value       = trim(value);
                callback(userdata, section, key, value);
            }
        }
    }
    fclose(file);
}
