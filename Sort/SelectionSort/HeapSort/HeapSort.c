#include <stdio.h>
#include <stdlib.h>
/* 堆排序 */
/* 数据结构	:数组 */
/*
稳定性：不稳定 
时间复杂度	O(n*log n)
最优时间复杂度	O(n*log n)
平均时间复杂度	O(n*log n)
空间复杂度	O(n) total
*/

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxSize 100
typedef int ElementType;

typedef struct heap{
	ElementType *data;		/* 存储堆元素的数组 */ 
	int Size;	/* 堆的元素个数 */
	int Capacity;	/* 堆的最大容量 */ 
}MaxHeap;

int isEmpty(MaxHeap *H) {	
	/* 判断堆是否为空 */
	return (H->Size == 0);
}

int isFull(MaxHeap *H) {	
	// 判断最大堆是否为满
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
		FatalError("堆已经满了"); 
	}
	H->Size++;
	int i;
	for(i=H->Size-1; i>=1&&H->data[(i-1)/2]<item; i=(i-1)/2) 
		H->data[i] = H->data[(i-1)/2];
	H->data[i] = item; 
	return;
}

void Add(MaxHeap *H, ElementType item) {	
	/* 往初始数组中添加元素 */
	if( isFull(H) )
		FatalError("the array is full");
	H->data[(H->Size)++] = item;
	return;
}

//void Adjust(MaxHeap *H, int Parent, int N)
//{	/* 对a[]中的前N个元素从i个元素开始向下迁移调整 */
//	int Child;
//	ElementType temp;
//	
//	for(temp=H->data[Parent]; ( Parent*2+1 )<N; Parent=Child)
//	{
//		Child = Parent*2 + 1;	/* 左孩子结点 */
//		if( (Child != N-1) && H->data[Child+1]>H->data[Child])	/* 此时N-1是最大值已经被排除出去了 */
//			Child++;	/* Child指向左右子结点的较大者 */
//		if( temp < H->data[Child] )
//			H->data[Parent] = H->data[Child];	/* 移动Child元素到上层 */
//		else break; 
//	} 
//	H->data[Parent] = temp;		/* 将temp放到当前位置 */
//	return;
//}

void Adjust(MaxHeap *H, int i, int N) {
	/* 对a[]中的前N个元素从i个元素开始向下迁移调整 */
	int Parent, Child;
	ElementType temp;
	temp = H->data[i];		// 临时记录H->data[i]的值 
	for(Parent=i; (Parent*2+1)<N; Parent=Child) {
		Child = Parent*2 + 1;	/* 左孩子结点 */
		if( (Child != N-1) && (H->data[Child+1]>H->data[Child]) ) 	/* 此时N-1是最大值已经被排除出去了 */
			Child++;	/* Child指向左右子结点的较大者 */
		if( temp < H->data[Child] ) 
			H->data[Parent] = H->data[Child];		/* 移动Child元素到上层 */
		else 
			break;
	}
	H->data[Parent] = temp;		/* 将temp放到当前位置 */
	return;
}

//void HeapSort(MaxHeap *H, int N)
//{	/* 堆排序 */
//	int i;
//	ElementType temp;
//	
//	/* 建立最大堆 */
//	for(i=(N-1)/2; i>=0; i--)	/* 从有儿子的最后一个结点开始(从最后一个结点的父结点开始) */
//		Adjust(H, i, N);
//	for(i=N-1; i>0; i--)
//	{
//		/* 将堆顶元素H->data[0]与当前堆的最后一个元素H->data[i]换位 */
//		temp = H->data[0];
//		H->data[0] = H->data[i];
//		H->data[i] = temp;
//		/* 将有i个元素的新堆从根结点向下过滤调整 */
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
	// 堆排序 
	int i;
	ElementType temp;
	for(i=N-1; i>0; i--) {
		/* 将堆顶元素H->data[0]与当前堆的最后一个元素H->data[i]换位 */
		temp = H->data[i];
		H->data[i] = H->data[0];
		H->data[0] = temp;
		/* 将有i个元素的新堆从根结点向下过滤调整 */
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
	printf("删除的最大值为%d\n", max);
	print(H);
	Insert(H, 10);
	printf("插入新元素后:\n");
	print(H);
	printf("堆排序后:\n");
	HeapSort(H, H->Size); 
	print(H);
	return 0;
}
