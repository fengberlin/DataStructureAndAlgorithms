#include <stdio.h>
#include <stdlib.h>
#define Error 65535
typedef int ElementType;

typedef struct AVLTreeNode {
	ElementType data;
	struct AVLTreeNode *left;
	struct AVLTreeNode *right;
	int height;		// �Ըý��Ϊ���������ĸ߶� 
}AVLTree; 

typedef struct node {	/* the node of the queue */
	AVLTree *data;
	struct node *next;
}QNode; 

typedef struct {	/* the structure of the queue */
	QNode *front;	/* point to the head of the queue */
	QNode *rear;	/* point to the tail of the queue */
}LinkQueue;

int isEmpty(LinkQueue *PtrQ) {  // �ж϶����Ƿ�Ϊ�� 
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
	// ���򴴽�ƽ�������(�ݹ�ʵ��)
	AVLTree *BT;
	ElementType data;
	scanf("%d", &data);
	if( data ) {	/* ���������data�ǲ�Ϊ0���� */
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
	// ǰ�����(�ݹ�ʵ��) 
	if( BT ) {
		printf("%d ", BT->data);
		PreOrderTraversal( BT->left );
		PreOrderTraversal( BT->right );
	}
	return;
}

int GetHeight(AVLTree *T) {
	// �������ĸ߶� 
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
	// �����������������ֵ 
	return ( Height1 > Height2 ? Height1 : Height2 );
}

AVLTree *SingleLeftRotation(AVLTree *A) {	/* ���� */
	// ע��: A������һ�����ӽ��B
   // ��A��B������, ����A��B�ĸ߶�, �������µĸ����B
   AVLTree *B = A->left;
   A->left = B->right;
   B->right = A;
   A->height = Max( GetHeight(A->left), GetHeight(A->right) ) + 1;
   B->height = Max( GetHeight(B->left), A->height ) + 1;
   return B;
}

AVLTree *SingleRightRotation(AVLTree *A) {		/* �ҵ��� */
	// ע��: A������һ�����ӽ��B
   // ��A��B���ҵ���, ����A��B�ĸ߶�, �������µĸ����B
   AVLTree *B = A->right;
   A->right = B->left;
   B->left = A;
   A->height = Max( GetHeight(A->left), GetHeight(A->right) ) + 1;
   B->height = Max( GetHeight(B->left), A->height ) + 1;
   return B;
}

AVLTree *DoubleLeftRightRotation(AVLTree *A) {  /* ��-��˫�� */
	// ע��: A������һ�����ӽ��B, ��B������һ�����ӽ��C
	// ��A��B��C�����ε���, �����µĸ����C
	A->left = SingleRightRotation( A->left );     // ��B��C���ҵ���, C������ 
	return SingleLeftRotation( A );    // ��A��C������, C������ 
}

AVLTree *DoubleRightLeftRotation(AVLTree *A) {  /* ��-��˫�� */
	// ע��: A������һ�����ӽ��B, ��B������һ�����ӽ��C
	// ��A��B��C�����ε���, �����µĸ����C
	A->right = SingleLeftRotation( A->right ); 
	return SingleRightRotation( A );
}

AVLTree *AVL_Insertion(AVLTree *T, ElementType data) {
	// ��data����AVL��T��, ���ҷ��ص������AVL�� 
	if( !T ) {		/* �����������TΪ��, ���½�����һ�������� */
		T = (AVLTree *)malloc(sizeof(AVLTree));
		T->data = data;
		T->height = 0;
		T->left = T->right = NULL;
	} else {
		if( data < T->data ) {
			T->left = AVL_Insertion(T->left, data);
			if( GetHeight(T->left) - GetHeight(T->right) == 2 ) {
				// ��Ҫ����(��˳ʱ��ת)
				if( data < T->left->data ) {
					T = SingleLeftRotation( T );    // ����
				} else {
					T = DoubleLeftRightRotation( T );    // ��-��˫��(���ҵ���, ������)
				}
			}
		} else if( data > T->data ) {
			// ����T��������
			T->right = AVL_Insertion(T->right, data);
			if( GetHeight(T->left) - GetHeight(T->right) == -2 ) {
				if( data > T->right->data ) {
					T = SingleRightRotation( T );    // �ҵ���
				} else {
					T = DoubleRightLeftRotation( T );    // ��-����(������, ���ҵ���)
				}	
			}
		}
	}
	/* else x == T->data, ������� */
	T->height = Max( GetHeight(T->left), GetHeight(T->right) ) + 1;    // �������ĸ߶�
	return T; 
}

int main()
{
	AVLTree *T, *Root;
	T = PreOrderCreBinTree();
	PreOrderTraversal( T );
	printf("\n");
	ElementType x;
	printf("��������Ҫ���������: ");
	scanf("%d", &x);
	Root = AVL_Insertion(T, x); 
	PreOrderTraversal( Root );
}
