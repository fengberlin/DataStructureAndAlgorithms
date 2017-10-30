#include <stdio.h>
#include <stdlib.h>
/* ϣ�������㷨 */
/* ���ݽṹ	:���� */
/*
�ȶ��ԣ����ȶ� 
ʱ�临�Ӷ�	���ݲ������еĲ�ͬ����ͬ����֪��õģ� O(n*(logn)^2)
����ʱ�临�Ӷ�	O(n)
ƽ��ʱ�临�Ӷ�	���ݲ���(����)���еĲ�ͬ����ͬ��
�ռ临�Ӷ�	O(n)
*/

typedef int ElementType;

//void ShellSort(ElementType *arr, int len, int *Incre, int n) {
//	/* ϣ������ */
//	/* ����Incre[]Ϊ����n������������, �ݼ�����, �����һ��Ԫ��Ϊ1 */
//	int i, j, k, Increment; 
//	ElementType temp;
//	for(i=0; i<n; i++) {
//		Increment = Incre[i];	/* ѡ�����������Ҫ������ */
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
	/* ϣ������ - ��Sedgewick�������� */
	int n, i, j, k;
	int gap[] = {929, 505, 209, 109, 41, 19, 5, 1};	/* ����Ԫ�طֱ�����9*4^i-9*2^i+1��(2^(i+2))*(2^(i+2)-3)+1 */
	ElementType temp;
	
	/* ��ʼ������Sedgewick[Si]���ܳ����������г���, ��������˾��Ҳ����ڶ�������, ��ֻ��һ���� */
	for(n=0; gap[n]>=len; n++);		// �ҵ����ʵĳ�ʼ���� 
	
	for(i=gap[n]; i>0&&n<sizeof(gap)/sizeof(gap[0]); i=gap[++n]) {	// �������� 
		for(k=i; k<len; k++) {
			temp = arr[k];
			for(j=k; j-i>=0&&arr[j-i]>temp; j-=i) 
				arr[j] = arr[j-i];
			arr[j] = temp;
		}
	}
}

//void ShellSort(ElementType *arr, int len) {
//	/* ��N/(2^i)��������---->((N/2), (N/(2^2)), (N/(2^3)), ..., 1 ) */
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
