#include "QuadraticProbing.h"

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)
#define MinTableSize 10

enum EntryType {
	Legitimate,		/* Legitimate->合法的, 即表示元素是存在的 */
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
	/* 单元 *TheCells 是一个数组, 每个元素是HashEntry */
	/* 随后分配存储 */
};

static int NextPrime(int n) {
	/* 假定 n>=10 */
	/* 找一个合适的TableSize */
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
		Error("散列表太小了");
		return NULL;
	}
	
	/* 分配散列表 */
	HashTable *H = (HashTable *)malloc(sizeof(HashTable));
	if( H == NULL ) {
		FatalError("空间溢出!!!"); 
	}
	H->TableSize = NextPrime(TableSize);
	
	/* 为数组分配空间 */
	H->TheCells = (Cell *)malloc(sizeof(Cell)*H->TableSize);
	if( H->TheCells == NULL ) {
		FatalError("空间溢出!!!");
	}
	int i;
	for(i=0; i<H->TableSize; i++) {
		H->TheCells[i].Info = Empty;
	} 
	return H;
}

Position Hash(ElementType key, int TableSize) {
	/* 构造散列函数并计算出key的地址 */ 
	/* 这里给出一个数字为关键字的散列函数构造方法: 除留余数法 */
	/* 这里假设key都为正数或者0 */ 
	Position pos;
	pos = key % TableSize;
	if( pos < 0 ) {
		FatalError("空间溢出!!!");
	}
	return pos;
}

//Position Hash(const char *key, int TableSize) {
//	/* 这里给出一个字符串为关键字的散列函数构造方法: 移位法 */
//	unsigned int l = 0;		/* 散列函数值，初始化为0 */
//	while( *key != '\0' ) {		/* 位移映射 */ 
//		l = (l << 5) + *key++;		// 移位法, 每位字符占5位  
//	}
//	return l % TableSize;
//} 

Position Find(HashTable *H, ElementType key) {
	Position CurrentPos, NewPos;
	int CollisionNum = 0;	/* 记录冲突次数 */
	NewPos = CurrentPos = Hash(key, H->TableSize);
	while( H->TheCells[NewPos].Info != Empty && H->TheCells[NewPos].Element != key ) {
		/* 字符串类型的关键字需要strcmp函数 */
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
	/* 散列表插入关键字key */
	Position pos;
	pos = Find(H, key);
	if( H->TheCells[pos].Info != Legitimate ) {		/* 确认在此插入 */
		H->TheCells[pos].Info = Legitimate;
		H->TheCells[pos].Element = key;		/* 字符串类型的关键字需要strcpy函数 */
	}
}

int Delete(HashTable *H, ElementType key) {
	/* 开放定址散列表需要"懒惰删除", 即增加一个"删除"操作, 而不是真正删除 */ 
	/* 判断某个关键字是否被“删除” */
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
			printf("所在位置为[%d], 键值为%d\n", i, H->TheCells[i].Element);	
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

