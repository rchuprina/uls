#include "libmx.h"

int mx_count_words(const char *str, char c)
{
    int i = 0;

    if (!str)
        return -1;
    while (*str)
    {
        if (*str != c)
        {
            i++;
            while (*str != c)
            {
                if (!(*str))
                    return i;
                str++;
            }
        }
        str++;
    }
    return i;
}

