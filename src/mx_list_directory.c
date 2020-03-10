#include "uls.h"

static int count_dir(int count, char **files)
{
    int dirs = 0;

    for (int i = 0; i < count; i++)
    {
        if (mx_get_type(files[i]) == 100)
            dirs++;
    }
    return dirs;
}

static char **dnames(int count, char **files, int dirs, char *root)
{
    char **names = (char **)malloc((dirs) * sizeof(char *));

    for (int i = 0; i < count; i++)
    {
        if (mx_get_type(files[i]) == 100)
        {
            dirs--;
            names[dirs] = mx_strjoin(root, files[i]);
        }
    }
    free(root);
    return names;
}

void mx_list_dir(int count, t_arg **arg, t_flags *flags)
{
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
                    int dirs = count_dir(arg[i]->size, arg[i]->files);
                    if (dirs > 0)
                    {
                        char **na = dnames(arg[i]->size, arg[i]->files, dirs, mx_strjoin(arg[i]->path, "/"));
                        mx_uls(dirs, na, flags);
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
