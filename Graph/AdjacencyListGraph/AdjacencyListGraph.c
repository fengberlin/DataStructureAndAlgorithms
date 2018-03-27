#include <stdio.h>
#include <stdlib.h>

#define Error(Str) fprintf(stderr, "%s\n", Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#define MaxVertexNum 100	/* 最大顶点数为100 */
enum GraphType { DG, UG, DN, UN };		/* 有向图, 无向图, 有向网图, 无向网图 */

typedef struct Node {	/* 边表结点 */ 
	int AdjV;		/* 邻接点域  Adj->Adjacency邻接 */ 
	struct Node *next;		/* 指向下一个邻接点的指针域 */
	/* 若要表示边上的权值信息, 则应增加一个数据域Weight */ 
}EdgeNode;

typedef char VertexType;	/* 顶点用字符表示 */
typedef struct VNode {		/* 顶点表表示 */
	VertexType Vertex;		/* 顶点域 */ 
	EdgeNode *FirstEdge;	/* 边表头指针 */ 
}VertexNode;

/* ALGraph是以邻接表方式存储的图类型 */
typedef VertexNode AdjList[MaxVertexNum];	/* AdjList是邻接表类型 */
typedef struct {
	AdjList Adjlist;	/* 邻接表 */
	int n, e;		/* 顶点数和边数 */
	enum GraphType GType;		/* 4种图类型 */ 
}ALGraph;

ALGraph *Init() {	/* 初始化图 */
	ALGraph *graph;
	graph = (ALGraph *)malloc(sizeof(ALGraph));
	if( !graph )
		FatalError("Failed to allocate memory space!");
	return graph; 
}

void CreateALGraph(ALGraph *G) {
	int i, j, k;
	EdgeNode *edge;
	
	G->GType = DG;		/* directed graph 有向图 */
	printf("请输入顶点数和边数(输入格式为:顶点数,边数):\n");
	scanf("%d,%d", &(G->n), &(G->e));		/* 输入顶点数和边数 */
	printf("请输入顶点信息(输入格式为:顶点符号<CR>, 每个顶点以回车作为结束):\n");		/* <CR>是回车 */
	for(i=0; i<G->n; i++) {	/* 建立有n个顶点的顶点表 */
		scanf("\n%c", &(G->Adjlist[i].Vertex));	/* 读入顶点信息 注意空格！！！ */ 
		G->Adjlist[i].FirstEdge = NULL;		/* 顶点的边表头指针设为空 */ 
	}
	printf("请输入边的信息(输入格式为:i,j<CR>):\n");	/* <CR> -> 回车 */
	for(k=0; k<G->e; k++) {
		scanf("\n%d,%d", &i, &j);	/* 读入边<Vi, Vj>的顶点对应序号 */
		edge = (EdgeNode *)malloc(sizeof(EdgeNode));	/* 生成新边表结点edge */
		edge->AdjV = j;		/* 邻接点序号为j */
		edge->next = G->Adjlist[i].FirstEdge;	/* 将新边表结点edge插入到顶点Vi的边表头 */
		G->Adjlist[i].FirstEdge = edge;
		/* 若是无向图, 还要生成一个结点, 用来表示边<Vj, Vi> */ 
	}
} 

int main()
{
	ALGraph *G;
	G = Init();
	CreateALGraph( G );
	return 0;
}

//#define MaxVertexNum 100    /* 最大顶点数设为100 */
//typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
//typedef int WeightType;        /* 边的权值设为整型 */
//typedef char DataType;        /* 顶点存储的数据类型设为字符型 */
// 
///* 边的定义 */
//typedef struct ENode *PtrToENode;
//struct ENode{
//    Vertex V1, V2;      /* 有向边<V1, V2> */
//    WeightType Weight;  /* 权重 */
//};
//typedef PtrToENode Edge;
// 
///* 邻接点的定义 */
//typedef struct AdjVNode *PtrToAdjVNode; 
//struct AdjVNode{
//    Vertex AdjV;        /* 邻接点下标 */
//    WeightType Weight;  /* 边权重 */
//    PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
//};
// 
///* 顶点表头结点的定义 */
//typedef struct Vnode{
//    PtrToAdjVNode FirstEdge;/* 边表头指针 */
//    DataType Data;            /* 存顶点的数据 */
//    /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
//} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */
// 
///* 图结点的定义 */
//typedef struct GNode *PtrToGNode;
//struct GNode{  
//    int Nv;     /* 顶点数 */
//    int Ne;     /* 边数   */
//    AdjList G;  /* 邻接表 */
//};
//typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */
// 
// 
// 
//LGraph CreateGraph( int VertexNum )
//{ /* 初始化一个有VertexNum个顶点但没有边的图 */
//    Vertex V;
//    LGraph Graph;
//     
//    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* 建立图 */
//    Graph->Nv = VertexNum;
//    Graph->Ne = 0;
//    /* 初始化邻接表头指针 */
//    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
//       for (V=0; V<Graph->Nv; V++)
//        Graph->G[V].FirstEdge = NULL;
//             
//    return Graph; 
//}
//        
//void InsertEdge( LGraph Graph, Edge E )
//{
//    PtrToAdjVNode NewNode;
//     
//    /* 插入边 <V1, V2> */
//    /* 为V2建立新的邻接点 */
//    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
//    NewNode->AdjV = E->V2;
//    NewNode->Weight = E->Weight;
//    /* 将V2插入V1的表头 */
//    NewNode->Next = Graph->G[E->V1].FirstEdge;
//    Graph->G[E->V1].FirstEdge = NewNode;
//         
//    /* 若是无向图，还要插入边 <V2, V1> */
//    /* 为V1建立新的邻接点 */
//    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
//    NewNode->AdjV = E->V1;
//    NewNode->Weight = E->Weight;
//    /* 将V1插入V2的表头 */
//    NewNode->Next = Graph->G[E->V2].FirstEdge;
//    Graph->G[E->V2].FirstEdge = NewNode;
//}
// 
//LGraph BuildGraph()
//{
//    LGraph Graph;
//    Edge E;
//    Vertex V;
//    int Nv, i;
//     
//    scanf("%d", &Nv);   /* 读入顶点个数 */
//    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
//     
//    scanf("%d", &(Graph->Ne));   /* 读入边数 */
//    if ( Graph->Ne != 0 ) { /* 如果有边 */ 
//        E = (Edge)malloc( sizeof(struct ENode) ); /* 建立边结点 */ 
//        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
//        for (i=0; i<Graph->Ne; i++) {
//            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
//            /* 注意：如果权重不是整型，Weight的读入格式要改 */
//            InsertEdge( Graph, E );
//        }
//    } 
// 
//    /* 如果顶点有数据的话，读入数据 */
//    for (V=0; V<Graph->Nv; V++) 
//        scanf(" %c", &(Graph->G[V].Data));
// 
//    return Graph;
//}
