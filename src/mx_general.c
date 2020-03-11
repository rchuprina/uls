#include "uls.h"

char *mx_get_fullname(char *dir, char *file)
{
    char *buf = NULL;
    char *buf2 = NULL;

    if (!mx_memcmp(dir, ".\0", 2))
        return mx_strdup(file);
    else
    {
        if (dir[mx_strlen(dir) - 1] != '/')
        {
            if (dir[1] == '/')
                buf = mx_strjoin(&dir[2], "/");
            else
                buf = mx_strjoin(dir, "/");
            buf2 = mx_strjoin(buf, file);
            free(buf);
            return buf2;
        }
        else
        {
            if (dir[1] == '/')
                return mx_strjoin(&dir[2], file);
            else
                return mx_strjoin(dir, file);
        }
    }
}

char *mx_get_link(char *path, char *file)
{
    char link[255];
    int size = 0;
    char *buf = mx_get_fullname(path, file);

    size = readlink(buf, link, sizeof(link) - 1);
    link[size] = '\0';
    free(buf);
    return mx_strdup(link);
}

int mx_get_size(char *str)
{
    struct dirent *entry = NULL;
    DIR *dir = opendir(str);
    int size = 0;

    while ((entry = readdir(dir)) != NULL)
        if (entry->d_name[0] != '.')
            size++;
    closedir(dir);
    return size;
}

int mx_get_maxlen(char **names, int size)
{
    int maxlen = 0;

    for (int i = 0; i < size; i++)
        if (maxlen < mx_strlen(names[i]))
            maxlen = mx_strlen(names[i]);
    return maxlen;
}

char **mx_get_names(char *str, int size)
{
    char **names =  (char **)malloc(size *sizeof(char *));
    struct dirent *entry = NULL;
    DIR *dir = opendir(str);

    for (int i = 0; (entry = readdir(dir)) != NULL;)
    {
        if (entry->d_name[0] != '.')
        {
            names[i] = mx_strdup(entry->d_name);
            i++;
        }
    }
    closedir(dir);
    return names;
}

