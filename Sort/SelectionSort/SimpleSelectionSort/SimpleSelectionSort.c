#include <stdio.h>
#include <stdlib.h>
/* ��ѡ�������㷨 */
/* ���ݽṹ	:���� */
/*
�ȶ��ԣ����ȶ� 
ʱ�临�Ӷ�	��(n^2)
����ʱ�临�Ӷ�	��(n^2)
ƽ��ʱ�临�Ӷ�	��(n^2)
�ռ临�Ӷ�	��(n) total
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
//		}	// else ���һ��ʼarr[i]�Ѿ�����С�����ˣ��������κβ���
//	}
//	return;
//}

void SimpleSelectionSort(ElementType *arr, int len) {
	int i, j, min;
	ElementType temp;
	for(i=0; i<len; i++) {
		min = i;	// ��ʼ��min������minΪ��С�����±� 
		for(j=i+1; j<len; j++) {	// ��ȥ������û�б�arr[min]��С�� 
			if( arr[j] < arr[min]) {
				min = j;	// ��¼��С�������±� 
			}
		}
		if( min != i ) {	
			temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;
		}	// else ���һ��ʼarr[i]�Ѿ�����С�����ˣ��������κβ��� 
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
