#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LIST_INIT_SIZE 10 /* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
int comp(ElemType c1,ElemType c2)//比较两者的大小
{
    int i;
    if(c1<c2)
        i=1;
    else if(c1==c2)
        i=0;
    else
        i=-1;
    return i;
}

Status InitList(LinkList &L)
{
    /* 操作结果：构造一个空的线性表L */
    L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
    if(!L) /* 存储分配失败 */
        exit(OVERFLOW);
    L->next=NULL; /* 指针域为空 */
    return OK;
}
Status ListInsert(LinkList &L,ElemType e,int(*vf)(ElemType,ElemType))
{
    /* 在带头结点的单链线性表L中第i个位置之前插入元素e */
    int j=0;
    LinkList p=L,s;
    //比较寻找比e小的前一个节点
    while(p->next&&vf(p->next->data,e))
     {
         p=p->next;
     }
    s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
    s->data=e; /* 插入L中 */
    s->next=p->next;
    p->next=s;
    return OK;
}
Status ListDelete(LinkList L,int i,ElemType &e) /* 算法2.10。不改变L */
{
    /* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
    int j=0;
    LinkList p=L,q;
    while(p->next&&j<i-1) /* 寻找第i个结点,并令p指向其前趋 */
    {
        p=p->next;
        j++;
    }
    if(!p->next||j>i-1) /* 删除位置不合理 */
        return ERROR;
    q=p->next; /* 删除并释放结点 */
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}
Status ListTraverse(LinkList L,void(*vi)(ElemType))
/* vi的形参类型为ElemType，与bo2-1.c中相应函数的形参类型ElemType&不同 */
{
    /* 初始条件：线性表L已存在 */
    /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
    if(!L) return ERROR;
    LinkList p=L->next;
    while(p)
    {
        vi(p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}
void visit(ElemType c) /* ListTraverse()调用的函数(类型要一致) */
{
    printf("%d ",c);
}
Status equal(ElemType c1,ElemType c2)
{
    /* 判断是否相等的函数，Union()用到 */
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
int compare(ElemType c1,ElemType c2)//比较两者的大小
{
    int i;
    if(c1<c2)
        i=1;
    else
        i=0;
    return i;
}
void MergeList(LinkList La,LinkList &Lb,LinkList &Lc)/* 算法2.12 */
{
    /* 已知单链线性表La和Lb的元素按值非递减排列。 */
    /* 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列 */
    LinkList pa=La->next,pb=Lb->next,pc;
    Lc=pc=La; /* 用La的头结点作为Lc的头结点 */
    while(pa&&pb)
        if(pa->data<=pb->data)
        {
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    pc->next=pa?pa:pb; /* 插入剩余段 */
    free(Lb); /* 释放Lb的头结点 */
    Lb=NULL;
}
//找倒数第k个节点
//sandy
//2014/7/18
Status ListTraverseDaoK(LinkList p,void(*vi)(ElemType),int &i,int k)
{
    if(p)
        ListTraverseDaoK(p->next,visit,i,k);
    if(i==k)
        vi(p->data);
    i++;
    return OK;
}
int main()
{
    LinkList La,Lb,Lc;
    int a[]= {9,7,6,4,3,5,1};
    int b[]= {4,3,2,5,7,8,9,6};
    ElemType e;
    InitList(La);
    int j;
    for(j=1; j<=7; j++)
        ListInsert(La,a[j-1],compare);
    printf("新建La= "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    printf("删除La第二个元素\n");
    ListDelete(La,2,e);
    printf("删除的元素为%d\n",e);
    printf("La= ");
    ListTraverse(La,visit);
    InitList(Lb);
    for(j=1; j<=8; j++)
        ListInsert(Lb,b[j-1],compare);
    printf("新建Lb= "); /* 输出表La的内容 */
    ListTraverse(Lb,visit);
    MergeList(La,Lb,Lc);
    printf("合并后 Lc= ");
    ListTraverse(Lc,visit);
    int k=4;
    printf("倒数第%d ",k);
    int i=0;
    ListTraverseDaoK(Lc->next,visit,i,k);
}
