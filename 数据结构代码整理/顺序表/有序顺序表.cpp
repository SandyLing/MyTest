#include <stdio.h>
#include <stdlib.h>
#define   LIST_INIT_SIZE 100
#define   LISTINCREMENT 10
typedef struct SqList
{
  int     *elem;
  int     length;//当前长度
  int     listsize;//分配的空间大小
}SqList;
int InitList_Sq(SqList &L) {  // 算法2.3
  // 构造一个空的线性表L。
  L.elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
  if (!L.elem) return 1;        // 存储分配失败
  L.length = 0;                  // 空表长度为0
  L.listsize = LIST_INIT_SIZE;   // 初始存储容量
  return 1;
} // InitList_Sq
int compare_position(SqList &L,int e)
{
    int i=1;
    int *q;
    q=L.elem;
    for(;*q<e;q++)
     i++;
     return i;
}
int ListInsert_Sq(SqList &L,int e) {  // 算法2.4
  // 在顺序线性表L的第i个元素之前插入新的元素e，
  // i的合法值为1≤i≤ListLength_Sq(L)+1
  int *p;
  if (L.length >= L.listsize) {   // 当前存储空间已满，增加容量
    int *newbase = (int *)realloc(L.elem,
                  (L.listsize+LISTINCREMENT)*sizeof (int));
    if (!newbase) return 0;   // 存储分配失败
    L.elem = newbase;             // 新基址
    L.listsize += LISTINCREMENT;  // 增加存储容量
  }
  int i=compare_position(L,e);
  int *q = &(L.elem[i-1]);   // q为插入位置
  for (p = &(L.elem[L.length-1]); p>=q; --p) *(p+1) = *p;
                                  // 插入位置及之后的元素右移
  *q = e;       // 插入e
  ++L.length;   // 表长增1
  return 1;
} // ListInsert_Sq
int ListDelete_Sq(SqList &L, int i, int &e) {  // 算法2.5
  // 在顺序线性表L中删除第i个元素，并用e返回其值。
  // i的合法值为1≤i≤ListLength_Sq(L)。
  int *p, *q;
  if (i<1 || i>L.length)

  {
      printf("\nerror!\n");
      return 0;
  }   // i值不合法 // i值不合法
  p = &(L.elem[i-1]);                   // p为被删除元素的位置
  e = *p;                               // 被删除元素的值赋给e
  q = L.elem+L.length-1;                // 表尾元素的位置
  for (++p; p<=q; ++p) *(p-1) = *p;     // 被删除元素之后的元素左移
  --L.length;                           // 表长减1
  return 1;
} // ListDelete_Sq
int compare(int a,int b)
{
    if (a==b)
     return 1;
     return 0;
}
int LocateElem_Sq(SqList L, int e) {  // 算法2.6
  // 在顺序线性表L中查找第1个值与e满足compare()的元素的位序。
  // 若找到，则返回其在L中的位序，否则返回0。
  int i;
  int *p;
  i = 1;        // i的初值为第1个元素的位序
  p = L.elem;   // p的初值为第1个元素的存储位置
  while (i <= L.length && !(*compare)(*p++, e))
    ++i;
  if (i <= L.length) return i;
  else return 0;
} // LocateElem_Sq
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc) {  // 算法2.7
  // 已知顺序线性表La和Lb的元素按值非递减排列。
  // 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列。
  int *pa,*pb,*pc,*pa_last,*pb_last;
  pa = La.elem;  pb = Lb.elem;
  Lc.listsize = Lc.length = La.length+Lb.length;
  pc = Lc.elem = (int *)malloc(Lc.listsize*sizeof(int));
  if (!Lc.elem)
    exit (9);   // 存储分配失败
  pa_last = La.elem+La.length-1;
  pb_last = Lb.elem+Lb.length-1;
  while (pa <= pa_last && pb <= pb_last) {  // 归并
    if (*pa <= *pb) *pc++ = *pa++;
    else *pc++ = *pb++;
  }
  while (pa <= pa_last) *pc++ = *pa++;      // 插入La的剩余元素
  while (pb <= pb_last) *pc++ = *pb++;      // 插入Lb的剩余元素
} // MergeList

void display(SqList &l)
{
  for(int i=0;i<l.length;i++)
    printf("%d ",l.elem[i]);
    printf("\n");
}
int main()
{
    SqList la;
    SqList lb;
    SqList lc;
    int temp[20],a,d=0,b;
    InitList_Sq(la);
    InitList_Sq(lb);
    InitList_Sq(lc);
    printf("输入顺序表la一些初始数（结束按^z)：\n");
    while(scanf("%d",&a)!=EOF)
    {
     ListInsert_Sq(la,a);
    }
    display(la);
    printf("\n请输入要插入的元素位置（结束按^z)\n");
    while(scanf("%d",&a)!=EOF)
    {
     ListInsert_Sq(la,a);
     printf("元素列表为：\n");
     display(la);
    }
    printf("\n请输入要删除的元素位置（结束按^z)");
    while(scanf("%d",&a)!=EOF)
    {
      ListDelete_Sq(la,a,temp[d]);
      //printf("\n被删除的元素为：%d\n",temp);
      d++;
      printf("剩下的元素为：\n");
      display(la);
    }
    for(int i=0;i<d;i++)
    printf("\n被删除的元素为：%d\n",temp[i]);
    printf("\n请输入要查询的元素（结束按^z)\n");
    while(scanf("%d",&a)!=EOF)
    {
        int g;
        g=LocateElem_Sq(la,a);
     if(!g)
     printf("你输入的元素未发现！\n");
     else
     printf("您输入的元素在线性表中的%d位置\n",g);
    }
    printf("输入顺序表lb初始数（结束按^z)：\n");
    while(scanf("%d",&a)!=EOF)
    {
     ListInsert_Sq(lb,a);
    }
     printf("线性表lb为： ");
     display(lb);
     MergeList_Sq(la,lb,lc);
     printf("合并l和lb线性表，合并后lc为：\n");
     display(lc);
    return 0;
}
