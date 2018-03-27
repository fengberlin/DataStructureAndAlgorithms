#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100
#define INFINITY 65535
#define ERROR -1 
typedef int VertexType;		/* �������� */
typedef int EdgeType;		/* �ߵ�Ȩֵ���� */ 
enum GraphType { DG, UG, DN, UN };		/* ͼ���� */ 

typedef struct {
	VertexType Vertices[MaxVertexNum];		/* ����� */ 
	EdgeType Edges[MaxVertexNum][MaxVertexNum];		/* �ڽӾ���, ���߱� */ 
	int n, e;		/* �������ͱ��� */ 
	enum GraphType GType;	/* ͼ���� */ 
}MGraph;

MGraph *Init()
{	/* ��ʼ��ͼ */
	MGraph *graph;
	graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

/* ����һ��������ͼ, ���ڽӾ���洢 */
void CreateMGraph(MGraph *G)
{
	int i, j, k, w;
	G->GType = UN;		/* undirected network ������ͼ */
	printf("�����붥�����ͱ���(�����ʽΪ:������,����):\n");
	scanf("%d,%d", &(G->n), &(G->e));		/* ���붥�����ͱ��� */
	printf("�����붥����Ϣ(�����ʽΪ:�������<CR>, ÿ�������Իس���Ϊ����):\n");		/* <CR>�ǻس� */
	for(i=0; i<G->n; i++)
		scanf("\n%c", &(G->Vertices[i]));		/* ���붥����Ϣ, ���������  ע�⻻�з�\n������*/
	for(i=0; i<G->n; i++)
		for(j=0; j<G->n; j++)
			G->Edges[i][j] = INFINITY;		/* ��ʼ���ڽӾ��� */
	printf("������ÿ���߶�Ӧ�������������ź�Ȩֵ, �����ʽΪ:i,j,w:\n");
	for(k=0; k<G->e; k++) 
	{
		scanf("\n%d,%d,%d", &i, &j, &w);		/* ����e�����ϵ�Ȩ, �����ڽӾ��� */
		G->Edges[i][j] = w;
		G->Edges[j][i] = w;		/* ��Ϊ������ͼ���ڽӾ����ǶԳƵ� */ 
	}	
}

int FindMinDist(int dist[], int n) {
	/* ��V-VT�е�VT��С����ĵ� */
	int j, k, MinDist=INFINITY;
	for(j=0,k=0; j<n; j++) {
		if( dist[j] && dist[j]<INFINITY ) {
			MinDist = dist[j];
			k = j;
		}
	}
	if( MinDist < INFINITY )	/* ���ҵ���Сdist */
		return k;		/* ���ض�Ӧ�������±� */
	else 
		return ERROR;
}

void Prim(MGraph *G, int Parent[]) {
	/* Ĭ�ϴ����Ϊ0�Ķ������ */
	/* ��ʾÿ������ĸ�������С��������������Parent�� */
	int dist[MaxVertexNum];
	int i, j, k;
	for(i=0; i<G->n; i++) {
		/* ��ʼ��dist */
		dist[i] = G->Edges[0][i];
		Parent[i] = 0;		/* ������Ϊ���ж���ĸ������0(�����) */
	}
	
	dist[0] = 0;		/* �����Ϊ0�Ķ������������С������ */
	Parent[0] = -1;		/* �������ĸ���� */
	for(i=1; i<G->n; i++) {
		/* ��������С����������Ҫ�ռ�n-1����� */
		k = FindMinDist(dist, G->n);		/* ��V-VT�е�VT��С����ĵ�  V-VT��ָ��V�����г���VT�����ڵ�Ԫ�� */
		if( k ) {
			/* ����ҵ� */
			dist[k] = 0;	/* ����������k */
			for(j=1; j<G->n; j++) {		/* ���µ�ǰ��С������ */
				if( dist[j] && (G->Edges[k][j] < dist[j]) ) {
					/* ���j��V-VT�еĶ����Ҿ�����Ҫ���� */
					dist[j] = G->Edges[k][j];	/* ������С���� */
					Parent[j] = k;		/* ������Ϊ����j�ĸ������k */
				}	/* ����if��Ҫ����j */
			}
		} else {	/* ����if�ҵ���һ��k */
			/* ��û�ռ������н��Ͳ��ܼ�������, һ��Ϊ����ͨͼ */
			printf("ͼ����ͨ.\n");
			break;
		}
	}	/* �����ռ�����forѭ�� */ 
}

//int Prim( MGraph Graph, LGraph MST )
//{ /* ����С����������Ϊ�ڽӱ�洢��ͼMST��������СȨ�غ� */
//    WeightType dist[MaxVertexNum], TotalWeight;
//    Vertex parent[MaxVertexNum], V, W;
//    int VCount;
//    Edge E;
//     
//    /* ��ʼ����Ĭ�ϳ�ʼ���±���0 */
//       for (V=0; V<Graph->Nv; V++) {
//        /* ���������V��Wû��ֱ�ӵıߣ���Graph->G[V][W]����ΪINFINITY */
//           dist[V] = Graph->G[0][V];
//           parent[V] = 0; /* ���Ҷ������ж���ĸ���㶼�ǳ�ʼ��0 */ 
//    }
//    TotalWeight = 0; /* ��ʼ��Ȩ�غ�     */
//    VCount = 0;      /* ��ʼ����¼�Ķ����� */
//    /* �����������ж��㵫û�бߵ�ͼ��ע�����ڽӱ�汾 */
//    MST = CreateGraph(Graph->Nv);
//    E = (Edge)malloc( sizeof(struct ENode) ); /* �����յı߽�� */
//            
//    /* ����ʼ��0��¼��MST */
//    dist[0] = 0;
//    VCount ++;
//    parent[0] = -1; /* ��ǰ������0 */
// 
//    while (1) {
//        V = FindMinDist( Graph, dist );
//        /* V = δ����¼������dist��С�� */
//        if ( V==ERROR ) /* ��������V������ */
//            break;   /* �㷨���� */
//             
//        /* ��V����Ӧ�ı�<parent[V], V>��¼��MST */
//        E->V1 = parent[V];
//        E->V2 = V;
//        E->Weight = dist[V];
//        InsertEdge( MST, E );
//        TotalWeight += dist[V];
//        dist[V] = 0;
//        VCount++;
//         
//        for( W=0; W<Graph->Nv; W++ ) /* ��ͼ�е�ÿ������W */
//            if ( dist[W]!=0 && Graph->G[V][W]<INFINITY ) {
//            /* ��W��V���ڽӵ㲢��δ����¼ */
//                if ( Graph->G[V][W] < dist[W] ) {
//                /* ����¼Vʹ��dist[W]��С */
//                    dist[W] = Graph->G[V][W]; /* ����dist[W] */
//                    parent[W] = V; /* ������ */
//                }
//            }
//    } /* while����*/
//    if ( VCount < Graph->Nv ) /* MST���յĶ��㲻��|V|�� */
//       TotalWeight = ERROR;
//    return TotalWeight;   /* �㷨ִ����ϣ�������СȨ�غͻ������ */
//}

int main()
{
	int Parent[100];
	MGraph *G = Init();
	CreateMGraph( G );
	Prim(G, Parent);
	return 0;
} 
