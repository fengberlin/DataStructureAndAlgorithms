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
	// 层序生成二叉树(非递归)
	ElementType data;
	BinTree *BT, *T;
	LinkQueue *PtrQ = InitQueue();		
	int cnt = 0;	/* 记录还要输入的0的个数 */
	scanf("%d", &data);		// 建立第1个结点, 即根结点
	if( data ) {
		cnt++;
		BT = (BinTree *)malloc(sizeof(BinTree));
		BT->data = data;
		AddQ(PtrQ, BT);
		printf( "需要读入%d个0才能结束输入.\n", cnt+1);
	} else {
		return NULL;
	}
	while( !isEmpty(PtrQ) ) {
		// 创建左子树 
		T = DeleteQ(PtrQ);
		scanf("%d", &data);
		if( data ) {
			cnt++;
			T->left = (BinTree *)malloc(sizeof(BinTree));
			T->left->data = data;
			AddQ(PtrQ, T->left);
			printf( "需要读入%d个0才能结束输入.\n", cnt+1);
		} else {
			if( cnt != 0 ) {
				printf( "需要读入%d个0才能结束输入.\n", cnt--);
			}
			T->left = NULL;
		}
		// 创建右子树
		scanf("%d", &data);
		if( data ) {
			cnt++;
			T->right = (BinTree *)malloc(sizeof(BinTree));
			T->right->data = data;
			AddQ(PtrQ, T->right);
			printf( "需要读入%d个0才能结束输入.\n", cnt+1);
		} else {
			if( cnt != 0 ) {
				printf( "需要读入%d个0才能结束输入.\n", cnt--);
			}
			T->right = NULL;
		}
	}
	return BT;
}

void PreOrderTraversal(BinTree *BT)
{ // 前序遍历(递归实现)
	if( BT ) {
		printf("%d ", BT->data);
		PreOrderTraversal(BT->left);
		PreOrderTraversal(BT->right);
	}
	return;
}

void InOrderTraversal(BinTree *BT) {
	// 中序遍历(递归实现)
	if( BT ) {
		InOrderTraversal(BT->left);
		printf("%d ", BT->data);
		InOrderTraversal(BT->right);
	}
	return;
}

void PostOrderTraversal(BinTree *BT) {
	// 后序遍历(递归实现)
	if( BT ) {
		PostOrderTraversal(BT->left);
		PostOrderTraversal(BT->right);
		printf("%d ", BT->data);
	} 
	return;
}

void PreOrderPrintLeaves(BinTree *BT) {
	// 输出二叉树的叶结点(在二叉树遍历的基础上修改) 
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
	// 采用二叉树后序遍历的原理, 递归求出二叉树的高度 
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
	// 计算树的结点的数量 
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
	printf("请输入结点的数据(每输入一次就按一次回车(enter)):\n");
	BinTree *BT = CreateBinTree();
	if( BT )
	{
		printf("前序遍历输出为: ");
		PreOrderTraversal(BT);
		printf("\n");
		printf("中序遍历输出为: ");
		InOrderTraversal(BT);
		printf("\n");
		printf("后序遍历输出为: ");
		PostOrderTraversal(BT);
		printf("\n");
	} else {
		printf("树为空.\n");
		exit(-1);
	}	
	printf("树的结点分别为:");
	PreOrderPrintLeaves(BT);
	printf("\n");
	height = PostOrderGetHeight(BT);
	printf("树的深度为%d。\n", height); 
	amount = GetAmount(BT);
	printf("树结点的数量为%d。\n", amount);
	return 0;
}
