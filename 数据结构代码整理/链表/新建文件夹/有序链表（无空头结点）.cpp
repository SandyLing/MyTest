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
int ListInsert_L(LinkList &L, int e) {  // �㷨2.9
  // �ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
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
   printf("�������Ա�һЩ��ʼ����������^z)��\n");
   while(scanf("%d",&a)!=EOF)
    {
   if(head==NULL)
   {
   s = (LinkList)malloc(sizeof(LNode));  // �����½��
   s->data = a;
   head=s;      // ����L��
   s->next = NULL;
   }
   else
   {
   ListInsert_L(head,a);
   }

    }
    return head;
}
int ListDelete_L(LinkList &L, int i) {  // �㷨2.10
  // �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
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
   while (p->next!=NULL && j < i-2) {  // Ѱ�ҵ�i-1����㣬����pָ����ǰ��
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
    p->next = q->next;           // ɾ�����ͷŽ��
    a = q->data;
    free(q);
   }
  }
  return a;
} // ListDelete_L
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
  // �㷨2.12
  // ��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С�
  // �鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С�
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
  pc->next = pa ? pa : pb;  // ����ʣ���
  //free(Lb);                 // �ͷ�Lb��ͷ���
} // MergeList_L

void display(LinkList &l)
{
    LinkList p=l;
    printf("����Ϊ��");
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

     printf("\n������Ҫ�����Ԫ�أ�������^z)\n");
     while(scanf("%d",&a)!=EOF)
    {
     ListInsert_L(la,a);
     printf("Ԫ���б�Ϊ��\n");
     printf("la");
     display(la);
    }
     printf("\n������Ҫɾ����Ԫ��λ�ã�������^z)\n");
     while(scanf("%d",&a)!=EOF)
    {
     temp[i]=ListDelete_L(la,a);
     printf("Ԫ���б�Ϊ��\n");
     printf("la");
     display(la);
     i++;
    }
    for(int n=0;n<i;n++)
     printf("\n��ɾ����Ԫ��Ϊ��%d\n",temp[n]);
    LinkList lb=ListCreat_L();
    printf("lb");
    display(lb);
    MergeList_L(la,lb,lc);
    printf("lc");
    display(lc);
    return 0;

}
