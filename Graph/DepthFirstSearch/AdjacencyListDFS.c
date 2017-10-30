#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100		/* 最大顶点数设为100 */ 
enum GraphType { DG, UG, DN, UN };		/* 4种图类型 */
typedef int ElementType;
#define FALSE 0
#define TRUE 1 

typedef struct Node {		/* 边表结点 */
	int AdjV;				/* 邻接点域 */
	struct Node *next;		/* 指向下一个邻接点的指针域 */
//	ElementType weight;		/* 如需要权值的话可以加这条语句 */ 
}EdgeNode;

typedef char VertexType;
typedef struct VNode {		/* 顶点表结点 */ 
	VertexType Vertex;		/* 顶点表结点 */ 
	EdgeNode *FirstEdge;	/* 边表头结点 */  
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];	/* AdjList是邻接表类型 */
typedef struct {
	AdjList Adjlist;		/* 邻接表 */ 
	int n, e; 				/* 顶点数和边数 */
	int *Visited;			/* 记录顶点或邻接点是否被访问过 */
	enum GraphType GType;		/* 图类型 */ 
}ALGraph;

ALGraph *Init() {	/* 初始化图 */ 
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
	/* 以Vi为出发点对一个连通分量进行DFS搜索 */
	EdgeNode *W;
	printf("visit vertex: %c\n", G->Adjlist[Vi].Vertex);
	
	/* 相当于VisitFunc(Vi), 即访问顶点Vi */
	G->Visited[Vi] = TRUE;		/* 标记Vi已访问 */
	for(W=G->Adjlist[Vi].FirstEdge; W; W=W->next) {
		if( !G->Visited[W->AdjV] ) {
			DFS(G, W->AdjV);
		}
	}
}

void DFS_ALG(ALGraph *G) {
	/* 对图的各个连通分量进行递归遍历 */
	/* 时间复杂度为O(|V|+|E|) */
	int i;
	for(i=0; i<G->n; i++)
		G->Visited[i] = FALSE;		/* 标志向量初始化 */
	for(i=0; i<G->n; i++) {
		if( !G->Visited[i] )	/* 若Vi未被访问过 */
			DFS(G, i);		/* 从Vi开始探索一个连通分量 */ 
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
