#include <stdio.h>
#include <stdlib.h>
#define Error NULL 
typedef int ElementType;

typedef struct TreeNode {
	ElementType data;
	struct TreeNode *left;
	struct TreeNode *right;
}BinTree;

typedef struct node {	/* the node of the queue */
	BinTree *data;
	struct node *next;
}QNode; 

typedef struct {	/* the structure of the queue */
	QNode *front;	/* point to the head of the queue */
	QNode *rear;	/* point to the tail of the queue */
}LinkQueue;

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

int isEmpty(LinkQueue *PtrQ) {
	// Judge the queue is empty or not 
	return ( (PtrQ->front == NULL) ); 
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

void AddQ(LinkQueue *PtrQ, BinTree *item) {
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

BinTree *DeleteQ(LinkQueue *PtrQ) {
	/* delete a node from the queue */
	if( isEmpty(PtrQ) ) {
		printf("the queue is empty!\n");
		return Error;
	}
	QNode *del = PtrQ->front;	/* delete the node pinted by the front pointer */
	BinTree *result = del->data;
	if ( PtrQ->front == PtrQ->rear ) {	/* if the queue has only one node */
		PtrQ->front = PtrQ->rear = NULL;
	} else {
		PtrQ->front = PtrQ->front->next;
	}
	free( del );
	return result;
}

BinTree *CreateBinTree() {
	// �������ɶ�����(�ǵݹ�)
	ElementType data;
	BinTree *BT, *T;
	LinkQueue *PtrQ = InitQueue();		
	int cnt = 0;	/* ��¼��Ҫ�����0�ĸ��� */
	scanf("%d", &data);		// ������1�����, �������
	if( data ) {
		cnt++;
		BT = (BinTree *)malloc(sizeof(BinTree));
		BT->data = data;
		AddQ(PtrQ, BT);
		printf( "��Ҫ����%d��0���ܽ�������.\n", cnt+1);
	} else {
		return NULL;
	}
	while( !isEmpty(PtrQ) ) {
		// ���������� 
		T = DeleteQ(PtrQ);
		scanf("%d", &data);
		if( data ) {
			cnt++;
			T->left = (BinTree *)malloc(sizeof(BinTree));
			T->left->data = data;
			AddQ(PtrQ, T->left);
			printf( "��Ҫ����%d��0���ܽ�������.\n", cnt+1);
		} else {
			if( cnt != 0 ) {
				printf( "��Ҫ����%d��0���ܽ�������.\n", cnt--);
			}
			T->left = NULL;
		}
		// ����������
		scanf("%d", &data);
		if( data ) {
			cnt++;
			T->right = (BinTree *)malloc(sizeof(BinTree));
			T->right->data = data;
			AddQ(PtrQ, T->right);
			printf( "��Ҫ����%d��0���ܽ�������.\n", cnt+1);
		} else {
			if( cnt != 0 ) {
				printf( "��Ҫ����%d��0���ܽ�������.\n", cnt--);
			}
			T->right = NULL;
		}
	}
	return BT;
}

void PreOrderTraversal(BinTree *BT)
{ // ǰ�����(�ݹ�ʵ��)
	if( BT ) {
		printf("%d ", BT->data);
		PreOrderTraversal(BT->left);
		PreOrderTraversal(BT->right);
	}
	return;
}

void InOrderTraversal(BinTree *BT) {
	// �������(�ݹ�ʵ��)
	if( BT ) {
		InOrderTraversal(BT->left);
		printf("%d ", BT->data);
		InOrderTraversal(BT->right);
	}
	return;
}

void PostOrderTraversal(BinTree *BT) {
	// �������(�ݹ�ʵ��)
	if( BT ) {
		PostOrderTraversal(BT->left);
		PostOrderTraversal(BT->right);
		printf("%d ", BT->data);
	} 
	return;
}

void PreOrderPrintLeaves(BinTree *BT) {
	// �����������Ҷ���(�ڶ����������Ļ������޸�) 
	if( BT ) {
		if( !BT->left && !BT->right ) {
			printf("%d ", BT->data);
		}
		PreOrderPrintLeaves(BT->left);
		PreOrderPrintLeaves(BT->right);
	}
	return;
}

int PostOrderGetHeight(BinTree *BT) {
	// ���ö��������������ԭ��, �ݹ�����������ĸ߶� 
	int HL, HR, MaxH;
	if( BT ) {
		HL = PostOrderGetHeight(BT->left);
		HR = PostOrderGetHeight(BT->right);
		MaxH = HL > HR ? HL : HR;
		return ( MaxH + 1 );
	} else {
		return 0;
	}
}

int GetAmount(BinTree *BT) {
	// �������Ľ������� 
	int LAmount, RAmount, TotalAmount;
	if( BT ) {
		LAmount = GetAmount(BT->left);
		RAmount = GetAmount(BT->right);
		TotalAmount = LAmount + RAmount;
		return ( TotalAmount + 1 );
	} else {
		return 0;
	}
}

int main()
{
	int height;
	int amount;
	printf("�������������(ÿ����һ�ξͰ�һ�λس�(enter)):\n");
	BinTree *BT = CreateBinTree();
	if( BT )
	{
		printf("ǰ��������Ϊ: ");
		PreOrderTraversal(BT);
		printf("\n");
		printf("����������Ϊ: ");
		InOrderTraversal(BT);
		printf("\n");
		printf("����������Ϊ: ");
		PostOrderTraversal(BT);
		printf("\n");
	} else {
		printf("��Ϊ��.\n");
		exit(-1);
	}	
	printf("���Ľ��ֱ�Ϊ:");
	PreOrderPrintLeaves(BT);
	printf("\n");
	height = PostOrderGetHeight(BT);
	printf("�������Ϊ%d��\n", height); 
	amount = GetAmount(BT);
	printf("����������Ϊ%d��\n", amount);
	return 0;
}
