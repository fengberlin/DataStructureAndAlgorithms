#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define MaxData NULL

// Huffman tree�Ľ�����������С��ʱ��Ϊÿ�ζ�����������С������Ԫ�����

typedef struct TreeNode {
	int weight;
	struct TreeNode *left;
	struct TreeNode *right;
}HuffmanTree;

typedef struct HeapStruct {
	HuffmanTree *Elements[MaxSize+1];	// �洢��Ԫ�ص�����
	int Size;		// �ѵĵ�ǰԪ�ظ���
	int Capacity;	/* �ѵ��������(������MaxSize������ʱ, ����Ӧ�ý���MaxSize+1��Ԫ��
						��ΪҪ���������ʼ��ԪΪ1, Ԫ���Ǵ��ڵ�1~MaxSize����Ԫ��ļ�ÿ������Ҫ��MaxSize+1�����鵥Ԫ ) */
}MinHeap;

MinHeap *CreateHeap() {   
	// ����һ���յ���С��
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
	// �ж���С���Ƿ�Ϊ�� 
	return (H->Size == MaxSize);
}

int isEmpty(MinHeap *H) {	
	// �ж���С���Ƿ��ѿ� 
	return (H->Size == 0);
} 

void Add(MinHeap *H, int item) {   
	// ���������Ԫ�� 
	if( isFull(H) ) {
		printf("��С������.\n");
		return;
	}
	HuffmanTree *T;
	T = (HuffmanTree *)malloc(sizeof(HuffmanTree));
	T->weight = item;
	H->Elements[++(H->Size)] = T;
	return;
}

void Insert(MinHeap *H, HuffmanTree *item) {	
	// ��С�ѵĲ��� 
	int i;
	if( isFull(H) ) {
		printf("��С������.\n");
		return;
	}
	i = ++(H->Size);
	for(; (H->Elements[i/2]->weight)>(item->weight);i/=2)
		H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = item;
}

HuffmanTree *DeleteMin(MinHeap *H) {	
	// ��С�ѵ�ɾ�� 
	int Parent, Child;
	HuffmanTree *MinValueNode, *tempNode;
	if( isEmpty(H) ) {
		printf("��С��Ϊ��.\n");
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
	// ��С�ѵĵ���(������Ϊ��С�ѵ���̬) 
	int Parent, Child;
	HuffmanTree *temp;
	temp = H->Elements[i];
	for(Parent=i; Parent*2<=H->Size; Parent=Child) {
		Child = Parent * 2;
		if( (Child != H->Size) && (H->Elements[Child]->weight > H->Elements[Child+1]->weight) )
			Child++;      // Childָ�����ҽ��Ľ�С�� 
		if( temp->weight <= H->Elements[Child]->weight )     // �������С�ڵ����ӽ��
			break;
		else        // �ƶ�tempԪ�ص���һ��
			H->Elements[Parent] = H->Elements[Child];      
	}
	H->Elements[Parent] = temp;
}

void BuildMinHeap(MinHeap *H) {	
	// ��С�ѵĳ��� 
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
	// ʱ�临�Ӷȣ�O(NlogN)
	/* ����H->Size��Ȩֵ�Ѿ�����H->Elements[]->weight�� */
	int i;
	HuffmanTree *T;
	
	BuildMinHeap( H );     // ��H->Elements[]��Ȩֵ����Ϊ��С�� 
	for(i=1; i<H->Size; i++) {
		// ���ݹ���, Ҫ��H->Size-1�κϲ� 
		T = (HuffmanTree *)malloc(sizeof(HuffmanTree));      // ÿ�κϲ��ʹ���һ���µĸ����
		T->left = DeleteMin( H );      // ����С����ɾ��һ�����, ��Ϊ��T�����ӽ��
		T->right = DeleteMin( H );     // ����С����ɾ��һ�����, ��Ϊ��T�����ӽ�� 
		T->weight = T->left->weight + T->right->weight;      // ������Ȩֵ
		Insert(H, T); 
	}
	T = DeleteMin( H );
	return T;
}

void print_heap(MinHeap *H) {
	int i;
	if( isEmpty(H) ) {
		printf("��С��Ϊ��.\n");
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
	printf("����������:\n");
	scanf("%d", &x);
	while( x ) {
		Add(heap, x);
		scanf("%d", &x);
	}   
	printf("���ǳ�ʼ��Ԫ��:\n");
	print_heap( heap );
	printf("�ѵ�Ԫ�ظ���Ϊ%d\n", heap->Size);
	BuildMinHeap(heap);
	print_heap( heap );
//	heap = BuildMinHeap(heap); 
//	printf("����Ϊ��С�Ѻ�Ķ�Ԫ��:\n");
//	print_heap( heap );
//	printf("%d\n", heap->Size);
	HT = DeleteMin( heap );
	printf("ɾ���Ľ���ֵΪ%d\n", HT->weight);
	print_heap( heap );
	
//	T = (HuffmanTree *)malloc(sizeof(HuffmanTree));
//	T->weight = 9;
//	T->left = NULL;
//	T->right = NULL;
//	Insert(heap, T);
//	printf("����Ľ���ֵΪ%d\n", T->weight);
//	print_heap( heap );
//	HT = Huffman( heap );
//	print_heap( heap );
//	printf("%d\n", HT->weight);
//	printf("���Ƕ�Ԫ��:\n");
//	printf("������Ԫ��:\n");
//	print_tree( HT );
	return 0; 
}
