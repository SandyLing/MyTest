#include <stdio.h>
#include <stdlib.h>
typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode,*LinkList;
int compare_positon (LinkList &L,int e)
{
    LinkList p=L;
    int i=1;
   while(p!=NULL&&p->data<e)
     {
         p=p->next;
         i++;
     }
     return i;
}
int ListInsert_L(LinkList &L, int e) {  // 算法2.9
  // 在带头结点的单链线性表L的第i个元素之前插入元素e
  LinkList s,q=L;
  int i=compare_positon(L,e);
  s = (LinkList)malloc(sizeof(LNode));
  s->data = e;
  if(i==1)
  {
      s->next=q;
      L=s;
      return 1;
  }
  else
  {
    for(int n=1;n<i-1;n++)
    q=q->next;
  }
  if(q==NULL)
  {
    q=s;
    s->next=NULL;
  }
  else
  {
      s->next = q->next;
      q->next = s;
  }

  return 1;
} // LinstInsert_L
LinkList ListCreat_L()
{
   LinkList  head=NULL,s;
   int i,j,a;
   printf("输入线性表一些初始数（结束按^z)：\n");
   while(scanf("%d",&a)!=EOF)
    {
   if(head==NULL)
   {
   s = (LinkList)malloc(sizeof(LNode));  // 生成新结点
   s->data = a;
   head=s;      // 插入L中
   s->next = NULL;
   }
   else
   {
   ListInsert_L(head,a);
   }

    }
    return head;
}
int ListDelete_L(LinkList &L, int i) {  // 算法2.10
  // 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
  LinkList p,q;
  int a;
  p = L;
  int j = 0;
  if(i==1)
  {
        a=L->data;
        L=L->next;
        free(p);
  }
  else
  {
   while (p->next!=NULL && j < i-2) {  // 寻找第i-1个结点，并令p指向其前趋
    p = p->next;
    ++j;}
   if(p->next->next==NULL)
   {
     a=p->next->data;
     p->next=NULL;
   }
   else
   {
    q = p->next;
    p->next = q->next;           // 删除并释放结点
    a = q->data;
    free(q);
   }
  }
  return a;
} // ListDelete_L
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
  // 算法2.12
  // 已知单链线性表La和Lb的元素按值非递减排列。
  // 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列。
  LinkList pa, pb, pc;
  pa = La;    pb = Lb;
  int a;
  if (pa->data <= pb->data)
    {Lc=La;pa = pa->next;}
  else
    {Lc=Lb;pb = pb->next;}
  pc =  Lc;
  while (pa!=NULL&&pb!=NULL) {
    if (pa->data <= pb->data) {
        pc->next= pa;
        pc=pa;
        pa = pa->next;

    }
    else {   pc->next= pb; pc=pb;   pb = pb->next; }
  }
  pc->next = pa ? pa : pb;  // 插入剩余段
  //free(Lb);                 // 释放Lb的头结点
} // MergeList_L

void display(LinkList &l)
{
    LinkList p=l;
    printf("链表为：");
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
     }
    printf("\n");
}
int main()
{
     int a,i=0;
     int temp[20];
     LinkList la=ListCreat_L();
     LinkList lc;
     //printf("la");
     printf("la");
     display(la);

     printf("\n请输入要插入的元素（结束按^z)\n");
     while(scanf("%d",&a)!=EOF)
    {
     ListInsert_L(la,a);
     printf("元素列表为：\n");
     printf("la");
     display(la);
    }
     printf("\n请输入要删除的元素位置（结束按^z)\n");
     while(scanf("%d",&a)!=EOF)
    {
     temp[i]=ListDelete_L(la,a);
     printf("元素列表为：\n");
     printf("la");
     display(la);
     i++;
    }
    for(int n=0;n<i;n++)
     printf("\n你删除的元素为：%d\n",temp[n]);
    LinkList lb=ListCreat_L();
    printf("lb");
    display(lb);
    MergeList_L(la,lb,lc);
    printf("lc");
    display(lc);
    return 0;

}
