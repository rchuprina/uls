#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2)
{
    int i = 0;
    int j = 0;

    if (!s2)
        return s1;
    while (s1[i])
        i++;
    while (s2[j])
    {
        s1[i + j] = s2[j];
        j++;
    }
    s1[i + j] = '\0';
    return s1;
}
