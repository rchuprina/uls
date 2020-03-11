#include "uls.h"

void mx_set_flags(t_flags *flags, char *arg)
{
    char *err = NULL;

    for (int i = 1; arg[i]; i++)
    {
        switch (arg[i])
        {
        case 'l':
            flags->print_ls = mx_long_format;
            break;
        case 'r':
            flags->order = mx_reverse_order;
            break;
        case 'R':
            flags->recursion = true;
            break;
        default:
            err = mx_strndup(&arg[i], 1);
            mx_print_error(0, err);
            free(err);
            free(flags);
            exit(0);
            break;
        }
    }
}
