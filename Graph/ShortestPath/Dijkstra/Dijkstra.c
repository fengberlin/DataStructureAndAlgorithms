#include <stdio.h>
#include <stdlib.h>
/* �ڽӾ���洢 - ��Ȩͼ�ĵ�Դ���·�㷨 */

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str),exit(1)

#define MaxVertexNum 100
#define INFINITY 65535
#define TRUE 1
#define FALSE 0 
enum GraphType { DG, UG, DN, UN };
typedef char VertexType;
typedef int EdgeType;
typedef int VertexNum;

typedef struct {	/* �ڽӾ���洢ͼ */
	VertexType vertex[MaxVertexNum];	/* ����� */
	EdgeType edge[MaxVertexNum][MaxVertexNum];	/* �ڽӾ���, ���߱� */
	int n, e;		/* �������ͱ��� */ 
	enum GraphType GType;	/* ͼ���� */
}MGraph; 

MGraph *Init() {
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory!");
	return graph;
} 

void CreateMGraph(MGraph *G) {	/* ����ͼ */
	int i, j, k, w;
	G->GType = DN;
	printf("Please input the num of vertex and edge(Input Format:VertexNum,EdgeNum<CR>):\n");
	scanf("\n%d,%d", &G->n, &G->e);
	printf("Please input the vertex(Input Format:VertexName<CR>):\n");
	for(i=0; i<G->n; i++)
		scanf("\n%c", &(G->vertex[i]));
	
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++)
			G->edge[i][j] = INFINITY;
	}		
			
	printf("Please input the edge(Input Format:i,j,weight<CR>):\n");
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d,%d", &i, &j, &w);
		G->edge[i][j] = w;
	}
}

///* ��Ȩͼ�ĵ�Դ���·�㷨 */
//VertexNum FindMinDist(MGraph *Graph, int dist[], int collected[])
//{	/* ����δ����¼������dist��С�� */
//	VertexNum MinV, V;
//	int MinDist = INFINITY;
//	
//	for(V=0; V<Graph->n; V++)
//	{
//		if( collected[V]==FALSE && dist[V]<MinDist )
//		{	/* ��Vδ����¼, ��dist[V]��С */
//			MinDist = dist[V];		/* ������С���� */
//			MinV = V;	/* ���¶�Ӧ���� */ 
//		}
//		if(MinDist < INFINITY)	/* ���ҵ���Сdist */
//			return MinV;	/* ���ض�Ӧ�Ķ����±� */
//		else 
//			return ERROR;	/* �������Ķ��㲻����, ���ش����� */ 
//	}
//}
//
//void Dijkstra(MGraph *G, int *dist, int *path, VertexNum S)
//{	/* �Ͻ�˹�����㷨---��·�����ȵ����Ĵ���������·�� */ 
//	int collected[MaxVertexNum];
//	VertexNum V, W;
//	
//	/* ��ʼ��: �˴�Ĭ���ڽӾ����в����ڵı���INFINITY��ʾ */
//	for(V=0; V<G->n; V++) 
//	{
//		dist[V] = G->edge[S][V];
//		if( dist[V] < INFINITY )
//			path[V] = S;
//		else
//			path[V] = 1;
//		collected[V] = FALSE;
//	}
//	/* �Ƚ�Դ�����뼯�� */
//	dist[S] = 0;
//	collected[S] = TRUE;
//	
//	while(1)
//	{	/* V=δ����¼�����е�dist��С�� */
//		V = FindMinDist(G, dist, collected);
//		if( V == Error )		/* ��������V������ */
//			break;
//		collected[V] = TRUE;	/* ��¼V */
//		for( W=0; W<G->n; W++)
//		{	/* ��ͼ�е�ÿ������ */
//			/* ��W��V���ڽӵ㲢��Ϊ����¼ */ 
//			if( collected[W]==FALSE && G->edge[V][W]<INFINITY )
//			{
//				if( G->edge[V][W] < 0 )		/* ���и��� */
//					FatalError("���ڸ���!");
//				
//				/* ����¼Vʹ��dist[W]��С */
//				if( dist[V]+G->edge[V][W] < dist[W] )
//				{
//					dist[W] = dist[V] + G->edge[V][W];		/* ����dist[W]ֵ */
//					path[W] = V;	/* ����S��W��·�� */ 
//				} 
//			}
//		} 
//	}		 
//}

void Dijkstra(MGraph *G, int *path, int *dist, int v0) {
	/* ������ͼG��v0���㵽���ඥ������·��path[]����·������dist[] */
	/* ��path[v]==w, ��w�Ǵ�v0��v��ǰ������·���ϵĶ��� */
	/* collected[v]ΪTRUE���ҽ���v����S, ���Ѿ���ô�v0��v�����·�� */
	/* ����INFINITYΪ����Ȩֵ���ܵ����ֵ */
	int collected[MaxVertexNum], v, w, i, MinDist;
	for(v=0; v<G->n; v++) {
		collected[v] = FALSE;
		dist[v] = G->edge[v0][v];
		for(w=0; w<G->n; w++) {
			if( dist[w] < INFINITY ) {
				path[w] = -1;	/* ��Ϊ������v0 */
			}
		}
	}
	dist[v0] = 0;
	collected[v0] = TRUE;	/* ��ʼ״̬: v0��������S��(S������ҵ����·���Ķ���) */
	
	/* ��ʼ��ѭ��, ÿ�����v0��ĳ��v��������·��, ����v������S */
	for(i=0; i<G->n; i++) {
		MinDist = INFINITY;		/* MinDistΪ��ǰ��֪��v0�������̾��� */
		for(w=0; w<G->n; w++) {
			if( !collected[w] && (dist[w] < MinDist) ) {	/* w����δ����¼��S�� */
				/* Ѱ�����·������v */ 
				v = w;
				MinDist = dist[w];
			}
		}
		if( MinDist < INFINITY ) {
			collected[v] = TRUE;	/* ��v0���������v����S���� */
		} else break;	/* �����Ƿ���ͨͼ, ����ѭ�� */
		for(w=0; w<G->n; w++) {
			if( !collected[w] && (MinDist+G->edge[v][w]<dist[w]) ) {
				dist[w] = MinDist + G->edge[v][w];
				path[w] = v;
			}
		}
	}
}

void printPath(int v, int *path) {
	if( path[v] == -1 )
		return;
	printPath(path[v], path);
	printf("%d ", v);
}

int main() 
{
	MGraph *G;
	int *dist, *path;
	G = Init();
	CreateMGraph(G);
	dist = (int *)malloc(sizeof(int)*G->n);
	path = (int *)malloc(sizeof(int)*G->n);
	Dijkstra(G, path, dist, 0);
	printPath(3, path);
}
