#include "../inc/uls.h"

DIR* open_dir(const char* name, int* exit_stts) {
    DIR* dir = opendir(name);

    if(dir == NULL) {
        mx_printerr("uls: ");
        mx_printerr(name);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        *exit_stts = 1;
    }

    return dir;
}

