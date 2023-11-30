#include "../inc/uls.h"

int maximum_elem(char*** info, int size, int col) {
    int max = mx_strlen(info[0][col]);
    
    for(int i = 0; i < size ; i++){
        if (mx_strlen(info[i][col]) > max ){
            max = mx_strlen(info[i][col]);
        }
    }

    return max;
}


