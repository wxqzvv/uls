#include "../inc/uls.h"

char getfile_type(mode_t mode) {
    switch(mode & S_IFMT) {
        case S_IFSOCK:
            return 's';
        case S_IFLNK:
            return 'l';
        case S_IFBLK:
            return 'b';
        case S_IFDIR:
            return 'd';
        case S_IFCHR:
            return 'c';
        case S_IFIFO:
            return 'p';
    }
    
    return '-';
}


