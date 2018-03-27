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
	// 前序遍历(非递归实现)
	Stack *PtrS = InitStack();		// 初始化一个堆栈 
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
	//递归查找元素 
	// 在最好的情况下，时间复杂度为O(logN)，最坏的情况下，时间复杂度为O(N) 
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
//	// 非递归查找元素 
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
	// 查找最小结点(递归查找)
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
//	// 查找最小结点(非递归查找)
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
	// 查找最大结点(递归查找)
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
//	// 查找最小结点(非递归查找)
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
	// 二叉树搜索树的插入 
	// 时间复杂度为O(logN) 
	if( BST ) {		// 开始找要插入元素的位置 
		if( data < BST->data ) {	// 递归插入左子树 
			BST->left = Insert(BST->left, data);
		} else if( data >BST->data ) {		// 递归插入右子树 
			BST->right = Insert(BST->right, data);
		}
		/* else x已经存在, 则什么都不做 */	
	} else {	// 原树为空, 生成并返回一个结点的二叉搜索树 
		BST = (BinTree *)malloc(sizeof(BinTree));
		BST->data = data;
		BST->left = BST->right = NULL;
	}
	return BST;
}

BinTree *Delete(BinTree *BST, ElementType data) {
	// 删除一个结点
	// 时间复杂度为O(logN) 
	Position *tmp;
	if( !BST ) {
		printf("这是一棵空树!\n");
	} else {
		if( data < BST->data ) {
			BST->left = Delete(BST->left, data);	// 左子树递归删除
		} else if( data >BST->data ) {
			BST->right = Delete(BST->right, data);		// 右子树递归删除
		} else {	// 找到要删除的结点 BST->data == data 
			if( BST->left && BST->right ) {		// 被删除的结点有左、右两个子结点(这里有两种选择: 一是找左子树的最大值, 一是找右子树的最小值)
				tmp = FindMin(BST->right);		// 寻找右子树的最小的元素填充删除结点
				BST->data = tmp->data;
				BST->right = Delete(BST->right, BST->data);		// 在删除结点的右子树中删除最小元素并返回被删除的树
			} else {	// 被删除结点有一个或无结点
				tmp = BST;
				if( !BST->left ) {		// 有右孩子或无结点
					BST = BST->right;
				} else if( !BST->right ) {		// 有左孩子或无结点
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
