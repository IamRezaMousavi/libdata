#ifndef __ARGPARSER_H__
#define __ARGPARSER_H__

#include <stdint.h>

struct argparse;
struct argparse_option;

typedef int argparse_callback(struct argparse *self, const struct argparse_option *option);

enum opt_type_t {
    ARGPARSE_OPT_END,
    ARGPARSE_OPT_GROUP,

    ARGPARSE_OPT_BOOLEAN,
    ARGPARSE_OPT_BIT,

    ARGPARSE_OPT_INTEGER,
    ARGPARSE_OPT_FLOAT,
    ARGPARSE_OPT_STRING,
};

struct argparse_option {
    enum opt_type_t    type;
    const char         short_name;
    const char        *long_name;
    void              *value;
    const char        *help;
    argparse_callback *callback;
    intptr_t           data;
};

struct argparse {
    int                           argc;
    const char                  **argv;
    const struct argparse_option *options;

    const char *description; // a description after usage
    const char *epilog;      // a description at the end

    const char *optvalue; // current option value
};

int argparse_help_cb(struct argparse *self, const struct argparse_option *option);

#define OPT_END()        {ARGPARSE_OPT_END, 0, NULL, NULL, 0, NULL, 0}
#define OPT_BOOLEAN(...) {ARGPARSE_OPT_BOOLEAN, __VA_ARGS__}
#define OPT_BIT(...)     {ARGPARSE_OPT_BIT, __VA_ARGS__}
#define OPT_INTEGER(...) {ARGPARSE_OPT_INTEGER, __VA_ARGS__}
#define OPT_FLOAT(...)   {ARGPARSE_OPT_FLOAT, __VA_ARGS__}
#define OPT_STRING(...)  {ARGPARSE_OPT_STRING, __VA_ARGS__}
#define OPT_GROUP(name)  {ARGPARSE_OPT_GROUP, 0, NULL, NULL, name, NULL, 0}
#define OPT_HELP()       OPT_BOOLEAN('h', "help", NULL, "show this help message and exit", argparse_help_cb, 0)

int  argparse_init(struct argparse *self, struct argparse_option *options);
void argparse_describe(struct argparse *self, const char *description, const char *epilog);
void argparse_parse(struct argparse *self, int argc, const char **argv);
void argparse_usage(struct argparse *self);

#endif /* __ARGPARSER_H__ */
