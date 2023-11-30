#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
	int left = 0;
	int right = size - 1;
	
	while(left <= right) {
		int mid = (left + right) / 2;
		*count += 1;
		if(mx_strcmp(arr[mid], s) == 0) {
			return mid;
		}
		else if(mx_strcmp(arr[mid], s) > 0) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	*count = 0;
	return -1;
}


