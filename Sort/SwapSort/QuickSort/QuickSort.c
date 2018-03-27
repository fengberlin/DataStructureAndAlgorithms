#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
/* 快速排序算法 */
/* 稳定性：不稳定 */ 
/* 数据结构: 不定 */
/*
最差时间复杂度	O(n^2)
最优时间复杂度	O(n*log n)
平均时间复杂度	O(n*log n)
空间复杂度	根据实现的方式不同而不同
*/ 
/* 可以设置一个阈值CutOff, 当数据足够的时候就用快速排序, 否则用简单排序, 如插入排序 */

typedef int ElementType; 

void Swap(ElementType *a, ElementType *b) {	
	/* 交换两个数 */
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
} 

void QSort(ElementType *arr, int Low, int High) {
	/* 对a[Low]~a[High]进行快速排序 */
	ElementType Pivot = arr[Low];	/* 简单地取首元素为基准 */
	int Left, Right;
	Left = Low;
	Right = High;
	if( Low >= High ) return;
	Swap(&arr[Low], &arr[Right]);	/* 将基准与最后一个元素交换 */
	while( Low < High ) {
		while( Low<High && arr[Low]<=Pivot )
			Low++;
		while( Low<High && arr[High]>=Pivot )
			High--;
		if( Low < High )
			Swap(&arr[Low], &arr[High]);
	}
	/* 因为Low和High一旦错位即Low>=High，即Low所指的元素就大于基准，所以一交换，大小的关系就确定了 */
	Swap(&arr[Low], &arr[Right]);	/* 将最后的基准换到正确的位置, High一直在变, 所以不能用a[High] */
	
	/* 递归-->分别对两个子集进行快排 */ 
	if( Low )
		QSort(arr, Left, Low-1);
	QSort(arr, Low+1, Right);
}

void QuickSort(ElementType *arr, int len) {	
	/* 保持与其他排序算法相同的函数接口 */
	QSort(arr, 0, len-1);
}

void print(ElementType *a, int len) {
	int i;
	for(i=0; i<len; i++)
		printf("%d ", a[i]);
	printf("\n");
	return;
}

int main()
{
	int arr[] = {5,9,12,30,15,75,91,84,100,2,42,23};
	int len = sizeof(arr)/sizeof(arr[0]);
	QuickSort(arr, len);
	print(arr, len);
	return 0;
} 
