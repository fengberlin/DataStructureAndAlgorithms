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
	BinTree *data[MaxSize];		/* 堆栈中的元素为指向树结点的一个指针 */
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
	// 前序创建二叉树(递归实现)   在输入时要非常注意输入的格式
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
	// 前序遍历(非递归实现)
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
	// 中序遍历(非递归实现) 
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
	printf("请按前序建立二叉树的顺序输入树结点的数据:\n");
	BT = CreateBinTree();
	printf("前序遍历结果:\n");
	PreOrderTraversal( BT );
	printf("\n");
	printf("中序遍历结果:\n"); 
	InOrderTraversal(BT);
	return 0;
}
