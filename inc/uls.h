#ifndef ULS_H
#define ULS_H

#include "libmx.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>

typedef struct s_arg{
    int type;
    int size;
    char *path;
    char **files;
}t_arg;

typedef struct s_flags {
    bool ex;
    bool recursion;
    bool (*order)(int cmp);
    void (*print_ls)(t_arg *arg, struct s_flags *flags);
}t_flags;

void mx_delstrarr(char ***arr, int size);
void mx_del_arg(t_arg **arg, int size);
void mx_uls(int argc, char **argv, t_flags *flags);
bool mx_standart_order(int cmp);
bool mx_reverse_order(int cmp);
t_flags *mx_flags_constructor();
void mx_set_flags(t_flags *flags, char *arg);
void mx_bsort(char **arr, int size, bool (*order)(int cmp));

void mx_bsort(char **arr, int size, bool (*order)(int cmp));
t_arg **create_arg(int *size, char **argv, t_flags *flags);
//general
int mx_get_size(char *str);
int mx_get_maxlen(char **names, int size);
char *mx_get_fullname(char *name, char *dir);
char **mx_get_names(char *str, int size);
char *mx_get_link(char *path);

//errors
int mx_get_type(char *name);
void mx_print_error(int error, char *str);

//list dir
void mx_list_dir(int count, t_arg **arg, t_flags *flags);

//ls
void mx_ls(t_arg *arg, t_flags *flags);


//long form
void mx_long_format(t_arg *arg, t_flags *flags);

#endif
