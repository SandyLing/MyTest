#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW -2
#define OK 1
#define QElemType BiTNode
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef int Status;
typedef char ElemType;
typedef struct BiTNode   // 结点结构
{
    ElemType     data;
    struct BiTNode  *lchild, *rchild;
    // 左右孩子指针
} BiTNode, *BiTree;

typedef struct QNode  //队列节点
{
    BiTNode data;
    struct QNode *next;
} QNode,*QueuePtr;
typedef struct
{
    QueuePtr front,rear; /* 队头、队尾指针 */
} LinkQueue;
//关于队列的函数
Status InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q.front)
        exit(OVERFLOW);
    Q.front->next=NULL;
    return OK;
}
Status QueueEmpty(LinkQueue Q)
{
    /* 若Q为空队列,则返回TRUE,否则返回FALSE */
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}
Status EnQueue(LinkQueue &Q,QElemType e)
{
    /* 插入元素e为Q的新的队尾元素 */
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) /* 存储分配失败 */
        exit(OVERFLOW);
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    return OK;
}
Status DeQueue(LinkQueue &Q,QElemType &e)
{
    /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
    QueuePtr p;
    if(Q.front==Q.rear)
        return ERROR;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    free(p);
    return OK;
}

Status PreOrderTraverse(BiTree T, Status(*visit)(ElemType&))
{
    //T为树根的指针,先序遍历
    if (T)
    {
        visit(T->data); // 访问结点
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
}
Status InOrderTraverse (BiTree T, Status(*visit)(ElemType&))
{
    // 中序遍历二叉树，T为树根的指针
    if (T)
    {
        InOrderTraverse(T->lchild, visit);// 遍历左子树
        visit(T->data) ;// 访问结点
        InOrderTraverse(T->rchild, visit);// 遍历右子树
    }
}
Status PostOrderTraverse (BiTree T, Status(*visit)(ElemType&))
{
    // 后序遍历二叉树，T为树根的指针
    if (T)
    {
        PostOrderTraverse(T->lchild, visit);//遍历左子树
        PostOrderTraverse(T->rchild, visit);//遍历右子树
        visit(T->data); // 访问结点
    }
}
int CreateBiTree(BiTree &T)
{
//按前序次序输入结点信息
    char ch;
    scanf("%c",&ch);
    if (ch=='#') T = NULL;
    else
    {
        if ((T =(BiTNode *)malloc(sizeof(BiTNode)))==NULL) exit(OVERFLOW);
        T->data = ch;              // 生成根结点
        CreateBiTree(T->lchild);   // 构造左子树
        CreateBiTree(T->rchild);   // 构造右子树
    }
    return OK;
} // CreateBiTree ,无头结点
// 求二叉树的深度
int BiTDepth(BiTree& T)
{
    int l,r;
    if(!T) return 0;
    else
    {
        l=BiTDepth(T->lchild)+1;
        r=BiTDepth(T->rchild)+1;
        return l>r?l:r;
    }
}
// 求二叉树中叶子结点的数目
Status POLeafNodeNum(int& i,BiTree& T)
{
    if(T)
    {
        i++;
        POLeafNodeNum(i,T->lchild);
        POLeafNodeNum(i,T->rchild);
    }
    return OK;
}
int HierarchyBiTree(BiTree& tr, Status(*visit)(ElemType&))//遍历二叉树
{
    LinkQueue Q;
    InitQueue(Q);  // 初始化队列
    if (!tr) return 0; //树为空则返回
    BiTNode p;
    EnQueue(Q,*tr);
    while (!QueueEmpty(Q))  // 若队列不空，则层序遍历
    {
        DeQueue(Q, p); // 出队列
        visit(p.data);// 访问当前节点
        if (p.lchild)
          EnQueue(Q, *(p.lchild)); // 若存在左孩子，左孩子进队列
        if (p.rchild)
          EnQueue(Q, *(p.rchild)); // 若存在右孩子，右孩子进队列
    }
}
Status print(ElemType &c)
{
    printf("%c ",c);
}
int main()
{
    int depth,num=0;
    printf("输入ABC##DE#G##F###建立二叉树\n");
    BiTree t;
    CreateBiTree(t);
    printf("先序遍历 ：");
    PreOrderTraverse(t,print);
    printf("\n");
    printf("中序遍历 ：");
    InOrderTraverse(t,print);
    printf("\n");
    printf("后序遍历 ：");
    PostOrderTraverse(t,print);
    printf("\n");
    depth=BiTDepth(t);
    printf("二叉树的深度为 ：%d",depth);
    POLeafNodeNum(num,t);
    printf("\n二叉树中叶子结点的数目为 :%d",num);
    printf("\n遍历二叉树 ");
    HierarchyBiTree(t,print);

}
