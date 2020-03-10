#include "libmx.h"

char **mx_strarrnew(int size)
{
	char **sarr = (char **)malloc((size + 1) * sizeof(char *));

	for (int i = 0; i <= size; i++)
		sarr[i] = NULL;
	return sarr;
}

char **mx_strsplit(const char *s, char c)
{
    if (!s)
        return NULL;
    int size = mx_count_words(s, c);
    char **arr = mx_strarrnew(size);
    int len = 0;

    for (int i = 0; i < size; i++)
    {
        len = 0;
        while (s[len] == c)
            s++;
        while (s[len] != c && s[len])
            len++;
        arr[i] = mx_strndup(s, len);
        for (int j = 0; j < len; j++)
            s++;
    }
    return arr;
}

