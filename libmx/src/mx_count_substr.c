#include "libmx.h"

int mx_count_substr(const char *str, const char *sub)
{
    int i = 0;

    if (!str || !sub)
        return -1;
    while (str)
    {
        str = mx_strstr(str, sub);
        if (str)
        {
            i++;
            str++;
        }
    }
    return i;
}

