#include "libmx.h"

static int mx_len(const char *s)
{
	if (!s)
		return 0;
    return mx_strlen(s);
}

char *mx_strjoin(const char *s1, const char *s2)
{
    if (!s1 && !s2)
        return NULL;
    char *str = mx_strnew(mx_len(s1) + mx_len(s2));

    mx_strcat(str, s1);
    mx_strcat(str, s2);
    return str;
}

