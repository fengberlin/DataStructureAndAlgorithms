#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100
enum GraphType { DG, UG, DN, UN };
typedef char VertexType;
typedef int VertexNum;

typedef struct Node{	/* �߱��� */
	int Adjv;		/* �ڽӵ��� */ 
//	int Weight;		/* Ȩ�� */ 
	struct Node *next;		/* ָ����һ���ڽӵ��ָ�� */
}EdgeNode; 

typedef struct VNode{	/* ������� */
	VertexType vertex;		/* ���� */
	EdgeNode *FirstEdge;	/* ָ��߱�ͷ����ָ�� */
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];
typedef struct {
	AdjList Adjlist;	/* �ڽӵ� */
	int n, e;		/* �������ͱ��� */ 
	enum GraphType GType;	/* ͼ���� */
}ALGraph;

typedef struct {
	EdgeNode *front;
	EdgeNode *rear;
}LinkQueue;

LinkQueue *CreateQueue()
{	/* ����һ������ͷ���Ķ��� */
	EdgeNode *Q;
	LinkQueue *LQ;
	LQ = (LinkQueue *)malloc(sizeof(LinkQueue));
	if( !LQ )
		FatalError("Failed to allocate memory!");
	Q = LQ->front = LQ->rear = NULL;
	return LQ; 
}

int isEmpty(LinkQueue *PtrL)
{	/* �ж϶����Ƿ�Ϊ�� */
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
{	/* ��G������������,  ToplogicalOrder[]˳��洢�����Ķ����±� */
	int Indegree[MaxVertexNum], cnt=0;
	int v;
	EdgeNode *w;
	LinkQueue *Q = CreateQueue();
	
	/* ��ʼ��Indegree[] */
	for(v=0; v<G->n; v++)
		Indegree[v] = 0;
	
	/* ����ͼ, �õ�Indegree[] */
	for(v=0; v<G->n; v++)
		for(w=G->Adjlist[v].FirstEdge; w; w=w->next)
			Indegree[w->Adjv]++;	/* �������<v, w->Adjv>�ۼ��յ����� */
			
	/* ���������Ϊ0�Ķ�������� */
	for(v=0; v<G->n; v++)
		if( Indegree[v] == 0 )
			AddQ(Q, v);
			
	/* ��������������� */
	while( !isEmpty(Q) )
	{
		v = DeleteQ(Q);		/* ����һ�����Ϊ0�Ķ��� */
		ToplogicalOrder[cnt++] = v;		/* ��֮��Ϊ������е���һ��Ԫ�� */
		/* ��vdeÿһ���ڽӵ�w->Adjv */
		for(w=G->Adjlist[v].FirstEdge; w; w=w->next)
			if( --Indegree[w->Adjv] == 0 )		/* ��ɾ��vʹ��w->Adjv���Ϊ0 */
				AddQ(Q, w->Adjv); 
	} 
	
	if( cnt != G->n )
		printf("ͼ���л�·!");
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
