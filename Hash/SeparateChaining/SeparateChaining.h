/* 分离链接法散列表.h文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYLENGTH 15	/* 关键字字符串的长度不超过15 */
typedef char ElementType[KEYLENGTH+1];	   /* 关键字类型用字符串 */
typedef unsigned int Index; 

#ifndef _HashSep_H
#define _HashSep_H

struct ListNode;
typedef struct ListNode Position, List;
struct HashTbl;
typedef struct HashTbl HashTable;

HashTable *InitializeTable(int TableSize);
void DestroyTable(HashTable *H);
static int NextPrime( int n );
Position *Find(HashTable *H, ElementType key);
void InsertAndCount(HashTable *H, ElementType key);
Index Hash(ElementType key, int TableSize);
Position *Delete(HashTable *H, ElementType key);

#endif		/* _HashSep_H */
