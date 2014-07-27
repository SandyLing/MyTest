//���������βָ���ѭ������ĺϲ�
//LΪ�����е����һԪ�أ�L->next Ϊͷ����սڵ�
#include<string.h>
//#include<ctype.h>
#include<malloc.h> /* malloc()�� */
#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<stdlib.h> /* atoi() */
//#include<io.h> /* eof() */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#include<process.h> /* exit() */
#define LIST_INIT_SIZE 10 /* ���Ա�洢�ռ�ĳ�ʼ������ */
#define LISTINCREMENT 2 /* ���Ա�洢�ռ�ķ������� */
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
typedef int ElemType;
struct LNode
{
   ElemType data;
   struct LNode *next;
};
int count=0;
typedef struct LNode *LinkList; /* ��һ�ֶ���LinkList�ķ��� */
typedef struct DuLNode
 {
   ElemType data;
   struct DuLNode *prior,*next;
 }DuLNode,*DuLinkList;
//����βָ��ĵ�ѭ������(�洢�ṹ��c2-2.h����)��12����������
Status InitList_CL(LinkList &L)
{ /* �������������һ���յ����Ա�L */
   L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ���,��ʹLָ���ͷ��� */
   if(!L) /* �洢����ʧ�� */
     exit(OVERFLOW);
   L->next=L; /* ָ����ָ��ͷ��� */
   return OK;
 }
