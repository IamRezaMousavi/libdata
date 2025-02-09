#ifndef __INI_H__
#define __INI_H__

#include <stddef.h>

#define MAX_LINE 256

#define INI_COMMENT_PREFIXES ";#"

typedef int (*ini_handler)(void *userdata, const char *section, const char *key, const char *value);

size_t parse_ini(const char *filename, ini_handler handler, void *userdata);

#endif /* __INI_H__ */
