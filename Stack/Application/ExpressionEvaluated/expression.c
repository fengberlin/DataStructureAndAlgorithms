#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXOP 100	// 运算数序列可能得最大长度
#define MaxSize 100		// 堆栈元素最大个数
#define NUMBER 0	// 运算数的标识
typedef double ElementType;	// 将堆栈的元素类型具体化

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
	/* 从输入中获得下一个对象(运算数或运算符)，并保存在字符数组s中 */
	/* 返回值为NUMBER或运算符本身 */
	/* 此时输入的表达式为后缀表达式，表达式中只有运算数(还有小数点)或者运算符 */ 
	int i, c;
	
	/* 跳过表达式前空格等字符 */ 
	while( (s[0] = c = getchar()) == ' ' || c == '\t' );
	
	s[1] = '\0';
	if( !isdigit(c) && c != '.' )	/* 如果c是运算符 */ 
		return c;	/* 直接返回运算符 */ 
	i = 0;
	if( isdigit(c) )	/* 如果c是数字，则一直读完连续的数字并存入s */
		while( isdigit(s[++i] = c = getchar()) );
	if( c == '.' )		/* 如果有小数点，则继续读完小数点后的连续数字 */
		while( isdigit(s[++i] = getchar()) );
	s[i] = '\0';	/* 完成对实数字符串的存储 */
	return NUMBER;		/* 表示此时s中存的是一个数字 */ 
} 

int main()
{
	int type;
	double op;
	char s[MAXOP];
	Stack *PtrS = Init();	/* Initialize a stack to store the operator */
	printf("Please input the post-order expression(请输入后缀表达式):\n");
	while( (type = GetOp(s)) != EOF ) {		/* 当未读到输入结束时 */
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
					   if( 0 != op ) {		/* 检查除法的分母是否为0 */
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
	free(PtrS);		/* 释放堆栈 */
	return 0;
} 
