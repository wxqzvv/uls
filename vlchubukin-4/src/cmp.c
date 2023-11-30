#include "../inc/uls.h"

bool atime_cmp(t_fileinfo a, t_fileinfo b) {
    if(a.st.st_atime == b.st.st_atime) {
        if(a.st.st_atimespec.tv_nsec == b.st.st_atimespec.tv_nsec){
            return !name_compare(a, b);
        }
        return a.st.st_atimespec.tv_nsec < b.st.st_atimespec.tv_nsec;
    }
    return a.st.st_atime < b.st.st_atime;
}

bool ctime_cmp(t_fileinfo a, t_fileinfo b) {
    if(a.st.st_ctime == b.st.st_ctime) {
        if(a.st.st_ctimespec.tv_nsec == b.st.st_ctimespec.tv_nsec) {
            return !name_compare(a, b);
        }
        return a.st.st_ctimespec.tv_nsec < b.st.st_ctimespec.tv_nsec;
    }
    return a.st.st_ctime < b.st.st_ctime;
}

bool mtime_compare(t_fileinfo a, t_fileinfo b) {
    if(a.st.st_mtime == b.st.st_mtime) {
        if(a.st.st_mtimespec.tv_nsec == b.st.st_mtimespec.tv_nsec) {
            return !name_compare(a, b);
        }
        return a.st.st_mtimespec.tv_nsec < b.st.st_mtimespec.tv_nsec;
    }
    return a.st.st_mtime < b.st.st_mtime;
}

bool name_compare(t_fileinfo a, t_fileinfo b) {
    return mx_strcmp(a.name, b.name) > 0;
}

bool sz_compare(t_fileinfo a, t_fileinfo b) {
    if(a.st.st_size == b.st.st_size) {
        return name_compare(a, b);
    }
    return a.st.st_size < b.st.st_size;
}

