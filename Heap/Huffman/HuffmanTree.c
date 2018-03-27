#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define MaxData NULL

// Huffman tree的建树过程用最小堆时因为每次都可以挑出最小的两个元素组成

typedef struct TreeNode {
	int weight;
	struct TreeNode *left;
	struct TreeNode *right;
}HuffmanTree;

typedef struct HeapStruct {
	HuffmanTree *Elements[MaxSize+1];	// 存储堆元素的数组
	int Size;		// 堆的当前元素个数
	int Capacity;	/* 堆的最大容量(当根据MaxSize建立堆时, 我们应该建立MaxSize+1个元素
						因为要求的数组起始单元为1, 元素是存在第1~MaxSize个单元里的即每次我们要建MaxSize+1个数组单元 ) */
}MinHeap;

MinHeap *CreateHeap() {   
	// 创建一个空的最小堆
	MinHeap *H;
//	HuffmanTree *T;
	H = (MinHeap *)malloc(sizeof(MinHeap));
//	T = (HuffmanTree *)malloc(sizeof(HuffmanTree));
//	T->weight = 0;
	H->Elements[0] = NULL;
	H->Size = 0;
	H->Capacity = MaxSize;
	return H;
}

int isFull(MinHeap *H) {   
	// 判断最小堆是否为满 
	return (H->Size == MaxSize);
}

int isEmpty(MinHeap *H) {	
	// 判断最小堆是否已空 
	return (H->Size == 0);
} 

void Add(MinHeap *H, int item) {   
	// 往堆上添加元素 
	if( isFull(H) ) {
		printf("最小堆已满.\n");
		return;
	}
	HuffmanTree *T;
	T = (HuffmanTree *)malloc(sizeof(HuffmanTree));
	T->weight = item;
	H->Elements[++(H->Size)] = T;
	return;
}

void Insert(MinHeap *H, HuffmanTree *item) {	
	// 最小堆的插入 
	int i;
	if( isFull(H) ) {
		printf("最小堆已满.\n");
		return;
	}
	i = ++(H->Size);
	for(; (H->Elements[i/2]->weight)>(item->weight);i/=2)
		H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = item;
}

HuffmanTree *DeleteMin(MinHeap *H) {	
	// 最小堆的删除 
	int Parent, Child;
	HuffmanTree *MinValueNode, *tempNode;
	if( isEmpty(H) ) {
		printf("最小堆为空.\n");
		return NULL;
	}
	MinValueNode = H->Elements[1];
	tempNode = H->Elements[H->Size--];
	for(Parent=1; Parent*2<=H->Size; Parent=Child) {
		Child = Parent * 2;
		if( (Child != H->Size) && (H->Elements[Child]->weight > H->Elements[Child+1]->weight) )
			Child++;
		if( tempNode->weight <= H->Elements[Child]->weight )
			break;
		else 
			H->Elements[Parent] = H->Elements[Child];
	} 
	H->Elements[Parent] = tempNode;
	return MinValueNode; 
}

void PercDown(MinHeap *H, int i) {	
	// 最小堆的调整(即调整为最小堆的形态) 
	int Parent, Child;
	HuffmanTree *temp;
	temp = H->Elements[i];
	for(Parent=i; Parent*2<=H->Size; Parent=Child) {
		Child = Parent * 2;
		if( (Child != H->Size) && (H->Elements[Child]->weight > H->Elements[Child+1]->weight) )
			Child++;      // Child指向左右结点的较小者 
		if( temp->weight <= H->Elements[Child]->weight )     // 若父结点小于等于子结点
			break;
		else        // 移动temp元素到下一层
			H->Elements[Parent] = H->Elements[Child];      
	}
	H->Elements[Parent] = temp;
}

void BuildMinHeap(MinHeap *H) {	
	// 最小堆的成型 
	int i;
	for(i=H->Size/2; i>0; i--)
		PercDown(H, i);
	return;
}

//MinHeap *BuildMinHeap(MinHeap *H)
//{
//	int Parent, Child, i;
//	HuffmanTree *tempNode;
//	for(i=H->Size/2; i>0; i--)
//	{
//		tempNode = H->Elements[i];
//		for(Parent=i; Parent*2<=H->Size; Parent=Child)
//		{
//			Child = Parent * 2;
//			if( (Child != H->Size) && (H->Elements[Child]->weight > H->Elements[Child+1]->weight))
//				Child++;
//			if( tempNode->weight <= H->Elements[Child]->weight)
//				break;
//			else 
//				H->Elements[Parent] = H->Elements[Child];
//		}
//		H->Elements[Parent] = tempNode;
//	}
//	return H;
//}

HuffmanTree *Huffman(MinHeap *H) {	
	// 时间复杂度：O(NlogN)
	/* 假设H->Size个权值已经存在H->Elements[]->weight里 */
	int i;
	HuffmanTree *T;
	
	BuildMinHeap( H );     // 将H->Elements[]按权值调整为最小堆 
	for(i=1; i<H->Size; i++) {
		// 根据规律, 要做H->Size-1次合并 
		T = (HuffmanTree *)malloc(sizeof(HuffmanTree));      // 每次合并就创建一个新的根结点
		T->left = DeleteMin( H );      // 从最小堆中删除一个结点, 作为新T的左子结点
		T->right = DeleteMin( H );     // 从最小堆中删除一个结点, 作为新T的右子结点 
		T->weight = T->left->weight + T->right->weight;      // 计算新权值
		Insert(H, T); 
	}
	T = DeleteMin( H );
	return T;
}

void print_heap(MinHeap *H) {
	int i;
	if( isEmpty(H) ) {
		printf("最小堆为空.\n");
		return;
	}
	for(i=1; i<=H->Size; i++)
		printf("%d   ", H->Elements[i]->weight);
	printf("\n");
} 

void print_tree(HuffmanTree *T) {
	if( T ) {
		print_tree(T->left);
		printf("%d ", T->weight);
		print_tree(T->right);
	}
	return;
}

int main()
{
	MinHeap *heap;
	HuffmanTree *HT, *T;
	heap = CreateHeap();
	int x;
	printf("请输入数据:\n");
	scanf("%d", &x);
	while( x ) {
		Add(heap, x);
		scanf("%d", &x);
	}   
	printf("这是初始堆元素:\n");
	print_heap( heap );
	printf("堆的元素个数为%d\n", heap->Size);
	BuildMinHeap(heap);
	print_heap( heap );
//	heap = BuildMinHeap(heap); 
//	printf("调整为最小堆后的堆元素:\n");
//	print_heap( heap );
//	printf("%d\n", heap->Size);
	HT = DeleteMin( heap );
	printf("删除的结点的值为%d\n", HT->weight);
	print_heap( heap );
	
//	T = (HuffmanTree *)malloc(sizeof(HuffmanTree));
//	T->weight = 9;
//	T->left = NULL;
//	T->right = NULL;
//	Insert(heap, T);
//	printf("插入的结点的值为%d\n", T->weight);
//	print_heap( heap );
//	HT = Huffman( heap );
//	print_heap( heap );
//	printf("%d\n", HT->weight);
//	printf("这是堆元素:\n");
//	printf("这是树元素:\n");
//	print_tree( HT );
	return 0; 
}
