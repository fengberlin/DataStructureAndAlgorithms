#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
typedef int ElementType;

typedef struct {
	ElementType data[MaxSize];	// or use <ElementType *data>.
	int last;     // It is like a pointer pointing to the last element of the array.
}List;

List *Initialize();
int Find(List *PtrL, ElementType x);
void Insert(List *PtrL, ElementType x, int index);
void Delete(List *PtrL, int index);
void print(List *PtrL);
