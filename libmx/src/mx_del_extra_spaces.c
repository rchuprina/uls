#include "libmx.h"

static int get_extra_len(const char *str)
{
    int len = 0;

    while (*str)
    {
        if (mx_is_space(*str))
            while (mx_is_space(*str))
                str++;
        else
            str++;
        len++;
    }
    return len;
}

char *mx_del_extra_spaces(const char *str)
{
    int len = 0;
    char *s = NULL;
    char *buf = NULL;

    if (!str)
        return NULL;
    buf = mx_strtrim(str);
    len = get_extra_len(buf); 
    s = mx_strnew(len);
    for (int i = 0, j = 0; i < len; i++)
    {
        if (mx_is_space(buf[i + j]))
        {
            s[i] = ' ';
            while (mx_is_space(buf[i + j + 1]))
                j++;
        }
        else
            s[i] = buf[i + j];
    }
    mx_strdel(&buf);
    return s;
}

