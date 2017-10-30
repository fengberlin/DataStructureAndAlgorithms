#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100
#define INFINITY 65535
#define FALSE 0
#define TRUE 1
typedef char VertexType;
typedef int EdgeType;
enum GraphType { DG, UG, DN, UN };

typedef struct {
	VertexType Vertices[MaxVertexNum];		/* 顶点表 */ 
	EdgeType Edges[MaxVertexNum][MaxVertexNum];		/* 邻接矩阵, 即边表 */ 
	int n, e;		/* 顶点数和边数 */ 
	int *Visited;
	enum GraphType GType;	/* 图类型 */
}MGraph;

typedef struct {
	int vertex[MaxVertexNum];
	int front;
	int rear;	
}Queue; 

Queue *Initialize() {
	Queue *Q;
	Q = (Queue *)malloc(sizeof(Queue));
	if( !Q )
		FatalError("Failed to allocate memory!");
	Q->front = Q->rear = 0;
	return Q;
}

int isEmpty(Queue *PtrQ) {
	return ( PtrQ->front == PtrQ->rear );
}

int isFull(Queue *PtrQ) {
	return ( (PtrQ->rear+1)%MaxVertexNum == PtrQ->front );
}

void AddQ(Queue *PtrQ, int VertexNum)
{
	if( isFull(PtrQ) )
		FatalError("the queue is full!");
	PtrQ->rear = (PtrQ->rear+1) % MaxVertexNum;
	PtrQ->vertex[PtrQ->rear] = VertexNum;
	return; 
}

int DeleteQ(Queue *PtrQ)
{
	int result;
	if( isEmpty(PtrQ) )
		FatalError("the queue is empty!");
	PtrQ->front = (PtrQ->front+1) % MaxVertexNum;
	result = PtrQ->vertex[PtrQ->front];
	return result;
}

MGraph *Init() {
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory!");
	return graph;
}

void CreateMGraph(MGraph *G) {
	int i, j, k, w;
	G->GType = UN;	
	printf("Please input the num of vertex and edge(Input Format:VertexNum,EdgeNum):\n");
	scanf("%d,%d", &G->n, &G->e);
	
	G->Visited = (int *)malloc(sizeof(int));
	if( !G->Visited )
		FatalError("Failed to allocate memory!");
//	for(i=0; i<G->n; i++)
//		Visited[i] = FALSE;		/* 记录Vertex是否已被访问 */
	
	printf("Please input the vertex(Input Format:VertexName<CR>):\n");
	for(i=0; i<G->n; i++) {
		scanf("\n%c", &(G->Vertices[i]));
		G->Visited[i] = FALSE;		/* 记录Vertex是否已被访问 */
	}
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++)
			G->Edges[i][j] = INFINITY;		/* 初始化邻接矩阵 */ 
	}
	printf("Please input the edges(Input Format:BeginVertexNum,EndVertexNum,Weight<CR>):\n");
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d,%d", &i, &j, &w);
		G->Edges[i][j] = w;		/* 邻接矩阵是对称的(无向的时候) */
		G->Edges[j][i] = w;
	}			
}

int isEdge(MGraph *G, int i, int j) {
	return ( G->Edges[i][j] < INFINITY ? TRUE : FALSE ) ;
}

void BFS(MGraph *G, int vertex) {
	// 时间复杂度为O(|V|+|E|) 
	Queue *Q = Initialize();
	int v, i;
	if( !G->Visited[vertex] ) {
		printf("visit:Vertex %c\n", G->Vertices[vertex]);
		G->Visited[vertex] = TRUE;
		AddQ(Q, vertex);
		while( !isEmpty(Q) ) {
			v = DeleteQ(Q);
			for(i=0; i<G->n; i++) {
				if( !G->Visited[i] && isEdge(G, v, i) ) {
					printf("visit:Vertex %c\n", G->Vertices[i]);
					G->Visited[i] = TRUE;
					AddQ(Q, i);
				}
			}
		}
	} 
}

int main()
{
	MGraph *G;
	G = Init();
	CreateMGraph( G );
	BFS( G, 0 );
	return 0;
}
