#include "../inc/uls.h"

void files_sort(t_fileinfo files[], int size, unsigned short flags) {
    bool (*cmp)(t_fileinfo, t_fileinfo) = NULL;

	if(flags & FLAG_t) {
		if(flags & FLAG_u) {
			cmp = atime_cmp;
		}
		else if(flags & FLAG_c) {
			cmp = ctime_cmp;
		}
		else {
			cmp = mtime_compare;
		}
	}
	else if(flags & FLAG_S) {
		cmp = sz_compare;
	}
	else {
		cmp = name_compare;
	}
	if(flags & FLAG_r){
		int isSorted = 0;
		while(!isSorted) {
			isSorted = 1;

			for(int i = 0; i < size - 1; i++) {
				if(!cmp(files[i], files[i + 1])) {
					isSorted = 0;
					
					t_fileinfo buff = files[i];
					files[i] = files[i + 1];
					files[i + 1] = buff;
				}
			}
		}
	}
	else {
		int isSorted = 0;
		while(!isSorted) {
			isSorted = 1;

			for(int i = 0; i < size - 1; i++) {
				if(cmp(files[i], files[i + 1])) {
					isSorted = 0;
					
					t_fileinfo buff = files[i];
					files[i] = files[i + 1];
					files[i + 1] = buff;
				}
			}
		}
	}
}

