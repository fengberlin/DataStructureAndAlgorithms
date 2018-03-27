#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100		/* ��󶥵�����Ϊ100 */ 
enum GraphType { DG, UG, DN, UN };		/* 4��ͼ���� */
typedef int ElementType;
#define FALSE 0
#define TRUE 1 

typedef struct Node {		/* �߱��� */
	int AdjV;				/* �ڽӵ��� */
	struct Node *next;		/* ָ����һ���ڽӵ��ָ���� */
//	ElementType weight;		/* ����ҪȨֵ�Ļ����Լ�������� */ 
}EdgeNode;

typedef char VertexType;
typedef struct VNode {		/* ������� */ 
	VertexType Vertex;		/* ������� */ 
	EdgeNode *FirstEdge;	/* �߱�ͷ��� */  
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];	/* AdjList���ڽӱ����� */
typedef struct {
	AdjList Adjlist;		/* �ڽӱ� */ 
	int n, e; 				/* �������ͱ��� */
	int *Visited;			/* ��¼������ڽӵ��Ƿ񱻷��ʹ� */
	enum GraphType GType;		/* ͼ���� */ 
}ALGraph;

ALGraph *Init() {	/* ��ʼ��ͼ */ 
	ALGraph *graph = (ALGraph *)malloc(sizeof(ALGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

void CreateALGraph(ALGraph *G) {	/* Use AdjacencyList to represent the graph */
	int i, j, k; 
	EdgeNode *Edge;
	G->GType = UG;		/* undirected graph */
	printf("please input the num of Vertex and Edge(Input format is:VertexNum,EdgeNum):\n"); 
	scanf("%d,%d", &(G->n), &(G->e));
	
	// Initialize the Visited List
	G->Visited = (int *)malloc(sizeof(int) * G->n);
	if( !G->Visited )
		FatalError("Failed to allocate memory space!");
	for(i=0; i<G->n; i++)
		G->Visited[i] = FALSE;
	
	printf("please input the Vertexs(Input Format is:Vertex<CR>):\n");	/* <CR> is Button Enter */
	for(i=0; i<G->n; i++) {
		scanf("\n%c", &(G->Adjlist[i].Vertex));
		G->Adjlist[i].FirstEdge = NULL;		/* point to the NULL at the first time */
	}
	printf("please input the edge between two Vertices(Input Format is:i,j<CR>):\n");
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d", &i, &j);		/* <Vi, Vj> is an edge */
		Edge = (EdgeNode *)malloc(sizeof(EdgeNode));
		Edge->AdjV = j;
		Edge->next = G->Adjlist[i].FirstEdge;	/* Insert to the head */
		G->Adjlist[i].FirstEdge = Edge;
	}		
}

void DFS(ALGraph *G, int Vi) {
	/* ��ViΪ�������һ����ͨ��������DFS���� */
	EdgeNode *W;
	printf("visit vertex: %c\n", G->Adjlist[Vi].Vertex);
	
	/* �൱��VisitFunc(Vi), �����ʶ���Vi */
	G->Visited[Vi] = TRUE;		/* ���Vi�ѷ��� */
	for(W=G->Adjlist[Vi].FirstEdge; W; W=W->next) {
		if( !G->Visited[W->AdjV] ) {
			DFS(G, W->AdjV);
		}
	}
}

void DFS_ALG(ALGraph *G) {
	/* ��ͼ�ĸ�����ͨ�������еݹ���� */
	/* ʱ�临�Ӷ�ΪO(|V|+|E|) */
	int i;
	for(i=0; i<G->n; i++)
		G->Visited[i] = FALSE;		/* ��־������ʼ�� */
	for(i=0; i<G->n; i++) {
		if( !G->Visited[i] )	/* ��Viδ�����ʹ� */
			DFS(G, i);		/* ��Vi��ʼ̽��һ����ͨ���� */ 
	}	
}

int main()
{
	ALGraph *G;
	G = Init();
	CreateALGraph( G );
	DFS_ALG( G );
	return 0;
}
