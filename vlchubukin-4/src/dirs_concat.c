#include "../inc/uls.h"

char *dirs_concat(char* fst, char* scd) {
    char *res = mx_strnew(mx_strlen(fst) + mx_strlen(scd) + 1);
    mx_strncpy(res, fst, mx_strlen(fst));
    mx_strcat(res, "/");
    mx_strcat(res, scd);

    return res;
}

