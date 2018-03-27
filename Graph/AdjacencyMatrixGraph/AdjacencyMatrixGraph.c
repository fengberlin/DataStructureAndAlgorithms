#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100	/* ��󶥵�����Ϊ100 */
#define INFINITY 65535		/* ����Ϊ˫�ֽ��޷������������ֵ65535 */ 
typedef char VertexType;		/* ����������Ϊ�ַ��� */
typedef int EdgeType;		/* �ߵ�Ȩֵ��Ϊ���� */
enum GraphType { DG, UG, DN, UN };		/* directed graph, undirected graph, directed network, undirected network */

/* �ڽӾ���洢ͼ */
typedef struct {
	VertexType Vertices[MaxVertexNum];		/* ����� */
	EdgeType Edges[MaxVertexNum][MaxVertexNum];		/* �ڽӾ���, ���߱� */
	int n, e;	/* ������n�ͱ���e */
	enum GraphType GType;	/* ͼ�����ͷ�4��: UG, DG, UN, DN */ 
}MGraph;		/* MGraph�����ڽӾ���洢��ͼ����  M->Matrix*/

MGraph *Init() {	/* ��ʼ��ͼ */
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

void CreateMGraph(MGraph *G) {		/* ����һ��������ͼ, ���ڽӾ���洢 */
	int i, j, k, w;
	G->GType = UN;		/* undirected network ������ͼ */
	printf("�����붥�����ͱ���(�����ʽΪ:������,����):\n");
	scanf("%d,%d", &(G->n), &(G->e));
	printf("�����붥����Ϣ(�����ʽΪ:�������<CR>, ÿ������������Իس���Ϊ����):\n");		/* <CR>�ǻس� */
	for(i=0; i<G->n; i++) {
		scanf("\n%c", &(G->Vertices[i]));		/* ���붥����Ϣ, ���������  ע�⻻�з�\n������*/
	}
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++) {
			G->Edges[i][j] = INFINITY;		/* ��ʼ���ڽӾ��� */
		}
	}
	printf("������ÿ���߶�Ӧ�������������ź�Ȩֵ, �����ʽΪ:i,j,w:\n");
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d,%d", &i, &j, &w);
		G->Edges[i][j] = w;
		G->Edges[j][i] = w;		/* ����ͼ���ڽӾ����ǶԳƵ� */ 
	}
}

//void InsertEdge(MGraph *G, int i, int j, int weight)
//{		/* ���Ƚ�һ��Edge�Ľ��, ����������, �յ�, Ȩ�� */
//	G->Edges[i][j] = weight;
//	G->Edges[j][i] = weight;
//}

int main()
{
	MGraph *G;
	G = Init();
	CreateMGraph( G );
	printf("weight=%d\n", G->Edges[0][1]);
	return 0;
} 

//#define MaxVertexNum 100    /* ��󶥵�����Ϊ100 */
//#define INFINITY 65535        /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
//typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
//typedef int WeightType;        /* �ߵ�Ȩֵ��Ϊ���� */
//typedef char DataType;        /* ����洢������������Ϊ�ַ��� */
//
///* �ߵĶ��� */
//typedef struct ENode *PtrToENode;
//struct ENode {
//    Vertex V1, V2;      /* �����<V1, V2> */
//    WeightType Weight;  /* Ȩ�� */
//};
//typedef PtrToENode Edge;
//
///* ͼ���Ķ��� */
//typedef struct GNode *PtrToGNode;
//struct GNode {
//    int Nv;  /* ������ */
//    int Ne;  /* ����   */
//    WeightType G[MaxVertexNum][MaxVertexNum]; /* �ڽӾ��� */
//    DataType Data[MaxVertexNum];      /* �涥������� */
//    /* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
//};
//typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */
//
//MGraph CreateGraph( int VertexNum ) { 
//	/* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
//    Vertex V, W;
//    MGraph Graph;
//     
//    Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
//    Graph->Nv = VertexNum;
//    Graph->Ne = 0;
//    /* ��ʼ���ڽӾ��� */
//    /* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
//    for (V=0; V<Graph->Nv; V++) {
//    	for (W=0; W<Graph->Nv; W++)  
//            Graph->G[V][W] = INFINITY;
//	}       
//    return Graph; 
//}
//        
//void InsertEdge( MGraph Graph, Edge E ) {
//     /* ����� <V1, V2> */
//     Graph->G[E->V1][E->V2] = E->Weight;    
//     /* ��������ͼ����Ҫ�����<V2, V1> */
////     Graph->G[E->V2][E->V1] = E->Weight;
//}
// 
//MGraph BuildGraph() {
//    MGraph Graph;
//    Edge E;
//    Vertex V;
//    int Nv, i;
//     
//    scanf("%d", &Nv);   /* ���붥����� */
//    Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
//     
//    scanf("%d", &(Graph->Ne));   /* ������� */
//    if ( Graph->Ne != 0 ) { /* ����б� */ 
//        E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */ 
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
//        scanf(" %c", &(Graph->Data[V]));
// 
//    return Graph;
//}
