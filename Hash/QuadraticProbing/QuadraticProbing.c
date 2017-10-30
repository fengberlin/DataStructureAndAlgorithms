#include "QuadraticProbing.h"

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)
#define MinTableSize 10

enum EntryType {
	Legitimate,		/* Legitimate->�Ϸ���, ����ʾԪ���Ǵ��ڵ� */
	Empty,
	Deleted
};

typedef struct HashEntry {
	ElementType Element;
	enum EntryType Info;
}Cell;

struct HashTbl {
	int TableSize;
	Cell *TheCells;
	/* ��Ԫ *TheCells ��һ������, ÿ��Ԫ����HashEntry */
	/* ������洢 */
};

static int NextPrime(int n) {
	/* �ٶ� n>=10 */
	/* ��һ�����ʵ�TableSize */
	int i;
	if( i % 2 == 0 ) {
		n++;
	}
	for(; ; i+=2) {
		for(i=3; i*i<=n; i+=2) {
			if( n % i == 0 )
				break;
		}
		if( i*i > n ) 
			return n;
	}
}

HashTable *InitializeTable(int TableSize) {
	if( TableSize < MinTableSize ) {
		Error("ɢ�б�̫С��");
		return NULL;
	}
	
	/* ����ɢ�б� */
	HashTable *H = (HashTable *)malloc(sizeof(HashTable));
	if( H == NULL ) {
		FatalError("�ռ����!!!"); 
	}
	H->TableSize = NextPrime(TableSize);
	
	/* Ϊ�������ռ� */
	H->TheCells = (Cell *)malloc(sizeof(Cell)*H->TableSize);
	if( H->TheCells == NULL ) {
		FatalError("�ռ����!!!");
	}
	int i;
	for(i=0; i<H->TableSize; i++) {
		H->TheCells[i].Info = Empty;
	} 
	return H;
}

Position Hash(ElementType key, int TableSize) {
	/* ����ɢ�к����������key�ĵ�ַ */ 
	/* �������һ������Ϊ�ؼ��ֵ�ɢ�к������췽��: ���������� */
	/* �������key��Ϊ��������0 */ 
	Position pos;
	pos = key % TableSize;
	if( pos < 0 ) {
		FatalError("�ռ����!!!");
	}
	return pos;
}

//Position Hash(const char *key, int TableSize) {
//	/* �������һ���ַ���Ϊ�ؼ��ֵ�ɢ�к������췽��: ��λ�� */
//	unsigned int l = 0;		/* ɢ�к���ֵ����ʼ��Ϊ0 */
//	while( *key != '\0' ) {		/* λ��ӳ�� */ 
//		l = (l << 5) + *key++;		// ��λ��, ÿλ�ַ�ռ5λ  
//	}
//	return l % TableSize;
//} 

Position Find(HashTable *H, ElementType key) {
	Position CurrentPos, NewPos;
	int CollisionNum = 0;	/* ��¼��ͻ���� */
	NewPos = CurrentPos = Hash(key, H->TableSize);
	while( H->TheCells[NewPos].Info != Empty && H->TheCells[NewPos].Element != key ) {
		/* �ַ������͵Ĺؼ�����Ҫstrcmp���� */
		if( (++CollisionNum) % 2 ) {
			NewPos = CurrentPos + (CollisionNum+1)/2 * (CollisionNum+1)/2;
			while( NewPos >= H->TableSize ) {
				NewPos -= H->TableSize;
			}
		} else {
			NewPos = CurrentPos - (CollisionNum+1)/2 * (CollisionNum+1)/2;
			while( NewPos < 0 ) {
				NewPos += H->TableSize;
			}
		}
	}
	return NewPos;
} 

void Insert(HashTable *H, ElementType key) {
	/* ɢ�б����ؼ���key */
	Position pos;
	pos = Find(H, key);
	if( H->TheCells[pos].Info != Legitimate ) {		/* ȷ���ڴ˲��� */
		H->TheCells[pos].Info = Legitimate;
		H->TheCells[pos].Element = key;		/* �ַ������͵Ĺؼ�����Ҫstrcpy���� */
	}
}

int Delete(HashTable *H, ElementType key) {
	/* ���Ŷ�ַɢ�б���Ҫ"����ɾ��", ������һ��"ɾ��"����, ����������ɾ�� */ 
	/* �ж�ĳ���ؼ����Ƿ񱻡�ɾ���� */
	Position pos;
	int ret = 0;
	pos = Find(H, key); 
	if( H->TheCells[pos].Info == Legitimate ) {
		H->TheCells[pos].Info = Deleted;
		ret = 1;
	}
	return ret;	
} 

void print(HashTable *H) {
	Position p;
	int i;
	for(i=0; i<H->TableSize; i++) {
		if( H->TheCells[i].Info == Empty ) continue;
		else if( H->TheCells[i].Info == Legitimate ) {
			printf("����λ��Ϊ[%d], ��ֵΪ%d\n", i, H->TheCells[i].Element);	
		}
	}
}

int main()
{
	HashTable *H;
	int TblSize;
	Position p;
	ElementType key;
	printf("Please input the size of the HashTable(you had'better input a number>=10): ");
	scanf("%d", &TblSize);
	H = InitializeTable(TblSize);
	if( H == NULL )
		return 0;
	printf("please input the key:\n");
	scanf("%d",&key);
	while( key >= 0 )
	{
		Insert(H, key);
		scanf("%d", &key);
	}
	print( H );
	printf("\n");
	return 0;
}

