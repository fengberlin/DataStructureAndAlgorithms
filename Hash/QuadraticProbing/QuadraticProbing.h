/* 平方探测法散列表的.h文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;	/* 关键字类型用整型 */

#ifndef _HashQuad_H
#define _HashQuad_H

typedef unsigned int Index;		/* 散列地址类型 */
typedef Index Position; 		/* 数据所在位置与散列地址是同一类型 */

struct HashTbl;
typedef struct HashTbl HashTable;

static int NextPrime(int n);
HashTable *InitializeTable(int TableSize);
Position Hash(ElementType key, int TableSize);
void DestoryTable(HashTable *H);
int Delete(HashTable *H, ElementType key);
void print(HashTable *H);
Position Find(HashTable *H, ElementType key);
void Insert(HashTable *H, ElementType key);
ElementType Retrieve(Position p, HashTable *H);     // 按位置检索一个键值 
HashTable *Rehash(HashTable *H);     // 再散列法, 即当装填因子过大时, 加倍扩大散列表

#endif    /* _HashQuad_H */
