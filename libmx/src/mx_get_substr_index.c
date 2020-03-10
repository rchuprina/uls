#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub)
{
    if (!str || !sub)
        return -2;
    int i = 0;
    int j = 0;

    while (str[i])
    {
        j = 0;

        if (str[i] == *sub)
        {
            while (str[i + j] == sub[j] && str[i + j])
                j++;
            if (!sub[j])
                return i;
        }
        i += j;
        i++;
    }
    return -1;
}

