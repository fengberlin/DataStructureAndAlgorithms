#include "Array_Linear_List.h"
// use array to realize a linear-list.

List *Initialize() 
{
	// Initialize a empty linear-list.
	List *pList = (List *)malloc(sizeof(List));
	if ( pList ) {
		pList->last = -1;
		return pList;
	} else {
		printf("Error:It is failed to allocate the memory!");
		exit(-1);
	}
}

int Find(List *PtrL, ElementType x) 
{
	// Find the element "x" in the linear-list.
	int i = 0;
	int ret;
	while ( i <= PtrL->last && PtrL->data[i++] != x );
	if ( i > PtrL->last ) {
		ret = -1;
	} else {
		ret = i;
	}
	return ret;
}

void Insert(List *PtrL, ElementType x, int index) 
{
	// Index indicates the location of the math concept(such as 1st, 2nd, 3rd...) 
	// The average number of moves is n/2 ( n is the number of elements )
	// The time complexity is O(n)
	int i;
	if ( PtrL->last == MaxSize-1 ) {
		// The memory is full
		printf("The is no memory!");
		return;
	}
	if ( index < 1 || index > PtrL->last + 2 ) {
		// 	Inspect the location
		printf("The location is illegal!");
		return;
	}
	for(i=PtrL->last; i>=index-1; i--) {
		PtrL->data[i+1] = PtrL->data[i];	// move the element
	}
	PtrL->data[index-1] = x;
	PtrL->last++;
	return;
}

void Delete(List *PtrL, int index) 
{
	// Index indicates the location of the math concept(such as 1st, 2nd, 3rd...)
	// The average number of moves is (n-1)/2 ( n is the number of elements )
	// The time complexity is O(n)
	int i;
	if ( index < 1 || index > PtrL->last + 1 ) {
		printf("It doesn't exist!");
		return;
	}
	for(i=index; i<=PtrL->last ;i++) {
		PtrL->data[i-1] = PtrL->data[i];	// move the element
	}
	PtrL->last--;
	return;
}

void print(List *PtrL) 
{
	int i;
	if ( PtrL->last == -1 ) {
		printf("It is empty.");
		return;
	}
	for(i=0; i<=PtrL->last; i++) {
		printf("%d ", PtrL->data[i]);
	}
	printf("\n");
	return;
}


int main() 
{
	// This is a main test.
	List *List;
	int i, num, result, data;
	List = Initialize();
	printf("please input the number of the data: ");
	scanf("%d", &num);
	while ( num > MaxSize ) {
		printf("It is out of range, please input again.");
		scanf("%d", &num);
	}
	for(i=0; i<num; i++) {
		scanf("%d", &List->data[i]);
		List->last++;
	}
	printf("Please input the data you want to find: ");
	scanf("%d", &data);
	result = Find(List, data);
	printf("result = %d.\n", result);
	printf("After insert a number '6' at the 5th:\n");
	Insert(List, 6, 5);
	print(List);
	printf("After delete the 3th data:\n");
	Delete(List, 3);
	print(List);
	free(List);
	return 0; 
}
