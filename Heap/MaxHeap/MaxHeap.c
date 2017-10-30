#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define MaxData 10000
typedef int ElementType; 

typedef struct HeapStruct {
	ElementType *Elements;		// 存储堆元素的数组
	int Size;	// 堆的当前元素个数	
	int Capacity;		/* 堆的最大容量(当根据MaxSize建立堆时, 我们应该建立MaxSize+1个元素
						因为要求的数组起始单元为1, 元素是存在第1~MaxSize个单元里的即每次我们要建MaxSize+1个数组单元 ) */
}MaxHeap;

int isFull(MaxHeap *H) {   
	// 判断最大堆是否已满 
	return (H->Size == MaxSize);
} 

int isEmpty(MaxHeap *H) {
	// 判断最大堆是否为空 
	return (H->Size == 0);
}

MaxHeap *CreateHeap() {
	// 创建容量为MaxSize的空的最大堆
	MaxHeap *H = (MaxHeap *)malloc(sizeof(MaxHeap));
	if( H ) {
		H->Size = 0;
		H->Elements = (ElementType *)malloc(sizeof(ElementType) * (MaxSize+1));
		H->Capacity = MaxSize;
		H->Elements[0] = MaxData;	// 定义"哨兵"为大于堆中所有可能元素的值(此单元不属于堆)
	} 
	return H;
} 

void Add(MaxHeap *H, ElementType item) {
	// 向数组中添加元素
	if( isFull(H) ) {
		printf("It is full!\n");
		return;
	} else {
		H->Elements[++(H->Size)] = item;
		return;
	}
}

void Insert(MaxHeap *H, ElementType item) {
	/* 将元素item插入最大堆H, 其中H->Elements[0]已经定义为哨兵 */
	if( isFull(H) ) {
		printf("It is full!\n");
		return;
	} else {
		int i;
		for(i=++(H->Size); H->Elements[i/2]<item; i/=2) {	// 一开始i指向插入后堆中的最后一个元素的位置
			H->Elements[i] = H->Elements[i/2];		// 向下过滤上层结点
		}
		H->Elements[i] = item;		// 将item插入
		return;
	}
}

ElementType DeleteMax(MaxHeap *H) {
	/* 从最大堆H中取出键值为最大的元素, 并删除一个结点 */
	int Parent, Child;
	ElementType MaxValue, temp;
	if( isEmpty(H) ) {
		printf("最大堆为空.\n");
		exit(-1);
	}
	MaxValue = H->Elements[1];
	temp = H->Elements[(H->Size)--];
	for(Parent=1; Parent*2<=H->Size; Parent=Child) {	/* 用最大堆中最后一个元素从根结点开始向上过滤下层结点 */
		// 对于下标为i的结点, 其父结点为(int)(i/2), 其左右结点分别为2i和2i+1
		Child = Parent * 2;
		if( (Child != H->Size) && (H->Elements[Child] < H->Elements[Child+1]) )		// Child != H->Size这个条件保证H->Elements[Child+1]有效, 不会越界
			Child++;		// Child指向左右子结点的较大者
		if( temp >= H->Elements[Child] )
			break;
		else 
			H->Elements[Parent] = H->Elements[Child];	// 移动temp元素到下一层
	}
	H->Elements[Parent] = temp;
	return MaxValue;
} 

//void PercDown(MaxHeap *H, int p) {
//	/* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
//	int Parent, Child;
//	ElementType temp;
//	temp = H->Elements[p];
//	for(Parent=p; Parent*2<=H->Size; Parent=Child) {
//		Child = Parent * 2;
//		if( (Child != H->Size ) && (H->Elements[Child] < H->Elements[Child+1]) )
//			Child++;
//		if( temp >= H->Elements[Child] ) 
//			break;
//		else 
//			H->Elements[Parent] = H->Elements[Child];
//	}
//	H->Elements[Parent] = temp;
//}

//void BuildMaxHeap(MaxHeap *H) {
//	/* 这里所谓的"建立", 是指如何将已经存在的N个元素按最大堆的要求调整 */
//	/* 这里假设所有H->Size个元素已经存在H->Elements[]中 */
//	/* 本函数将H->Elements[]中的元素调整, 使其满足最大堆的有相对的序性(兄弟结点之间不存在特殊的约束关系) */
//	int i;
//	for(i=H->Size/2; i>0; i--) {
//		PercDown(H, i);
//	}
//	return;
//}

MaxHeap *BuildMaxHeap(MaxHeap *H) {
	/* 这里所谓的"建立", 是指如何将已经存在的N个元素按最大堆的要求调整 */
	/* 这里假设所有H->Size个元素已经存在H->Elements[]中 */
	/* 本函数将H->Elements[]中的元素调整, 使其满足最大堆的有相对的序性(兄弟结点之间不存在特殊的约束关系) */
	int i, Parent, Child;
	ElementType temp;
	for(i=H->Size/2; i>0; i--) {	// 从最后一个结点的父结点开始
		temp = H->Elements[i];
		for(Parent=i; Parent*2<=H->Size; Parent=Child) {	// 对于下标为i的结点, 其父结点为(int)(i/2), 其左右结点分别为2i和2i+1
			Child = Parent * 2;
			if( (Child != H->Size) && (H->Elements[Child] < H->Elements[Child+1]) ) 
				Child++;
			if( temp >= H->Elements[Child] ) 
				break;
			else
				H->Elements[Parent] = H->Elements[Child];	
		}
		/* 结束内部for循环对以H->Elements[i]为根的子树的调整 */
		H->Elements[Parent] = temp;
	}
	return H;
}

void print(MaxHeap *H) {
	int i;
	if( isEmpty(H) ) {
		printf("最大堆为空.\n");
		return;
	}
	for(i=1; i<=H->Size; i++)
		printf("%d   ", H->Elements[i]);
	printf("\n");
	return;
}

int main()
{
	MaxHeap *heap;
	int x, result;
	heap = CreateHeap();
	printf("请输入数据:\n");
	scanf("%d", &x);
	while( x ) {
		Add(heap, x);
		scanf("%d", &x);
	} 
	print(heap);
	heap = BuildMaxHeap(heap);
	print(heap);
	result = DeleteMax( heap );
	printf("删除的值为%d\n", result);
	print(heap);
	Insert(heap, 10);
	print(heap);
	return 0;
}


