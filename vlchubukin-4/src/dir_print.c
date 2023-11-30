#include "../inc/uls.h"

void dir_print(char* name, unsigned short flags, int* exit_stts, bool print_name) {
    if(print_name) {
        mx_printstr(name);
        mx_printstr(":\n");
    }
    DIR* dir = opendir(name);
    if(dir == NULL){
        err_print(name);
        *exit_stts = 1;
    }
    else {
        int size = dir_sz(name, flags);
        struct s_fileinfo *files = (t_fileinfo*)malloc(size * sizeof(t_fileinfo));
        
        int i = 0;
        struct dirent *entry = NULL;
        while( (entry = readdir(dir)) != NULL ) {
            if(mx_strcmp(entry->d_name, ".") == 0 || mx_strcmp(entry->d_name, "..") == 0) {
                if(!(flags & FLAG_a)) {
                    continue;
                }
            } 
            else if(entry->d_name[0] == '.') {
                if(!(flags & (FLAG_a | FLAG_A))) {
                    continue;
                }
            }
            files[i].path = dirs_concat(name, entry->d_name);
            files[i].name = mx_strdup(entry->d_name);
            int res = lstat(files[i].path, &files[i].st);
            if(res == -1){
                err_print(files[i].name);
                *exit_stts = 1;
            }
            i++;
        }
        files_sort(files, size, flags);
        
        files_print(files, size, flags, size > 0);

        if(flags & FLAG_R) {
            for(int i = 0; i < size; i++) {
                if(mx_strcmp(files[i].name, ".") != 0 && mx_strcmp(files[i].name, "..") != 0) {
                    char *path = dirs_concat(name, files[i].name);
                    struct stat st;
                    int res = lstat(path, &st);

                    if(res != -1){
                        if((st.st_mode & S_IFMT) == S_IFDIR) {
                            mx_printchar('\n');
                            dir_print(path, flags, exit_stts, true);
                        }
                    }

                    free(path);
                }
            }
        }

        free_file_into_array(files, size);
        closedir(dir);
    }
}

void xattr_print(const char *path) {
    ssize_t len_of_atribute = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    char* xattr_list = malloc(len_of_atribute);
    ssize_t xattr = listxattr(path, xattr_list, len_of_atribute, XATTR_NOFOLLOW);

    if(xattr > 0) {
        for(char *list = xattr_list; list < xattr_list + xattr; list += mx_strlen(list) + 1){
            int len = getxattr(path, list, NULL, 0, 0, XATTR_NOFOLLOW);
            mx_printchar('\t'); 
            mx_printstr(list);
            mx_printstr("\t   ");
            mx_printint(len);
            mx_printchar('\n');
        }
    }
}

void mx_printnchar(char c, int n) {
    for(int i = 0; i < n; i++) {
        mx_printchar(c);
    }
}
