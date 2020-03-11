#include "uls.h"

static void print_ls(char **names, int size, int cols, int tabs)
{
    int lines = size / cols + (size % cols ? 1 : 0);

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; i + lines * j < size; j++) 
        {
            int d = i + lines * j;
            mx_printstr(names[d]);
            if (i + lines * (j + 1) < size)
                for (int t = mx_strlen(names[d]); t < tabs; t += 8)
                    mx_printchar('\t');
        }
        mx_printchar('\n');
    }
}

void mx_ls(t_arg *arg, t_flags *flags)
{
    struct winsize sz;
    int tab = 8;
    int cols = 1;
    int maxlen = mx_get_maxlen(arg->files, arg->size);
    char *link = NULL;

    if (arg->type == 20)
    {
        for (int i = 0; i < arg->size; i++)
        {
            link = mx_get_link(arg->path, arg->files[0]);
            if (mx_get_type(link) == 100)
            {
                t_arg ** buf = create_arg(&cols, arg->files, flags); //bug will be here
                mx_ls(*buf, flags);
                mx_del_arg(buf, 1);
                return;
            }
            free(link);
        }
    }
    ioctl(0, TIOCGWINSZ, &sz);
    mx_bsort(arg->files, arg->size, flags->order);
    //mx_bubble_sort(arg->files, arg->size);
    for (; tab <= maxlen; tab += 8);
    for (; cols <= arg->size && (cols + 1) * tab <= sz.ws_col; cols++);
    print_ls(arg->files, arg->size, cols, tab);
}

