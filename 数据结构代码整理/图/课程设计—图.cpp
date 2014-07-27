//����ͼ
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
bool visited[MAX_VERTEX_NUM];//���ʱ�־����
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct   // ͼ�Ķ���
{
    VertexType   vexs[MAX_VERTEX_NUM];//��������
    AdjMatrix    arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //�ڽӾ���
    int    vexnum, arcnum;    //ͼ�ĵ�ǰ�������ͻ���
}MGraph;
//����
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
//ͼG�в���Ԫ��c��λ��
int Locate(MGraph G,char c)
{
    for(int i=0; i<G.vexnum; i++)
        if(G.vexs[i]==c)  return i;
    return -1;
}
//ͼG�ж���k�ĵ�һ���ڽӶ���
int FirstVex(MGraph G,int k){
  if(k>=0 && k<G.vexnum){ //k����
    for(int i=0;i<G.vexnum;i++)
      if(G.arcs[k][i]!=INFINITY) return i;
  }
  return -1;
}
//ͼG�ж���i�ĵ�j���ڽӶ������һ���ڽӶ���
int NextVex(MGraph G,int i,int j){
  if(i>=0 && i<G.vexnum && j>=0 && j<G.vexnum){ //i,j����
    for(int k=j+1;k<G.vexnum;k++)
      if(G.arcs[i][k]!=INFINITY) return k;
  }
  return -1;
}
Status CreateGra(MGraph &G)
{
    int i,j,k,temp;
    char v1,v2;
    printf("������ͼ�ĵ�ǰ�������ͻ���\n");
    scanf("%d%d",&G.vexnum,&G.arcnum);
    temp=getchar(); //���ջس�
    printf("����%d������.\n",G.vexnum);
    for (i=0 ; i< G.vexnum; ++i)
    {
        printf("�����%d����:",i);
        scanf("%c",&G.vexs[i]);//���춥������
        temp=getchar(); //���ջس�
    }
    for (i=0 ; i< G.vexnum; ++i)//��ʼ���ڽӾ���
        for(j=0 ; j< G.vexnum; ++j)
            G.arcs[i][j]=INFINITY;
    printf("����%d����.\n",G.arcnum);
    for (k=0; k< G.arcnum; k++)//�����ڽӾ���
    {
        printf("���뻡%d:",k);
        scanf("%c %c",&v1,&v2);//����һ���������Ķ���
        temp=getchar(); //���ջس�
        i=Locate(G,v1);
        j= Locate(G,v2);
        G.arcs[j][i]=G.arcs[i][j]=1;
    }
    return OK;
}
//������Ⱥ����㷨
void DFS(MGraph G, int v,Status (*Visit)(VertexType))
{
// �Ӷ���v�����������������������ͨͼ G
    int w;
    visited[v] = TRUE;
    Visit(G.vexs[v]);
    for(w=FirstVex(G, v); w>=0 ; w=NextVex(G,v,w))
        if (!visited[w])  DFS(G, w ,Visit);
    // ��v����δ���ʵ��ڽӶ���w
    // �ݹ����DFS
} // DFS
void DFSTraverse(MGraph &G,Status (*Visit)(VertexType))
{
  //��ͼ G ��������ȱ�����
    int v;
    for (v=0; v<G.vexnum; ++v)
        visited[v] = FALSE; // ���ʱ�־�����ʼ��
    for (v=0; v<G.vexnum; ++v)
        if (!visited[v])  DFS(G, v, Visit);// ����δ���ʵĶ������DFS
}
//������Ⱥ����㷨
void BFSTraverse(MGraph G, Status (*Visit)(VertexType)) {
  // ��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited��
  int v,w;
  LinkQuene Q;
  int u;
  for (v=0; v<G.vexnum; ++v) visited[v] = FALSE;
  InitQuene(Q);                     // �ÿյĸ�������Q
  for (v=0;  v<G.vexnum;  ++v)
    if (!visited[v]) {              // v��δ����
      visited[v] = TRUE;  Visit(G.vexs[v]); // ����v
      EnQuene(Q,v);                // v�����
      while (!Queueempty(Q)) {
        DeQuene(Q,u);              // ��ͷԪ�س��Ӳ���Ϊu
        for (w=FirstVex(G,u);  w>=0;  w=NextVex(G, u, w))
          if (!visited[w]) {        // u����δ���ʵ��ڽӶ���w�����Q
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
  printf("\n������ȱ���: ");
  DFSTraverse(G,print);
  printf("\n������ȱ���: ");
  BFSTraverse(G,print);
  return 0;
}
