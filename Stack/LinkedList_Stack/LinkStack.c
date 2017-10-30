#include <stdio.h>
#include <stdlib.h>
#define Error -1
typedef int ElementType;

typedef struct node {
	ElementType data;
	struct node *next;
}Node;

typedef struct {
	Node *top;
}LinkStack;

LinkStack *Create() {
	// Create a empty stack.
	LinkStack *PtrL = (LinkStack *)malloc(sizeof(LinkStack));
	if ( PtrL ) {
		PtrL->top = NULL;
	}
	return PtrL;
}

int isEmpty(LinkStack *PtrS) {
	// Judge the stack is empty or not.
	return ( PtrS->top == NULL );
}

void Push(LinkStack *PtrS, ElementType item) {
	// This is an example using head pointer.
	Node *p = (Node *)malloc(sizeof(Node));
	if ( p ) {
		p->data = item;
		p->next = PtrS->top;
		PtrS->top = p;
	} else {
		exit(-1);
	}
}

ElementType Pop(LinkStack *PtrS) {
	// Pop a item of the stack.
	int value;
	if ( isEmpty(PtrS) ) {
		printf("The stack is empty.");
		return Error;
	} else {
		Node *q = PtrS->top;
		value = q->data;
		PtrS->top = q->next;
		free(q);
		return value;
	}
}

void Print(LinkStack *PtrL) {
	// Print the data of the stack.
	Node *p;
	if ( isEmpty(PtrL) ) {
		printf("The stack is empty.");
	} else {
		for(p=PtrL->top; p; p=p->next) {
			printf("%d ", p->data);
		}
		printf("\n");
	}
	return;
} 

void Destory(LinkStack *PtrL) {
	// free the memory of the linklist
	Node *p = PtrL->top;
	while( NULL != p ) {
		PtrL->top = PtrL->top->next;
		free(p);
		p = PtrL->top;
	}
	return;
}
 
int main()
{
	LinkStack *L = Create();
	int i, value;
	if ( L ) {
		for(i=0; i<10; i++) {
			Push(L, i+1);
		}
		Print(L);
		value = Pop(L);
		printf("value=%d\n", value);
		Print(L);
	} else {
		exit(-1);
	}
	Destory(L);
	return 0;
}
