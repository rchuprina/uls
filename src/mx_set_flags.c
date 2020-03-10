#include "uls.h"

void mx_set_flags(t_flags *flags, char *arg)
{
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
            mx_print_error(0, &arg[i]);
            exit(0);
            break;
        }
    }
}
