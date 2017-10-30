#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define Error -1
typedef int ElementType;

typedef struct {
	ElementType data[MaxSize];
	int top1;
	int top2;
}DStack;

DStack *Init() {
	// Initialize a double-stack.
	DStack *S = (DStack *)malloc(sizeof(DStack));
	if ( S ) {
		S->top1 = -1;
		S->top2 = MaxSize;
	}
	return S;
}

int isFull(DStack *PtrS) {
	// Judge the double-stack is full or not.
	return ( PtrS->top2 - PtrS->top1 == 1 );
}

int isEmpty1(DStack *PtrS) {
	// Judge the first stack is empty or not.
	return ( PtrS->top1 == -1 );
} 

int isEmpty2(DStack *PtrS) {
	// Judge the second stack is empty or not.
	return ( PtrS->top2 == MaxSize );
} 

//int isEmpty(DStack *PtrS) {
//	// Judge the double-stack is empty or not.
//	
//}

void Push(DStack *PtrS, ElementType item, int tag) {
	// Push a item of the stack.
	// if tag is equal to 1, then operate the first stack. 
	if ( isFull(PtrS) ) {
		printf("The stack is full.");
		return;
	}
	if ( tag == 1 ) {
		PtrS->data[++(PtrS->top1)] = item;
	} else {
		PtrS->data[--(PtrS->top2)] = item;
	}
}

ElementType Pop(DStack *PtrS, int tag) {
	// Pop a item of the stack.
	// if tag isn't equal to 1, then operate the second stack.
	if ( tag == 1 ) {
		if ( isEmpty1(PtrS) ) {
			printf("The first stack is empty.");
			return Error;
		} else {
			return PtrS->data[(PtrS->top1)--];
		}
	} else {
		if ( isEmpty2(PtrS) ) {
			printf("The second stack is empty.");
			return Error;
		} else {
			return PtrS->data[(PtrS->top2)++];
		}
	}
}

void Print(DStack *PtrS, int tag) {
	// Show the data of the stack.
	int i;
	if( tag == 1 ) {
		if ( isEmpty1(PtrS) ) {
			printf("The first stack is empty.");
			return;
		} else {
			for(i=PtrS->top1; i>=0; i--) {
				printf("%d ", PtrS->data[i]);
			}
			printf("\n");
		}
	} else {
		if ( isEmpty2(PtrS) ) {
			printf("The second stack is empty.");
			return;
		} else {
			for(i=PtrS->top2; i<MaxSize; i++) {
				printf("%d ", PtrS->data[i]);
			}
			printf("\n");
		}
	}
} 

int main() 
{
	DStack *S = Init();
	int i, value1, value2;
	if( S ) {
		for(i=0; i<10; i++) {
			Push(S, i+1, 1);
			Push(S, i-2, 2);
		}
		Print(S, 1);
		Print(S, 2);
		value1 = Pop(S, 1);
		value2 = Pop(S, 2);
		printf("value1 = %d\n", value1);
		printf("value2 = %d\n", value2);
	} else {
		printf("Failed to allocate the memory.\n");
		exit(-1);
	}
	free(S);
	return 0;
}
