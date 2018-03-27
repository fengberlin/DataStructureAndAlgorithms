#include <stdio.h>
#include <stdlib.h>
/* 邻接矩阵存储 - 有权图的单源最短路算法 */

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

typedef struct {	/* 邻接矩阵存储图 */
	VertexType vertex[MaxVertexNum];	/* 顶点表 */
	EdgeType edge[MaxVertexNum][MaxVertexNum];	/* 邻接矩阵, 即边表 */
	int n, e;		/* 顶点数和边数 */ 
	enum GraphType GType;	/* 图类型 */
}MGraph; 

MGraph *Init() {
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory!");
	return graph;
} 

void CreateMGraph(MGraph *G) {	/* 构建图 */
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

///* 有权图的单源最短路算法 */
//VertexNum FindMinDist(MGraph *Graph, int dist[], int collected[])
//{	/* 返回未被收录顶点中dist最小者 */
//	VertexNum MinV, V;
//	int MinDist = INFINITY;
//	
//	for(V=0; V<Graph->n; V++)
//	{
//		if( collected[V]==FALSE && dist[V]<MinDist )
//		{	/* 若V未被收录, 且dist[V]更小 */
//			MinDist = dist[V];		/* 更新最小距离 */
//			MinV = V;	/* 更新对应顶点 */ 
//		}
//		if(MinDist < INFINITY)	/* 若找到最小dist */
//			return MinV;	/* 返回对应的顶点下标 */
//		else 
//			return ERROR;	/* 若这样的顶点不存在, 返回错误标记 */ 
//	}
//}
//
//void Dijkstra(MGraph *G, int *dist, int *path, VertexNum S)
//{	/* 迪杰斯特拉算法---按路径长度递增的次序产生最短路径 */ 
//	int collected[MaxVertexNum];
//	VertexNum V, W;
//	
//	/* 初始化: 此处默认邻接矩阵中不存在的边用INFINITY表示 */
//	for(V=0; V<G->n; V++) 
//	{
//		dist[V] = G->edge[S][V];
//		if( dist[V] < INFINITY )
//			path[V] = S;
//		else
//			path[V] = 1;
//		collected[V] = FALSE;
//	}
//	/* 先将源点收入集合 */
//	dist[S] = 0;
//	collected[S] = TRUE;
//	
//	while(1)
//	{	/* V=未被收录顶点中的dist最小者 */
//		V = FindMinDist(G, dist, collected);
//		if( V == Error )		/* 若这样的V不存在 */
//			break;
//		collected[V] = TRUE;	/* 收录V */
//		for( W=0; W<G->n; W++)
//		{	/* 对图中的每个顶点 */
//			/* 若W是V的邻接点并且为被收录 */ 
//			if( collected[W]==FALSE && G->edge[V][W]<INFINITY )
//			{
//				if( G->edge[V][W] < 0 )		/* 若有负边 */
//					FatalError("存在负边!");
//				
//				/* 若收录V使得dist[W]变小 */
//				if( dist[V]+G->edge[V][W] < dist[W] )
//				{
//					dist[W] = dist[V] + G->edge[V][W];		/* 更新dist[W]值 */
//					path[W] = V;	/* 更新S到W的路径 */ 
//				} 
//			}
//		} 
//	}		 
//}

void Dijkstra(MGraph *G, int *path, int *dist, int v0) {
	/* 求有向图G的v0顶点到其余顶点的最短路径path[]及其路径长度dist[] */
	/* 若path[v]==w, 则w是从v0到v当前求得最短路径上的顶点 */
	/* collected[v]为TRUE当且仅当v属于S, 即已经求得从v0到v的最短路径 */
	/* 常量INFINITY为边上权值可能的最大值 */
	int collected[MaxVertexNum], v, w, i, MinDist;
	for(v=0; v<G->n; v++) {
		collected[v] = FALSE;
		dist[v] = G->edge[v0][v];
		for(w=0; w<G->n; w++) {
			if( dist[w] < INFINITY ) {
				path[w] = -1;	/* 设为父顶点v0 */
			}
		}
	}
	dist[v0] = 0;
	collected[v0] = TRUE;	/* 初始状态: v0顶点属于S集(S存放已找到最短路径的顶点) */
	
	/* 开始主循环, 每次求得v0到某个v顶点的最短路径, 并加v到集合S */
	for(i=0; i<G->n; i++) {
		MinDist = INFINITY;		/* MinDist为当前所知离v0顶点的最短距离 */
		for(w=0; w<G->n; w++) {
			if( !collected[w] && (dist[w] < MinDist) ) {	/* w顶点未被收录进S中 */
				/* 寻找最短路径顶点v */ 
				v = w;
				MinDist = dist[w];
			}
		}
		if( MinDist < INFINITY ) {
			collected[v] = TRUE;	/* 离v0顶点最近的v加入S集合 */
		} else break;	/* 否则是非连通图, 结束循环 */
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
