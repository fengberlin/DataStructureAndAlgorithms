#include <stdio.h>
#include <stdlib.h>
/* ���������㷨 */
/* ���ݽṹ: ����
ʱ�临�Ӷ�	O(kN)	kΪ�ؼ��ֵ�λ�� 
�ռ临�Ӷ�	O(k+N)
*/

//typedef struct Node PtrToNode;
//typedef PtrToNode List;
//
//struct Node {
//	int key[MaxDigit];
//	PtrToNode *next;
//}; 
//
//List *RadixSort(List *A)
//{	/* �������� */
//	List *Bucket[Radix];	/* ����Radix��Ͱ */
//	List *Rear[Radix];		/* ��Ҫ��¼ÿ��Ͱ�����βԪ��λ�� */
//	int i, j, Digit;
//	
//	for(i=MaxDigit-1; i>=0; i--)	/* �����λ�ؼ��ֿ�ʼ */ 
//	{
//		for(j=0; j<Radix; j++)
//			Bucket[j] = Rear[j] = NULL;		/* ��ʼ�� */
//		while( A )
//		{	/* ���ؼ�����һ���䵽Ͱ */
//			Digit = A->key[i];		/* ȡ����ǰ�ؼ���λ */
//			if( !Bucket[Digit] )	/* ����Ӧ��Ͱ�ǿյ� */
//				Bucket[Digit] = A;	/* �����Ͱ */
//			else
//				Rear[Digit]->next = A;	/* �������Ͱβ */
//			Rear[Digit] = A;	/* ����βָ�� */
//			A = A->next; 
//		}	/* ����while������� */
//		for(j=Radix-1; j>=0; j--)	/* ������Ͱ��Ԫ���ռ����� */
//		{
//			if( Bucket[j] )
//			{
//				Rear[j]->next = A;
//				A = Bucket[j];
//			}
//		}	/* ����for�ռ����� */ 
//	} 
//	return A; 
//}


/**********************
*******�����ķָ���****
**********************/ 


/* �������� - ��λ���� */
/* ����Ԫ�������MaxDigit���ؼ��֣�����ȫ��ͬ����Radix */
#define MaxDigit 4
#define Radix 10
typedef int ElementType;
 
/* ͰԪ�ؽ�� */
struct Node {
    int key;
    struct Node *next;
};

typedef struct Node *PtrToNode;
 
/* Ͱͷ��� */
struct HeadNode {
    PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];
  
int GetDigit ( int X, int D )
{ /* Ĭ�ϴ�λD=1, ��λD<=MaxDigit */
    int d, i;
     
    for (i=1; i<=D; i++) {
        d = X % Radix;
        X /= Radix;
    }
    return d;
}
 
void LSDRadixSort( ElementType A[], int N )
{ /* �������� - ��λ���� */
     int D, Di, i;
     Bucket B;
     PtrToNode tmp, p, List = NULL; 
      
     for (i=0; i<Radix; i++) /* ��ʼ��ÿ��ͰΪ������ */
         B[i].head = B[i].tail = NULL;
     for (i=0; i<N; i++) { /* ��ԭʼ������������ʼ����List */
         tmp = (PtrToNode)malloc(sizeof(struct Node));
         tmp->key = A[i];
         tmp->next = List;
         List = tmp;
     }
     /* ���濪ʼ���� */ 
     for (D=1; D<=MaxDigit; D++) { /* �����ݵ�ÿһλѭ������ */
         /* �����Ƿ���Ĺ��� */
         p = List;
         while (p) {
             Di = GetDigit(p->key, D); /* ��õ�ǰԪ�صĵ�ǰλ���� */
             /* ��List��ժ�� */
             tmp = p; p = p->next;
             /* ����B[Di]��Ͱβ */
             tmp->next = NULL;
             if (B[Di].head == NULL)
                 B[Di].head = B[Di].tail = tmp;
             else {
                 B[Di].tail->next = tmp;
                 B[Di].tail = tmp;
             }
         }
         /* �������ռ��Ĺ��� */
         List = NULL; 
         for (Di=Radix-1; Di>=0; Di--) { /* ��ÿ��Ͱ��Ԫ��˳���ռ���List */
             if (B[Di].head) { /* ���Ͱ��Ϊ�� */
                 /* ��Ͱ����List��ͷ */
                 B[Di].tail->next = List;
                 List = B[Di].head;
                 B[Di].head = B[Di].tail = NULL; /* ���Ͱ */
             }
         }
     }
     /* ��List����A[]���ͷſռ� */
     for (i=0; i<N; i++) {
        tmp = List;
        List = List->next;
        A[i] = tmp->key;
        free(tmp);
     } 
}


