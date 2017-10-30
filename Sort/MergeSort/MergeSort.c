#include <stdio.h>
#include <stdlib.h>
/* �鲢�����㷨 */
/* �ȶ��ԣ��ȶ� */
/* ���ݽṹ	:���� */
/* ʱ�临�Ӷ�	O(n*log n)
����ʱ�临�Ӷ�	O(n)
ƽ��ʱ�临�Ӷ�	O(n*log n)
�ռ临�Ӷ�	O(n)
*/

typedef int ElementType;
/* �鲢���� - �ݹ�ʵ�� */
void Merge(ElementType *arr, ElementType *temp, int Left, int Mid, int Right) {
	/* �������a[Left]~a[Mid-1]��a[Mid]~a[Right]�鲢��һ���������� */
	int start, LeftEnd, i;	
	start = Left;	/* �������е���ʼλ�� */
	LeftEnd = Mid - 1;		/* ���������ֹ��λ�� */
	int Num = Right-Left+1; 
	while( (Left <= LeftEnd) && (Mid <= Right) ) {
		if( arr[Left] <= arr[Mid] )		/* a[Left]��a[Mid]�ֱ����������п�ͷ����Ԫ�� */
			temp[start++] = arr[Left++];	/* ��������е�Ԫ�ظ��Ƹ�temp����洢 */
		else
			temp[start++] = arr[Mid++];	/* ���ұ����е�Ԫ�ظ��Ƹ�temp����洢 */
	}
	while( Left <= LeftEnd )	/* ������������Ԫ��ʣ�¶��ұ��Ѿ����� */
		temp[start++] = arr[Left++];		/* ��������е�ʣ��Ԫ�ظ��Ƶ�temp */ 
	while( Mid <= Right )		/* ����ұ���Ԫ��ʣ�¶�����Ѿ����� */
		temp[start++] = arr[Mid++];		/* ���ұ�����ʣ��Ԫ�ظ��Ƶ�temp */
	for(i=0; i<Num; i++,Right--)
		arr[Right] = temp[Right];
} 

void MSort(ElementType *arr, ElementType *temp, int Left, int Right) {
	/* �ݹ�ؽ�a[Left]~a[Right]���� */
	int Center;
	if( Left < Right ) {
		Center = (Left+Right) >> 1;
		MSort(arr, temp, Left, Center);		/* �ݹ������� */
		MSort(arr, temp, Center+1, Right);		/* �ݹ����Ұ�� */
		Merge(arr, temp, Left, Center+1, Right); 	/* �鲢(�ϲ�) */
	} 
}

void MergeSort(ElementType *arr, int len) {
	// �鲢���� 
	ElementType *temp = (ElementType *)malloc(sizeof(ElementType)*len);
	if( temp != NULL ) {
		MSort(arr, temp, 0, len-1);
		free(temp);
	}else
		printf("�ռ䲻��");
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



/* �鲢���� - ѭ��ʵ�� */
/* ����Merge�����ڵݹ�汾�и��� */ 
/* length = ��ǰ�������еĳ���*/
//void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length )
//{ /* �����鲢������������ */
//     int i, j;
//       
//     for ( i=0; i <= N-2*length; i += 2*length )
//         Merge( A, TmpA, i, i+length, i+2*length-1 );
//     if ( i+length < N ) /* �鲢���2������*/
//         Merge( A, TmpA, i, i+length, N-1);
//     else /* ���ֻʣ1������*/
//         for ( j = i; j < N; j++ ) TmpA[j] = A[j];
//}
// 
//void Merge_Sort( ElementType A[], int N )
//{ 
//     int length; 
//     ElementType *TmpA;
//      
//     length = 1; /* ��ʼ�������г���*/
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
//     else printf( "�ռ䲻��" );
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
