#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXOP 100	// ���������п��ܵ���󳤶�
#define MaxSize 100		// ��ջԪ��������
#define NUMBER 0	// �������ı�ʶ
typedef double ElementType;	// ����ջ��Ԫ�����;��廯

typedef struct {
	ElementType data[MaxSize];
	int top;
}Stack; 

Stack *Init() {
	Stack *PtrS = (Stack *)malloc(sizeof(Stack));
	if ( PtrS ) {
		PtrS->top = -1;
	}
	return PtrS;
}

int isEmpty(Stack *PtrS) {
	// Judge if the stack is empty or not.
	return ( -1 == PtrS->top);
}

int isFull(Stack *PtrS) {
	// Judge if the stack is full or not.
	return ( MaxSize-1 == PtrS->top );
}

void Push(Stack *PtrS, ElementType item) {
	// Push an item into the stack.
	if ( isFull(PtrS) ) {
//		printf("The stack is full.\n");
		return;
	} else {
		PtrS->data[++(PtrS->top)] = item;
		return;
	}	
}

ElementType Pop(Stack *PtrS) {
	// Pop an item from the stack.
	if( isEmpty(PtrS) ) {
//		printf("The stack is empty.\n");
		exit(-1);
	} else {
		return PtrS->data[(PtrS->top)--];
	}
} 

int GetOp(char s[]) {
	/* �������л����һ������(�������������)�����������ַ�����s�� */
	/* ����ֵΪNUMBER����������� */
	/* ��ʱ����ı��ʽΪ��׺���ʽ�����ʽ��ֻ��������(����С����)��������� */ 
	int i, c;
	
	/* �������ʽǰ�ո���ַ� */ 
	while( (s[0] = c = getchar()) == ' ' || c == '\t' );
	
	s[1] = '\0';
	if( !isdigit(c) && c != '.' )	/* ���c������� */ 
		return c;	/* ֱ�ӷ�������� */ 
	i = 0;
	if( isdigit(c) )	/* ���c�����֣���һֱ�������������ֲ�����s */
		while( isdigit(s[++i] = c = getchar()) );
	if( c == '.' )		/* �����С���㣬���������С�������������� */
		while( isdigit(s[++i] = getchar()) );
	s[i] = '\0';	/* ��ɶ�ʵ���ַ����Ĵ洢 */
	return NUMBER;		/* ��ʾ��ʱs�д����һ������ */ 
} 

int main()
{
	int type;
	double op;
	char s[MAXOP];
	Stack *PtrS = Init();	/* Initialize a stack to store the operator */
	printf("Please input the post-order expression(�������׺���ʽ):\n");
	while( (type = GetOp(s)) != EOF ) {		/* ��δ�����������ʱ */
		switch( type ) {
			case NUMBER : Push(PtrS, atof(s));
						  break;
			case '+' : Push(PtrS, Pop(PtrS)+Pop(PtrS));
					   break;
			case '*' : Push(PtrS, Pop(PtrS)*Pop(PtrS));
					   break;
			case '-' : op = Pop(PtrS);
					   Push(PtrS, Pop(PtrS)-op);
					   break;
			case '/' : op = Pop(PtrS);
					   if( 0 != op ) {		/* �������ķ�ĸ�Ƿ�Ϊ0 */
					       Push(PtrS, Pop(PtrS)/op);
					   } else {
					   	   printf("error:zero divisor!\n");
					   }
					   break;
			case '\n' : printf("result = %.8g\n", Pop(PtrS));
						break;
			default : printf("error:unknown command %s!\n", s);
					  break;
		}
	}
	free(PtrS);		/* �ͷŶ�ջ */
	return 0;
} 
