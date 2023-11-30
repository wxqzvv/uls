#include "../inc/uls.h"

int main(int argc, char *argv[]) {  
    unsigned short flags = 0;
    int exit_stts = EXIT_SUCCESS;
    int files_counter = mx_check_flags(argc, argv, &flags);
    
    if(files_counter > 0) {
        int files_sz = 0;
        int dirs_sz = 0;

        for(int i = 1; i < argc; i++) {
            if(argv[i][0] != '-') {
                struct stat buf;
                int res = lstat(argv[i], &buf);
                if(res == -1) {
                    exit_stts = 1;
                    err_print(argv[i]);
                }
                else {
                    if((buf.st_mode & S_IFMT) == S_IFDIR) {
                        dirs_sz++;
                    }
                    else if((buf.st_mode & S_IFMT) == S_IFLNK) {
                        struct stat st;
                        stat(argv[i], &st);
                        
                        if((st.st_mode & S_IFMT) == S_IFDIR && !(flags & FLAG_l)) {
                            dirs_sz++;
                        }
                        else {
                            files_sz++;
                        }
                    }
                    else {
                        files_sz++;
                    }
                }
            }
        }
        
        t_fileinfo *files = (t_fileinfo*)malloc(files_sz * sizeof(t_fileinfo));
        t_fileinfo *dirs = (t_fileinfo*)malloc(dirs_sz * sizeof(t_fileinfo));

        int i = 0;
        int j = 0;
        for(int k = 1; k < argc; k++) {
            if(argv[k][0] != '-') {
                struct stat buf;
                int res = lstat(argv[k], &buf);
            
                if(res != -1) {
                    if((buf.st_mode & S_IFMT) == S_IFDIR) {
                        dirs[i].name = mx_strdup(argv[k]);
                        dirs[i].path = mx_strdup(argv[k]);
                        lstat(argv[k], &dirs[i].st);
                        i++;
                    }
                    else if((buf.st_mode & S_IFMT) == S_IFLNK) {
                        struct stat st;
                        stat(argv[k], &st);
                        
                        if((st.st_mode & S_IFMT) == S_IFDIR && !(flags & FLAG_l)) {
                            char link[PATH_MAX];
                            ssize_t len = readlink(argv[k], link, sizeof(link) - 1);

                            if(len != -1) {
                                link[len] = '\0';
                                dirs[i].name = mx_strdup(argv[k]);
                                dirs[i].path = mx_strdup(link);
                                stat(link, &dirs[i].st);
                                i++;
                            }
                        }
                        else {
                            files[j].name = mx_strdup(argv[k]);
                            files[j].path = mx_strdup(argv[k]);
                            lstat(argv[k], &files[j].st);
                            j++;
                        }
                    }
                    else {
                        files[j].name = mx_strdup(argv[k]);
                        files[j].path = mx_strdup(argv[k]);
                        lstat(argv[k], &files[j].st);
                        j++;
                    }
                }
            }
        }
        files_sort(files, files_sz, flags);
        files_sort(dirs, dirs_sz, flags);

        if(files_sz > 0){
            files_print(files, files_sz, flags, false);
        }
        for(int i = 0; i < dirs_sz; i++) {
            if( i != 0 || files_sz > 0){
                mx_printchar('\n');
            }
            dir_print(dirs[i].name, flags, &exit_stts, files_counter > 1);
        }

        free_file_into_array(dirs, dirs_sz);
        free_file_into_array(files, files_sz);
    }
    else {
        dir_print(".", flags, &exit_stts, false);
    }
    
    return exit_stts;
}

