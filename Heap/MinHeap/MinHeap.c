#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define MaxData 10000 
typedef int ElementType;

typedef struct HeapStruct {
	ElementType *Elements;     // 存储堆元素的数组
	int Size;      // 堆的当前元素个数
	int Capacity;      /* 堆的最大容量(当根据MaxSize建立堆时, 我们应该建立MaxSize+1个元素
						  因为要求的数组起始单元为1, 元素是存在第1~MaxSize个单元里的即每次我们要建MaxSize+1个数组单元 ) */
}MinHeap;

MinHeap *CreateHeap() {
	// 构建空的最小堆 
	MinHeap *H = (MinHeap *)malloc(sizeof(MinHeap));
	if( H ) {
		H->Elements = (ElementType *)malloc( sizeof(ElementType) * (MaxSize+1) );
		H->Size = 0;
		H->Capacity = MaxSize;
		H->Elements[0] = MaxData;
	}
	return H; 
}

int isEmpty(MinHeap *H) {   
	// 判断最小堆是否为空 
	return (H->Size == 0);
}

int isFull(MinHeap *H) {   
	// 判断最小堆是否为满 
	return (H->Size == MaxSize);
}

void Add(MinHeap *H, ElementType item) {
	// 向数组中添加元素 
	if( isFull(H) ) {
		printf("最小堆已满.\n");
		return;
	}
	H->Elements[++(H->Size)] = item;
	return;
}

void Insert(MinHeap *H, ElementType item) {
	// 最小堆的插入
	int i;
	if( isFull(H) ) {
		printf("最小堆已满!\n");
		return;
	}
	for(i=++(H->Size); H->Elements[i]>item; i/=2) {		// i指向插入后堆中的最后一个元素的位置
		H->Elements[i] = H->Elements[i/2];
	}
	H->Elements[i] = item;
	return;
} 

ElementType DeleteMin(MinHeap *H) {
	// 最小堆的删除
	int Parent, Child;
	ElementType MinValue, temp;
	if( isEmpty(H) ) {
		printf("最小堆为空.\n");
		return -1;
	}
	MinValue = H->Elements[1];
	temp = H->Elements[H->Size--];
	for(Parent=1; Parent*2<=H->Size; Parent=Child) {
		Child = Parent * 2;
		if( (Child != H->Size) && (H->Elements[Child] > H->Elements[Child+1]) )
			Child++;
		if( temp <= H->Elements[Child] ) 
			break;
		else
			H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;
	return MinValue;
}

MinHeap *BuildMinHeap(MinHeap *H)
{	/* 这里所谓的"建立", 是指如何将已经存在的N个元素按最小堆的要求调整 */
	/* 这里假设所有H->Size个元素已经存在H->Elements[]中 */
	/* 本函数将H->Elements[]中的元素调整, 使其满足最小堆的有相对的序性(兄弟结点之间不存在特殊的约束关系) */
	int Parent, Child, i;
	ElementType temp;
	
	for(i=H->Size/2; i>0; i--) {
		temp = H->Elements[i];
		for(Parent=i; Parent*2<=H->Size; Parent=Child) {
			Child = Parent * 2;
			if( (Child != H->Size) && (H->Elements[Child] > H->Elements[Child+1]) )
				Child++;
			if( temp <= H->Elements[Child] )
				break;
			else
				H->Elements[Parent] = H->Elements[Child];
		}
		H->Elements[Parent] = temp;
	}
	return H;
}

void print(MinHeap *H) {
	int i;
	if( isEmpty(H) ) {
		printf("最小堆为空.\n");
		return; 
	}
	for(i=1; i<=H->Size; i++)
		printf("%d   ", H->Elements[i]);
	printf("\n");
}

int main()
{
	MinHeap *heap;
	int x, result;
	heap = CreateHeap();
	printf("请输入数据:\n");
	scanf("%d", &x);
	while( x ) {
		Add(heap, x);
		scanf("%d", &x);
	}
	printf("未调整前:\n");
	print(heap);
	heap = BuildMinHeap(heap);
	printf("调整为堆时:\n");
	print(heap);
	result = DeleteMin( heap );
	printf("删除的值为%d\n", result);
	printf("删除一个元素后的堆为:\n");
	print(heap);
	result = DeleteMin( heap );
	printf("删除的值为%d\n", result);
	Insert(heap, 8);
	printf("插入后的全部堆元素为:\n");
	print(heap);
	return 0;
}
