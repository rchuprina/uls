#include "uls.h"

t_flags *mx_flags_constructor()
{
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));

    flags->ex = false;
    flags->recursion = false;
    flags->order = mx_standart_order;
    flags->print_ls = mx_ls;
    return flags;
}
