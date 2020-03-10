#include "libmx.h"

char *mx_strnew(const int size)
{
    char *s = (char *) malloc((size + 1) * sizeof(char));

    for (int i = 0; i <= size; i++)
        s[i] = '\0';
    return s;
}
