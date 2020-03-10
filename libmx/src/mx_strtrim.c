#include "libmx.h"

bool mx_is_space(char c)
{
    if (c == '\t' || c == '\n' || c == '\v' ||
        c == '\f' || c == '\r' || c == ' ')
        return true;
    return false;
}

static int get_len(const char *str)
{
    int len = mx_strlen(str);

    while (mx_is_space(str[len - 1]) && *str)
        len--;
    return len;
}

char *mx_strtrim(const char *str)
{
    if (!str)
        return NULL;
    while (mx_is_space(*str))
        str++;
    return mx_strndup(str, get_len(str));
}

