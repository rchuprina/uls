#include "uls.h"

char *mx_get_fullname(char *dir, char *file)
{
    if (dir[0] != '.')
    {
        if (dir[mx_strlen(dir) - 1] != '/')
            return mx_strjoin(mx_strjoin(dir, "/"), file);
        else
            return mx_strjoin(dir, file);
    }
    else
        return file;
}

char *mx_get_link(char *path)
{
    char link[255];
    int size = 0;

    path++;
    //size = readlink(path, link, sizeof(link) - 1);
    link[size] = '\0';
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

