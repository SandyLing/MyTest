#include<string.h>
//#include<ctype.h>
#include<malloc.h> /* malloc()等 */
#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<stdlib.h> /* atoi() */
//#include<io.h> /* eof() */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#include<process.h> /* exit() */
#define LIST_INIT_SIZE 10 /* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int ElemType;
struct LNode
{
    ElemType data;
    struct LNode *next;
};
typedef struct LNode *LinkList; /* 另一种定义LinkList的方法 */
Status InitList(LinkList &L)
{
    /* 操作结果：构造一个空的线性表L */
    L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
    if(!L) /* 存储分配失败 */
        exit(OVERFLOW);
    L->next=NULL; /* 指针域为空 */
    return OK;
}
Status DestroyList(LinkList &L)
{
    /* 初始条件：线性表L已存在。操作结果：销毁线性表L */
    LinkList q;
    while(L)
    {
        q=L->next;
        free(L);
        L=q;
    }
    return OK;
}
Status ClearList(LinkList &L) /* 不改变L */
{
    /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
    LinkList p,q;
    p=L->next; /* p指向第一个结点 */
    while(p) /* 没到表尾 */
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL; /* 头结点指针域为空 */
    return OK;
}
Status ListEmpty(LinkList &L)
{
    /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
    if(L->next) /* 非空 */
        return FALSE;
    else
        return TRUE;
}
int ListLength(LinkList L)
{
    /* 初始条件：线性表L已存在。操作结果：返回L中数据元素个数 */
    int i=0;
    LinkList p=L->next; /* p指向第一个结点 */
    while(p) /* 没到表尾 */
    {
        i++;
        p=p->next;
    }
    return i;
}
Status GetElem(LinkList L,int i,ElemType &e) /* 算法2.8 */
{
    /* L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
    int j=1; /* j为计数器 */
    LinkList p=L->next; /* p指向第一个结点 */
    while(p&&j<i) /* 顺指针向后查找,直到p指向第i个元素或p为空 */
    {
        p=p->next;
        j++;
    }
    if(!p||j>i) /* 第i个元素不存在 */
        return ERROR;
    e=p->data; /* 取第i个元素 */
    return OK;
}
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    /* 初始条件: 线性表L已存在,compare()是数据元素判定函数(满足为1,否则为0) */
    /* 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序。 */
    /*           若这样的数据元素不存在,则返回值为0 */
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(compare(p->data,e)) /* 找到这样的数据元素 */
            return i;
        p=p->next;
    }
    return 0;
}
Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
{
    /* 初始条件: 线性表L已存在 */
    /* 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱, */
    /*           返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE */
    LinkList q,p=L->next; /* p指向第一个结点 */
    while(p->next) /* p所指结点有后继 */
    {
        q=p->next; /* q为p的后继 */
        if(q->data==cur_e)
        {
            pre_e=p->data;
            return OK;
        }
        p=q; /* p向后移 */
    }
    return INFEASIBLE;
}
Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
{
    /* 初始条件：线性表L已存在 */
    /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
    /*           返回OK;否则操作失败，next_e无定义，返回INFEASIBLE */
    LinkList p=L->next; /* p指向第一个结点 */
    while(p->next) /* p所指结点有后继 */
    {
        if(p->data==cur_e)
        {
            next_e=p->next->data;
            return OK;
        }
        p=p->next;
    }
    return INFEASIBLE;
}
Status ListInsert(LinkList L,int i,ElemType e) /* 算法2.9。不改变L */
{
    /* 在带头结点的单链线性表L中第i个位置之前插入元素e */
    int j=0;
    LinkList p=L,s;
    while(p&&j<i-1) /* 寻找第i-1个结点 */
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1) /* i小于1或者大于表长 */
        return ERROR;
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
void CreateList(LinkList &L,int n) /* 算法2.11 */
{
    /* 逆位序(插在表头)输入n个元素的值，建立带表头结构的单链线性表L */
    int i;
    LinkList p;
    L=(LinkList)malloc(sizeof(struct LNode));
    L->next=NULL; /* 先建立一个带头结点的单链表 */
    printf("请输入%d个数据\n",n);
    for(i=n; i>0; --i)
    {
        p=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
        scanf("%d",&p->data); /* 输入元素值 */
        p->next=L->next; /* 插入到表头 */
        L->next=p;
    }
}
void CreateList2(LinkList &L,int n)
{
    /* 正位序(插在表尾)输入n个元素的值，建立带表头结构的单链线性表 */
    int i;
    LinkList p,q;
    L=(LinkList)malloc(sizeof(struct LNode)); /* 生成头结点 */
    L->next=NULL;
    q=L;
    printf("请输入%d个数据\n",n);
    for(i=1; i<=n; i++)
    {
        p=(LinkList)malloc(sizeof(struct LNode));
        scanf("%d",&p->data);
        q->next=p;
        q=q->next;
    }
    p->next=NULL;
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
int main()
{
    LinkList La,Lb,Lc,Ld,Le;
    Status i;
    int j;
    ElemType e;
    ElemType p;
    int a[]= {9,7,6,4,3,5,1};
    int b[]= {1,2,3,4,5,6,7,8,9,10,11};
    int c[]= {1,3,5,7,9,11,13};
    int d[]= {1,4,6,8,12,14,16,19};
    i=InitList(La);
    if(i==1) /* 创建空表La成功 */
        for(j=1; j<=5; j++) /* 在表La中插入5个元素 */
            i=ListInsert(La,j,j);
    printf("La= "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    DestroyList(La);
    printf("销毁顺序表La "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    InitList(La); /* 也可不判断是否创建成功 */
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(La,j,a[j-1]);
    printf("新建La= "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    ClearList(La);
    printf("清空La "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(La,j,a[j-1]);
    printf("新建La= "); /* 输出表Lb的内容 */
    ListTraverse(La,visit);
    printf("La数据元素个数为 %d\n",ListLength(La));
    printf("输出的元素位置 2\n");
    GetElem(La,2,e);
    printf("La中对应的数据元素为%d\n",e);
    printf("判断是否存在元素1\n");
    if(LocateElem(La,1,equal))
        printf("La存在元素1\n");
    else
        printf("La不存在元素1\n");
    if(PriorElem(La,5,p))
        printf("p为La中元素5的前驱 %d\n",p);
    else
        printf("La中不存在对应的元素\n");
    if(NextElem(La,5,p))
        printf("p为La中元素5的前驱 %d\n",p);
    else
        printf("La中不存在对应的元素\n");
    printf("在La第四位置插入5\n");
    ListInsert(La,4,5);
    ListTraverse(La,visit);
    printf("删除La第二个元素\n");
    ListDelete(La,2,e);
    ListTraverse(La,visit);
    InitList(Lc); /* 也可不判断是否创建成功 */
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(Lc,j,c[j-1]);
    printf("新建Lc= "); /* 输出表Lb的内容 */
    ListTraverse(Lc,visit);
    InitList(Ld); /* 也可不判断是否创建成功 */
    for(j=1; j<=8; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(Ld,j,d[j-1]);
    printf("新建Ld= "); /* 输出表Lb的内容 */
    ListTraverse(Ld,visit);
    InitList(Le);
    MergeList(Lc,Ld,Le);
    printf("合并后为 ");
    ListTraverse(Le,visit);
    CreateList(Lb,5);
    printf("逆位序(插在表头)输入n个元素的值，建立带表头结构的单链线性表L\n");
    ListTraverse(Lb,visit);
    DestroyList(Lb);
    CreateList2(Lb,5);
    printf("正位序(插在表尾)输入n个元素的值，建立带表头结构的单链线性表\n");
    ListTraverse(Lb,visit);
}
