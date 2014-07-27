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
typedef struct
{
    ElemType *elem; /* 存储空间基址 */
    int length; /* 当前长度 */
    int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
} SqList;
/* bo2-1.c 顺序表示的线性表(存储结构由c2-1.h定义)的基本操作(12个) */
Status InitList(SqList &L);/* 操作结果：构造一个空的顺序线性表 */
Status DestroyList(SqList &L);/*操作结果：销毁顺序线性表L*/
Status ClearList(SqList &L);/*操作结果：将则返回TRUE，否则返回FALSE */
int ListLength(SqList L);/*操作结果：返回L中L重置为空表 */
Status ListEmpty(SqList L);/*操作结果：若L为空表，数据元素个数 */
Status GetElem(SqList L,int i,ElemType e);/* 操作结果：用e返回L中第i个数据元素的值 */
int LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType));
/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0。算法2.6 */
Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e);
/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
Status NextElem(SqList L,ElemType cur_e,ElemType &next_e);
/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
Status ListInsert(SqList &L,int i,ElemType e);
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListDelete(SqList &L,int i,ElemType &e);
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status equal(ElemType c1,ElemType c2);
/* 判断是否相等的函数，Union()用到 */
void Union(SqList &La,SqList Lb);
/* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
Status ListTraverse(const SqList &L,void(*vi)(ElemType*));
/* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
/*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
void MergeList(SqList La,SqList Lb,SqList &Lc); /* 算法2.2 */
/* 已知线性表La和Lb中的数据元素按值非递减排列。 */
/* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
int comp(ElemType c1,ElemType c2);//比较两者的大小
Status InitList(SqList &L) /* 算法2.3 */
{
    /* 操作结果：构造一个空的顺序线性表 */
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW); /* 存储分配失败 */
    L.length=0; /* 空表长度为0 */
    L.listsize=LIST_INIT_SIZE; /* 初始存储容量 */
    return OK;
}
Status DestroyList(SqList &L)
{
    /* 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L */
    free(L.elem);
    L.elem=NULL;
    L.length=0;
    L.listsize=0;
    return OK;
}
Status ClearList(SqList &L)
{
    /* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
    L.length=0;
    return OK;
}
Status ListEmpty(SqList L)
{
    /* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}
int ListLength(SqList L)
{
    /* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
    return L.length;
}
Status GetElem(SqList &L,int i,ElemType *e)
{
    /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
    /* 操作结果：用e返回L中第i个数据元素的值 */
    if(i<1||i>L.length)
        exit(ERROR);
    *e=*(L.elem+i-1);
    return OK;
}
int LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    /* 初始条件：顺序线性表L已存在，compare()是数据元素判定函数(满足为1,否则为0) */
    /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
    /*           若这样的数据元素不存在，则返回值为0。算法2.6 */
    ElemType *p;
    int i=1; /* i的初值为第1个元素的位序 */
    p=L.elem; /* p的初值为第1个元素的存储位置 */
    while(i<=L.length&&!compare(*p++,e))
        ++i;
    if(i<=L.length)
        return i;
    else
        return 0;
}

Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
{
    /* 初始条件：顺序线性表L已存在 */
    /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
    /*           否则操作失败，pre_e无定义 */
    int i=2;
    ElemType *p=L.elem+1;
    while(i<=L.length&&*p!=cur_e)
    {
        p++;
        i++;
    }
    if(i>L.length)
        return 0;
    else
    {
        pre_e=*(--p);
        return OK;
    }
}
Status NextElem(SqList L,ElemType cur_e,ElemType &next_e)
{
    /* 初始条件：顺序线性表L已存在 */
    /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
    /*           否则操作失败，next_e无定义 */
    int i=1;
    ElemType *p=L.elem;
    while(i<L.length&&*p!=cur_e)
    {
        i++;
        p++;
    }
    if(i==L.length)
        return INFEASIBLE;
    else
    {
        next_e=*++p;
        return OK;
    }
}
Status ListInsert(SqList &L,int i,ElemType e) /* 算法2.4 */
{
    /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
    /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
    ElemType *newbase,*q,*p;
    if(i<1||i>L.length+1) /* i值不合法 */
        return ERROR;
    if(L.length>=L.listsize) /* 当前存储空间已满,增加分配 */
    {
        newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW); /* 存储分配失败 */
        L.elem=newbase; /* 新基址 */
        L.listsize+=LISTINCREMENT; /* 增加存储容量 */
    }
    q=L.elem+i-1; /* q为插入位置 */
    for(p=L.elem+L.length-1; p>=q; --p) /* 插入位置及之后的元素右移 */
        *(p+1)=*p;
    *q=e; /* 插入e */
    ++L.length; /* 表长增1 */
    return OK;
}
Status ListDelete(SqList &L,int i,ElemType &e) /* 算法2.5 */
{
    // 初始条件：顺序线性表L巭??，1≤i≤ListLength(L) */
    // 操作结果：删除L的第i个??元素，并用e返回其值，L的长度减1 */
    ElemType *p,*q;
    if(i<1||i>L.length) /* i值不合法 */
        return ERROR;
    p=L.elem+i-1; /* p为被删除元素的位置 */
    e=*p; /* 被删除元素的值赋给e */
    q=L.elem+L.length-1; /* 表尾元素的位置 */
    for(++p; p<=q; ++p) /* 被删除元素之后的元素左移 */
        *(p-1)=*p;
    L.length--; /* 表长减1 */
    return OK;
}
Status ListTraverse(const SqList &L,void(*vi)(ElemType&))
{
    /* 初始条件：顺序线性表L已存在 */
    /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
    /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
    ElemType *p;
    int i;
    p=L.elem;
    for(i=1; i<=L.length; i++)
        vi(*p++);
    printf("\n");
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
void Union(SqList &La,SqList Lb) /* 算法2.1 */
{
    /* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
    ElemType e;
    int La_len,Lb_len;
    int i;
    La_len=ListLength(La); /* 求线性表的长度 */
    Lb_len=ListLength(Lb);
    for(i=1; i<=Lb_len; i++)
    {
        GetElem(Lb,i,&e); /* 取Lb中第i个数据元素赋给e */
        if(!LocateElem(La,e,equal)) /* La中不存在和e相同的元素,则插入之 */
            ListInsert(La,++La_len,e);
    }
}
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
//合并后没有重复的元素
void MergeList(SqList La,SqList Lb,SqList &Lc)
{
    /* 另一种合并线性表的方法（根据算法2.7下的要求修改算法2.7） */
    ElemType  *pa,*pa_last,*pb,*pb_last,*pc;
    pa=La.elem;
    pb=Lb.elem;
    Lc.listsize=La.length+Lb.length; /* 此句与算法2.7不同 */
    pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
    if(!Lc.elem)
        exit(OVERFLOW);
    pa_last=La.elem+La.length-1;
    pb_last=Lb.elem+Lb.length-1;
    while(pa<=pa_last&&pb<=pb_last) /* 表La和表Lb均非空 */
        switch(comp(*pa,*pb)) /* 此句与算法2.7不同 */
        {
        case  0:
            pb++;
        case  1:
            *pc++=*pa++;
            break;
        case -1:
            *pc++=*pb++;
        }
    while(pa<=pa_last) /* 表La非空且表Lb空 */
        *pc++=*pa++;
    while(pb<=pb_last) /* 表Lb非空且表La空 */
        *pc++=*pb++;
    Lc.length=pc-Lc.elem; /* 加此句 */
}
//合并后有重复的元素
// void MergeList(SqList La,SqList Lb,SqList &Lc) /* 算法2.7 */
// { /* 已知顺序线性表La和Lb的元素按值非递减排列。 */
//   // 归并La和Lb得到新的顺序纀?hLc,Lc的元素也按值非递减排列 */
//   ElemType *pa,*pa_last,*pb,*pb_last,*pc;
//   pa=La.elem;
//   pb=Lb.elem;
//   Lc.listsize=Lc.length=La.length+Lb.length;/*不用InitList()创建空表Lc */
//   pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
//   if(!Lc.elem) /* 存储分配失败 */
//     exit(OVERFLOW);
//   pa_last=La.elem+La.length-1;
//   pb_last=Lb.elem+Lb.length-1;
//   while(pa<=pa_last&&pb<=pb_last) /* 表La和表Lb均非空 */
//   { /* 归并 */
//     if(*pa<=*pb)
//       *pc++=*pa++;
//     else
//       *pc++=*pb++;
//   }
//   while(pa<=pa_last) /* 表La非空且表Lb空 */
//     *pc++=*pa++; /* 插入La的剩余元素 */
//   while(pb<=pb_last) /* 表Lb非空且表La空 */
//     *pc++=*pb++; /* 插入Lb的剩余元素 */

// }
    void print(ElemType &c)
    {
        printf("%d ",c);
    }
//主函数为验证函数
int main()
{
    SqList La,Lb,Lc,Ld,Le;
    Status i;
    int j;
    ElemType e;
    ElemType p;
    int a[]= {9,7,6,4,3,5,1};
    int b[]= {1,2,3,4,5,6,7,8,9,10,11};
    int c[]= {1,3,5,7,9,11,13};
    int d[]= {2,4,6,8,12,14,16,19};
    i=InitList(La);
    if(i==1) /* 创建空表La成功 */
        for(j=1; j<=5; j++) /* 在表La中插入5个元素 */
            i=ListInsert(La,j,j);
    printf("La= "); /* 输出表La的内容 */
    ListTraverse(La,print);
    DestroyList(La);
    printf("销毁顺序表La "); /* 输出表La的内容 */
    ListTraverse(La,print);
    InitList(La); /* 也可不判断是否创建成功 */
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(La,j,a[j-1]);
    printf("新建La= "); /* 输出表Lb的内容 */
    ListTraverse(La,print);
    ClearList(La);
    printf("清空La "); /* 输出表La的内容 */
    ListTraverse(La,print);
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(La,j,a[j-1]);
    printf("新建La= "); /* 输出表Lb的内容 */
    ListTraverse(La,print);
    printf("La数据元素个数为 %d\n",ListLength(La));
    printf("输出的元素位置 2\n");
    GetElem(La,2,&e);
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
    ListTraverse(La,print);
    printf("删除La第二个元素\n");
    ListDelete(La,2,e);
    ListTraverse(La,print);
    InitList(Lb); /* 也可不判断是否创建成功 */
    for(j=1; j<=11; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(Lb,j,b[j-1]);
    printf("新建Lb= "); /* 输出表Lb的内容 */
    ListTraverse(Lb,print);
    Union(La,Lb);
    printf("new La= "); /* 输出新表La的内容 */
    ListTraverse(La,print);
    InitList(Lc); /* 也可不判断是否创建成功 */
    for(j=1; j<=7; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(Lc,j,c[j-1]);
    printf("新建Lc= "); /* 输出表Lb的内容 */
    ListTraverse(Lc,print);
    InitList(Ld); /* 也可不判断是否创建成功 */
    for(j=1; j<=8; j++) /* 在表Lb中插入5个元素 */
        i=ListInsert(Ld,j,d[j-1]);
    printf("新建Ld= "); /* 输出表Lb的内容 */
    ListTraverse(Ld,print);
    InitList(Le);
    MergeList(Lc,Ld,Le);
    printf("合并后为 ");
    ListTraverse(Le,print);
}
