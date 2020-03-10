#include "uls.h"

void type_sort(int size, t_arg **arg, t_flags *flags)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arg[i]->type > arg[j]->type)
                mx_swap_void((void **)(&arg[i]),(void **)(&arg[j]));
            if (arg[i]->type == arg[j]->type)
            {
                if (flags->order(mx_strcmp(arg[i]->path, arg[j]->path)))
                    mx_swap_void((void **)(&arg[i]),(void **)(&arg[j]));
            }
        }
    }
}

static int count_files(int size, char **argv)
{
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (mx_get_type(argv[i]) == ENOTDIR)
        {
            count++;
        }
    }
    return count;
}

static int auditor(int x)
{
    if (x == 1)
        x = 0;
    else if (x > 1)
        x--;
    return x;
}

t_arg *create_enotdir_arg(int size, char **argv, int files)
{
    t_arg *enotd = (t_arg *)malloc(sizeof(t_arg));

    enotd->type = ENOTDIR;
    enotd->path = mx_strdup(".");
    enotd->size = files;
    enotd->files = (char **)malloc(files * sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        if (mx_get_type(argv[i]) == ENOTDIR)
        {
            files--;
            enotd->files[files] = mx_strdup(argv[i]);
        }
    }
    return enotd;
}

t_arg **create_arg(int *size, char **argv, t_flags *flags)
{
    int files = count_files(*size, argv);
    int count = *size - auditor(files);
    t_arg **arg = (t_arg **)malloc(count * sizeof(t_arg *));

    if (files > 0)
    {
        count--;
        arg[count] = create_enotdir_arg(*size, argv, files);
    }
    for (int i = 0; i < *size; i++)
    {
        if (mx_get_type(argv[i]) != ENOTDIR)
        {
            count--;
            arg[count] = (t_arg *)malloc(sizeof(t_arg));
            arg[count]->type = mx_get_type(argv[i]);
            if (arg[count]->type == 100)
            {
                arg[count]->size = mx_get_size(argv[i]);
                arg[count]->path = mx_strdup(argv[i]);
                arg[count]->files = mx_get_names(argv[i], arg[count]->size);
            }
            else
            {
                if (mx_get_type(argv[i]) == ENOENT)
                    flags->ex = true;
                arg[count]->path = mx_strdup(argv[i]);
                arg[count]->size = 1;
                arg[count]->files = (char **)malloc(sizeof(char *));
                *(arg[count]->files) = mx_strdup(argv[i]);
            }
        }
    }
    *size -= auditor(files);
    //*size -= 1; //delete this
    type_sort(*size, arg, flags);
    return arg;
}
