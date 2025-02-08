#ifndef __INI_H__
#define __INI_H__

#define MAX_LINE 256

typedef int (*ini_handler)(void *userdata, const char *section, const char *key, const char *value);

void parse_ini(const char *filename, ini_handler callback, void *userdata);

#endif /* __INI_H__ */
