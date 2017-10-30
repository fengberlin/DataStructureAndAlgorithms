#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
/* ���������㷨 */
/* �ȶ��ԣ����ȶ� */ 
/* ���ݽṹ: ���� */
/*
���ʱ�临�Ӷ�	O(n^2)
����ʱ�临�Ӷ�	O(n*log n)
ƽ��ʱ�临�Ӷ�	O(n*log n)
�ռ临�Ӷ�	����ʵ�ֵķ�ʽ��ͬ����ͬ
*/ 
/* ��������һ����ֵCutOff, �������㹻��ʱ����ÿ�������, �����ü�����, ��������� */

typedef int ElementType; 

void Swap(ElementType *a, ElementType *b) {	
	/* ���������� */
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
} 

void QSort(ElementType *arr, int Low, int High) {
	/* ��a[Low]~a[High]���п������� */
	ElementType Pivot = arr[Low];	/* �򵥵�ȡ��Ԫ��Ϊ��׼ */
	int Left, Right;
	Left = Low;
	Right = High;
	if( Low >= High ) return;
	Swap(&arr[Low], &arr[Right]);	/* ����׼�����һ��Ԫ�ؽ��� */
	while( Low < High ) {
		while( Low<High && arr[Low]<=Pivot )
			Low++;
		while( Low<High && arr[High]>=Pivot )
			High--;
		if( Low < High )
			Swap(&arr[Low], &arr[High]);
	}
	/* ��ΪLow��Highһ����λ��Low>=High����Low��ָ��Ԫ�ؾʹ��ڻ�׼������һ��������С�Ĺ�ϵ��ȷ���� */
	Swap(&arr[Low], &arr[Right]);	/* �����Ļ�׼������ȷ��λ��, Highһֱ�ڱ�, ���Բ�����a[High] */
	
	/* �ݹ�-->�ֱ�������Ӽ����п��� */ 
	if( Low )
		QSort(arr, Left, Low-1);
	QSort(arr, Low+1, Right);
}

void QuickSort(ElementType *arr, int len) {	
	/* ���������������㷨��ͬ�ĺ����ӿ� */
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
