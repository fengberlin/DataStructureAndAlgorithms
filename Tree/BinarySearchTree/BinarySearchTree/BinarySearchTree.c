#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define Error NULL
#define Position BinTree
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
	BinTree *BST;
	ElementType data;
	scanf("%d", &data);
	if( !data ) {
		BST = NULL;
	} else {
		BST = (BinTree *)malloc(sizeof(BinTree));
		if( BST ) {
			BST->data = data;
			BST->left = CreateBinTree();
			BST->right = CreateBinTree();
		}
	}
	return BST;
}

void PreOrderTraversal(BinTree *BST) {
	// ǰ�����(�ǵݹ�ʵ��)
	Stack *PtrS = InitStack();		// ��ʼ��һ����ջ 
	BinTree *T;
	T = BST;
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

Position *Find(BinTree *BST, ElementType data) {
	//�ݹ����Ԫ�� 
	// ����õ�����£�ʱ�临�Ӷ�ΪO(logN)���������£�ʱ�临�Ӷ�ΪO(N) 
	if( BST ) {
		if( data < BST->data ) {
			return Find(BST->left, data);
		} else if( data > BST->data ){
			return Find(BST->right, data);
		} else {
			return BST;
		}
	} else {
		return NULL;
	}
}

//Position *IterFind(BinTree *BST, ElementType data) {
//	// �ǵݹ����Ԫ�� 
//	while( BST ) {
//		if( data < BST->data ) {
//			BST = BST->left;
//		} else if( data > BST->right){
//			BST = BST->right;
//		} else {
//			return BST;
//		}
//	}
//	return NULL;
//}

Position *FindMin(BinTree *BST) {
	// ������С���(�ݹ����)
	if( BST ) {
		if( !BST->left ) {
			return BST;
		} else {
			return FindMin(BST->left);
		}
	} else {
		return NULL;
	}
}

//Position *FindMin(BinTree *BST) {
//	// ������С���(�ǵݹ����)
//	while( BST ) {
//		if( BST->left ) {
//			BST = BST->left
//		} else {
//			return BST;
//		}
//	}
//	return NULL;
//}

Position *FindMax(BinTree *BST) {
	// ���������(�ݹ����)
	if( BST ) {
		if( BST->right ) {
			return FindMax(BST->right);
		} else {
			return BST;
		}
	} else {
		return NULL;
	}
} 

//Position *FindMax(BinTree *BST) {
//	// ������С���(�ǵݹ����)
//	while( BST ) {
//		if( BST->right ) {
//			BST = BST->right;
//		} else {
//			return BST;
//		}
//	} 
//	return NULL;
//}

BinTree *Insert(BinTree *BST, ElementType data) {
	// �������������Ĳ��� 
	// ʱ�临�Ӷ�ΪO(logN) 
	if( BST ) {		// ��ʼ��Ҫ����Ԫ�ص�λ�� 
		if( data < BST->data ) {	// �ݹ���������� 
			BST->left = Insert(BST->left, data);
		} else if( data >BST->data ) {		// �ݹ���������� 
			BST->right = Insert(BST->right, data);
		}
		/* else x�Ѿ�����, ��ʲô������ */	
	} else {	// ԭ��Ϊ��, ���ɲ�����һ�����Ķ��������� 
		BST = (BinTree *)malloc(sizeof(BinTree));
		BST->data = data;
		BST->left = BST->right = NULL;
	}
	return BST;
}

BinTree *Delete(BinTree *BST, ElementType data) {
	// ɾ��һ�����
	// ʱ�临�Ӷ�ΪO(logN) 
	Position *tmp;
	if( !BST ) {
		printf("����һ�ÿ���!\n");
	} else {
		if( data < BST->data ) {
			BST->left = Delete(BST->left, data);	// �������ݹ�ɾ��
		} else if( data >BST->data ) {
			BST->right = Delete(BST->right, data);		// �������ݹ�ɾ��
		} else {	// �ҵ�Ҫɾ���Ľ�� BST->data == data 
			if( BST->left && BST->right ) {		// ��ɾ���Ľ�������������ӽ��(����������ѡ��: һ���������������ֵ, һ��������������Сֵ)
				tmp = FindMin(BST->right);		// Ѱ������������С��Ԫ�����ɾ�����
				BST->data = tmp->data;
				BST->right = Delete(BST->right, BST->data);		// ��ɾ��������������ɾ����СԪ�ز����ر�ɾ������
			} else {	// ��ɾ�������һ�����޽��
				tmp = BST;
				if( !BST->left ) {		// ���Һ��ӻ��޽��
					BST = BST->right;
				} else if( !BST->right ) {		// �����ӻ��޽��
					BST = BST->left;
				} 
				free(tmp);
			}
		}
	}
	return BST;
}

int main()
{
	ElementType x;
	BinTree	*BT;
	Position *destination;
	BinTree *del;
	BT = CreateBinTree();
	printf("This traversal is PreOrderTraversal:\n");
	PreOrderTraversal( BT );
	printf("\n");
	printf("Please input the data that you want to find: ");
	scanf("%d", &x);
	destination = Find(BT, x);
	printf("result = %d\n", destination->data);
	destination = FindMax( BT );
	printf("The max data is %d.\n", destination->data);
	destination = FindMin( BT );
	printf("The min data is %d.\n", destination->data);
	printf("Please input the data that you want to delete: ");
	scanf("%d", &x);
	del = Delete(BT, x);
	printf("This traversal is PreOrderTraversal:\n");
	PreOrderTraversal( del );
	printf("\n");
	return 0;
}
