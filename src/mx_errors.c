#include "uls.h"

int mx_get_type(char *name)
{
    DIR *dir = opendir(name);
    
    if (!dir)
    {
        if (errno == EACCES)
            return 25;
        return errno;
    }
    closedir(dir);
    return 100;
}

void mx_print_error(int error, char *str)
{
    char *err = NULL;
    char *buf = NULL;

    if (!error)
        err = mx_replace_substr("uls: illegal option -- zzz\nusage: uls [-l] [file ...]\n", "zzz", str);
    if (error == ENOENT)
        err = mx_replace_substr("uls: xxx: No such file or directory\n", "xxx", str);
    if (error == 26)
    {
        buf = mx_memrchr(str, '/', mx_strlen(str));
        if (!buf)
            buf = str;
        else
            buf++;
        err = mx_replace_substr("uls: xxx: Permission denied\n", "xxx", buf);
    }
    write(2, err, mx_strlen(err));
    free(err);
    //system("leaks -q uls");
}
