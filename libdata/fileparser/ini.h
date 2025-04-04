/**
 * This project uses the modified version of inih library.
 * Original repository: https://github.com/benhoyt/inih
 * License: BSD
 */

#ifndef __INI_H__
#define __INI_H__

#include <stddef.h>

#define MAX_LINE 256

#define INI_COMMENT_PREFIXES ";#"

typedef int (*ini_handler)(void *userdata, const char *section, const char *key, const char *value);

size_t ini_parse(const char *filename, ini_handler handler, void *userdata);

#endif /* __INI_H__ */
