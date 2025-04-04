#include <stdio.h>

#include <libdata/cli/argparser.h>

#define PERM_READ  (1 << 0)
#define PERM_WRITE (1 << 1)
#define PERM_EXEC  (1 << 2)

int main(int argc, const char *argv[]) {
    int   force   = 0;
    int   perms   = 0;
    int   int_num = 0;
    float flt_num = 0.f;
    char *path    = NULL;

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('f', "force", &force, "force to do", NULL, 0),
        OPT_STRING('p', "path", &path, "path to read", NULL, 0),
        OPT_INTEGER('i', "int", &int_num, "selected integer", NULL, 0),
        OPT_FLOAT('s', "float", &flt_num, "selected float", NULL, 0),
        OPT_GROUP("Bits options"),
        OPT_BIT(0, "read", &perms, "read perm", NULL, PERM_READ),
        OPT_BIT(0, "write", &perms, "write perm", NULL, PERM_WRITE),
        OPT_BIT(0, "exec", &perms, "exec perm", NULL, PERM_EXEC),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options);
    argparse_describe(
        &argparse,
        "\nA brief description of what the program does and how it works.",
        "\nAdditional description of the program after the description of the arguments."
    );
    argparse_parse(&argparse, argc, argv);

    printf("force: %d\n", force);
    printf("int_num: %d\n", int_num);
    printf("flt_num: %g\n", flt_num);
    printf("perms: %b\n", perms);
    if (path != NULL)
        printf("path: %s\n", path);
    return 0;
}
