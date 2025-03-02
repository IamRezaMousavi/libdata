#include "argparser.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void argparse_error(struct argparse *self, const struct argparse_option *opt, const char *reason) {
    (void)self;
    fprintf(stderr, "error: option %s %s\n", opt->long_name, reason);
    exit(EXIT_FAILURE);
}

static int argparse_getvalue(struct argparse *self, const struct argparse_option *opt) {
    if (!opt->value)
        goto skipped;

    const char *s = NULL;

    switch (opt->type) {
        case ARGPARSE_OPT_BOOLEAN:
            *(int *)opt->value = 1;
            break;
        case ARGPARSE_OPT_BIT:
            *(int *)opt->value |= opt->data;
            break;
        case ARGPARSE_OPT_STRING:
            if (self->optvalue) {
                *(const char **)opt->value = self->optvalue;
                self->optvalue             = NULL;
                self->argv++;
                self->argc--;
            } else {
                argparse_error(self, opt, "requires a value");
            }
            break;
        case ARGPARSE_OPT_INTEGER:
            errno = 0;
            if (self->optvalue) {
                *(int *)opt->value = strtol(self->optvalue, (char **)&s, 0);
                self->optvalue     = NULL;
                self->argv++;
                self->argc--;
            } else {
                argparse_error(self, opt, "requires a value");
            }
            if (errno == ERANGE)
                argparse_error(self, opt, "numerical result out of range");
            if (s[0] != '\0') // no digits or contains invalid characters
                argparse_error(self, opt, "expects an integer value");
            break;
        case ARGPARSE_OPT_FLOAT:
            errno = 0;
            if (self->optvalue) {
                *(float *)opt->value = strtof(self->optvalue, (char **)&s);
                self->optvalue       = NULL;
                self->argv++;
                self->argc--;
            } else {
                argparse_error(self, opt, "requires a value");
            }
            if (errno == ERANGE)
                argparse_error(self, opt, "numerical result out of range");
            if (s[0] != '\0') // no digits or contains invalid characters
                argparse_error(self, opt, "expects a numerical value");
            break;
        default:
            assert(0);
    }

skipped:
    if (opt->callback) {
        return opt->callback(self, opt);
    }
    return 0;
}

static int argparse_short_opt(struct argparse *self, const struct argparse_option *options) {
    for (; options->type != ARGPARSE_OPT_END; options++) {
        if (options->short_name && self->argv[0][1] == options->short_name) {
            return argparse_getvalue(self, options);
        }
    }
    return -2;
}

static int argparse_long_opt(struct argparse *self, const struct argparse_option *options) {
    for (; options->type != ARGPARSE_OPT_END; options++) {
        if (!options->long_name)
            continue;

        if (strcmp(self->argv[0] + 2, options->long_name) == 0)
            return argparse_getvalue(self, options);
    }
    return -2;
}

int argparse_init(struct argparse *self, struct argparse_option *options) {
    memset(self, 0, sizeof(*self));
    self->options     = options;
    self->description = NULL;
    self->epilog      = NULL;
    return 0;
}

void argparse_describe(struct argparse *self, const char *description, const char *epilog) {
    self->description = description;
    self->epilog      = epilog;
}

void argparse_parse(struct argparse *self, int argc, const char **argv) {
    self->argc = argc - 1;
    self->argv = argv + 1;

    for (; self->argc; self->argc--, self->argv++) {
        const char *arg = self->argv[0];
        if (arg[0] != '-' && !arg[1]) {
            /* option value */
            continue;
        }
        if (arg[1] != '-') {
            /* short option */
            if (self->argc > 1)
                self->optvalue = self->argv[1];
            switch (argparse_short_opt(self, self->options)) {
                case -1:
                    break;
                case -2:
                    goto unknown;
            }
            continue;
        }
        if (!arg[2]) {
            /* '--' presents */
            self->argc--;
            self->argv++;
            break;
        }
        /* long option */
        if (self->argc > 1)
            self->optvalue = self->argv[1];
        switch (argparse_long_opt(self, self->options)) {
            case -1:
                break;
            case -2:
                goto unknown;
        }
        continue;
unknown:
        fprintf(stderr, "error: unknown option `%s`\n", self->argv[0]);
        argparse_usage(self);
        exit(EXIT_FAILURE);
    }
}

void argparse_usage(struct argparse *self) {
    fprintf(stdout, "Usage:\n");

    if (self->description)
        fprintf(stdout, "%s\n", self->description);

    fputc('\n', stdout);

    const struct argparse_option *options;

    // figure out best width
    size_t usage_opts_width = 0;
    size_t len;
    options = self->options;
    for (; options->type != ARGPARSE_OPT_END; options++) {
        len = 0;
        if ((options)->short_name) {
            len += 2;
        }
        if ((options)->short_name && (options)->long_name) {
            len += 2; // separator ", "
        }
        if ((options)->long_name) {
            len += strlen((options)->long_name) + 2;
        }
        if (options->type == ARGPARSE_OPT_INTEGER) {
            len += strlen(" <int>");
        }
        if (options->type == ARGPARSE_OPT_FLOAT) {
            len += strlen(" <flt>");
        } else if (options->type == ARGPARSE_OPT_STRING) {
            len += strlen(" <str>");
        }
        len = (len + 3) - ((len + 3) & 3);
        if (usage_opts_width < len) {
            usage_opts_width = len;
        }
    }
    usage_opts_width += 4; // 4 spaces prefix

    options = self->options;
    for (; options->type != ARGPARSE_OPT_END; options++) {
        size_t pos = 0;
        size_t pad = 0;
        if (options->type == ARGPARSE_OPT_GROUP) {
            fputc('\n', stdout);
            fprintf(stdout, "%s", options->help);
            fputc('\n', stdout);
            continue;
        }
        pos = fprintf(stdout, "    ");
        if (options->short_name) {
            pos += fprintf(stdout, "-%c", options->short_name);
        }
        if (options->long_name && options->short_name) {
            pos += fprintf(stdout, ", ");
        }
        if (options->long_name) {
            pos += fprintf(stdout, "--%s", options->long_name);
        }
        if (options->type == ARGPARSE_OPT_INTEGER) {
            pos += fprintf(stdout, " <int>");
        } else if (options->type == ARGPARSE_OPT_FLOAT) {
            pos += fprintf(stdout, " <flt>");
        } else if (options->type == ARGPARSE_OPT_STRING) {
            pos += fprintf(stdout, " <str>");
        }
        if (pos <= usage_opts_width) {
            pad = usage_opts_width - pos;
        } else {
            fputc('\n', stdout);
            pad = usage_opts_width;
        }
        fprintf(stdout, "%*s%s\n", (int)pad + 2, "", options->help);
    }

    // print epilog
    if (self->epilog)
        fprintf(stdout, "%s\n", self->epilog);
}

int argparse_help_cb(struct argparse *self, const struct argparse_option *option) {
    (void)option;
    argparse_usage(self);
    exit(EXIT_SUCCESS);
}
