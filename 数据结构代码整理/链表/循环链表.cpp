//两个仅设表尾指针的循环链表的合并
//L为链表中的最后一元素，L->next 为头结点或空节点
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
int count=0;
typedef struct LNode *LinkList; /* 另一种定义LinkList的方法 */
typedef struct DuLNode
 {
   ElemType data;
   struct DuLNode *prior,*next;
 }DuLNode,*DuLinkList;
//设立尾指针的单循环链表(存储结构由c2-2.h定义)的12个基本操作
Status InitList_CL(LinkList &L)
{ /* 操作结果：构造一个空的线性表L */
   L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!L) /* 存储分配失败 */
     exit(OVERFLOW);
   L->next=L; /* 指针域指向头结点 */
   return OK;
 }
Status DestroyList_CL(LinkList &L)
 { /* 操作结果：销毁线性表L */
   LinkList q,p=L->next; /* p指向头结点 */
   while(p!=L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   free(L);
   L=NULL;
   return OK;
 }
 Status ClearList_CL(LinkList &L) /* 改变L */
 { /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
   LinkList p,q;
   L=L->next; /* L指向头结点 */
   p=L->next; /* p指向第一个结点 */
   while(p!=L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   L->next=L; /* 头结点指针域指向自身 */
   return OK;
 }
 Status ListEmpty_CL(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L->next==L) /* 空 */
     return TRUE;
   else
     return FALSE;
 }
 int ListLength_CL(LinkList L)
 { /* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
   int i=0;
   LinkList p=L->next; /* p指向头结点 */
   while(p!=L) /* 没到表尾 */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem_CL(LinkList L,int i,ElemType &e)
 { /* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
   int j=1; /* 初始化,j为计数器 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   if(i<=0||i>ListLength_CL(L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i)
   { /* 顺指针向后查找,直到p指向第i个元素 */
     p=p->next;
     j++;
   }
   e=p->data; /* 取第i个元素 */
   return OK;
 }

 int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0 */
   int i=0;
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L->next)
   {
     i++;
     if(compare(p->data,e)) /* 满足关系 */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem_CL(LinkList L,ElemType cur_e,ElemType &pre_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   LinkList q,p=L->next->next; /* p指向第一个结点 */
   q=p->next;
   while(q!=L->next) /* p没到表尾 */
   {
     if(q->data==cur_e)
     {
       pre_e=p->data;
       return TRUE;
     }
     p=q;
     q=q->next;
   }
   return FALSE;
 }

 Status NextElem_CL(LinkList L,ElemType cur_e,ElemType &next_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L) /* p没到表尾 */
   {
     if(p->data==cur_e)
     {
       next_e=p->next->data;
       return TRUE;
     }
     p=p->next;
   }
   return FALSE;
 }

 Status ListInsert_CL(LinkList &L,int i,ElemType e) /* 改变L */
 { /* 在L的第i个位置之前插入元素e */
   LinkList p=L->next,s; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(L)+1) /* 无法在第i个元素之前插入 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 插入L中 */
   s->next=p->next;
   p->next=s;
   if(p==L) /* 改变尾结点 */
     L=s;
   return OK;
 }

 Status ListDelete_CL(LinkList &L,int i,ElemType &e) /* 改变L */
 { /* 删除L的第i个元素,并由e返回其值 */
   LinkList p=L->next,q; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   q=p->next; /* q指向待删除结点 */
   p->next=q->next;
   e=q->data;
   if(L==q) /* 删除的是表尾元素 */
     L=p;
   free(q); /* 释放待删除结点 */
   return OK;
 }
Status equal(ElemType c1,ElemType c2)
{
    /* 判断是否相等的函数，Union()用到 */
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
 Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
 { /* 初始条件:L已存在。操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
  if(!L) return ERROR;
  LinkList p=L->next->next;
   while(p!=L->next)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }
 void MergeList_CL(LinkList &La,LinkList Lb)
 {
   LinkList p=Lb->next;
   Lb->next=La->next;
   La->next=p->next;
   free(p);
   La=Lb;
 }
 void visit(ElemType c)
 {
   printf("%d ",c);
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
    i=InitList_CL(La);
    if(i==1) /* 创建空表La成功 */
        for(j=1; j<=5; j++) /* 在表La中插入5个元素 */
            i=ListInsert_CL(La,j,j);
    printf("La= "); /* 输出表La的内容 */
    ListTraverse_CL(La,visit);
    DestroyList_CL(La);
    printf("销毁顺序表La "); /* 输出表La的内容 */
    ListTraverse_CL(La,visit);
    InitList_CL(La); /* 也可不判断是否创建成功 */
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert_CL(La,j,a[j-1]);
    printf("新建La= "); /* 输出表La的内容 */
    ListTraverse_CL(La,visit);
    ClearList_CL(La);
    printf("清空La "); /* 输出表La的内容 */
    ListTraverse_CL(La,visit);
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert_CL(La,j,a[j-1]);
    printf("新建La= "); /* 输出表Lb的内容 */
    ListTraverse_CL(La,visit);
    printf("La数据元素个数为 %d\n",ListLength_CL(La));
    printf("输出的元素位置 2\n");
    GetElem_CL(La,2,e);
    printf("La中对应的数据元素为%d\n",e);
    printf("判断是否存在元素1\n");
    if(LocateElem_CL(La,1,equal))
        printf("La存在元素1\n");
    else
        printf("La不存在元素1\n");
    if(PriorElem_CL(La,5,p))
        printf("p为La中元素5的前驱 %d\n",p);
    else
        printf("La中不存在对应的元素\n");
    if(NextElem_CL(La,5,p))
        printf("p为La中元素5的前驱 %d\n",p);
    else
        printf("La中不存在对应的元素\n");
    printf("在La第四位置插入5\n");
    ListInsert_CL(La,4,5);
    ListTraverse_CL(La,visit);
    printf("删除La第二个元素\n");
    ListDelete_CL(La,2,e);
    ListTraverse_CL(La,visit);
    InitList_CL(Lc); /* 也可不判断是否创建成功 */
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert_CL(Lc,j,c[j-1]);
    printf("新建Lc= "); /* 输出表Lb的内容 */
    ListTraverse_CL(Lc,visit);
    InitList_CL(Ld); /* 也可不判断是否创建成功 */
    for(j=1; j<=8; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert_CL(Ld,j,d[j-1]);
    printf("新建Ld= "); /* 输出表Lb的内容 */
    ListTraverse_CL(Ld,visit);
    InitList_CL(Le);
    MergeList_CL(Lc,Ld);
    printf("合并后为 ");
    ListTraverse_CL(Lc,visit);
 }

