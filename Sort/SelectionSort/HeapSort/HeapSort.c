#include <stdio.h>
#include <stdlib.h>
/* ������ */
/* ���ݽṹ	:���� */
/*
�ȶ��ԣ����ȶ� 
ʱ�临�Ӷ�	O(n*log n)
����ʱ�临�Ӷ�	O(n*log n)
ƽ��ʱ�临�Ӷ�	O(n*log n)
�ռ临�Ӷ�	O(n) total
*/

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxSize 100
typedef int ElementType;

typedef struct heap{
	ElementType *data;		/* �洢��Ԫ�ص����� */ 
	int Size;	/* �ѵ�Ԫ�ظ��� */
	int Capacity;	/* �ѵ�������� */ 
}MaxHeap;

int isEmpty(MaxHeap *H) {	
	/* �ж϶��Ƿ�Ϊ�� */
	return (H->Size == 0);
}

int isFull(MaxHeap *H) {	
	// �ж������Ƿ�Ϊ��
	return (H->Size == MaxSize);
}

MaxHeap *CreateHeap() {
	MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
	if( !heap )
		FatalError("Failed to allocate memory!");
	heap->Capacity = MaxSize;
	heap->Size = 0;
	heap->data = (ElementType *)malloc(sizeof(ElementType)*MaxSize);
	return heap;
}

void Insert(MaxHeap *H, ElementType item) {
	if( isFull(H) ) {
		FatalError("���Ѿ�����"); 
	}
	H->Size++;
	int i;
	for(i=H->Size-1; i>=1&&H->data[(i-1)/2]<item; i=(i-1)/2) 
		H->data[i] = H->data[(i-1)/2];
	H->data[i] = item; 
	return;
}

void Add(MaxHeap *H, ElementType item) {	
	/* ����ʼ���������Ԫ�� */
	if( isFull(H) )
		FatalError("the array is full");
	H->data[(H->Size)++] = item;
	return;
}

//void Adjust(MaxHeap *H, int Parent, int N)
//{	/* ��a[]�е�ǰN��Ԫ�ش�i��Ԫ�ؿ�ʼ����Ǩ�Ƶ��� */
//	int Child;
//	ElementType temp;
//	
//	for(temp=H->data[Parent]; ( Parent*2+1 )<N; Parent=Child)
//	{
//		Child = Parent*2 + 1;	/* ���ӽ�� */
//		if( (Child != N-1) && H->data[Child+1]>H->data[Child])	/* ��ʱN-1�����ֵ�Ѿ����ų���ȥ�� */
//			Child++;	/* Childָ�������ӽ��Ľϴ��� */
//		if( temp < H->data[Child] )
//			H->data[Parent] = H->data[Child];	/* �ƶ�ChildԪ�ص��ϲ� */
//		else break; 
//	} 
//	H->data[Parent] = temp;		/* ��temp�ŵ���ǰλ�� */
//	return;
//}

void Adjust(MaxHeap *H, int i, int N) {
	/* ��a[]�е�ǰN��Ԫ�ش�i��Ԫ�ؿ�ʼ����Ǩ�Ƶ��� */
	int Parent, Child;
	ElementType temp;
	temp = H->data[i];		// ��ʱ��¼H->data[i]��ֵ 
	for(Parent=i; (Parent*2+1)<N; Parent=Child) {
		Child = Parent*2 + 1;	/* ���ӽ�� */
		if( (Child != N-1) && (H->data[Child+1]>H->data[Child]) ) 	/* ��ʱN-1�����ֵ�Ѿ����ų���ȥ�� */
			Child++;	/* Childָ�������ӽ��Ľϴ��� */
		if( temp < H->data[Child] ) 
			H->data[Parent] = H->data[Child];		/* �ƶ�ChildԪ�ص��ϲ� */
		else 
			break;
	}
	H->data[Parent] = temp;		/* ��temp�ŵ���ǰλ�� */
	return;
}

//void HeapSort(MaxHeap *H, int N)
//{	/* ������ */
//	int i;
//	ElementType temp;
//	
//	/* �������� */
//	for(i=(N-1)/2; i>=0; i--)	/* ���ж��ӵ����һ����㿪ʼ(�����һ�����ĸ���㿪ʼ) */
//		Adjust(H, i, N);
//	for(i=N-1; i>0; i--)
//	{
//		/* ���Ѷ�Ԫ��H->data[0]�뵱ǰ�ѵ����һ��Ԫ��H->data[i]��λ */
//		temp = H->data[0];
//		H->data[0] = H->data[i];
//		H->data[i] = temp;
//		/* ����i��Ԫ�ص��¶ѴӸ�������¹��˵��� */
//		Adjust(H, 0, i);
//	} 
//} 

void BuildMaxHeap(MaxHeap *H) {
	int i;
	for(i=(H->Size-2)/2; i>=0; i--) 
		Adjust(H, i, H->Size);
	return;
}

void HeapSort(MaxHeap *H, int N) {
	// ������ 
	int i;
	ElementType temp;
	for(i=N-1; i>0; i--) {
		/* ���Ѷ�Ԫ��H->data[0]�뵱ǰ�ѵ����һ��Ԫ��H->data[i]��λ */
		temp = H->data[i];
		H->data[i] = H->data[0];
		H->data[0] = temp;
		/* ����i��Ԫ�ص��¶ѴӸ�������¹��˵��� */
		Adjust(H, 0, i);
	}
}

ElementType DeleteMax(MaxHeap *H) {
	int temp, Parent, Child, maxValue;
	maxValue = H->data[0];
	temp = H->data[--H->Size];
	for(Parent=0; (Parent*2+1)<H->Size; Parent=Child)
	{
		Child = Parent*2 + 1;
		if( (Child != H->Size-1) && H->data[Child+1]>H->data[Child] )
			Child++;
		if( temp < H->data[Child] )
			H->data[Parent] = H->data[Child];
		else break;
	} 
	H->data[Parent] = temp;
	return maxValue;
}

void print(MaxHeap *H)
{
	int i;
	if( isEmpty(H) )
		FatalError("the heap is empty!");
	for(i=0; i<H->Size; i++)
		printf("%d ", H->data[i]);
	printf("\n");
	return;
}

int main()
{
	MaxHeap *H;
	int x, n, max;
	H = CreateHeap();
	printf("Please input the data(input 0 to stop):\n");
	scanf("%d", &x);
	while( x ) {
		Add(H, x);
		scanf("%d", &x);
	}
	BuildMaxHeap(H);
	print(H);
	max = DeleteMax(H);
	printf("ɾ�������ֵΪ%d\n", max);
	print(H);
	Insert(H, 10);
	printf("������Ԫ�غ�:\n");
	print(H);
	printf("�������:\n");
	HeapSort(H, H->Size); 
	print(H);
	return 0;
}
