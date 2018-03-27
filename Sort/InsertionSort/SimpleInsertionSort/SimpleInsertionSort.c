#include <stdio.h>
#include <stdlib.h>
/* 简单插入排序算法 */
/* 数据结构: 数组 */
/* 
稳定性：稳定 
时间复杂度	O(n^2)
最优时间复杂度	O(n)
平均时间复杂度	O(n^2)
空间复杂度	总共O(n) ，需要辅助空间O(1)
*/

typedef int ElementType;

void SimpleInsertionSort(ElementType *arr, int len) {
	/* 插入排序 */
	int i, j;
	ElementType temp;
	for(i=1; i<len; i++) {
		temp = arr[i];		/* 取出未排序序列中的第二个元素 */
		for(j=i; (j>0)&&(arr[j-1]>temp); j--) {
			arr[j] = arr[j-1];		/* 依次与已排序序列中元素比较并右移 */
		}
		arr[j] = temp;	/* 放进合适的位置 */ 
	}
}

void print(ElementType *arr, int len) {
	int i;
	for(i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return;
} 

int main()
{
	int i, len;
	printf("Please input tne num of data you want:\n");
	scanf("%d", &len);
	ElementType *arr = (ElementType *)malloc(sizeof(ElementType)*len);
	printf("Please input the data:\n");
	for(i=0; i<len; i++)
		scanf("%d", &arr[i]);
	SimpleInsertionSort(arr,len);
	print(arr,len);
	return 0;
} 
