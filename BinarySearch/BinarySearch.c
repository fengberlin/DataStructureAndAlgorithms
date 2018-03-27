#include <stdio.h>
#include <stdlib.h>
#define NotFound 65536
typedef int ElementType;

typedef struct {
	ElementType *Element;
	int Length;
}StaticTable;

int BinarySearch(StaticTable *Tbl, ElementType K) {
	/* �����Ա��в��ҹؼ���ΪK������Ԫ�� */
	/* ʱ�临�Ӷ�ΪO(logN) */
	int left, right, mid;
	left = 0;
	right = Tbl->Length-1;
	while( left <= right ) {
		mid = (right-left)/2 + left;		/* �����м�Ԫ������ */ 
		if( K < Tbl->Element[mid] ) {
			right = mid - 1;
		} else if( K > Tbl->Element[mid] ){
			left = mid + 1; 
		} else {
			return mid;		/* ���ҳɹ�����������Ԫ�ص��±� */
		}
	} 
	return NotFound;
}

int main()
{
	int a[] = {1, 3, 5, 7, 9, 55, 100, 121};
	int input, result;
	StaticTable *tbl;
	tbl = (StaticTable *)malloc(sizeof(StaticTable));
	tbl->Element = a;
	tbl->Length = sizeof(a)/sizeof(a[0]);
	printf("������Ҫ���ҵ�Ԫ��:");
	scanf("%d", &input);
	result = BinarySearch(tbl, input);
	if( result == NotFound )
		printf("����������.\n");
	else 
		printf("������λ����a[%d].\n", result);
	return 0; 
}
