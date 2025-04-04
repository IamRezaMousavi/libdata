#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdata/fileparser/ini.h>

typedef struct configuration {
    int run;

    /* protocol */
    int version;

    /* user */
    char *name;
    char *email;
} configuration;

int handler(void *userdata, const char *section, const char *key, const char *value) {
    configuration *config = (configuration *)userdata;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(key, n) == 0
    if (MATCH("", "run")) {
        config->run = atoi(value);
    } else if (MATCH("protocol", "version")) {
        config->version = atoi(value);
    } else if (MATCH("user", "name")) {
        config->name = strdup(value);
    } else if (MATCH("user", "email")) {
        config->email = strdup(value);
    } else {
        return 0; /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, const char *argv[]) {
    /* Default config */
    configuration config = {.run = 1, .version = 4, .name = "Bob", .email = "b@b.com"};

    size_t ini_err = ini_parse("config.ini", handler, &config);
    if (ini_err < 0) {
        printf("Error: can't open config.ini\n");
        exit(EXIT_FAILURE);
    } else if (ini_err > 0) {
        printf("Error parse ini file: error in line %ld\n", ini_err);
        exit(EXIT_FAILURE);
    }

    printf(
        "Config loaded from 'config.ini':\n"
        "run=%d\n"
        "version=%d\n"
        "name=%s\n"
        "email=%s\n",
        config.run, config.version, config.name, config.email
    );

    if (config.name)
        free(config.name);
    if (config.email)
        free(config.email);

    return EXIT_SUCCESS;
}
