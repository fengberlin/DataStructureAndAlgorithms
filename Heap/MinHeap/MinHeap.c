#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define MaxData 10000 
typedef int ElementType;

typedef struct HeapStruct {
	ElementType *Elements;     // �洢��Ԫ�ص�����
	int Size;      // �ѵĵ�ǰԪ�ظ���
	int Capacity;      /* �ѵ��������(������MaxSize������ʱ, ����Ӧ�ý���MaxSize+1��Ԫ��
						  ��ΪҪ���������ʼ��ԪΪ1, Ԫ���Ǵ��ڵ�1~MaxSize����Ԫ��ļ�ÿ������Ҫ��MaxSize+1�����鵥Ԫ ) */
}MinHeap;

MinHeap *CreateHeap() {
	// �����յ���С�� 
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
	// �ж���С���Ƿ�Ϊ�� 
	return (H->Size == 0);
}

int isFull(MinHeap *H) {   
	// �ж���С���Ƿ�Ϊ�� 
	return (H->Size == MaxSize);
}

void Add(MinHeap *H, ElementType item) {
	// �����������Ԫ�� 
	if( isFull(H) ) {
		printf("��С������.\n");
		return;
	}
	H->Elements[++(H->Size)] = item;
	return;
}

void Insert(MinHeap *H, ElementType item) {
	// ��С�ѵĲ���
	int i;
	if( isFull(H) ) {
		printf("��С������!\n");
		return;
	}
	for(i=++(H->Size); H->Elements[i]>item; i/=2) {		// iָ��������е����һ��Ԫ�ص�λ��
		H->Elements[i] = H->Elements[i/2];
	}
	H->Elements[i] = item;
	return;
} 

ElementType DeleteMin(MinHeap *H) {
	// ��С�ѵ�ɾ��
	int Parent, Child;
	ElementType MinValue, temp;
	if( isEmpty(H) ) {
		printf("��С��Ϊ��.\n");
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
{	/* ������ν��"����", ��ָ��ν��Ѿ����ڵ�N��Ԫ�ذ���С�ѵ�Ҫ����� */
	/* �����������H->Size��Ԫ���Ѿ�����H->Elements[]�� */
	/* ��������H->Elements[]�е�Ԫ�ص���, ʹ��������С�ѵ�����Ե�����(�ֵܽ��֮�䲻���������Լ����ϵ) */
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
		printf("��С��Ϊ��.\n");
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
	printf("����������:\n");
	scanf("%d", &x);
	while( x ) {
		Add(heap, x);
		scanf("%d", &x);
	}
	printf("δ����ǰ:\n");
	print(heap);
	heap = BuildMinHeap(heap);
	printf("����Ϊ��ʱ:\n");
	print(heap);
	result = DeleteMin( heap );
	printf("ɾ����ֵΪ%d\n", result);
	printf("ɾ��һ��Ԫ�غ�Ķ�Ϊ:\n");
	print(heap);
	result = DeleteMin( heap );
	printf("ɾ����ֵΪ%d\n", result);
	Insert(heap, 8);
	printf("������ȫ����Ԫ��Ϊ:\n");
	print(heap);
	return 0;
}
