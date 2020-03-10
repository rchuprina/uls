#include "uls.h"

void mx_uls(int argc, char **argv, t_flags *flags)
{
    t_arg **arg = create_arg(&argc, argv, flags);
    mx_list_dir(argc, arg, flags);
}

int main(int argc, char **argv)
{
    char *root = mx_strdup(".");
    int start = 1;
    t_flags *flags = mx_flags_constructor();
    t_arg **arg = NULL;

    if (argc > 1 && argv[1][0] == '-') {
        mx_set_flags(flags, argv[start]);
        argc--;
        start++;
    }
    if (argc == 1)
    {
        arg = create_arg(&argc, &root, flags);
        mx_list_dir(argc, arg, flags);
    }
    else
    {
        argc--;
        mx_uls(argc, &argv[start], flags);
    }
    if (flags->ex)
        exit(1);
}
