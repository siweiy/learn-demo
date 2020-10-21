/********************************************************************
 *							多种排序函数头文件						*
 ********************************************************************
 *		void bubbling_sort(int a[], int n);					冒泡排序	*	
 *		void insert_sort(int a[], int n);					插入排序	*
 *		void select_sort(int a[], int n);					选择排序	*
 *		void Quick_Sort(int arr[], int start, int end);		快速排序 *
 ********************************************************************/

#ifndef _MY_SORT_H
#define _MY_SORT_H

/*参数说明
 *			冒泡排序				
 ******************************
 *		  a ----待排序数组		
 *		  n ----数组长度			
 ******************************/

void Bubbling_Sort(int a[], int n)
{
	int i, j;
	int tmp;
	for (i = 0; i < n-1; i++)
		for (j = 0; j < n-1-i; j++)
			if (a[j] > a[j+1]) {
				tmp = a[j]; a[j] = a[j+1]; a[j+1] = tmp;
			}
}


/*参数说明
 *			插入排序				
 ******************************
 *		  a ----待排序数组		
 *		  n ----数组长度			
 ******************************/

void Insert_Sort(int a[], int n)
{
	
	int i, j;
	int tmp;
	for (i = 1; i < n; i++) {
		tmp = a[i];
		j = i;
		while(tmp < a[j-1]) {
			a[j] = a[j-1];
			j--;
			if (j <= 0)
				break;
		}
		a[j] = tmp;
	}
}


/*参数说明
 *			选择排序				
 ********************************
 *		  a ----待排序数组		
 *		  n ----数组长度			
 ********************************/

void Select_Sort(int a[], int n)
{
	int tmp, min;
	for (int i = 0; i < n-1; i++) {
		min = i;
		for(int j = i+1; j < n; j++)
			if (a[j] < a[min])
				min = j;//获取最小数的下标
			
		if(i != min) {
			tmp = a[i]; a[i] = a[min]; a[min] = tmp;		
		}
	}
}


/*参数说明
 *				快速排序				
 *************************************
 *		  arr ----待排序数组		
 *		  start --需排序的开始位置
 *		  end ----需排序的结束位置	
 *************************************/

void Quick_Sort(int arr[], int start, int end)
{	
	if (start >= end)		
		return;	
	int i = start;	
	int j = end;	
	int baseval = arr[start];	// 基准数	
	while (i < j) {		
		// 从右向左找比基准数小的数		
		while (i < j && arr[j] >= baseval)		
			j--;		
	
		if (i < j) {			
			arr[i] = arr[j];			
			i++;		
		}		
		// 从左向右找比基准数大的数		
		while (i < j && arr[i] < baseval)		
			i++;				
		if (i < j) {			
			arr[j] = arr[i];			
			j--;		
		}	
	}	
	// 把基准数放到i的位置	
	arr[i] = baseval;	
	// 递归	
	Quick_Sort(arr, start, i - 1); //分组好的两部分分别再次使用快速排序
	Quick_Sort(arr, i + 1, end);
}


#endif