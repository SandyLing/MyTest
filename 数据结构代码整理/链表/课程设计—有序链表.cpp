#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LIST_INIT_SIZE 10 /* ���Ա�洢�ռ�ĳ�ʼ������ */
#define LISTINCREMENT 2 /* ���Ա�洢�ռ�ķ������� */
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
int comp(ElemType c1,ElemType c2)//�Ƚ����ߵĴ�С
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
    /* �������������һ���յ����Ա�L */
    L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ���,��ʹLָ���ͷ��� */
    if(!L) /* �洢����ʧ�� */
        exit(OVERFLOW);
    L->next=NULL; /* ָ����Ϊ�� */
    return OK;
}
Status ListInsert(LinkList &L,ElemType e,int(*vf)(ElemType,ElemType))
{
    /* �ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
    int j=0;
    LinkList p=L,s;
    //�Ƚ�Ѱ�ұ�eС��ǰһ���ڵ�
    while(p->next&&vf(p->next->data,e))
     {
         p=p->next;
     }
    s=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
    s->data=e; /* ����L�� */
    s->next=p->next;
    p->next=s;
    return OK;
}
Status ListDelete(LinkList L,int i,ElemType &e) /* �㷨2.10�����ı�L */
{
    /* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ��,����e������ֵ */
    int j=0;
    LinkList p=L,q;
    while(p->next&&j<i-1) /* Ѱ�ҵ�i�����,����pָ����ǰ�� */
    {
        p=p->next;
        j++;
    }
    if(!p->next||j>i-1) /* ɾ��λ�ò����� */
        return ERROR;
    q=p->next; /* ɾ�����ͷŽ�� */
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}
Status ListTraverse(LinkList L,void(*vi)(ElemType))
/* vi���β�����ΪElemType����bo2-1.c����Ӧ�������β�����ElemType&��ͬ */
{
    /* ��ʼ���������Ա�L�Ѵ��� */
    /* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
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
void visit(ElemType c) /* ListTraverse()���õĺ���(����Ҫһ��) */
{
    printf("%d ",c);
}
Status equal(ElemType c1,ElemType c2)
{
    /* �ж��Ƿ���ȵĺ�����Union()�õ� */
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
int compare(ElemType c1,ElemType c2)//�Ƚ����ߵĴ�С
{
    int i;
    if(c1<c2)
        i=1;
    else
        i=0;
    return i;
}
void MergeList(LinkList La,LinkList &Lb,LinkList &Lc)/* �㷨2.12 */
{
    /* ��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С� */
    /* �鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����� */
    LinkList pa=La->next,pb=Lb->next,pc;
    Lc=pc=La; /* ��La��ͷ�����ΪLc��ͷ��� */
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
    pc->next=pa?pa:pb; /* ����ʣ��� */
    free(Lb); /* �ͷ�Lb��ͷ��� */
    Lb=NULL;
}
//�ҵ�����k���ڵ�
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
    printf("�½�La= "); /* �����La������ */
    ListTraverse(La,visit);
    printf("ɾ��La�ڶ���Ԫ��\n");
    ListDelete(La,2,e);
    printf("ɾ����Ԫ��Ϊ%d\n",e);
    printf("La= ");
    ListTraverse(La,visit);
    InitList(Lb);
    for(j=1; j<=8; j++)
        ListInsert(Lb,b[j-1],compare);
    printf("�½�Lb= "); /* �����La������ */
    ListTraverse(Lb,visit);
    MergeList(La,Lb,Lc);
    printf("�ϲ��� Lc= ");
    ListTraverse(Lc,visit);
    int k=4;
    printf("������%d ",k);
    int i=0;
    ListTraverseDaoK(Lc->next,visit,i,k);
}
