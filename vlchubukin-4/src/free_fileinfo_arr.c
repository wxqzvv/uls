#include "../inc/uls.h"

void free_file_into_array(t_fileinfo* arr, int size) {
    for(int i = 0; i < size; i++) {
        free(arr[i].name);
        free(arr[i].path);
        arr[i].name = NULL;
        arr[i].path = NULL;
    }
    free(arr);
    arr = NULL;
}

