#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if(str == NULL || sub == NULL) {
        return -2;
    }

    int index = 0;
    while (*str != '\0') {
        if(mx_strchr(str, *sub) && mx_strncmp(str, sub, mx_strlen(sub)) == 0) {
            	return index;
        }
        str++;
        index++;
    }
		
    return -1;
}


