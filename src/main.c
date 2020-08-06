#include "uls.h"

void mx_delstrarr(char **arr, int size)
{
    for (int j = 0; j < size; j++)
        free(arr[j]);
    free(arr);
}

void mx_del_arg(t_arg **arg, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(arg[i]->path);
        mx_delstrarr(arg[i]->files, arg[i]->size);
        free(arg[i]);
    }
    free(arg);
}

void mx_uls(int argc, char **argv, t_flags *flags)
{
    t_arg **arg = create_arg(&argc, argv, flags);
    mx_list_dir(argc, arg, flags);
    mx_del_arg(arg, argc);
}

void quit(char *root, t_flags *flags)
{
    free(root);
    if (flags->ex)
    {
        free(flags);
        //system("leaks -q uls");
        exit(1);
    }
    free(flags);
    //system("leaks -q uls");
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
        mx_del_arg(arg, 1);
    }
    else
    {
        argc--;
        mx_uls(argc, &argv[start], flags);
    }
    quit(root, flags);
}
