#include <stdio.h>
#include <stdlib.h>

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
	MGraph *graph;
	graph = (MGraph *)malloc(sizeof(MGraph));
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

void Floyd(MGraph *G, EdgeType dist[][MaxVertexNum], int path[][MaxVertexNum]) {
	/* 求有向图G中各对顶点v和w之间的最短路径path[v][w]及其带权长度dist[v][w] */
	/* 若path[v][w]=u, 代表u是从v到w的最短路径必经的顶点 */
	int u, v, w, i;
	for(v=0; v<G->n; v++) {		/* 各对顶点之间初始已知路径及距离 */ 
		for(w=0; w<G->n; w++) {
			dist[v][w] = G->edge[v][w];
			path[v][w] = v;		/* 假设从v到w有直接路径 */
		}	/* 如果不存在直接的边, dist[v][w]=∞, path[v][w]=v也不会混淆 */
	}
	for(u=0; u<G->n; u++) {
		for(v=0; v<G->n; v++) {
			for(w=0; w<G->n; w++) {
				if( (dist[v][u] + dist[u][w]) < dist[v][w] ) {	/* 从v经u到w的一条路径更短 */
					dist[v][w] = dist[v][u]+dist[u][w];
					path[v][w] = u;
				}
			}
		}
	}
}

int main()
{
	MGraph *G;
	int dist[MaxVertexNum][MaxVertexNum], path[MaxVertexNum][MaxVertexNum];
	G = Init();
	CreateMGraph(G);
	Floyd(G, dist, path);
}
