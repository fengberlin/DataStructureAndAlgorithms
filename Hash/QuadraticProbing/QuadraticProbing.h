/* ƽ��̽�ⷨɢ�б��.h�ļ� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;	/* �ؼ������������� */

#ifndef _HashQuad_H
#define _HashQuad_H

typedef unsigned int Index;		/* ɢ�е�ַ���� */
typedef Index Position; 		/* ��������λ����ɢ�е�ַ��ͬһ���� */

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
ElementType Retrieve(Position p, HashTable *H);     // ��λ�ü���һ����ֵ 
HashTable *Rehash(HashTable *H);     // ��ɢ�з�, ����װ�����ӹ���ʱ, �ӱ�����ɢ�б�

#endif    /* _HashQuad_H */
