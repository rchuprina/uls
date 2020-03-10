#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace)
{
    if (!str || !sub || !replace)
        return NULL;
    int subcount = mx_count_substr(str, sub);
    int len = mx_strlen(str) - mx_strlen(sub) * subcount + mx_strlen(replace) * subcount;
    char *s = mx_strnew(len);
    char *sbegin = s;
    char *strstr = mx_strstr(str, sub);

    while (*str)
    {
        if (strstr && str == strstr)
        {
            for (int i = 0; sub[i]; i++)
                str++;
            for (int i = 0; replace[i]; i++)
            {
                *s = replace[i];
                s++;
            }
            strstr = mx_strstr(str, sub);
        }
        *s = *str;
        s++;
        str++;
    }
    return sbegin;
}

