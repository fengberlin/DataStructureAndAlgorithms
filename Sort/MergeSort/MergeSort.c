#include <stdio.h>
#include <stdlib.h>
/* 归并排序算法 */
/* 稳定性：稳定 */
/* 数据结构	:数组 */
/* 时间复杂度	O(n*log n)
最优时间复杂度	O(n)
平均时间复杂度	O(n*log n)
空间复杂度	O(n)
*/

typedef int ElementType;
/* 归并排序 - 递归实现 */
void Merge(ElementType *arr, ElementType *temp, int Left, int Mid, int Right) {
	/* 将有序的a[Left]~a[Mid-1]和a[Mid]~a[Right]归并成一个有序序列 */
	int start, LeftEnd, i;	
	start = Left;	/* 有序序列的起始位置 */
	LeftEnd = Mid - 1;		/* 左边序列终止的位置 */
	int Num = Right-Left+1; 
	while( (Left <= LeftEnd) && (Mid <= Right) ) {
		if( arr[Left] <= arr[Mid] )		/* a[Left]和a[Mid]分别是两段序列开头的首元素 */
			temp[start++] = arr[Left++];	/* 将左边序列的元素复制给temp数组存储 */
		else
			temp[start++] = arr[Mid++];	/* 将右边序列的元素复制给temp数组存储 */
	}
	while( Left <= LeftEnd )	/* 如果左边序列有元素剩下而右边已经结束 */
		temp[start++] = arr[Left++];		/* 将左边序列的剩余元素复制到temp */ 
	while( Mid <= Right )		/* 如果右边有元素剩下而左边已经结束 */
		temp[start++] = arr[Mid++];		/* 将右边序列剩余元素复制到temp */
	for(i=0; i<Num; i++,Right--)
		arr[Right] = temp[Right];
} 

void MSort(ElementType *arr, ElementType *temp, int Left, int Right) {
	/* 递归地将a[Left]~a[Right]排序 */
	int Center;
	if( Left < Right ) {
		Center = (Left+Right) >> 1;
		MSort(arr, temp, Left, Center);		/* 递归排左半边 */
		MSort(arr, temp, Center+1, Right);		/* 递归排右半边 */
		Merge(arr, temp, Left, Center+1, Right); 	/* 归并(合并) */
	} 
}

void MergeSort(ElementType *arr, int len) {
	// 归并排序 
	ElementType *temp = (ElementType *)malloc(sizeof(ElementType)*len);
	if( temp != NULL ) {
		MSort(arr, temp, 0, len-1);
		free(temp);
	}else
		printf("空间不足");
	return;
}


//void merge_sort_recursive(int arr[], int reg[], int start, int end) {
//	if (start >= end)
//		return;
//	int len = end - start, mid = (len >> 1) + start;
//	int start1 = start, end1 = mid;
//	int start2 = mid + 1, end2 = end;
//	merge_sort_recursive(arr, reg, start1, end1);
//	merge_sort_recursive(arr, reg, start2, end2);
//	int k = start;
//	while (start1 <= end1 && start2 <= end2)
//		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
//	while (start1 <= end1)
//		reg[k++] = arr[start1++];
//	while (start2 <= end2)
//		reg[k++] = arr[start2++];
//	for (k = start; k <= end; k++)
//		arr[k] = reg[k];
//}
//void merge_sort(int arr[], const int len) {
//	int *reg;
//	reg = (int *)malloc(sizeof(int)*len);
//	merge_sort_recursive(arr, reg, 0, len - 1);
//}



/* 归并排序 - 循环实现 */
/* 这里Merge函数在递归版本中给出 */ 
/* length = 当前有序子列的长度*/
//void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length )
//{ /* 两两归并相邻有序子列 */
//     int i, j;
//       
//     for ( i=0; i <= N-2*length; i += 2*length )
//         Merge( A, TmpA, i, i+length, i+2*length-1 );
//     if ( i+length < N ) /* 归并最后2个子列*/
//         Merge( A, TmpA, i, i+length, N-1);
//     else /* 最后只剩1个子列*/
//         for ( j = i; j < N; j++ ) TmpA[j] = A[j];
//}
// 
//void Merge_Sort( ElementType A[], int N )
//{ 
//     int length; 
//     ElementType *TmpA;
//      
//     length = 1; /* 初始化子序列长度*/
//     TmpA = (ElementType *)malloc( N * sizeof( ElementType ) );
//     if ( TmpA != NULL ) {
//          while( length < N ) {
//              Merge_pass( A, TmpA, N, length );
//              length *= 2;
//              Merge_pass( TmpA, A, N, length );
//              length *= 2;
//          }
//          free( TmpA );
//     }
//     else printf( "空间不足" );
//}


void print(ElementType *a, int len) {
	int i;
	for(i=0; i<len; i++)
		printf("%d ", a[i]);
	printf("\n");
	return;
}

int main()
{
	ElementType arr[] = {8,2,6,-1,7,1,6,5,9,2,0,3,63,15,24};
	int len = sizeof(arr)/sizeof(arr[0]);
	MergeSort(arr, len);
	print(arr, len);
	return 0;
}
