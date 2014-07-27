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
typedef struct LNode *LinkList; /* ��һ�ֶ���LinkList�ķ��� */
Status InitList(LinkList &L)
{
    /* �������������һ���յ����Ա�L */
    L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ���,��ʹLָ���ͷ��� */
    if(!L) /* �洢����ʧ�� */
        exit(OVERFLOW);
    L->next=NULL; /* ָ����Ϊ�� */
    return OK;
}
Status DestroyList(LinkList &L)
{
    /* ��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L */
    LinkList q;
    while(L)
    {
        q=L->next;
        free(L);
        L=q;
    }
    return OK;
}
Status ClearList(LinkList &L) /* ���ı�L */
{
    /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
    LinkList p,q;
    p=L->next; /* pָ���һ����� */
    while(p) /* û����β */
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL; /* ͷ���ָ����Ϊ�� */
    return OK;
}
Status ListEmpty(LinkList &L)
{
    /* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
    if(L->next) /* �ǿ� */
        return FALSE;
    else
        return TRUE;
}
int ListLength(LinkList L)
{
    /* ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
    int i=0;
    LinkList p=L->next; /* pָ���һ����� */
    while(p) /* û����β */
    {
        i++;
        p=p->next;
    }
    return i;
}
Status GetElem(LinkList L,int i,ElemType &e) /* �㷨2.8 */
{
    /* LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
    int j=1; /* jΪ������ */
    LinkList p=L->next; /* pָ���һ����� */
    while(p&&j<i) /* ˳ָ��������,ֱ��pָ���i��Ԫ�ػ�pΪ�� */
    {
        p=p->next;
        j++;
    }
    if(!p||j>i) /* ��i��Ԫ�ز����� */
        return ERROR;
    e=p->data; /* ȡ��i��Ԫ�� */
    return OK;
}
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    /* ��ʼ����: ���Ա�L�Ѵ���,compare()������Ԫ���ж�����(����Ϊ1,����Ϊ0) */
    /* �������: ����L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
    /*           ������������Ԫ�ز�����,�򷵻�ֵΪ0 */
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(compare(p->data,e)) /* �ҵ�����������Ԫ�� */
            return i;
        p=p->next;
    }
    return 0;
}
Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
{
    /* ��ʼ����: ���Ա�L�Ѵ��� */
    /* �������: ��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��, */
    /*           ����OK;�������ʧ��,pre_e�޶���,����INFEASIBLE */
    LinkList q,p=L->next; /* pָ���һ����� */
    while(p->next) /* p��ָ����к�� */
    {
        q=p->next; /* qΪp�ĺ�� */
        if(q->data==cur_e)
        {
            pre_e=p->data;
            return OK;
        }
        p=q; /* p����� */
    }
    return INFEASIBLE;
}
Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
{
    /* ��ʼ���������Ա�L�Ѵ��� */
    /* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
    /*           ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE */
    LinkList p=L->next; /* pָ���һ����� */
    while(p->next) /* p��ָ����к�� */
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
Status ListInsert(LinkList L,int i,ElemType e) /* �㷨2.9�����ı�L */
{
    /* �ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
    int j=0;
    LinkList p=L,s;
    while(p&&j<i-1) /* Ѱ�ҵ�i-1����� */
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1) /* iС��1���ߴ��ڱ� */
        return ERROR;
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
void CreateList(LinkList &L,int n) /* �㷨2.11 */
{
    /* ��λ��(���ڱ�ͷ)����n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�L */
    int i;
    LinkList p;
    L=(LinkList)malloc(sizeof(struct LNode));
    L->next=NULL; /* �Ƚ���һ����ͷ���ĵ����� */
    printf("������%d������\n",n);
    for(i=n; i>0; --i)
    {
        p=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
        scanf("%d",&p->data); /* ����Ԫ��ֵ */
        p->next=L->next; /* ���뵽��ͷ */
        L->next=p;
    }
}
void CreateList2(LinkList &L,int n)
{
    /* ��λ��(���ڱ�β)����n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա� */
    int i;
    LinkList p,q;
    L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ��� */
    L->next=NULL;
    q=L;
    printf("������%d������\n",n);
    for(i=1; i<=n; i++)
    {
        p=(LinkList)malloc(sizeof(struct LNode));
        scanf("%d",&p->data);
        q->next=p;
        q=q->next;
    }
    p->next=NULL;
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
    if(i==1) /* �����ձ�La�ɹ� */
        for(j=1; j<=5; j++) /* �ڱ�La�в���5��Ԫ�� */
            i=ListInsert(La,j,j);
    printf("La= "); /* �����La������ */
    ListTraverse(La,visit);
    DestroyList(La);
    printf("����˳���La "); /* �����La������ */
    ListTraverse(La,visit);
    InitList(La); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(La,j,a[j-1]);
    printf("�½�La= "); /* �����La������ */
    ListTraverse(La,visit);
    ClearList(La);
    printf("���La "); /* �����La������ */
    ListTraverse(La,visit);
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(La,j,a[j-1]);
    printf("�½�La= "); /* �����Lb������ */
    ListTraverse(La,visit);
    printf("La����Ԫ�ظ���Ϊ %d\n",ListLength(La));
    printf("�����Ԫ��λ�� 2\n");
    GetElem(La,2,e);
    printf("La�ж�Ӧ������Ԫ��Ϊ%d\n",e);
    printf("�ж��Ƿ����Ԫ��1\n");
    if(LocateElem(La,1,equal))
        printf("La����Ԫ��1\n");
    else
        printf("La������Ԫ��1\n");
    if(PriorElem(La,5,p))
        printf("pΪLa��Ԫ��5��ǰ�� %d\n",p);
    else
        printf("La�в����ڶ�Ӧ��Ԫ��\n");
    if(NextElem(La,5,p))
        printf("pΪLa��Ԫ��5��ǰ�� %d\n",p);
    else
        printf("La�в����ڶ�Ӧ��Ԫ��\n");
    printf("��La����λ�ò���5\n");
    ListInsert(La,4,5);
    ListTraverse(La,visit);
    printf("ɾ��La�ڶ���Ԫ��\n");
    ListDelete(La,2,e);
    ListTraverse(La,visit);
    InitList(Lc); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(Lc,j,c[j-1]);
    printf("�½�Lc= "); /* �����Lb������ */
    ListTraverse(Lc,visit);
    InitList(Ld); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=8; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(Ld,j,d[j-1]);
    printf("�½�Ld= "); /* �����Lb������ */
    ListTraverse(Ld,visit);
    InitList(Le);
    MergeList(Lc,Ld,Le);
    printf("�ϲ���Ϊ ");
    ListTraverse(Le,visit);
    CreateList(Lb,5);
    printf("��λ��(���ڱ�ͷ)����n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�L\n");
    ListTraverse(Lb,visit);
    DestroyList(Lb);
    CreateList2(Lb,5);
    printf("��λ��(���ڱ�β)����n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�\n");
    ListTraverse(Lb,visit);
}
