#include "uls.h"

static int count_dir(t_arg *arg)
{
    int dirs = 0;
    struct stat buf;
    char *fullname = NULL;

    for (int i = 0; i < arg->size; i++)
    {
        fullname = mx_get_fullname(arg->path, arg->files[i]);
        lstat(fullname, &buf);
        free(fullname);
        if (S_ISDIR(buf.st_mode))
            dirs++;
    }
    return dirs;
}

static char **dnames(t_arg *arg, int dirs)
{
    char **names = (char **)malloc((dirs) * sizeof(char *));
    char *root = mx_strjoin(arg->path, "/");
    struct stat buf;
    char *fullname = NULL;

    for (int i = 0; i < arg->size; i++)
    {
        fullname = mx_get_fullname(arg->path, arg->files[i]);
        lstat(fullname, &buf);
        free(fullname);
        if (S_ISDIR(buf.st_mode))
        {
            dirs--;
            names[dirs] = mx_strjoin(root, arg->files[i]);
        }
    }
    free(root);
    return names;
}

void mx_list_dir(int count, t_arg **arg, t_flags *flags)
{
    char **names = NULL;
    int dirs = 0;

    for (int i = 0; i < count; i++)
    {
        if (arg[i]->type == ENOENT)
            mx_print_error(ENOENT, arg[i]->files[0]);
        else if (arg[i]->type == ENOTDIR)
        {
            flags->print_ls(arg[i], flags);
            if (i < count - 1 && arg[i + 1]->type != ENOTDIR)
                mx_printchar('\n');
        }
        else
        {
            if (count > 1)
            {
                mx_printstr(arg[i]->path);
                mx_printstr(":\n");
            }
            if (arg[i]->type == 100)
            {
                flags->print_ls(arg[i], flags);
                if (flags->recursion)
                {
                    dirs = count_dir(arg[i]);
                    if (dirs > 0)
                    {
                        mx_printchar('\n');
                        names = dnames(arg[i], dirs);
                        mx_uls(dirs, names, flags);
                        mx_delstrarr(names, dirs);
                    }
                }
            }
            else
                mx_print_error(26, arg[i]->files[0]);
            if (i < count - 1)
                mx_printchar('\n');
        }
    }
}
