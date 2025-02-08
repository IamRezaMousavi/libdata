#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ini.h"

typedef struct configuration {
    int         version;
    const char *name;
    const char *email;
} configuration;

int handler(void *userdata, const char *section, const char *key, const char *value) {
    configuration *config = (configuration *)userdata;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(key, n) == 0
    if (MATCH("", "version")) {
        config->version = atoi(value);
    } else if (MATCH("user", "name")) {
        config->name = strdup(value);
    } else if (MATCH("user", "email")) {
        config->email = strdup(value);
    }
}

int main(int argc, const char *argv[]) {
    configuration config;

    parse_ini("config.ini", handler, &config);

    printf(
        "Config loaded from 'config.ini': "
        "version=%d, name=%s, email=%s\n",
        config.version, config.name, config.email
    );

    return 0;
}
