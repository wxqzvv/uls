#include "../inc/uls.h"

char* mx_get_size(t_fileinfo file) {
    if((file.st.st_mode & S_IFMT) == S_IFBLK || (file.st.st_mode & S_IFMT) == S_IFCHR) {
        if(file.st.st_rdev == 0) {
            return mx_itoa(file.st.st_rdev);
        }
        return mx_strjoin("0x", mx_nbr_to_hex(file.st.st_rdev));
    }

    return mx_itoa(file.st.st_size);
}

char* mx_get_usrname(t_fileinfo file) {
    struct passwd* pwd = getpwuid(file.st.st_uid);

    if(pwd == NULL) {
        return mx_itoa(file.st.st_uid);
    }
    
    return mx_strdup(pwd->pw_name);
}

char* mx_get_grpname(t_fileinfo file) {
    struct group* grp = getgrgid(file.st.st_gid);

    if(grp == NULL) {
        return mx_itoa(file.st.st_gid);
    }
    
    return mx_strdup(grp->gr_name);
}

void lng_outp(t_fileinfo files[], int size, unsigned short flags, bool is_total) {
    blkcnt_t total = 0;

    char*** info = (char***)malloc(size * sizeof(char**));
    for(int i = 0 ; i < size; i++) {
        info[i] = (char**)malloc(7 * sizeof(char*));
    }

    for(int i = 0 ; i < size; i++) {
        t_fileinfo file = files[i];
        
        info[i][0] = get_permissions(file);
        info[i][1] = mx_itoa(file.st.st_nlink);
        info[i][2] = mx_get_usrname(file);
        info[i][3] = mx_get_grpname(file);
        info[i][4] = mx_get_size(file);
        info[i][5] = get_time(file, flags);      
        info[i][6] = mx_strdup(file.name);
        total += file.st.st_blocks;
    }
    if(is_total) {
        mx_printstr("total ");
        mx_printlong(total);
        mx_printchar('\n');
    }

    for(int i = 0; i < size; i++) {
        mx_printstr(info[i][0]);
        mx_printnchar(' ', maximum_elem(info, size, 1) - mx_strlen(info[i][1]) + 1);

        mx_printstr(info[i][1]);
        mx_printchar(' ');

        mx_printstr(info[i][2]);
        mx_printnchar(' ', maximum_elem(info, size, 2) - mx_strlen(info[i][2]) + 2);

        mx_printstr(info[i][3]);
        mx_printnchar(' ', maximum_elem(info, size, 3) - mx_strlen(info[i][3]));
        mx_printnchar(' ', maximum_elem(info, size, 4) - mx_strlen(info[i][4]) + 2);

        mx_printstr(info[i][4]);
        mx_printnchar(' ', maximum_elem(info, size, 5) - mx_strlen(info[i][5]) + 1);

        mx_printstr(info[i][5]);
        mx_printchar(' ');

        if(flags & FLAG_G ){
            name_colors_print(files[i]);
        }
        else {
            mx_printstr(info[i][6]);
        }

        if((files[i].st.st_mode & S_IFMT) == S_IFLNK){
            link_print(files[i].path);
        }
        mx_printchar('\n');

        if(flags & FLAG_AT) {
            xattr_print(files[i].path);
        }
    }

    for(int i = 0 ; i < size; i++) {
        for(int j = 0 ; j < 7; j++) {
            free(info[i][j]);
        }
        free(info[i]);
    }
    free(info);
}

