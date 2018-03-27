/* �������ӷ�ɢ�б�.h�ļ� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYLENGTH 15	/* �ؼ����ַ����ĳ��Ȳ�����15 */
typedef char ElementType[KEYLENGTH+1];	   /* �ؼ����������ַ��� */
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
