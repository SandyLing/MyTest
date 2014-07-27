//无向图
#include <stdio.h>
#include <stdlib.h>
#define  VertexType  char
#define  Status      int
#define  AdjMatrix   int
#define  MAX_VERTEX_NUM 20
#define INFINITY 12767
#define OK 1
#define TRUE 1
#define FALSE 0
bool visited[MAX_VERTEX_NUM];//访问标志数组
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct   // 图的定义
{
    VertexType   vexs[MAX_VERTEX_NUM];//顶点向量
    AdjMatrix    arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int    vexnum, arcnum;    //图的当前顶点数和弧数
}MGraph;
//队列
typedef struct QNode
{
     int   data;
    struct QNode *next;
} QNode;
typedef struct
{
    QNode *front;
    QNode *rear;
} LinkQuene;
int InitQuene(LinkQuene &Q)
{
    Q.front=Q.rear=(QNode*)malloc(sizeof(QNode));
    if(!Q.front)exit(0);
    Q.front->next=NULL;
    return 1;
}
void EnQuene(LinkQuene &Q,int e)
{
    QNode *p;
    p=(QNode*)malloc(sizeof(QNode));
    if(!p)exit(0);
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
}
void DeQuene(LinkQuene &Q,int &e)
{
    QNode *p;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)Q.rear=Q.front;
    free(p);
}
int Queueempty(LinkQuene &Q)
{
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}
//图G中查找元素c的位置
int Locate(MGraph G,char c)
{
    for(int i=0; i<G.vexnum; i++)
        if(G.vexs[i]==c)  return i;
    return -1;
}
//图G中顶点k的第一个邻接顶点
int FirstVex(MGraph G,int k){
  if(k>=0 && k<G.vexnum){ //k合理
    for(int i=0;i<G.vexnum;i++)
      if(G.arcs[k][i]!=INFINITY) return i;
  }
  return -1;
}
//图G中顶点i的第j个邻接顶点的下一个邻接顶点
int NextVex(MGraph G,int i,int j){
  if(i>=0 && i<G.vexnum && j>=0 && j<G.vexnum){ //i,j合理
    for(int k=j+1;k<G.vexnum;k++)
      if(G.arcs[i][k]!=INFINITY) return k;
  }
  return -1;
}
Status CreateGra(MGraph &G)
{
    int i,j,k,temp;
    char v1,v2;
    printf("请输入图的当前顶点数和弧数\n");
    scanf("%d%d",&G.vexnum,&G.arcnum);
    temp=getchar(); //接收回车
    printf("输入%d个顶点.\n",G.vexnum);
    for (i=0 ; i< G.vexnum; ++i)
    {
        printf("输入第%d顶点:",i);
        scanf("%c",&G.vexs[i]);//构造顶点向量
        temp=getchar(); //接收回车
    }
    for (i=0 ; i< G.vexnum; ++i)//初始化邻接矩阵
        for(j=0 ; j< G.vexnum; ++j)
            G.arcs[i][j]=INFINITY;
    printf("输入%d条弧.\n",G.arcnum);
    for (k=0; k< G.arcnum; k++)//构造邻接矩阵
    {
        printf("输入弧%d:",k);
        scanf("%c %c",&v1,&v2);//输入一条边依附的顶点
        temp=getchar(); //接收回车
        i=Locate(G,v1);
        j= Locate(G,v2);
        G.arcs[j][i]=G.arcs[i][j]=1;
    }
    return OK;
}
//深度优先核心算法
void DFS(MGraph G, int v,Status (*Visit)(VertexType))
{
// 从顶点v出发，深度优先搜索遍历连通图 G
    int w;
    visited[v] = TRUE;
    Visit(G.vexs[v]);
    for(w=FirstVex(G, v); w>=0 ; w=NextVex(G,v,w))
        if (!visited[w])  DFS(G, w ,Visit);
    // 对v的尚未访问的邻接顶点w
    // 递归调用DFS
} // DFS
void DFSTraverse(MGraph &G,Status (*Visit)(VertexType))
{
  //对图 G 作深度优先遍历。
    int v;
    for (v=0; v<G.vexnum; ++v)
        visited[v] = FALSE; // 访问标志数组初始化
    for (v=0; v<G.vexnum; ++v)
        if (!visited[v])  DFS(G, v, Visit);// 对尚未访问的顶点调用DFS
}
//广度优先核心算法
void BFSTraverse(MGraph G, Status (*Visit)(VertexType)) {
  // 按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。
  int v,w;
  LinkQuene Q;
  int u;
  for (v=0; v<G.vexnum; ++v) visited[v] = FALSE;
  InitQuene(Q);                     // 置空的辅助队列Q
  for (v=0;  v<G.vexnum;  ++v)
    if (!visited[v]) {              // v尚未访问
      visited[v] = TRUE;  Visit(G.vexs[v]); // 访问v
      EnQuene(Q,v);                // v入队列
      while (!Queueempty(Q)) {
        DeQuene(Q,u);              // 队头元素出队并置为u
        for (w=FirstVex(G,u);  w>=0;  w=NextVex(G, u, w))
          if (!visited[w]) {        // u的尚未访问的邻接顶点w入队列Q
            visited[w] = TRUE;  Visit(G.vexs[w]);;
            EnQuene(Q, w);
          }//if
      }//while
    }//if
} // BFSTraverse

Status print(VertexType c)
{
    printf("%c ",c);
}
int main()
{
  MGraph G;
  CreateGra(G);
  printf("\n深度优先遍历: ");
  DFSTraverse(G,print);
  printf("\n广度优先遍历: ");
  BFSTraverse(G,print);
  return 0;
}
