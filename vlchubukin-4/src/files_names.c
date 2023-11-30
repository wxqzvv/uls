#include "../inc/uls.h"

void files_print(t_fileinfo files[], int size, unsigned short flags, bool is_total) {
    int max = maximum_name_len(files, size);
    int cols = cols_count(max, flags);

    int rows = size / cols;
    if(size % cols != 0) {
        rows += 1;
    }

    if(!isatty(STDOUT_FILENO) || flags & FLAG_1){
        if(flags & FLAG_l){
            lng_outp(files, size, flags, is_total);
        }
        else {
            for(int i = 0; i < size; i++){
                    mx_printstr(files[i].name);
                    mx_printchar('\n');
            }
        }
    }
    else if(flags & FLAG_l) {
        lng_outp(files, size, flags, is_total);
    }
    else {
            for(int i = 0; i < rows && size > 0; i++) {
                for(int j = 0; j < cols; j++) {
                    int index = i + j * rows;
                    if(index < size ) {
                        if(flags & FLAG_G){
                            name_colors_print(files[index]);
                        }
                        else {
                            mx_printstr(files[index].name);
                        }
                        mx_printnchar(' ', max - mx_strlen(files[index].name));
                    }
                    if(j != cols - 1) {
                        if(flags & FLAG_G){
                            mx_printchar(' ');
                        }
                        else{
                            mx_printchar('\t');
                        }
                    }
                }
                mx_printchar('\n');
            }
        }
    }