/**********************
*******�����ķָ���****
**********************/ 


///* �������� - ��λ���� */
///* ����Ԫ�������MaxDigit���ؼ��֣�����ȫ��ͬ����Radix */
//#define MaxDigit 4
//#define Radix 10
// 
///* ͰԪ�ؽ�� */
//typedef struct Node *PtrToNode;
//struct Node{
//    int key;
//    PtrToNode next;
//};
// 
///* Ͱͷ��� */
//struct HeadNode {
//    PtrToNode head, tail;
//};
//typedef struct HeadNode Bucket[Radix];
//  
//int GetDigit ( int X, int D )
//{ /* Ĭ�ϴ�λD=1, ��λD<=MaxDigit */
//    int d, i;
//     
//    for (i=1; i<=D; i++) {
//        d = X % Radix;
//        X /= Radix;
//    }
//    return d;
//} 
//
//void MSD( ElementType A[], int L, int R, int D )
//{ /* ���ĵݹ麯��: ��A[L]...A[R]�ĵ�Dλ���������� */
//     int Di, i, j;
//     Bucket B;
//     PtrToNode tmp, p, List = NULL; 
//     if (D==0) return; /* �ݹ���ֹ���� */
//      
//     for (i=0; i<Radix; i++) /* ��ʼ��ÿ��ͰΪ������ */
//         B[i].head = B[i].tail = NULL;
//     for (i=L; i<=R; i++) { /* ��ԭʼ������������ʼ����List */
//         tmp = (PtrToNode)malloc(sizeof(struct Node));
//         tmp->key = A[i];
//         tmp->next = List;
//         List = tmp;
//     }
//     /* �����Ƿ���Ĺ��� */
//     p = List;
//     while (p) {
//         Di = GetDigit(p->key, D); /* ��õ�ǰԪ�صĵ�ǰλ���� */
//         /* ��List��ժ�� */
//         tmp = p; p = p->next;
//         /* ����B[Di]��Ͱ */
//         if (B[Di].head == NULL) B[Di].tail = tmp;
//         tmp->next = B[Di].head;
//         B[Di].head = tmp;
//     }
//     /* �������ռ��Ĺ��� */
//     i = j = L; /* i, j��¼��ǰҪ�����A[]�����Ҷ��±� */
//     for (Di=0; Di<Radix; Di++) { /* ����ÿ��Ͱ */
//         if (B[Di].head) { /* ���ǿյ�Ͱ��Ͱ����A[], �ݹ����� */
//             p = B[Di].head;
//             while (p) {
//                 tmp = p;
//                 p = p->next;
//                 A[j++] = tmp->key;
//                 free(tmp);
//             }
//             /* �ݹ�Ը�Ͱ��������, λ����1 */
//             MSD(A, i, j-1, D-1);
//             i = j; /* Ϊ��һ��Ͱ��Ӧ��A[]��� */
//         } 
//     } 
//}
//void MSDRadixSort( ElementType A[], int N )
//{ /* ͳһ�ӿ� */
//    MSD(A, 0, N-1, MaxDigit); 
//}

void print(ElementType *a, int len)
{
	int i;
	for(i=0; i<len; i++)
		printf("%d ", a[i]);
	printf("\n");
	return;
}

int main()
{
	ElementType a[] = {8,2,6,-1,7,1,6,5,9,2,0,3,63,15,24};
	int len = sizeof(a)/sizeof(a[0]);
	LSDRadixSort(a, len);
	print(a, len);
	return 0;
}
