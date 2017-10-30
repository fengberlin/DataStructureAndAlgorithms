#include "SeparateChaining.h"

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MinTableSize (10)

typedef struct ListNode {
	ElementType Element;     /* Element��һ������ */
	unsigned short Times;	/* ���������н����������Ƶͳ��Ӧ��ʵ�������ڳ��ִ��� */
	struct ListNode *Next;
}Position, List;

/* Ϊ�˼����, ���������ͷ������ɢ�б�����Ԫ�� */

typedef struct HashTbl {
	int TableSize;
	struct ListNode *TheLists;		// ��ʵ��һ������ 
}HashTable; 

HashTable *InitializeTable(int TableSize) {
	HashTable *H;
	int i;
	if( TableSize < MinTableSize ) {
		Error("ɢ�б�̫С");
		return NULL;
	}
	/* ���·���ɢ�б� */
	H = (HashTable *)malloc(sizeof(HashTable));
	if( H == NULL )
		FatalError("�ռ����!!!");
	H->TableSize = NextPrime( TableSize );
	
	/* ���·����ͷ���� */
	H->TheLists = (List *)malloc(sizeof(List) * H->TableSize);
	if( H->TheLists == NULL )
		FatalError("�ռ����!!!");
	for(i=0; i<H->TableSize; i++) {
		H->TheLists[i].Element[0] = '\0';
		H->TheLists[i].Times = 0;	  /* ���������н������ */
		H->TheLists[i].Next  = NULL;
	}
	return H;
}

static int NextPrime( int n ) {	
	/* Ѱ��һ�����ʵ�������ΪTableSize */
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
	/* ���ַ����ؼ���ת��Ϊ������ʽ */
	unsigned int h = 0;
	while( *key != '\0' )
		h = ( h << 5 ) + *key++;
	return h % TableSize;
}

Position *Find(HashTable *H, ElementType key) {	
	/* Ѱ�ҹؼ���λ�� */
	Position *p;
	List *L;
	L = &(H->TheLists[Hash(key, H->TableSize)]);    /* H->TheLists[Hash(key, H->TableSize)] */
	p = L->Next;	/* pָ�������ĵ�һ��Ԫ�� */
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
	else {	  /* �ؼ���Ϊ�ҵ� */
		NewCell = (List *)malloc(sizeof(List));
		if( NewCell == NULL )
			FatalError("�ռ����!!!");
		else {
			L = &(H->TheLists[Hash(key, H->TableSize)]);
			NewCell->Next = L->Next;	/* �����һ����� */
			L->Next = NewCell;
			strcpy(NewCell->Element, key);
			NewCell->Times = 1;
			L->Times++;		/* ͷ����Times��ʾ������ĳ���, ����1 */
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
	InsertAndCount("abc", H);     // �������ȶ���һ���ַ������ٴ���ȥ 
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
