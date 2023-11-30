#include "../inc/uls.h"

void name_colors_print(t_fileinfo file) {
    switch(file.st.st_mode & S_IFMT) {
        case S_IFSOCK:
            mx_printstr(SOC_COLOR);
            break;
        case S_IFLNK:
            mx_printstr(LNK_COLOR);
            break;
        case S_IFBLK:
            mx_printstr(BLK_COLOR);
            break;
        case S_IFDIR:
            if(file.st.st_mode & S_IWOTH){
                if(file.st.st_mode & S_ISVTX){
                    mx_printstr(DIR_STK_COLOR);
                }
                else{
                    mx_printstr(DIR_NTK_COLOR);
                }
            }
            else {
                mx_printstr(DIR_COLOR);
            }
            break;
        case S_IFCHR:
            mx_printstr(CHR_COLOR);
            break;
        case S_IFIFO:
            mx_printstr(PIP_COLOR);
            break;
        default:
            if(file.st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
                if(file.st.st_mode & S_ISUID){
                    mx_printstr(EXE_UID_COLOR);
                }
                else if(file.st.st_mode & S_ISGID){
                    mx_printstr(EXE_GID_COLOR);
                }
                else {       
                    mx_printstr(EXE_COLOR);
                }
            }
            break;
    }
    mx_printstr(file.name);
    mx_printstr(NON_COLOR);
}

void link_print(const char *path){
    char buff[PATH_MAX];
    ssize_t len = readlink(path, buff, sizeof(buff) - 1);

    if(len != -1){
        buff[len] = '\0';
        mx_printstr(" -> ");
        mx_printstr(buff);
    }
}

void err_print(const char* filename) {
    mx_printerr("uls: ");
    mx_printerr(filename);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
}

