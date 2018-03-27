#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100
enum GraphType { DG, UG, DN, UN };
typedef char VertexType;
typedef int VertexNum;

typedef struct Node{	/* 边表结点 */
	int Adjv;		/* 邻接点域 */ 
//	int Weight;		/* 权重 */ 
	struct Node *next;		/* 指向下一个邻接点的指针 */
}EdgeNode; 

typedef struct VNode{	/* 顶点表结点 */
	VertexType vertex;		/* 顶点 */
	EdgeNode *FirstEdge;	/* 指向边表头结点的指针 */
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];
typedef struct {
	AdjList Adjlist;	/* 邻接点 */
	int n, e;		/* 顶点数和边数 */ 
	enum GraphType GType;	/* 图类型 */
}ALGraph;

typedef struct {
	EdgeNode *front;
	EdgeNode *rear;
}LinkQueue;

LinkQueue *CreateQueue()
{	/* 建立一个带空头结点的队列 */
	EdgeNode *Q;
	LinkQueue *LQ;
	LQ = (LinkQueue *)malloc(sizeof(LinkQueue));
	if( !LQ )
		FatalError("Failed to allocate memory!");
	Q = LQ->front = LQ->rear = NULL;
	return LQ; 
}

int isEmpty(LinkQueue *PtrL)
{	/* 判断队列是否为空 */
	return ( PtrL->front==NULL && PtrL->rear==NULL );
} 

void AddQ(LinkQueue *PtrL, int Adjv)
{
	EdgeNode *Cell;
	Cell = (EdgeNode *)malloc(sizeof(EdgeNode));
	if( !Cell )
		FatalError("Failed to allocate memory!");
	Cell->Adjv = Adjv;
	Cell->next = NULL;
	if( isEmpty(PtrL) )
	{
		PtrL->front = Cell;
		PtrL->rear = Cell;
	}
	else {
		PtrL->rear->next = Cell;
		PtrL->rear = Cell;
	}
	return;
}

VertexNum DeleteQ(LinkQueue *PtrL)
{
	EdgeNode *w;
	VertexNum i;	
	if( isEmpty(PtrL) )
		FatalError("Failed to allocate memory!");
	w = PtrL->front;
	if( PtrL->front==PtrL->rear && !PtrL->front && !PtrL->rear )
		PtrL->front = PtrL->rear = NULL;
	else if( PtrL->front != PtrL->rear )
		PtrL->front = PtrL->front->next;
	i = w->Adjv;
	free(w);
	return i;
}

ALGraph *Init()
{
	ALGraph *graph;
	graph = (ALGraph *)malloc(sizeof(ALGraph));
	if( !graph )
		FatalError("Failed to allocate memory!");
	return graph;
}

void CreateALGraph(ALGraph *G)
{
	int i, j, k;
	EdgeNode *Edge;
	G->GType = UN;
	printf("please input the num of Vertex and Edge(Input Format:Vertex,Edge):\n");
	scanf("%d,%d", &G->n, &G->e);
	printf("please input the Vertex(Input Format:VertexName<CR>):\n");
	for(i=0; i<G->n; i++)
	{
		scanf("\n%c", &G->Adjlist[i].vertex);
		G->Adjlist[i].FirstEdge = NULL;
	}
	printf("Please input the Edge(<Vi,Vj>)(Input Format:i,j<CR>):\n");
	for(k=0; k<G->e; k++)
	{
		scanf("\n%d,%d", &i, &j);
		Edge = (EdgeNode *)malloc(sizeof(EdgeNode));
		if( !Edge )
			FatalError("Failed to allocate memory!");
		Edge->Adjv = j;
		Edge->next = G->Adjlist[i].FirstEdge;
		G->Adjlist[i].FirstEdge = Edge;
	}
	return;	
}

void ToplogicalSort(ALGraph *G, int ToplogicalOrder[])
{	/* 对G进行拓扑排序,  ToplogicalOrder[]顺序存储排序后的顶点下标 */
	int Indegree[MaxVertexNum], cnt=0;
	int v;
	EdgeNode *w;
	LinkQueue *Q = CreateQueue();
	
	/* 初始化Indegree[] */
	for(v=0; v<G->n; v++)
		Indegree[v] = 0;
	
	/* 遍历图, 得到Indegree[] */
	for(v=0; v<G->n; v++)
		for(w=G->Adjlist[v].FirstEdge; w; w=w->next)
			Indegree[w->Adjv]++;	/* 对有向边<v, w->Adjv>累计终点的入度 */
			
	/* 将所有入度为0的顶点入队列 */
	for(v=0; v<G->n; v++)
		if( Indegree[v] == 0 )
			AddQ(Q, v);
			
	/* 下面进入拓扑排序 */
	while( !isEmpty(Q) )
	{
		v = DeleteQ(Q);		/* 弹出一个入度为0的顶点 */
		ToplogicalOrder[cnt++] = v;		/* 将之存为结果序列的下一个元素 */
		/* 对vde每一个邻接点w->Adjv */
		for(w=G->Adjlist[v].FirstEdge; w; w=w->next)
			if( --Indegree[w->Adjv] == 0 )		/* 若删除v使得w->Adjv入度为0 */
				AddQ(Q, w->Adjv); 
	} 
	
	if( cnt != G->n )
		printf("图中有回路!");
}

int main()
{
	ALGraph *G;
	G = Init();
	CreateALGraph(G);
	int ToplogicalOrder[G->n];
	ToplogicalSort(G, ToplogicalOrder);
	return 0;
}
