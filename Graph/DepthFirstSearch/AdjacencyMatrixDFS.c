#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100	/* ��󶥵�����Ϊ100 */
#define INFINITY 65535		/* ����Ϊ˫�ֽ��޷������������ֵ65535 */ 
#define TRUE 1
#define FALSE 0
typedef char VertexType;		/* ����������Ϊ�ַ��� */
typedef int EdgeType;		/* �ߵ�Ȩֵ��Ϊ���� */
enum GraphType { DG, UG, DN, UN };		/* directed graph, undirected graph, directed network, undirected network */

/* �ڽӾ���洢ͼ */
typedef struct {
	VertexType Vertices[MaxVertexNum];		/* ����� */
	EdgeType Edges[MaxVertexNum][MaxVertexNum];		/* �ڽӾ���, ���߱� */
	int n, e;	/* ������n�ͱ���e */
	int *Visited;
	enum GraphType GType;	/* ͼ�����ͷ�4��: UG, DG, UN, DN */ 
}MGraph;		/* MGraph�����ڽӾ���洢��ͼ����  M->Matrix*/

MGraph *Init() {	/* ��ʼ��ͼ */
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

void CreateMGraph(MGraph *G) {		/* ����һ��������ͼ, ���ڽӾ���洢 */
	int i, j, k, w;
	G->GType = UN;		/* undirected network ������ͼ */
	printf("�����붥�����ͱ���(�����ʽΪ:������,����):\n");
	scanf("%d,%d", &(G->n), &(G->e));
	
	G->Visited = (int *)malloc(sizeof(int) * G->n);
	if( !G->Visited )
		FatalError("Failed to allocate memory!");
	
	printf("�����붥����Ϣ(�����ʽΪ:�������<CR>, ÿ������������Իس���Ϊ����):\n");		/* <CR>�ǻس� */
	for(i=0; i<G->n; i++) {
		scanf("\n%c", &(G->Vertices[i]));		/* ���붥����Ϣ, ���������  ע�⻻�з�\n������*/
		G->Visited[i] = FALSE;
	}
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++) {
			G->Edges[i][j] = INFINITY;		/* ��ʼ���ڽӾ��� */
		}
	}
	printf("������ÿ���߶�Ӧ�������������ź�Ȩֵ, �����ʽΪ:i,j,w:\n");
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d,%d", &i, &j, &w);
		G->Edges[i][j] = w;
		G->Edges[j][i] = w;		/* ����ͼ���ڽӾ����ǶԳƵ� */ 
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
