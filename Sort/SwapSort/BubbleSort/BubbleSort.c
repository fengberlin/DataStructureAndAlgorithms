#include <stdio.h>
#include <stdlib.h>
/* 冒泡排序算法 */
/* 数据结构	:数组 */
/*
时间复杂度	O(n^2)
最优时间复杂度	O(n)
平均时间复杂度	O(n^2)
空间复杂度	总共O(n)，需要辅助空间O(1)
*/

typedef int ElementType;

void BubbleSort(ElementType *arr, int len) {
	int flag, i, j;		/* flag是记录是否交换的标志 */
	ElementType temp;
	for(i=len-1; i>=0; i--) {
		flag = 0;
		for(j=0; j<i; j++) {
			if( arr[j] > arr[j+1] ) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				flag = 1;
			}
		}
		if( !flag ) break;		/* flag==0, 说明序列已经有序, 不用再进行下一轮的循环 */
	}
}

int main()
{
	int i;
	int a[] = {2,1,45,6,90,32,54,64};
	BubbleSort(a, sizeof(a)/sizeof(a[0]));
	for(i=0; i<sizeof(a)/sizeof(a[0]); i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}

