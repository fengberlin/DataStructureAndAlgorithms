#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100	/* ��󶥵���Ϊ100 */
enum GraphType { DG, UG, DN, UN };		/* ����ͼ, ����ͼ, ������ͼ, ������ͼ */

typedef struct Node {	/* �߱��� */ 
	int AdjV;		/* �ڽӵ���  Adj->Adjacency�ڽ� */ 
	struct Node *next;		/* ָ����һ���ڽӵ��ָ���� */
	/* ��Ҫ��ʾ���ϵ�Ȩֵ��Ϣ, ��Ӧ����һ��������Weight */ 
}EdgeNode;

typedef char VertexType;	/* �������ַ���ʾ */
typedef struct VNode {		/* ������ʾ */
	VertexType Vertex;		/* ������ */ 
	EdgeNode *FirstEdge;	/* �߱�ͷָ�� */ 
}VertexNode;

/* ALGraph�����ڽӱ�ʽ�洢��ͼ���� */
typedef VertexNode AdjList[MaxVertexNum];	/* AdjList���ڽӱ����� */
typedef struct {
	AdjList Adjlist;	/* �ڽӱ� */
	int n, e;		/* �������ͱ��� */
	enum GraphType GType;		/* 4��ͼ���� */ 
}ALGraph;

ALGraph *Init() {	/* ��ʼ��ͼ */
	ALGraph *graph;
	graph = (ALGraph *)malloc(sizeof(ALGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

void CreateALGraph(ALGraph *G) {
	int i, j, k;
	EdgeNode *edge;
	
	G->GType = DG;		/* directed graph ����ͼ */
	printf("�����붥�����ͱ���(�����ʽΪ:������,����):\n");
	scanf("%d,%d", &(G->n), &(G->e));		/* ���붥�����ͱ��� */
	printf("�����붥����Ϣ(�����ʽΪ:�������<CR>, ÿ�������Իس���Ϊ����):\n");		/* <CR>�ǻس� */
	for(i=0; i<G->n; i++) {	/* ������n������Ķ���� */
		scanf("\n%c", &(G->Adjlist[i].Vertex));	/* ���붥����Ϣ ע��ո񣡣��� */ 
		G->Adjlist[i].FirstEdge = NULL;		/* ����ı߱�ͷָ����Ϊ�� */ 
	}
	printf("������ߵ���Ϣ(�����ʽΪ:i,j<CR>):\n");	/* <CR> -> �س� */
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d", &i, &j);	/* �����<Vi, Vj>�Ķ����Ӧ��� */
		edge = (EdgeNode *)malloc(sizeof(EdgeNode));	/* �����±߱���edge */
		edge->AdjV = j;		/* �ڽӵ����Ϊj */
		edge->next = G->Adjlist[i].FirstEdge;	/* ���±߱���edge���뵽����Vi�ı߱�ͷ */
		G->Adjlist[i].FirstEdge = edge;
		/* ��������ͼ, ��Ҫ����һ�����, ������ʾ��<Vj, Vi> */ 
	}
} 

int main()
{
	ALGraph *G;
	G = Init();
	CreateALGraph( G );
	return 0;
}

//#define MaxVertexNum 100    /* ��󶥵�����Ϊ100 */
//typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
//typedef int WeightType;        /* �ߵ�Ȩֵ��Ϊ���� */
//typedef char DataType;        /* ����洢������������Ϊ�ַ��� */
// 
///* �ߵĶ��� */
//typedef struct ENode *PtrToENode;
//struct ENode{
//    Vertex V1, V2;      /* �����<V1, V2> */
//    WeightType Weight;  /* Ȩ�� */
//};
//typedef PtrToENode Edge;
// 
///* �ڽӵ�Ķ��� */
//typedef struct AdjVNode *PtrToAdjVNode; 
//struct AdjVNode{
//    Vertex AdjV;        /* �ڽӵ��±� */
//    WeightType Weight;  /* ��Ȩ�� */
//    PtrToAdjVNode Next;    /* ָ����һ���ڽӵ��ָ�� */
//};
// 
///* �����ͷ���Ķ��� */
//typedef struct Vnode{
//    PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
//    DataType Data;            /* �涥������� */
//    /* ע�⣺�ܶ�����£����������ݣ���ʱData���Բ��ó��� */
//} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */
// 
///* ͼ���Ķ��� */
//typedef struct GNode *PtrToGNode;
//struct GNode{  
//    int Nv;     /* ������ */
//    int Ne;     /* ����   */
//    AdjList G;  /* �ڽӱ� */
//};
//typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */
// 
// 
// 
//LGraph CreateGraph( int VertexNum )
//{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
//    Vertex V;
//    LGraph Graph;
//     
//    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* ����ͼ */
//    Graph->Nv = VertexNum;
//    Graph->Ne = 0;
//    /* ��ʼ���ڽӱ�ͷָ�� */
//    /* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
//       for (V=0; V<Graph->Nv; V++)
//        Graph->G[V].FirstEdge = NULL;
//             
//    return Graph; 
//}
//        
//void InsertEdge( LGraph Graph, Edge E )
//{
//    PtrToAdjVNode NewNode;
//     
//    /* ����� <V1, V2> */
//    /* ΪV2�����µ��ڽӵ� */
//    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
//    NewNode->AdjV = E->V2;
//    NewNode->Weight = E->Weight;
//    /* ��V2����V1�ı�ͷ */
//    NewNode->Next = Graph->G[E->V1].FirstEdge;
//    Graph->G[E->V1].FirstEdge = NewNode;
//         
//    /* ��������ͼ����Ҫ����� <V2, V1> */
//    /* ΪV1�����µ��ڽӵ� */
//    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
//    NewNode->AdjV = E->V1;
//    NewNode->Weight = E->Weight;
//    /* ��V1����V2�ı�ͷ */
//    NewNode->Next = Graph->G[E->V2].FirstEdge;
//    Graph->G[E->V2].FirstEdge = NewNode;
//}
// 
//LGraph BuildGraph()
//{
//    LGraph Graph;
//    Edge E;
//    Vertex V;
//    int Nv, i;
//     
//    scanf("%d", &Nv);   /* ���붥����� */
//    Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
//     
//    scanf("%d", &(Graph->Ne));   /* ������� */
//    if ( Graph->Ne != 0 ) { /* ����б� */ 
//        E = (Edge)malloc( sizeof(struct ENode) ); /* �����߽�� */ 
//        /* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
//        for (i=0; i<Graph->Ne; i++) {
//            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
//            /* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
//            InsertEdge( Graph, E );
//        }
//    } 
// 
//    /* ������������ݵĻ����������� */
//    for (V=0; V<Graph->Nv; V++) 
//        scanf(" %c", &(Graph->G[V].Data));
// 
//    return Graph;
//}
