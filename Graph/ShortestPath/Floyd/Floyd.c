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

typedef struct {	/* �ڽӾ���洢ͼ */
	VertexType vertex[MaxVertexNum];	/* ����� */
	EdgeType edge[MaxVertexNum][MaxVertexNum];	/* �ڽӾ���, ���߱� */
	int n, e;		/* �������ͱ��� */ 
	enum GraphType GType;	/* ͼ���� */
}MGraph; 

MGraph *Init() {
	MGraph *graph;
	graph = (MGraph *)malloc(sizeof(MGraph));
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

void Floyd(MGraph *G, EdgeType dist[][MaxVertexNum], int path[][MaxVertexNum]) {
	/* ������ͼG�и��Զ���v��w֮������·��path[v][w]�����Ȩ����dist[v][w] */
	/* ��path[v][w]=u, ����u�Ǵ�v��w�����·���ؾ��Ķ��� */
	int u, v, w, i;
	for(v=0; v<G->n; v++) {		/* ���Զ���֮���ʼ��֪·�������� */ 
		for(w=0; w<G->n; w++) {
			dist[v][w] = G->edge[v][w];
			path[v][w] = v;		/* �����v��w��ֱ��·�� */
		}	/* ���������ֱ�ӵı�, dist[v][w]=��, path[v][w]=vҲ������� */
	}
	for(u=0; u<G->n; u++) {
		for(v=0; v<G->n; v++) {
			for(w=0; w<G->n; w++) {
				if( (dist[v][u] + dist[u][w]) < dist[v][w] ) {	/* ��v��u��w��һ��·������ */
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
