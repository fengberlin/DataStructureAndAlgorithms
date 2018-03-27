#include <stdio.h>
#include <stdlib.h>

#define Error 65535
typedef int ElementType;

typedef struct node {	/* the node of the queue */
	ElementType data;
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

void AddQ(LinkQueue *PtrQ, ElementType item) {
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

ElementType *DeleteQ(LinkQueue *PtrQ) {
	/* delete a node from the queue */
	if( NULL == PtrQ->front ) {
		printf("the queue is empty!\n");
		return Error;
	}
	QNode *del = PtrQ->front;	/* delete the node pinted by the front pointer */
	ElementType result = del->data;
	if ( PtrQ->front == PtrQ->rear ) {	/* if the queue has only one node */
		PtrQ->front = PtrQ->rear = NULL;
	} else {
		PtrQ->front = PtrQ->front->next;
	}
	free( del );
	return result;
}

void PrintQ(LinkQueue *PtrQ) {
	if( NULL == PtrQ->front ) {
		printf("the queue is empty!\n");
		return;
	} else {
		QNode *p = PtrQ->front;
		while ( p ) {
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n");
		return;
	}	
}

void Destroy(LinkQueue *PtrQ) {
	/* free the memory of the queue */
	if ( NULL == PtrQ->front) {\
		printf("the queue is empty!\n");
		return;
	} else {
		QNode *p = PtrQ->front;
		while( p ) {
			PtrQ->front = PtrQ->front->next;
			free(p);
			p = PtrQ->front;
		}
		return;
	}
}

int main()
{
	int i;
	ElementType ret;
	LinkQueue *PtrQ = InitQueue();
	for(i=0; i<10; i++) {
		AddQ(PtrQ, i+1);
	}
	PrintQ(PtrQ);
	ret = DeleteQ(PtrQ);
	printf("%d\n", ret);
	PrintQ(PtrQ);
	Destroy(PtrQ);
	return 0;
}
