#include "uls.h"

static char *getUsername(uid_t st_uid)
{
    struct passwd *pws;

    pws = getpwuid(st_uid);
    if (pws != NULL)
        return mx_strdup(pws->pw_name);
    return mx_itoa(st_uid);
}

static char *getGroupname(gid_t st_gid)
{
    struct group *grp;

    grp = getgrgid(st_gid);
    if (grp != NULL)
        return mx_strdup(grp->gr_name);
    return mx_itoa(st_gid);  
}

static char get_acl(char *file) {
	char character;
	ssize_t xattr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
	acl_t acl = acl_get_file(file, ACL_TYPE_EXTENDED);

    if (xattr > 0)
        character = '@';
    else if (acl == NULL)
        character = ' ';
    else
        character = '+';
	acl_free(acl);
    return character;
}

static char *get_mode(mode_t st_mode, char *file)
{
    char *mode = mx_strnew(11);

    mode[0] =   S_ISBLK(st_mode)   ? 'b' : \
                S_ISCHR(st_mode)   ? 'c' : \
                S_ISDIR(st_mode)   ? 'd' : \
                S_ISLNK(st_mode)   ? 'l' : \
                S_ISSOCK(st_mode)  ? 's' :
                S_ISFIFO(st_mode)  ? 'p' : '-';
    mode[1] = st_mode & S_IRUSR ? 'r' : '-';
    mode[2] = st_mode & S_IWUSR ? 'w' : '-';
    mode[3] = st_mode & S_IXUSR ? 'x' : '-';
    mode[4] = st_mode & S_IRGRP ? 'r' : '-';
    mode[5] = st_mode & S_IWGRP ? 'w' : '-';
    mode[6] = st_mode & S_IXGRP ? 'x' : '-';
    mode[7] = st_mode & S_IROTH ? 'r' : '-';
    mode[8] = st_mode & S_IWOTH ? 'w' : '-';
    mode[9] = st_mode & S_IXOTH ? 'x' : '-';
    mode[10] = get_acl(file);
    return mode;
}

static char *get_spaces(int len)
{
    if (len > 2)
        return NULL;
    if (len == 2)
        return mx_strdup(" ");
    return mx_strdup("  ");
}

static char *get_minor(int minornum) {
    char *minor =NULL;
    char *tmp = NULL;

    if (minornum > 127) {
        minor = mx_strnew(10);
        mx_strcpy(minor, "0x00000000");
        tmp = mx_nbr_to_hex(minornum);
        mx_strcpy(minor + (10 - mx_strlen(tmp)), tmp);
        free(tmp);
    }
    else
        minor = mx_itoa(minornum);
    return minor;
}

static void join_free(char **s1, char *s2)
{
    char *buf = mx_strjoin(*s1, s2);

    free(*s1);
    free(s2);
    *s1 = buf;
}

static char *major_minor(dev_t st_rdev) {
    //int tmp = (st_rdev & 0xffffff);
    char *major = mx_itoa((st_rdev >> 24) & 0xffffff); 
    char *minor = get_minor(st_rdev & 0xffffff);
    char *mm = get_spaces(mx_strlen(major));

    join_free(&mm, major);
    join_free(&mm, mx_strdup(", "));
    join_free(&mm, get_spaces(mx_strlen(minor)));
    join_free(&mm, minor);
    return mm;
}

static char* get_date(struct stat buf)
{
    time_t t = time(NULL);
    char *buf1 = NULL;
    char *buf2 = NULL;
    char *buf3 = NULL;

    if (t - buf.st_ctime >= 15768000)
    {
        buf1 = mx_strndup(&(ctime(&buf.st_ctime)[4]), 7);
        buf2 = mx_strndup(&(ctime(&buf.st_ctime)[19]), 5);
        buf3 = mx_strjoin(buf1, buf2);
        free(buf1);
        free(buf2);
        return buf3;
    }
    return mx_strndup(&(ctime(&buf.st_ctime)[4]), 12);
    //return mx_strndup(ctime(&buf.st_ctime), 24);
}

static char ***get_long_format(t_arg *arg, int *total, bool *special)
{
    struct stat buf;
    char *fullname = NULL;
    char ***l = (char ***)malloc(7 * sizeof(char **));

    for (int i = 0; i < 7; i++)
        l[i] = (char **)malloc(arg->size * sizeof(char *));
    for (int i = 0; i < arg->size; i++)
    {
        fullname = mx_get_fullname(arg->path, arg->files[i]);
        lstat(fullname, &buf); //lstat
        l[0][i] = get_mode(buf.st_mode, fullname);
        l[1][i] = mx_itoa(buf.st_nlink);
        l[2][i] = getUsername(buf.st_uid);
        l[3][i] = getGroupname(buf.st_gid);
        if (*l[0][i] == 'c' || *l[0][i] == 'b')
        {
            *special = true;
            l[4][i] = major_minor(buf.st_rdev);
        }
        else
            l[4][i] = mx_itoa(buf.st_size);
        l[5][i] = get_date(buf);
        l[6][i] = mx_strdup(arg->files[i]);
        mx_strdel(&fullname);
        *total += buf.st_blocks;
    }
    return l;
}

static int *get_maxlens(char ***long_form, int size, bool special)
{
    int *maxlens = (int *)malloc(7 * sizeof(int));

    for (int i = 0; i < 7; i++)
    {
        if ((i > 0 && i < 4) || i == 5 || (i == 4 && !special))
            maxlens[i] = mx_get_maxlen(long_form[i], size);
        else
            maxlens[i] = 0;
    }
    return maxlens;
}

void mx_printspaces(int count)
{
    for (int i = 0; i < count; i++)
        mx_printchar(' ');
}

void mx_del_long_format(char ***long_form, int size)
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < size; j++)
            free(long_form[i][j]);
        free(long_form[i]);
    }
    free(long_form);
}

void mx_long_format(t_arg *arg, t_flags *flags)
{
    mx_bsort(arg->files, arg->size, flags->order);
    int total = 0;
    bool special = false;
    char ***long_form = get_long_format(arg, &total, &special);
    int *maxlens = get_maxlens(long_form, arg->size, special);

    if (arg->type == 100)
    {
        mx_printstr("total ");
        mx_printint(total);
        mx_printchar('\n');
    }
    for (int i = 0; i < arg->size; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (j == 1 || (j == 4 && !special))
                mx_printspaces(maxlens[j] - mx_strlen(long_form[j][i]));
            if (j == 4 && special && *long_form[0][i] != 'c' &&
                *long_form[0][i] != 'b')
                mx_printspaces(8 - mx_strlen(long_form[j][i]));
            mx_printstr(long_form[j][i]);
            if (j == 6 && *long_form[0][i] == 'l')
            {
                mx_printstr(" -> ");
                char *link = mx_get_link(long_form[6][i]);
                mx_printstr(link);
                free(link);
            }
            if (j == 2 || j == 3)
                mx_printspaces(maxlens[j] - mx_strlen(long_form[j][i]) + 1);
            if (j < 6)
                mx_printchar(' ');
        }
        mx_printstr("\n");
    }
    free(maxlens);
    mx_del_long_format(long_form, arg->size);
}
