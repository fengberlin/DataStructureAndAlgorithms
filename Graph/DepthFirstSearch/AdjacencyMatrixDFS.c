#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100	/* 最大顶点数设为100 */
#define INFINITY 65535		/* ∞设为双字节无符号整数的最大值65535 */ 
#define TRUE 1
#define FALSE 0
typedef char VertexType;		/* 顶点类型设为字符型 */
typedef int EdgeType;		/* 边的权值设为整型 */
enum GraphType { DG, UG, DN, UN };		/* directed graph, undirected graph, directed network, undirected network */

/* 邻接矩阵存储图 */
typedef struct {
	VertexType Vertices[MaxVertexNum];		/* 顶点表 */
	EdgeType Edges[MaxVertexNum][MaxVertexNum];		/* 邻接矩阵, 即边表 */
	int n, e;	/* 顶点数n和边数e */
	int *Visited;
	enum GraphType GType;	/* 图的类型分4种: UG, DG, UN, DN */ 
}MGraph;		/* MGraph是以邻接矩阵存储的图类型  M->Matrix*/

MGraph *Init() {	/* 初始化图 */
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

void CreateMGraph(MGraph *G) {		/* 创建一个无向网图, 用邻接矩阵存储 */
	int i, j, k, w;
	G->GType = UN;		/* undirected network 无向网图 */
	printf("请输入顶点数和边数(输入格式为:顶点数,边数):\n");
	scanf("%d,%d", &(G->n), &(G->e));
	
	G->Visited = (int *)malloc(sizeof(int) * G->n);
	if( !G->Visited )
		FatalError("Failed to allocate memory!");
	
	printf("请输入顶点信息(输入格式为:顶点符号<CR>, 每个顶点的输入以回车作为结束):\n");		/* <CR>是回车 */
	for(i=0; i<G->n; i++) {
		scanf("\n%c", &(G->Vertices[i]));		/* 输入顶点信息, 建立顶点表  注意换行符\n！！！*/
		G->Visited[i] = FALSE;
	}
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++) {
			G->Edges[i][j] = INFINITY;		/* 初始化邻接矩阵 */
		}
	}
	printf("请输入每条边对应的两个顶点的序号和权值, 输入格式为:i,j,w:\n");
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d,%d", &i, &j, &w);
		G->Edges[i][j] = w;
		G->Edges[j][i] = w;		/* 无向图的邻接矩阵是对称的 */ 
	}
}

int isEdge(MGraph *G, int i, int j) {
	return ( G->Edges[i][j] < INFINITY ? TRUE : FALSE );
}

void DFS(MGraph *G, int Vi) {
	int j;
	printf("visit:Vertex %c\n", G->Vertices[Vi]);
	G->Vertices[Vi] = TRUE;
	for(j=0; j<G->n; j++) {
		if( !G->Visited[j] && isEdge(G,Vi,j) ) {
			DFS(G, j);
		}
	}
}

void DFS_MG(MGraph *G) {
	int i;
	for(i=0; i<G->n; i++)
		if( !G->Visited[i] )
			DFS(G, i);
	return;
}

int main()
{
	MGraph *G;
	G = Init();
	CreateMGraph( G );
	DFS_MG( G );
	return 0;
}
