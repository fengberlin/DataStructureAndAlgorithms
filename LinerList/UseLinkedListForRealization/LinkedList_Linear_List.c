#include <stdio.h>
#include <stdlib.h>
typedef int ElementType; 

typedef struct node {
	ElementType data;
	struct node *next;
}Node;

typedef struct list{
	Node *head;  	// this is a header pointing to the linked-list
	Node *tail;		// it always points to the last node of the linked-list
}List;

void Add(List *pList, ElementType x);
int Length(List *pList);
Node *FindKth(List *pList, int k);
Node *Find(List *pList, ElementType x);
Node *Insert(List *pList, ElementType x, int k);
Node *Delete(List *pList, int k);
void Print(List *pList);
void ClearAway(List *pList); 

int Length(List *pList) 
{
	// Get the length of the linked-list.
	int i, cnt=0;
	Node *p = pList->head;
	while ( p ) {
		p = p->next;
		cnt++;
	}
	return cnt;
}

void Add(List *pList, ElementType x) 
{
	// add a node to the linked-list
	Node *p = (Node *)malloc(sizeof(List));
	if ( p ) {
		p->data = x;
		p->next = NULL;
	} else {
		printf("Error:Failed to allocate memory.");
		exit(-1);
	}
//	Node *last = pList->head;
//	if( last ) {
//		while( last->next ) {
//			last = last->next;
//		}
//		last->next = p;
// 	} else {
//		pList->head = p; 		
//	}
	if ( pList->head ) {
		pList->tail->next = p;		// this reduces the number of times of traversal
		pList->tail = p;
	} else {
		pList->head = pList->tail = p;
	}
}

Node *FindKth(List *pList, int k) {
	// find the Kth node and return it 
	int cnt = 1;
	Node *p = pList->head;
	while ( p != NULL && cnt < k ) {
		p = p->next;
		cnt++;
	}
	if ( cnt == k ) {
		return p;
	} else {
		return NULL;
	}
}

Node *Find(List *pList, ElementType x) {
	// find the node according to the value 
	Node *p = pList->head;
	while ( p != NULL && p->data != x ) {	// here it is better to use
		p = p->next;
	}
	return p;
}

Node *Insert(List *pList, ElementType x, int k) {
	// Insert a node to the linked-list
	// when insertion appear, pList->head should point to the new header node
	// Here pList->head is as a function argument, also as a function return value
	Node *p, *q, *r;
//	r = (Node *)malloc(sizeof(Node));
//	if( r ) {
//		// add a empty node to operate conveniently
//		r->next = pList->head;
//		pList->head = r;
//	} else {
//		exit(-1);
//	}
//	int c = Length(pList);
//	printf("length=%d\n", c);
//	q = FindKth(pList, k);
//	printf("q->data=%d\n", q->data);
//	printf("q->next->data=%d\n", q->next->data);
//	if( q ) {
//		p = (Node *)malloc(sizeof(Node));
//		if( p ) {
//			p->data = x;
//			p->next = q->next;
//			q->next = p; 
//		} else {
//			exit(-1);
//		}
//	} else {
//		exit(-1);
//	}
//	pList->head = r->next;
//	free(r); 
//	classify the discussion
	if ( k == 1 ) {
		// If a node inserted to the header
		p = (Node *)malloc(sizeof(Node));
		if ( p ) {
			p->data = x;
			p->next = pList->head;
			return p;
		} else {
			return NULL;
		}
	}
	q = FindKth(pList, k-1);
	if ( q ) {
		p = (Node *)malloc(sizeof(Node));
		if ( p ) {
			p->data = x;
			p->next = q->next;
			q->next = p;
			return pList->head;
		} else {
			exit(-1);
		}
	} else {
		return NULL;
	}
}

Node *Delete(List *pList, int k) {
	// Delete a node from the linked-list
//	Node *p, *q, *r;
//	r = (Node *)malloc(sizeof(Node));
//	if( r ) {
//		r->next = pList->head;
//		pList->head = r;
//	} else {
//		exit(-1);
//	}
//	q = FindKth(pList, k);
//	if( q ) {
//		if( q->next ) {
//			p = q->next;
//			q->next = p->next;
//			free(p);
//		} else {
//			exit(-1);
//		}	
//	} else {
//		exit(-1);
//	}
//	pList->head = r->next;
//	free(r);
	
//	classify the discussion
	Node *p, *q;
	if ( k == 1 ) {
		q = pList->head;
		pList->head = q->next;
		free(q);
		return pList->head;
	}
	p = FindKth(pList, k-1);
	if ( p ) {
		if ( p->next ) {
			q = p->next;
			p->next = q->next;
			free(q);
			return pList->head;
		} else {
			return NULL;
		}		
	} else {
		return NULL;
	}
}

void Print(List *pList) {
	// print the elements of the linear-list
	Node *p;
	for(p=pList->head; p; p=p->next) {
		printf("%d ", p->data);
	}
	printf("\n");
}

void ClearAway(List *pList) {
	Node *p, *q;
	for(p=pList->head; p; p=q) {
		q = p->next;
		free(p);
	}
}

int main() 
{
	// this is a main test
	List list;
	list.head = list.tail = NULL;
	int number = 0;
	do {
		scanf("%d", &number);
		if ( number != -1 ) {
			Add(&list, number);
		}
	}while( number != -1 );
	Print(&list);
	list.head = Insert(&list, 5, 3);
	Print(&list);
	list.head = Delete(&list, 5);
	Print(&list);
	ClearAway(&list);
	return 0;
}
