#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

typedef struct PolyNode *Polynomial
typedef struct PolyNode {
	int coef;	/* the coef of the polynomial(系数) */
	int expon;	/* the expon of the polynomial(指数) */
	Polynomial link;
}; 

int Compare(int e1, int e2) {
	/* compare the expon1 and the expon2(比较两个指数的大小) */
	int flag;
	if ( e1 > e2 ) {
		flag = 1;
	} else if ( e1 < e2 ) {
		flag = -1;
	} else {
		flag = 0;
	}
	return flag;
}

void Attach(int coef, int expon, Polynomial *PtrRear) {
	Polynomial p = (Polynomial)malloc(sizeof(struct PolyNode));
	if ( !p ) {
		printf("failed to allocate memory!\n");
		exit(-1);
	}
	p->coef = coef;
	p->expon = expon;
	(*PtrRear)->link = p;
	*PtrRear = p;
}

Polynomial PolyAdd(Polynomial p1, Polynomial p2) {
	Polynomial front, rear, temp;
	int sum;
	
	/*  */
	rear = (Polynomial)malloc(sizeof(struct PolyNode));
	if ( !rear ) {
		printf("failed to allocate memory!\n");
		exit(-1);
	}
	front = rear;
	while ( p1 && p2 ) {
		switch ( Compare(p1->expon, p2->expon) ) {
			case 1 : Attach(p1->coef, p1->expon, &rear);
					 p1 = p1->link;
					 break;
			case -1 : Attach(p2->coef, p2->expon, &rear);
					  p2 = p2->link;
					  break;
			case 0 : sum = p1->coef + p2->coef;
					 if ( sum ) {
					 	Attach(sum, p1->expon, &rear);
					 }
					 p1 = p1->link;
					 p2 = p2->link;
					 break;
		}
	}
	for (; p1; p1=p1->link) {
		Attach(p1->coef, p1->expon, &rear);
	}
	for (; p2; p2=p2->link) {
		Attach(p2->coef, p2->expon, &rear);
	}
	rear->link = NULL;
	temp = front;
	front = front->link;
	free(temp);
	return front;
}

int main()
{
	return 0;
}