Status DestroyList_CL(LinkList &L)
 { /* ����������������Ա�L */
   LinkList q,p=L->next; /* pָ��ͷ��� */
   while(p!=L) /* û����β */
   {
     q=p->next;
     free(p);
     p=q;
   }
   free(L);
   L=NULL;
   return OK;
 }
 Status ClearList_CL(LinkList &L) /* �ı�L */
 { /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
   LinkList p,q;
   L=L->next; /* Lָ��ͷ��� */
   p=L->next; /* pָ���һ����� */
   while(p!=L) /* û����β */
   {
     q=p->next;
     free(p);
     p=q;
   }
   L->next=L; /* ͷ���ָ����ָ������ */
   return OK;
 }
 Status ListEmpty_CL(LinkList L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
   if(L->next==L) /* �� */
     return TRUE;
   else
     return FALSE;
 }
 int ListLength_CL(LinkList L)
 { /* ��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
   int i=0;
   LinkList p=L->next; /* pָ��ͷ��� */
   while(p!=L) /* û����β */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem_CL(LinkList L,int i,ElemType &e)
 { /* ����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
   int j=1; /* ��ʼ��,jΪ������ */
   LinkList p=L->next->next; /* pָ���һ����� */
   if(i<=0||i>ListLength_CL(L)) /* ��i��Ԫ�ز����� */
     return ERROR;
   while(j<i)
   { /* ˳ָ��������,ֱ��pָ���i��Ԫ�� */
     p=p->next;
     j++;
   }
   e=p->data; /* ȡ��i��Ԫ�� */
   return OK;
 }

 int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж����� */
   /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
   /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
   int i=0;
   LinkList p=L->next->next; /* pָ���һ����� */
   while(p!=L->next)
   {
     i++;
     if(compare(p->data,e)) /* �����ϵ */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem_CL(LinkList L,ElemType cur_e,ElemType &pre_e)
 { /* ��ʼ���������Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
   /*           �������ʧ�ܣ�pre_e�޶��� */
   LinkList q,p=L->next->next; /* pָ���һ����� */
   q=p->next;
   while(q!=L->next) /* pû����β */
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
 { /* ��ʼ���������Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣� */
   /*           �������ʧ�ܣ�next_e�޶��� */
   LinkList p=L->next->next; /* pָ���һ����� */
   while(p!=L) /* pû����β */
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

 Status ListInsert_CL(LinkList &L,int i,ElemType e) /* �ı�L */
 { /* ��L�ĵ�i��λ��֮ǰ����Ԫ��e */
   LinkList p=L->next,s; /* pָ��ͷ��� */
   int j=0;
   if(i<=0||i>ListLength_CL(L)+1) /* �޷��ڵ�i��Ԫ��֮ǰ���� */
     return ERROR;
   while(j<i-1) /* Ѱ�ҵ�i-1����� */
   {
     p=p->next;
     j++;
   }
   s=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
   s->data=e; /* ����L�� */
   s->next=p->next;
   p->next=s;
   if(p==L) /* �ı�β��� */
     L=s;
   return OK;
 }

 Status ListDelete_CL(LinkList &L,int i,ElemType &e) /* �ı�L */
 { /* ɾ��L�ĵ�i��Ԫ��,����e������ֵ */
   LinkList p=L->next,q; /* pָ��ͷ��� */
   int j=0;
   if(i<=0||i>ListLength_CL(L)) /* ��i��Ԫ�ز����� */
     return ERROR;
   while(j<i-1) /* Ѱ�ҵ�i-1����� */
   {
     p=p->next;
     j++;
   }
   q=p->next; /* qָ���ɾ����� */
   p->next=q->next;
   e=q->data;
   if(L==q) /* ɾ�����Ǳ�βԪ�� */
     L=p;
   free(q); /* �ͷŴ�ɾ����� */
   return OK;
 }
Status equal(ElemType c1,ElemType c2)
{
    /* �ж��Ƿ���ȵĺ�����Union()�õ� */
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
 Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
 { /* ��ʼ����:L�Ѵ��ڡ��������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
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
    if(i==1) /* �����ձ�La�ɹ� */
        for(j=1; j<=5; j++) /* �ڱ�La�в���5��Ԫ�� */
            i=ListInsert_CL(La,j,j);
    printf("La= "); /* �����La������ */
    ListTraverse_CL(La,visit);
    DestroyList_CL(La);
    printf("����˳���La "); /* �����La������ */
    ListTraverse_CL(La,visit);
    InitList_CL(La); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert_CL(La,j,a[j-1]);
    printf("�½�La= "); /* �����La������ */
    ListTraverse_CL(La,visit);
    ClearList_CL(La);
    printf("���La "); /* �����La������ */
    ListTraverse_CL(La,visit);
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert_CL(La,j,a[j-1]);
    printf("�½�La= "); /* �����Lb������ */
    ListTraverse_CL(La,visit);
    printf("La����Ԫ�ظ���Ϊ %d\n",ListLength_CL(La));
    printf("�����Ԫ��λ�� 2\n");
    GetElem_CL(La,2,e);
    printf("La�ж�Ӧ������Ԫ��Ϊ%d\n",e);
    printf("�ж��Ƿ����Ԫ��1\n");
    if(LocateElem_CL(La,1,equal))
        printf("La����Ԫ��1\n");
    else
        printf("La������Ԫ��1\n");
    if(PriorElem_CL(La,5,p))
        printf("pΪLa��Ԫ��5��ǰ�� %d\n",p);
    else
        printf("La�в����ڶ�Ӧ��Ԫ��\n");
    if(NextElem_CL(La,5,p))
        printf("pΪLa��Ԫ��5��ǰ�� %d\n",p);
    else
        printf("La�в����ڶ�Ӧ��Ԫ��\n");
    printf("��La����λ�ò���5\n");
    ListInsert_CL(La,4,5);
    ListTraverse_CL(La,visit);
    printf("ɾ��La�ڶ���Ԫ��\n");
    ListDelete_CL(La,2,e);
    ListTraverse_CL(La,visit);
    InitList_CL(Lc); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert_CL(Lc,j,c[j-1]);
    printf("�½�Lc= "); /* �����Lb������ */
    ListTraverse_CL(Lc,visit);
    InitList_CL(Ld); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=8; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert_CL(Ld,j,d[j-1]);
    printf("�½�Ld= "); /* �����Lb������ */
    ListTraverse_CL(Ld,visit);
    InitList_CL(Le);
    MergeList_CL(Lc,Ld);
    printf("�ϲ���Ϊ ");
    ListTraverse_CL(Lc,visit);
 }

