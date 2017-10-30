#include <stdio.h>
#include <stdlib.h>
#define NotFound 65536
typedef int ElementType;

typedef struct {
	ElementType *Element;
	int Length;
}StaticTable;

int BinarySearch(StaticTable *Tbl, ElementType K) {
	/* 在线性表中查找关键字为K的数据元素 */
	/* 时间复杂度为O(logN) */
	int left, right, mid;
	left = 0;
	right = Tbl->Length-1;
	while( left <= right ) {
		mid = (right-left)/2 + left;		/* 计算中间元素坐标 */ 
		if( K < Tbl->Element[mid] ) {
			right = mid - 1;
		} else if( K > Tbl->Element[mid] ){
			left = mid + 1; 
		} else {
			return mid;		/* 查找成功即返回数据元素的下标 */
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
	printf("请输入要查找的元素:");
	scanf("%d", &input);
	result = BinarySearch(tbl, input);
	if( result == NotFound )
		printf("此数不存在.\n");
	else 
		printf("此数的位置是a[%d].\n", result);
	return 0; 
}
