#include "../inc/uls.h"

int maximum_name_len(t_fileinfo arr[], int size) {
    if(size > 0) {
        int max = mx_strlen(arr[0].name);

        for(int i = 1; i < size; i++) {
            int length = mx_strlen(arr[i].name);
            if(length > max) {
                max = length;
            }
        }

        return max;
    }

    return -1;
}

