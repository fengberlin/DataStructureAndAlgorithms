#include <stdio.h>
#include <stdlib.h>
/* �򵥲��������㷨 */
/* ���ݽṹ: ���� */
/* 
�ȶ��ԣ��ȶ� 
ʱ�临�Ӷ�	O(n^2)
����ʱ�临�Ӷ�	O(n)
ƽ��ʱ�临�Ӷ�	O(n^2)
�ռ临�Ӷ�	�ܹ�O(n) ����Ҫ�����ռ�O(1)
*/

typedef int ElementType;

void SimpleInsertionSort(ElementType *arr, int len) {
	/* �������� */
	int i, j;
	ElementType temp;
	for(i=1; i<len; i++) {
		temp = arr[i];		/* ȡ��δ���������еĵڶ���Ԫ�� */
		for(j=i; (j>0)&&(arr[j-1]>temp); j--) {
			arr[j] = arr[j-1];		/* ������������������Ԫ�رȽϲ����� */
		}
		arr[j] = temp;	/* �Ž����ʵ�λ�� */ 
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
