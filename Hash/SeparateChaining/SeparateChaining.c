#include "SeparateChaining.h"

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MinTableSize (10)

typedef struct ListNode {
	ElementType Element;     /* Element是一个数组 */
	unsigned short Times;	/* 单向链表中结点数量，词频统计应用实例中用于出现次数 */
	struct ListNode *Next;
}Position, List;

/* 为了简单起见, 单向链表的头结点就是散列表数组元素 */

typedef struct HashTbl {
	int TableSize;
	struct ListNode *TheLists;		// 其实是一个数组 
}HashTable; 

HashTable *InitializeTable(int TableSize) {
	HashTable *H;
	int i;
	if( TableSize < MinTableSize ) {
		Error("散列表太小");
		return NULL;
	}
	/* 以下分配散列表 */
	H = (HashTable *)malloc(sizeof(HashTable));
	if( H == NULL )
		FatalError("空间溢出!!!");
	H->TableSize = NextPrime( TableSize );
	
	/* 以下分配表头数组 */
	H->TheLists = (List *)malloc(sizeof(List) * H->TableSize);
	if( H->TheLists == NULL )
		FatalError("空间溢出!!!");
	for(i=0; i<H->TableSize; i++) {
		H->TheLists[i].Element[0] = '\0';
		H->TheLists[i].Times = 0;	  /* 单向链表中结点数量 */
		H->TheLists[i].Next  = NULL;
	}
	return H;
}

static int NextPrime( int n ) {	
	/* 寻找一个合适的素数作为TableSize */
	int i;
	if( n % 2 == 0 )
		n++;
	for(; ; n+=2)
	{
		for(i=3; i*i<=n; i+=2)
			if( n % i == 0 )
				break;
		if( i*i > n )
			return n;
	} 
}

Index Hash(ElementType key, int TableSize) {	
	/* 将字符串关键字转化为数字形式 */
	unsigned int h = 0;
	while( *key != '\0' )
		h = ( h << 5 ) + *key++;
	return h % TableSize;
}

Position *Find(HashTable *H, ElementType key) {	
	/* 寻找关键字位置 */
	Position *p;
	List *L;
	L = &(H->TheLists[Hash(key, H->TableSize)]);    /* H->TheLists[Hash(key, H->TableSize)] */
	p = L->Next;	/* p指向真正的第一个元素 */
	while( p!=NULL && strcmp(p->Element, key) )		/* if p->Element==key, return 0 */ 
		p = p->Next;
	return p;
}

void InsertAndCount(HashTable *H, ElementType key) {
	Position *pos, *NewCell;
	List *L;
	pos = Find(key, H);
	if( pos )
		pos->Times++;
	else {	  /* 关键字为找到 */
		NewCell = (List *)malloc(sizeof(List));
		if( NewCell == NULL )
			FatalError("空间溢出!!!");
		else {
			L = &(H->TheLists[Hash(key, H->TableSize)]);
			NewCell->Next = L->Next;	/* 插入第一个结点 */
			L->Next = NewCell;
			strcpy(NewCell->Element, key);
			NewCell->Times = 1;
			L->Times++;		/* 头结点的Times表示该链表的长度, 增加1 */
		}
	}
	return;
}

Position *Delete(HashTable *H, ElementType key) {
	Position *p, *q, *tmp;
	p = Find(key, H);
	tmp = p;
	q = &(H->TheLists[Hash(key, H->TableSize)]);
	if( p && q ) {
		while( q->Next != p )
			q = q->Next;
		q->Next = p->Next;
		free(p);
	}
	return tmp;
}

void DestroyTable(HashTable *H) {
	Position *p, *tmp;
	int i;
	for(i=0; i<H->TableSize; i++) {
		p = H->TheLists[i].Next;
		while( p != NULL )
		{
			tmp = p->Next;
			free(p);
			p = tmp;
		}
	}
	free( H->TheLists );
	free( H );
	return;
} 

void print(HashTable *H) {
	List *p;
	int i;
	for(i=0; i<H->TableSize; i++) {
		p = H->TheLists[i].Next;
		while( p ) {
			printf("%s\t", p->Element);
			p = p->Next;
		}
		printf("***\n");
	}
	return;
}

int main()
{
	HashTable *H;
	Position *pos;
	int TableSize = 0;
	printf("please input the size of the HashTable: ");
	scanf("%d", &TableSize);
	H = InitializeTable(TableSize); 
	InsertAndCount("abc", H);     // 可以事先定义一个字符数组再传进去 
	InsertAndCount("qwe", H);
	InsertAndCount("feng", H);
	InsertAndCount("Berlin", H);
	print( H );
	printf("\n");
	pos = Delete("abc", H);
	printf("%s\n", pos->Element);
//	print( H );
	return 0;
}
