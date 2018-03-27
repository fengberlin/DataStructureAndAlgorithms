#include <stdio.h>
#include <stdlib.h>
/* 简单选择排序算法 */
/* 数据结构	:数组 */
/*
稳定性：不稳定 
时间复杂度	О(n^2)
最优时间复杂度	О(n^2)
平均时间复杂度	О(n^2)
空间复杂度	О(n) total
*/

typedef int ElementType;

//int MaxIndex(ElementType *arr, int len) {
//	int i, maxIndex=0;
//	for(i=1; i<len; i++) {
//		if( arr[maxIndex] < arr[i] ) {
//			maxIndex = i;
//		}
//	}
//	return;
//}

//void SimpleSelectionSort(ElementType *arr, int len) {
//	int i, maxIndex;
//	for(i=len-1; i>0; i--) {
//		maxIndex = MaxIndex(arr, i+1);
//		if( maxIndex != i ) {
//			temp = arr[maxIndex];
//			arr[maxIndex] = arr[i];
//			arr[i] = temp;
//		}	// else 如果一开始arr[i]已经是最小的数了，则无需任何操作
//	}
//	return;
//}

void SimpleSelectionSort(ElementType *arr, int len) {
	int i, j, min;
	ElementType temp;
	for(i=0; i<len; i++) {
		min = i;	// 初始化min，假设min为最小数的下标 
		for(j=i+1; j<len; j++) {	// 再去看看有没有比arr[min]更小的 
			if( arr[j] < arr[min]) {
				min = j;	// 记录更小的数的下标 
			}
		}
		if( min != i ) {	
			temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;
		}	// else 如果一开始arr[i]已经是最小的数了，则无需任何操作 
	}
	return;
}

void print(ElementType *arr, int len) {
	int i;
	for(i=0; i<len; i++)
		printf("%d ", arr[i]);
	return;
}

int main()
{
	int n, i;
	printf("Please input the n(number of data):\n");
	scanf("%d", &n);
	ElementType *arr = (ElementType *)malloc(sizeof(ElementType)*n);
	printf("Please input the data:\n");
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);
	SimpleSelectionSort(arr, n);
	print(arr, n);
	return 0;
}
