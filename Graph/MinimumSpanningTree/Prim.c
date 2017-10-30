#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100
#define INFINITY 65535
#define ERROR -1 
typedef int VertexType;		/* 顶点类型 */
typedef int EdgeType;		/* 边的权值类型 */ 
enum GraphType { DG, UG, DN, UN };		/* 图类型 */ 

typedef struct {
	VertexType Vertices[MaxVertexNum];		/* 顶点表 */ 
	EdgeType Edges[MaxVertexNum][MaxVertexNum];		/* 邻接矩阵, 即边表 */ 
	int n, e;		/* 顶点数和边数 */ 
	enum GraphType GType;	/* 图类型 */ 
}MGraph;

MGraph *Init()
{	/* 初始化图 */
	MGraph *graph;
	graph = (MGraph *)malloc(sizeof(MGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

/* 创建一个无向网图, 用邻接矩阵存储 */
void CreateMGraph(MGraph *G)
{
	int i, j, k, w;
	G->GType = UN;		/* undirected network 无向网图 */
	printf("请输入顶点数和边数(输入格式为:顶点数,边数):\n");
	scanf("%d,%d", &(G->n), &(G->e));		/* 输入顶点数和边数 */
	printf("请输入顶点信息(输入格式为:顶点符号<CR>, 每个顶点以回车作为结束):\n");		/* <CR>是回车 */
	for(i=0; i<G->n; i++)
		scanf("\n%c", &(G->Vertices[i]));		/* 输入顶点信息, 建立顶点表  注意换行符\n！！！*/
	for(i=0; i<G->n; i++)
		for(j=0; j<G->n; j++)
			G->Edges[i][j] = INFINITY;		/* 初始化邻接矩阵 */
	printf("请输入每条边对应的两个顶点的序号和权值, 输入格式为:i,j,w:\n");
	for(k=0; k<G->e; k++) 
	{
		scanf("\n%d,%d,%d", &i, &j, &w);		/* 输入e条边上的权, 建立邻接矩阵 */
		G->Edges[i][j] = w;
		G->Edges[j][i] = w;		/* 因为无向网图的邻接矩阵是对称的 */ 
	}	
}

int FindMinDist(int dist[], int n) {
	/* 求V-VT中到VT最小距离的点 */
	int j, k, MinDist=INFINITY;
	for(j=0,k=0; j<n; j++) {
		if( dist[j] && dist[j]<INFINITY ) {
			MinDist = dist[j];
			k = j;
		}
	}
	if( MinDist < INFINITY )	/* 若找到最小dist */
		return k;		/* 返回对应的数组下标 */
	else 
		return ERROR;
}

void Prim(MGraph *G, int Parent[]) {
	/* 默认从序号为0的顶点出发 */
	/* 表示每个顶点的父结点的最小生成树存于数组Parent中 */
	int dist[MaxVertexNum];
	int i, j, k;
	for(i=0; i<G->n; i++) {
		/* 初始化dist */
		dist[i] = G->Edges[0][i];
		Parent[i] = 0;		/* 暂且认为所有顶点的父结点是0(根结点) */
	}
	
	dist[0] = 0;		/* 从序号为0的顶点出发生成最小生成树 */
	Parent[0] = -1;		/* 生成树的根结点 */
	for(i=1; i<G->n; i++) {
		/* 生长成最小生成树还需要收集n-1个结点 */
		k = FindMinDist(dist, G->n);		/* 求V-VT中到VT最小距离的点  V-VT是指在V集合中除了VT集合内的元素 */
		if( k ) {
			/* 如果找到 */
			dist[k] = 0;	/* 生长到顶点k */
			for(j=1; j<G->n; j++) {		/* 更新当前最小生成树 */
				if( dist[j] && (G->Edges[k][j] < dist[j]) ) {
					/* 如果j是V-VT中的顶点且距离需要更新 */
					dist[j] = G->Edges[k][j];	/* 更新最小距离 */
					Parent[j] = k;		/* 暂且认为顶点j的父结点是k */
				}	/* 结束if需要更新j */
			}
		} else {	/* 结束if找到下一个k */
			/* 还没收集完所有结点就不能继续生长, 一定为非连通图 */
			printf("图不连通.\n");
			break;
		}
	}	/* 结束收集结点的for循环 */ 
}

//int Prim( MGraph Graph, LGraph MST )
//{ /* 将最小生成树保存为邻接表存储的图MST，返回最小权重和 */
//    WeightType dist[MaxVertexNum], TotalWeight;
//    Vertex parent[MaxVertexNum], V, W;
//    int VCount;
//    Edge E;
//     
//    /* 初始化。默认初始点下标是0 */
//       for (V=0; V<Graph->Nv; V++) {
//        /* 这里假设若V到W没有直接的边，则Graph->G[V][W]定义为INFINITY */
//           dist[V] = Graph->G[0][V];
//           parent[V] = 0; /* 暂且定义所有顶点的父结点都是初始点0 */ 
//    }
//    TotalWeight = 0; /* 初始化权重和     */
//    VCount = 0;      /* 初始化收录的顶点数 */
//    /* 创建包含所有顶点但没有边的图。注意用邻接表版本 */
//    MST = CreateGraph(Graph->Nv);
//    E = (Edge)malloc( sizeof(struct ENode) ); /* 建立空的边结点 */
//            
//    /* 将初始点0收录进MST */
//    dist[0] = 0;
//    VCount ++;
//    parent[0] = -1; /* 当前树根是0 */
// 
//    while (1) {
//        V = FindMinDist( Graph, dist );
//        /* V = 未被收录顶点中dist最小者 */
//        if ( V==ERROR ) /* 若这样的V不存在 */
//            break;   /* 算法结束 */
//             
//        /* 将V及相应的边<parent[V], V>收录进MST */
//        E->V1 = parent[V];
//        E->V2 = V;
//        E->Weight = dist[V];
//        InsertEdge( MST, E );
//        TotalWeight += dist[V];
//        dist[V] = 0;
//        VCount++;
//         
//        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
//            if ( dist[W]!=0 && Graph->G[V][W]<INFINITY ) {
//            /* 若W是V的邻接点并且未被收录 */
//                if ( Graph->G[V][W] < dist[W] ) {
//                /* 若收录V使得dist[W]变小 */
//                    dist[W] = Graph->G[V][W]; /* 更新dist[W] */
//                    parent[W] = V; /* 更新树 */
//                }
//            }
//    } /* while结束*/
//    if ( VCount < Graph->Nv ) /* MST中收的顶点不到|V|个 */
//       TotalWeight = ERROR;
//    return TotalWeight;   /* 算法执行完毕，返回最小权重和或错误标记 */
//}

int main()
{
	int Parent[100];
	MGraph *G = Init();
	CreateMGraph( G );
	Prim(G, Parent);
	return 0;
} 
