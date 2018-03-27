#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100
#define VertexNum int
#define FALSE 0
#define TRUE 1
enum GraphType { DG, UG, DN, UN };

typedef struct Node {	/* 边表结点 */
	int AdjV;			/* 邻接点域 */ 
	struct Node *next;	/* 指向下一个邻接点的指针域 */
	/* 必要时可以加一个权值  ElementType Weight; */ 
}EdgeNode;

typedef char VertexType;	
typedef struct VNode {		/* 顶点表结点 */
	VertexType Vertex;		/* 顶点类型 */ 
	EdgeNode *FirstEdge;	/* 边表头结点 */ 
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];	/* AdjList是邻接表类型 */
typedef struct {		 
	AdjList Adjlist;	/* 邻接表 */ 
	int n, e;			/* 顶点数和边数 */ 
	int *Visited;		/* 记录顶点或邻接点是否被访问过 */
	enum GraphType GType;	/* 图类型 */ 
}ALGraph;

typedef struct {
	EdgeNode *front;
	EdgeNode *rear;
}LinkQueue;

LinkQueue *CreateQueue() {	
	/* Create an empty queue */
	EdgeNode *Q;
	LinkQueue *LQ = (LinkQueue *)malloc(sizeof(LinkQueue));
	if( LQ )
		Q = LQ->front = LQ->rear = NULL;
	return LQ;
}

int isEmpty(LinkQueue *PtrL) {	
	/* Judge whether the queue is empty or not */	
	return ( PtrL->front == NULL );
}

void AddQ(LinkQueue *PtrL, int Adjv)
{	/* add a node to the queue */
	EdgeNode *v = (EdgeNode *)malloc(sizeof(EdgeNode));
	if( !v )
		FatalError("Failed to allocate memory space!");
	v->AdjV = Adjv;
	v->next = NULL;
	if( isEmpty(PtrL) ) {
		PtrL->front = PtrL->rear = v;
	} else {
		PtrL->rear->next = v;
		PtrL->rear = v;
	}
	return;
}

VertexNum DeleteQ(LinkQueue *PtrL)
{	/* 返回顶点的序号 */    
	EdgeNode *p;
	VertexNum i;
	if( isEmpty(PtrL) )
		FatalError("the queue is empty!");
	p = PtrL->front;
	if( PtrL->front == PtrL->rear )
		PtrL->front = PtrL->rear = NULL;	
	else
		PtrL->front = p->next;
	i = p->AdjV;
	free(p);	 
	return i;
}

ALGraph *Init() {
	ALGraph *graph;
	graph = (ALGraph *)malloc(sizeof(ALGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph;
}

void CreateALGraph(ALGraph *G) {
	int i, j, k;
	G->GType = DG;
	EdgeNode *Edge;
	printf("please input the num of Vertex and Edge(Input Format:Vertex,Edge):\n");
	scanf("%d,%d",&G->n, &G->e);
	
	G->Visited = (int *)malloc(sizeof(int) * G->n);
	if( !G->Visited )
		FatalError("Failed to allocate memory space!");
	for(i=0; i<G->n; i++)
		G->Visited[i] = FALSE;
		
	printf("please input the Vertex(Input Format:VertexName<CR>):\n");	  /* <CR> is Button Enter */
	for(i=0; i<G->n; i++) {
		scanf("\n%c", &(G->Adjlist[i].Vertex));
		G->Adjlist[i].FirstEdge = NULL;		/* point to the NULL at the first time */
	}	
	
	printf("please input the Edge(Input Format:BeginVertex,EndVertex<CR>):\n");
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d", &i, &j);		/* <Vi, Vj> is an edge */
		Edge = (EdgeNode *)malloc(sizeof(EdgeNode));
		if( !Edge )
			FatalError("Failed to allocate memory space!");
		Edge->AdjV = j;
		Edge->next = G->Adjlist[i].FirstEdge;		/* Insert to the head */
		G->Adjlist[i].FirstEdge = Edge;
	}
}

void BFS(ALGraph *G) {
	// 时间复杂度为O(|V|+|E|) 
	LinkQueue *Q = CreateQueue();
	EdgeNode *V, *W;
	int i, j;
	for(i=0; i<G->n; i++) {
		if( !G->Visited[i] ) {		/* 顶点Vi */
			G->Visited[i] = TRUE;
			printf("visit vertex %c\n", G->Adjlist[i].Vertex);
			AddQ(Q, i);
			while( !isEmpty(Q) ) {
				j = DeleteQ(Q);
				for(V=G->Adjlist[j].FirstEdge; V; V=V->next) {
					if( !G->Visited[V->AdjV] ) {
						G->Visited[V->AdjV] = TRUE;
						printf("visit vertex %c\n", G->Adjlist[V->AdjV].Vertex);
						AddQ(Q, V->AdjV);
					}
				}
			}
		}
	}
} 

int main()
{
	ALGraph *G;
	G = Init();
	CreateALGraph( G );
	BFS( G );
}
