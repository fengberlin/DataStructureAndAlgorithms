#include <stdio.h>
#include <stdlib.h>
/* 希尔排序算法 */
/* 数据结构	:数组 */
/*
稳定性：不稳定 
时间复杂度	根据步长序列的不同而不同。已知最好的： O(n*(logn)^2)
最优时间复杂度	O(n)
平均时间复杂度	根据步长(增量)序列的不同而不同。
空间复杂度	O(n)
*/

typedef int ElementType;

//void ShellSort(ElementType *arr, int len, int *Incre, int n) {
//	/* 希尔排序 */
//	/* 其中Incre[]为包含n个增量的序列, 递减有序, 且最后一个元素为1 */
//	int i, j, k, Increment; 
//	ElementType temp;
//	for(i=0; i<n; i++) {
//		Increment = Incre[i];	/* 选择该趟排序需要的增量 */
//		for(j=Increment; j<len; j++) {
//			temp = arr[j];
//			for(k=j; k-Increment>=0; k-=Increment) {
//				if( temp < arr[k-Increment] ) 
//					arr[j] = arr[k-Increment];
//				else 
//					break;
//			}
//			arr[k] = temp;
//		}
//	}
//} 

void ShellSort(ElementType *arr, int len) {
	/* 希尔排序 - 用Sedgewick增量序列 */
	int n, i, j, k;
	int gap[] = {929, 505, 209, 109, 41, 19, 5, 1};	/* 序列元素分别来自9*4^i-9*2^i+1和(2^(i+2))*(2^(i+2)-3)+1 */
	ElementType temp;
	
	/* 初始的增量Sedgewick[Si]不能超过待排序列长度, 如果超出了就找不到第二个数了, 就只有一个数 */
	for(n=0; gap[n]>=len; n++);		// 找到合适的初始增量 
	
	for(i=gap[n]; i>0&&n<sizeof(gap)/sizeof(gap[0]); i=gap[++n]) {	// 插入排序 
		for(k=i; k<len; k++) {
			temp = arr[k];
			for(j=k; j-i>=0&&arr[j-i]>temp; j-=i) 
				arr[j] = arr[j-i];
			arr[j] = temp;
		}
	}
}

//void ShellSort(ElementType *arr, int len) {
//	/* 用N/(2^i)增量序列---->((N/2), (N/(2^2)), (N/(2^3)), ..., 1 ) */
//	int gap, i, j;
//	ElementType temp;
//	for(gap=len>>1; gap>0; gap>>=1) {
//		for(i=gap; i<len; i++) {
//			temp = arr[i];
//			for(j=i; j-gap>=0&&arr[j-gap]>temp; j-=gap) 
//				arr[j] = arr[j-gap];
//			arr[j] = temp;
//		}
//	}
//} 

int main()
{
	int a[] = {0, 1, 3, 8, 100, 20,15, 123, -1, -11, 19};
//	int c[] = {5, 3, 1};
//	ShellSort(a, 11, c, 3);
	ShellSort(a,sizeof(a)/sizeof(a[0]));
	int i;	
	for(i=0; i<sizeof(a)/sizeof(a[0]); i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
} 
