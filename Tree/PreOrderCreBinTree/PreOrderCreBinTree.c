#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define Error NULL
typedef int ElementType;

typedef struct TreeNode {
	ElementType data;
	struct TreeNode *left;
	struct TreeNode *right;
}BinTree;

typedef struct {
	BinTree *data[MaxSize];		/* ��ջ�е�Ԫ��Ϊָ��������һ��ָ�� */
	int top;
}Stack;

Stack *InitStack() {
	Stack *PtrS = (Stack *)malloc(sizeof(Stack));
	if( PtrS != NULL ) {
		PtrS->top = -1;
	}
	return PtrS;
} 

int isFull(Stack *PtrS) {
	// Judge the stack is full or not
	return ( PtrS->top == MaxSize - 1 );
}

int isEmpty(Stack *PtrS) {
	// Judge the stack is empty or not
	return ( PtrS->top == -1 );
}

void Push(Stack *PtrS, BinTree *item) {
	// Push a item into the stack
	if( isFull(PtrS) ) {
		printf("The stack is full.");
		return;
	} else {
		PtrS->data[++(PtrS->top)] = item;
		return;
	}
}

BinTree *Pop(Stack *PtrS) {
	// Pop a item of the stack.
	if( isEmpty(PtrS) ) {
		printf("The stack is empty.");
		return Error;
	} else {
		return PtrS->data[(PtrS->top)--];
	}
}

BinTree *CreateBinTree() {
	// ǰ�򴴽�������(�ݹ�ʵ��)   ������ʱҪ�ǳ�ע������ĸ�ʽ
	BinTree *BT;
	ElementType data;
	scanf("%d", &data);
	if( !data ) {
		BT = NULL;
	} else {
		BT = (BinTree *)malloc(sizeof(BinTree));
		if( BT ) {
			BT->data = data;
			BT->left = CreateBinTree();
			BT->right = CreateBinTree();
		} else {
			return NULL;
		}
	}
	return BT;
}

void PreOrderTraversal(BinTree *BT) {
	// ǰ�����(�ǵݹ�ʵ��)
	Stack *PtrS = InitStack();
	BinTree *T;
	T = BT;
	while( T || !isEmpty(PtrS) ) {
		while( T ) {
			Push(PtrS, T);
			printf("%d ", T->data);
			T = T->left;
		}
		if( !isEmpty(PtrS) ) {
			T = Pop(PtrS);
			T = T->right;
		}
	}
	return;
}

void InOrderTraversal(BinTree *BT) {
	// �������(�ǵݹ�ʵ��) 
	Stack *PtrS = InitStack();
	BinTree *T;
	T = BT;
	while( T || !
	isEmpty(PtrS) ) {
		while( T ) {
			Push(PtrS, T);
			T = T->left;
		}
		if( !isEmpty(PtrS) ) {
			T = Pop(PtrS);
			printf("%d ", T->data);
			T = T->right;
		}
	}
	return;
}

int main()
{
	BinTree *BT;
	printf("�밴ǰ������������˳����������������:\n");
	BT = CreateBinTree();
	printf("ǰ��������:\n");
	PreOrderTraversal( BT );
	printf("\n");
	printf("����������:\n"); 
	InOrderTraversal(BT);
	return 0;
}
