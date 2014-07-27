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
typedef struct LNode /* 结点类型 */
 {
   ElemType data;
   struct LNode *next;
 }LNode,*Link,*Position;
 typedef struct LinkList /* 链表类型 */
 {
   Link head,tail; /* 分别指向线性链表中的头结点和最后一个结点 */
   int len; /* 指示线性链表中数据元素的个数 */
 }LinkList;
/* bo2-6.c 具有实用意义的线性链表(存储结构由c2-5.h定义)的24个基本操作 */
Status equal(ElemType c1,ElemType c2)
{
    /* 判断是否相等的函数，Union()用到 */
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
 Status MakeNode(Link &p,ElemType e)
 { /* 分配由p指向的值为e的结点，并返回OK；若分配失败。则返回ERROR */
   p=(Link)malloc(sizeof(LNode));
   if(!p)
     return ERROR;
   p->data=e;
   return OK;
 }
 void FreeNode(Link p)
 { /* 释放p所指结点 */
   free(p);
   p=NULL;
 }
 Status InitList(LinkList &L)
 { /* 构造一个空的线性链表 */
   Link p;
   p=(Link)malloc(sizeof(LNode)); /* 生成头结点 */
   if(p)
   {
     p->next=NULL;
     L.head=L.tail=p;
     L.len=0;
     return OK;
   }
   else
     return ERROR;
 }
Status ClearList(LinkList &L)
 { /* 将线性链表L重置为空表，并释放原链表的结点空间 */
   Link p,q;
   if(L.head!=L.tail)/* 不是空表 */
   {
     p=q=L.head->next;
     L.head->next=NULL;
     while(p!=L.tail)
     {
       p=q->next;
       free(q);
       q=p;
     }
     free(q);
     L.tail=L.head;
     L.len=0;
   }
   return OK;
 }
Status DestroyList(LinkList &L)
 { /* 销毁线性链表L，L不再存在 */
   ClearList(L); /* 清空链表 */
   FreeNode(L.head);
   L.tail=NULL;
   L.len=0;
   return OK;
 }
 Status InsFirst(LinkList &L,Link h,Link s) /* 形参增加L,因为需修改L */
 { /* h指向L的一个结点，把h当做头结点，将s所指结点插入在第一个结点之前 */
   s->next=h->next;
   h->next=s;
   if(h==L.tail) /* h指向尾结点 */
     L.tail=h->next; /* 修改尾指针 */
   L.len++;
   return OK;
 }
 Status DelFirst(LinkList &L,Link h,Link &q) /* 形参增加L,因为需修改L */
 { /* h指向L的一个结点，把h当做头结点，删除链表中的第一个结点并以q返回。 */
   /* 若链表为空(h指向尾结点)，q=NULL，返回FALSE */
   q=h->next;
   if(q) /* 链表非空 */
   {
     h->next=q->next;
     if(!h->next) /* 删除尾结点 */
       L.tail=h; /* 修改尾指针 */
     L.len--;
     return OK;
   }
   else
     return FALSE; /* 链表空 */
 }
 Status Append(LinkList &L,Link s)
 { /* 将指针s(s->data为第一个数据元素)所指(彼此以指针相链,以NULL结尾)的 */
   /* 一串结点链接在线性链表L的最后一个结点之后,并改变链表L的尾指针指向新 */
   /* 的尾结点 */
   int i=1;
   L.tail->next=s;
   while(s->next)
   {
     s=s->next;
     i++;
   }
   L.tail=s;
   L.len+=i;
   return OK;
 }
 Position PriorPos(LinkList L,Link p)
 { /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置 */
   /* 若无前驱，则返回NULL */
   Link q;
   q=L.head->next;
   if(q==p) /* 无前驱 */
     return NULL;
   else
   {
     while(q->next!=p) /* q不是p的直接前驱 */
       q=q->next;
     return q;
   }
 }
 Status Remove(LinkList &L,Link &q)
 { /* 删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点 */
   Link p=L.head;
   if(L.len==0) /* 空表 */
   {
     q=NULL;
     return FALSE;
   }
   while(p->next!=L.tail)
     p=p->next;
   q=L.tail;
   p->next=NULL;
   L.tail=p;
   L.len--;
   return OK;
 }
  Status InsBefore(LinkList &L,Link &p,Link s)
 { /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前， */
   /* 并修改指针p指向新插入的结点 */
   Link q;
   q=PriorPos(L,p); /* q是p的前驱 */
   if(!q) /* p无前驱 */
     q=L.head;
   s->next=p;
   q->next=s;
   p=s;
   L.len++;
   return OK;
 }
 Status InsAfter(LinkList &L,Link &p,Link s)
 { /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后， */
   /* 并修改指针p指向新插入的结点 */
   if(p==L.tail) /* 修改尾指针 */
     L.tail=s;
   s->next=p->next;
   p->next=s;
   p=s;
   L.len++;
   return OK;
 }
 Status SetCurElem(Link p,ElemType e)
 { /* 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值 */
   p->data=e;
   return OK;
 }
 ElemType GetCurElem(Link p)
 { /* 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值 */
   return p->data;
 }
 Status ListEmpty(LinkList L)
 { /* 若线性链表L为空表，则返回TRUE，否则返回FALSE */
   if(L.len)
     return FALSE;
   else
     return TRUE;
 }
 int ListLength(LinkList L)
 { /* 返回线性链表L中元素个数 */
   return L.len;
 }
 Position GetHead(LinkList L)
 { /* 返回线性链表L中头结点的位置 */
   return L.head;
 }
 Position GetLast(LinkList L)
 { /* 返回线性链表L中最后一个结点的位置 */
   return L.tail;
 }
 Position NextPos(Link p)
 { /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置 */
   /* 若无后继，则返回NULL */
   return p->next;
 }
 Status LocatePos(LinkList L,int i,Link &p)
 { /* 返回p指示线性链表L中第i个结点的位置，并返回OK，i值不合法时返回ERROR */
   /* i=0为头结点 */
   int j;
   if(i<0||i>L.len)
     return ERROR;
   else
   {
     p=L.head;
     for(j=1;j<=i;j++)
       p=p->next;
     return OK;
   }
 }
 Position LocateElem(LinkList L,ElemType e,Status (*compare)(ElemType,ElemType))
 { /* 返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置， */
   /* 若不存在这样的元素，则返回NULL */
   Link p=L.head;
   do
     p=p->next;
   while(p&&!(compare(p->data,e))); /* 没到表尾且没找到满足关系的元素 */
   return p;
 }

 Status ListTraverse(LinkList &L,void(*visit)(ElemType))
 { /* 依次对L的每个数据元素调用函数visit()。一旦visit()失败，则操作失败 */
   if(!&L) return ERROR;
   Link p=L.head->next;
   int j;
   for(j=1;j<=L.len;j++)
   {
     visit(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 Status OrderInsert(LinkList &L,ElemType e,int (*comp)(ElemType,ElemType))
 { /* 已知L为有序线性链表，将元素e按非降序插入在L中。（用于一元多项式） */
   Link o,p,q;
   q=L.head;
   p=q->next;
   while(p!=NULL&&comp(p->data,e)<0) /* p不是表尾且元素值小于e */
   {
     q=p;
     p=p->next;
   }
   o=(Link)malloc(sizeof(LNode)); /* 生成结点 */
   o->data=e; /* 赋值 */
   q->next=o; /* 插入 */
   o->next=p;
   L.len++; /* 表长加1 */
   if(!p) /* 插在表尾 */
     L.tail=o; /* 修改尾结点 */
   return OK;
 }
 Status LocateElemP(LinkList L,ElemType e,Position &q,int(*compare)(ElemType,ElemType))
 { /* 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 */
   /* 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数 */
   /* compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式） */
   Link p=L.head,pp;
   do
   {
     pp=p;
     p=p->next;
   }while(p&&(compare(p->data,e)<0)); /* 没到表尾且p->data.expn<e.expn */
   if(!p||compare(p->data,e)>0) /* 到表尾或compare(p->data,e)>0 */
   {
     q=pp;
     return FALSE;
   }
   else /* 找到 */
   {
     q=p;
     return TRUE;
   }
 }
 Status ListInsert_L(LinkList &L,int i,ElemType e) /* 算法2.20 */
 { /* 在带头结点的单链线性表L的第i个元素之前插入元素e */
   Link h,s;
   if(!LocatePos(L,i-1,h))
     return ERROR; /* i值不合法 */
   if(!MakeNode(s,e))
     return ERROR; /* 结点分配失败 */
   InsFirst(L,h,s); /*对于从第i个结点开始的链表,第i-1个结点是它的头结点 */
   return OK;
 }

//
// Status MergeList_L(LinkList La,LinkList Lb,LinkList &Lc,int(*compare)(ElemType,ElemType))
// { /* 已知单链线性表La和Lb的元素按值非递减排列。归并La和Lb得到新的单链 */
//   /* 线性表Lc，Lc的元素也按值非递减排列。（不改变La、Lb）算法2.21 */
//   Link ha,hb,pa,pb,q;
//   ElemType a,b;
//   if(!InitList(Lc))
//     return ERROR; /* 存储空间分配失败 */
//   ha=GetHead(La); /* ha和hb分别指向La和Lb的头结点 */
//   hb=GetHead(Lb);
//   pa=NextPos(ha); /* pa和pb分别指向La和Lb的第一个结点 */
//   pb=NextPos(hb);
//   while(!ListEmpty(La)&&!ListEmpty(Lb)) /* La和Lb均非空 */
//   {
//     a=GetCurElem(pa); /* a和b为两表中当前比较元素 */
//     b=GetCurElem(pb);
//     if(compare(a,b)<=0)
//     {
//       DelFirst(&La,ha,&q);
//       InsFirst(Lc,Lc.tail,q);
//       pa=NextPos(ha);
//     }
//     else /* a>b */
//     {
//       DelFirst(&Lb,hb,&q);
//       InsFirst(Lc,Lc.tail,q);
//       pb=NextPos(hb);
//     }
//   }
//   if(!ListEmpty(La))
//     Append(Lc,pa);
//   else
//     Append(Lc,pb);
//   FreeNode(&ha);
//   FreeNode(&hb);
//   return OK;
// }

Status ListDelete(LinkList &L,int i,ElemType &e) /* 算法2.10。不改变L */
{
    /* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
    int j=0;
    Link p,q;
    LocatePos(L,i-1,p);
    if(!p) /* 删除位置不合理 */
        return ERROR;
    DelFirst(L,p,q);
    e=q->data;
    return OK;
}
Status GetElem(LinkList L,int i,ElemType &e) /* 算法2.8 */
{

    Link p;
    LocatePos(L,i,p);
    e=GetCurElem(p);
    return OK;
}
Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
{
    /* 初始条件: 线性表L已存在 */
    /* 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱, */
    /*           返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE */
    Link p,q;
    p=LocateElem(L,cur_e,equal);
    q=PriorPos(L,p);
    if(q)
    {
        pre_e=q->data;
        return OK;
    }
    return INFEASIBLE;
}
Status NextElem(LinkList L,ElemType cur_e,ElemType &pre_e)
{
    /* 初始条件: 线性表L已存在 */
    /* 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱, */
    /*           返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE */
    Link q;
    q=LocateElem(L,cur_e,equal);
    q=q->next;
    if(q)
    {
        pre_e=GetCurElem(q);
        return OK;
    }
    return INFEASIBLE;
}
 int comp(ElemType c1,ElemType c2)
 {
   return c1-c2;
 }

 void visit(ElemType c)
 {
   printf("%d ",c); /* 整型 */
 }
int main()
 {
    LinkList La,Lb,Lc,Ld,Le;
    Status i;
    int a[]= {9,7,6,4,3,5,1};
    int b[]= {1,2,3,4,5,6,7,8,9,10,11};
    int c[]= {1,3,5,7,9,11,13};
    int d[]= {1,4,6,8,12,14,16,19};
    int j;
    ElemType e;
    ElemType p;
    i=InitList(La);
    if(i==1) /* 创建空表La成功 */
        for(j=1; j<=5; j++) /* 在表La中插入5个元素 */
            i=ListInsert_L(La,j,j);
    printf("La= "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    DestroyList(La);
    printf("销毁顺序表La "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    InitList(La); /* 也可不判断是否创建成功 */
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert_L(La,j,a[j-1]);
    printf("新建La= "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    ClearList(La);
    printf("清空La "); /* 输出表La的内容 */
    ListTraverse(La,visit);
    if(ListEmpty(La))
     printf("链表为空\n");
    else
     printf("链表不为空!\n");
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert_L(La,j,a[j-1]);
    printf("新建La= "); /* 输出表Lb的内容 */
    ListTraverse(La,visit);
    printf("La数据元素个数为 %d\n",ListLength(La));
    printf("输入的元素位置 2\n");
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
    ListInsert_L(La,4,5);
    ListTraverse(La,visit);
    printf("链表头为%d\n",GetHead(La)->data);
    printf("链表尾为%d\n",GetLast(La)->data);
    printf("删除La第二个元素\n");
    ListDelete(La,2,e);
    ListTraverse(La,visit);
    printf("删除La最后一元素\n");
    Link q;
    Remove(La,q);
    ListTraverse(La,visit);
    printf("在第三个元素前插入元素3\n");
    LocatePos(La,3,q);
    Link p1;
    MakeNode(p1,3);
    InsBefore(La,q,p1);
    ListTraverse(La,visit);
    printf("在第三个元素后插入元素4\n");
    MakeNode(p1,4);
    InsAfter(La,q,p1);
    ListTraverse(La,visit);
 }

