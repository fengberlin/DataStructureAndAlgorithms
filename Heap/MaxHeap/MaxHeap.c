#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define MaxData 10000
typedef int ElementType; 

typedef struct HeapStruct {
	ElementType *Elements;		// �洢��Ԫ�ص�����
	int Size;	// �ѵĵ�ǰԪ�ظ���	
	int Capacity;		/* �ѵ��������(������MaxSize������ʱ, ����Ӧ�ý���MaxSize+1��Ԫ��
						��ΪҪ���������ʼ��ԪΪ1, Ԫ���Ǵ��ڵ�1~MaxSize����Ԫ��ļ�ÿ������Ҫ��MaxSize+1�����鵥Ԫ ) */
}MaxHeap;

int isFull(MaxHeap *H) {   
	// �ж������Ƿ����� 
	return (H->Size == MaxSize);
} 

int isEmpty(MaxHeap *H) {
	// �ж������Ƿ�Ϊ�� 
	return (H->Size == 0);
}

MaxHeap *CreateHeap() {
	// ��������ΪMaxSize�Ŀյ�����
	MaxHeap *H = (MaxHeap *)malloc(sizeof(MaxHeap));
	if( H ) {
		H->Size = 0;
		H->Elements = (ElementType *)malloc(sizeof(ElementType) * (MaxSize+1));
		H->Capacity = MaxSize;
		H->Elements[0] = MaxData;	// ����"�ڱ�"Ϊ���ڶ������п���Ԫ�ص�ֵ(�˵�Ԫ�����ڶ�)
	} 
	return H;
} 

void Add(MaxHeap *H, ElementType item) {
	// �����������Ԫ��
	if( isFull(H) ) {
		printf("It is full!\n");
		return;
	} else {
		H->Elements[++(H->Size)] = item;
		return;
	}
}

void Insert(MaxHeap *H, ElementType item) {
	/* ��Ԫ��item��������H, ����H->Elements[0]�Ѿ�����Ϊ�ڱ� */
	if( isFull(H) ) {
		printf("It is full!\n");
		return;
	} else {
		int i;
		for(i=++(H->Size); H->Elements[i/2]<item; i/=2) {	// һ��ʼiָ��������е����һ��Ԫ�ص�λ��
			H->Elements[i] = H->Elements[i/2];		// ���¹����ϲ���
		}
		H->Elements[i] = item;		// ��item����
		return;
	}
}

ElementType DeleteMax(MaxHeap *H) {
	/* ������H��ȡ����ֵΪ����Ԫ��, ��ɾ��һ����� */
	int Parent, Child;
	ElementType MaxValue, temp;
	if( isEmpty(H) ) {
		printf("����Ϊ��.\n");
		exit(-1);
	}
	MaxValue = H->Elements[1];
	temp = H->Elements[(H->Size)--];
	for(Parent=1; Parent*2<=H->Size; Parent=Child) {	/* �����������һ��Ԫ�شӸ���㿪ʼ���Ϲ����²��� */
		// �����±�Ϊi�Ľ��, �丸���Ϊ(int)(i/2), �����ҽ��ֱ�Ϊ2i��2i+1
		Child = Parent * 2;
		if( (Child != H->Size) && (H->Elements[Child] < H->Elements[Child+1]) )		// Child != H->Size���������֤H->Elements[Child+1]��Ч, ����Խ��
			Child++;		// Childָ�������ӽ��Ľϴ���
		if( temp >= H->Elements[Child] )
			break;
		else 
			H->Elements[Parent] = H->Elements[Child];	// �ƶ�tempԪ�ص���һ��
	}
	H->Elements[Parent] = temp;
	return MaxValue;
} 

//void PercDown(MaxHeap *H, int p) {
//	/* ���ˣ���H����H->Data[p]Ϊ�����Ӷѵ���Ϊ���� */
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
//	/* ������ν��"����", ��ָ��ν��Ѿ����ڵ�N��Ԫ�ذ����ѵ�Ҫ����� */
//	/* �����������H->Size��Ԫ���Ѿ�����H->Elements[]�� */
//	/* ��������H->Elements[]�е�Ԫ�ص���, ʹ���������ѵ�����Ե�����(�ֵܽ��֮�䲻���������Լ����ϵ) */
//	int i;
//	for(i=H->Size/2; i>0; i--) {
//		PercDown(H, i);
//	}
//	return;
//}

MaxHeap *BuildMaxHeap(MaxHeap *H) {
	/* ������ν��"����", ��ָ��ν��Ѿ����ڵ�N��Ԫ�ذ����ѵ�Ҫ����� */
	/* �����������H->Size��Ԫ���Ѿ�����H->Elements[]�� */
	/* ��������H->Elements[]�е�Ԫ�ص���, ʹ���������ѵ�����Ե�����(�ֵܽ��֮�䲻���������Լ����ϵ) */
	int i, Parent, Child;
	ElementType temp;
	for(i=H->Size/2; i>0; i--) {	// �����һ�����ĸ���㿪ʼ
		temp = H->Elements[i];
		for(Parent=i; Parent*2<=H->Size; Parent=Child) {	// �����±�Ϊi�Ľ��, �丸���Ϊ(int)(i/2), �����ҽ��ֱ�Ϊ2i��2i+1
			Child = Parent * 2;
			if( (Child != H->Size) && (H->Elements[Child] < H->Elements[Child+1]) ) 
				Child++;
			if( temp >= H->Elements[Child] ) 
				break;
			else
				H->Elements[Parent] = H->Elements[Child];	
		}
		/* �����ڲ�forѭ������H->Elements[i]Ϊ���������ĵ��� */
		H->Elements[Parent] = temp;
	}
	return H;
}

void print(MaxHeap *H) {
	int i;
	if( isEmpty(H) ) {
		printf("����Ϊ��.\n");
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
	printf("����������:\n");
	scanf("%d", &x);
	while( x ) {
		Add(heap, x);
		scanf("%d", &x);
	} 
	print(heap);
	heap = BuildMaxHeap(heap);
	print(heap);
	result = DeleteMax( heap );
	printf("ɾ����ֵΪ%d\n", result);
	print(heap);
	Insert(heap, 10);
	print(heap);
	return 0;
}


