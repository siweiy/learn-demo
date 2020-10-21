#include <stdio.h>

int binSearch(int arr[], int len, int key) {
	int left = 0;
	int right = len - 1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] == key) {
			return mid;
		}else if (arr[mid] < key) {
			left = mid+1;
		}else{
			right = mid-1;
		}
	}
	
	return -1;
}

int main(int argc, char const *argv[])
{
	int arr[] = {1,2,4,5,7,9,11,23,44,56};
	printf("%d\n", binSearch(arr, 10, 5));
	return 0;
}
