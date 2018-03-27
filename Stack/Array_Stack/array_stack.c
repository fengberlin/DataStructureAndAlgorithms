#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define Error -1
typedef int ElementType;
// array stack 

typedef struct StackNode {
	ElementType data[MaxSize];  	// Here it can use poniter to represent array.
	int top;	// Top is a pointer pointing to the top of the stack.The value is the index of the array.
}Stack;

Stack *Init() {
	// Initialize a stack.
	Stack *S = (Stack *)malloc(sizeof(Stack));
	if( S ) {
		S->top = -1;
	}
	return S;
}

int isFull(Stack *PtrS) {
	// Judge the stack is full or not
	return ( PtrS->top == MaxSize - 1 );
}

int isEmpty(Stack *PtrS) {
	// Judge the stack is empty or not
	return ( PtrS->top == -1 );
}

void Push(Stack *PtrS, ElementType item) {
	// Push a item into the stack
	if( isFull(PtrS) ) {
		printf("The stack is full.");
		return;
	} else {
		PtrS->data[++(PtrS->top)] = item;
		return;
	}
}

ElementType Pop(Stack *PtrS) {
	// Pop a item of the stack.
	if( isEmpty(PtrS) ) {
		printf("The stack is empty.");
		return Error;
	} else {
		return PtrS->data[(PtrS->top)--];
	}
}

void Print(Stack *PtrS) {
	// Print the data of the stack.
	int i;
	if( isEmpty(PtrS) ) {
		printf("The stack is empty.");
		return;
	} else {
		for(i=0; i<=PtrS->top; i++) {
			printf("data=%d ", PtrS->data[i]);
		}
		printf("\n");
	}
}

int main()
{
	int i;
	int value;
	Stack *S = Init();
	if( S ) {
		for(i=0; i<5; i++) {
			S->data[i] = i + 1;
			S->top++; 
		}
		Push(S, 100);
	}
	Print(S);
	value = Pop(S);
	printf("value=%d\n", value);
	Print(S);
	free(S);
	return 0;
}
 
