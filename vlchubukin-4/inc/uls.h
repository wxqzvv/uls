#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"
#include "flags.h"
#include "color.h"

#include <string.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>
#include <sys/xattr.h>

typedef struct s_fileinfo {
    char *name;
    char *path;
    struct stat st; 
}              t_fileinfo;

DIR* open_dir(const char* name, int* exit_stts);
int dir_sz(char* path, unsigned short flags);
int maximum_name_len(t_fileinfo arr[], int size);
void mx_printnchar(char c, int n);
void dir_print(char* name, unsigned short flags, int* exit_stts, bool print_name);
void files_print(t_fileinfo files[], int size, unsigned short flags, bool is_total);
void files_sort(t_fileinfo files[], int size, unsigned short flags);
bool atime_cmp(t_fileinfo a, t_fileinfo b);
bool ctime_cmp(t_fileinfo a, t_fileinfo b);
bool mtime_compare(t_fileinfo a, t_fileinfo b);
bool name_compare(t_fileinfo a, t_fileinfo b);
bool sz_compare(t_fileinfo a, t_fileinfo b);
void lng_outp(t_fileinfo files[], int size, unsigned short flags, bool is_total);
char *dirs_concat(char* fst, char* scd);
int cols_count(int max, unsigned short flags);
void link_print(const char *path);
char getfile_type(mode_t mode);
char* get_permissions(t_fileinfo file);
int maximum_elem(char*** info, int size, int col);
void xattr_print(const char *path);
void name_colors_print(t_fileinfo file);
char* get_time(t_fileinfo file, unsigned short flags);
void err_print(const char* filename);
void free_file_into_array(t_fileinfo* arr, int size);

#endif
