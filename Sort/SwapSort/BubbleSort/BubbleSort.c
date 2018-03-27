#include <stdio.h>
#include <stdlib.h>
/* ð�������㷨 */
/* ���ݽṹ	:���� */
/*
ʱ�临�Ӷ�	O(n^2)
����ʱ�临�Ӷ�	O(n)
ƽ��ʱ�临�Ӷ�	O(n^2)
�ռ临�Ӷ�	�ܹ�O(n)����Ҫ�����ռ�O(1)
*/

typedef int ElementType;

void BubbleSort(ElementType *arr, int len) {
	int flag, i, j;		/* flag�Ǽ�¼�Ƿ񽻻��ı�־ */
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
		if( !flag ) break;		/* flag==0, ˵�������Ѿ�����, �����ٽ�����һ�ֵ�ѭ�� */
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

