#include <stdio.h>
#include <stdlib.h>
#define Error 65535
typedef int ElementType;

typedef struct AVLTreeNode {
	ElementType data;
	struct AVLTreeNode *left;
	struct AVLTreeNode *right;
	int height;		// 以该结点为根的子树的高度 
}AVLTree; 

typedef struct node {	/* the node of the queue */
	AVLTree *data;
	struct node *next;
}QNode; 

typedef struct {	/* the structure of the queue */
	QNode *front;	/* point to the head of the queue */
	QNode *rear;	/* point to the tail of the queue */
}LinkQueue;

int isEmpty(LinkQueue *PtrQ) {  // 判断队列是否为空 
	return ( NULL == PtrQ->front );
}

QNode *InitNode() {
	QNode *p = (QNode *)malloc(sizeof(QNode));
	if ( !p ) {
		printf("Failed to allocate the memory!\n");
		exit(-1);
	} else {
		p->next = NULL;
		return p;
	}
}

LinkQueue *InitQueue() {
	/* Initialize an empty queue */ 
	LinkQueue *PtrQ = (LinkQueue *)malloc(sizeof(LinkQueue));
	if ( !PtrQ ) {
		printf("Failed to allocate the memory!\n");
		exit(-1);
	} else {
		PtrQ->front = PtrQ->rear = NULL;
		return PtrQ;
	}
}

void AddQ(LinkQueue *PtrQ, AVLTree *item) {
	/* add an element to the queue */
	QNode *p = InitNode();
	p->data = item;
	if ( NULL == PtrQ->front ) {	/* if the queue has no node */
		PtrQ->front = PtrQ->rear = p;
	} else {
		PtrQ->rear->next = p;
		PtrQ->rear = p;
	}
	return;
}

AVLTree *DeleteQ(LinkQueue *PtrQ) {
	/* delete a node from the queue */
	if( isEmpty(PtrQ) ) {
		printf("the queue is empty!\n");
		return NULL;
	}
	QNode *del = PtrQ->front;	/* delete the node pinted by the front pointer */
	AVLTree *result = del->data;
	if ( PtrQ->front == PtrQ->rear ) {	/* if the queue has only one node */
		PtrQ->front = PtrQ->rear = NULL;
	} else {
		PtrQ->front = PtrQ->front->next;
	}
	free( del );
	return result;
}

AVLTree *PreOrderCreBinTree() {
	// 先序创建平衡二叉树(递归实现)
	AVLTree *BT;
	ElementType data;
	scanf("%d", &data);
	if( data ) {	/* 在这里假设data是不为0的数 */
		BT = (AVLTree *)malloc(sizeof(AVLTree));
		if( BT ) {
			BT->data = data;
			BT->left = PreOrderCreBinTree();
			BT->right = PreOrderCreBinTree();
		}
	} else {
		BT = NULL;
	}
	return BT;
}

void PreOrderTraversal(AVLTree *BT) {  
	// 前序遍历(递归实现) 
	if( BT ) {
		printf("%d ", BT->data);
		PreOrderTraversal( BT->left );
		PreOrderTraversal( BT->right );
	}
	return;
}

int GetHeight(AVLTree *T) {
	// 计算树的高度 
	int HL, HR, MaxH;
	if( T ) {
		HL = GetHeight( T->left );
		HR = GetHeight( T->right );
		MaxH = HL > HR ? HL : HR;
		return ( MaxH + 1 );
	}
	else { 
		return 0;
	} 
}

int Max(int Height1, int Height2) { 
	// 计算两棵子树的最大值 
	return ( Height1 > Height2 ? Height1 : Height2 );
}

AVLTree *SingleLeftRotation(AVLTree *A) {	/* 左单旋 */
	// 注意: A必须有一个左子结点B
   // 将A与B作左单旋, 更新A与B的高度, 并返回新的根结点B
   AVLTree *B = A->left;
   A->left = B->right;
   B->right = A;
   A->height = Max( GetHeight(A->left), GetHeight(A->right) ) + 1;
   B->height = Max( GetHeight(B->left), A->height ) + 1;
   return B;
}

AVLTree *SingleRightRotation(AVLTree *A) {		/* 右单旋 */
	// 注意: A必须有一个右子结点B
   // 将A与B作右单旋, 更新A与B的高度, 并返回新的根结点B
   AVLTree *B = A->right;
   A->right = B->left;
   B->left = A;
   A->height = Max( GetHeight(A->left), GetHeight(A->right) ) + 1;
   B->height = Max( GetHeight(B->left), A->height ) + 1;
   return B;
}

AVLTree *DoubleLeftRightRotation(AVLTree *A) {  /* 左-右双旋 */
	// 注意: A必须有一个左子结点B, 且B必须有一个右子结点C
	// 将A、B与C作两次单旋, 返回新的根结点C
	A->left = SingleRightRotation( A->left );     // 将B与C作右单旋, C被返回 
	return SingleLeftRotation( A );    // 将A与C作左单旋, C被返回 
}

AVLTree *DoubleRightLeftRotation(AVLTree *A) {  /* 右-左双旋 */
	// 注意: A必须有一个右子结点B, 且B必须有一个左子结点C
	// 将A、B与C作两次单旋, 返回新的根结点C
	A->right = SingleLeftRotation( A->right ); 
	return SingleRightRotation( A );
}

AVLTree *AVL_Insertion(AVLTree *T, ElementType data) {
	// 将data插入AVL树T中, 并且返回调整后的AVL树 
	if( !T ) {		/* 若插入空树即T为空, 则新建包含一个结点的树 */
		T = (AVLTree *)malloc(sizeof(AVLTree));
		T->data = data;
		T->height = 0;
		T->left = T->right = NULL;
	} else {
		if( data < T->data ) {
			T->left = AVL_Insertion(T->left, data);
			if( GetHeight(T->left) - GetHeight(T->right) == 2 ) {
				// 需要左旋(即顺时针转)
				if( data < T->left->data ) {
					T = SingleLeftRotation( T );    // 左单旋
				} else {
					T = DoubleLeftRightRotation( T );    // 左-右双旋(先右单旋, 再左单旋)
				}
			}
		} else if( data > T->data ) {
			// 插入T的右子树
			T->right = AVL_Insertion(T->right, data);
			if( GetHeight(T->left) - GetHeight(T->right) == -2 ) {
				if( data > T->right->data ) {
					T = SingleRightRotation( T );    // 右单旋
				} else {
					T = DoubleRightLeftRotation( T );    // 右-左单旋(先左单旋, 再右单旋)
				}	
			}
		}
	}
	/* else x == T->data, 无须插入 */
	T->height = Max( GetHeight(T->left), GetHeight(T->right) ) + 1;    // 更新树的高度
	return T; 
}

int main()
{
	AVLTree *T, *Root;
	T = PreOrderCreBinTree();
	PreOrderTraversal( T );
	printf("\n");
	ElementType x;
	printf("请输入你要插入的数据: ");
	scanf("%d", &x);
	Root = AVL_Insertion(T, x); 
	PreOrderTraversal( Root );
}
