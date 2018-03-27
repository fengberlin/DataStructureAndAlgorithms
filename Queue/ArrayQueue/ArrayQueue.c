#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
#define Error 65535
typedef int ElementType;

typedef struct {
	ElementType data[MaxSize];
	int rear;		/* the tail of the queue */
	int front;		/* the head of the queue, and it points to the front of the first element */
}Queue;

int isFull(Queue *PtrQ) {
	/* cycle queue */
	/* Judge whether the queue is full or not */
	return ( (PtrQ->rear+1)%MaxSize == PtrQ->front );
}

int isEmpty(Queue *PtrQ) {
	/* cycle queue */
	/* Judge whether the queue is empty or not */
	return ( PtrQ->front == PtrQ->rear );
}

Queue *Init() {
	/* Initialize a queue */
	Queue *PtrQ = (Queue *)malloc(sizeof(Queue));
	if ( !PtrQ ) {
		printf("Failed to allocate memory!\n");
		exit(-1);
	} else {
		PtrQ->front = PtrQ->rear = 0;
	}
}

void AddQ(Queue *PtrQ, ElementType item) {
	/* add a element to the queue */
	if ( isFull(PtrQ) ) {
		printf("the queue is full!\n");
		return;
	} else {
		PtrQ->rear = (PtrQ->rear+1) % MaxSize;
		PtrQ->data[PtrQ->rear] = item;
		return;
	}
}

ElementType DeleteQ(Queue *PtrQ) {
	/* delete a element from the queue */
	if ( isEmpty(PtrQ) ) {
		printf("the queue is empty!\n");
		return Error;
	} else {
		PtrQ->front = (PtrQ->front+1) % MaxSize;
		return PtrQ->data[PtrQ->front];
	}
}

void PrintQ(Queue *PtrQ) {
	/* print the element of the queue */
	if ( isEmpty(PtrQ) ) {
		printf("the queue is empty!");
		return;
	} else {
		int p = PtrQ->front;
		while( p%MaxSize != PtrQ->rear ) {
			printf("%d ", PtrQ->data[p+1]);
			p = (p+1) % MaxSize;
		}
	}
}

int main()
{
	int i;
	Queue *Q = Init();
	for(i=0; i<10; i++) {
		AddQ(Q, i+1);
	}
	PrintQ(Q);
	free(Q); 
	return 0;
}
