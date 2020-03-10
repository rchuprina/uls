#include "libmx.h"

void mx_str_reverse(char *s)
{
    if (!s)
        return;
    int len = mx_strlen(s);
    int mid = len /2;

    for (int i = 0; i < mid; i++)
        mx_swap_char(&s[i], &s[len - i - 1]);
}
