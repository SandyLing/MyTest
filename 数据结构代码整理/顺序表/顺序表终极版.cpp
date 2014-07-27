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
typedef struct
{
    ElemType *elem; /* �洢�ռ��ַ */
    int length; /* ��ǰ���� */
    int listsize; /* ��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ) */
} SqList;
/* bo2-1.c ˳���ʾ�����Ա�(�洢�ṹ��c2-1.h����)�Ļ�������(12��) */
Status InitList(SqList &L);/* �������������һ���յ�˳�����Ա� */
Status DestroyList(SqList &L);/*�������������˳�����Ա�L*/
Status ClearList(SqList &L);/*������������򷵻�TRUE�����򷵻�FALSE */
int ListLength(SqList L);/*�������������L��L����Ϊ�ձ� */
Status ListEmpty(SqList L);/*�����������LΪ�ձ�����Ԫ�ظ��� */
Status GetElem(SqList L,int i,ElemType e);/* �����������e����L�е�i������Ԫ�ص�ֵ */
int LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType));
/* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
/*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0���㷨2.6 */
Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e);
/* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
/*           �������ʧ�ܣ�pre_e�޶��� */
Status NextElem(SqList L,ElemType cur_e,ElemType &next_e);
/* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
/*           �������ʧ�ܣ�next_e�޶��� */
Status ListInsert(SqList &L,int i,ElemType e);
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
Status ListDelete(SqList &L,int i,ElemType &e);
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status equal(ElemType c1,ElemType c2);
/* �ж��Ƿ���ȵĺ�����Union()�õ� */
void Union(SqList &La,SqList Lb);
/* �����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La�� */
Status ListTraverse(const SqList &L,void(*vi)(ElemType*));
/* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
/*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
void MergeList(SqList La,SqList Lb,SqList &Lc); /* �㷨2.2 */
/* ��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����С� */
/* �鲢La��Lb�õ��µ����Ա�Lc,Lc������Ԫ��Ҳ��ֵ�ǵݼ����� */
int comp(ElemType c1,ElemType c2);//�Ƚ����ߵĴ�С
Status InitList(SqList &L) /* �㷨2.3 */
{
    /* �������������һ���յ�˳�����Ա� */
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW); /* �洢����ʧ�� */
    L.length=0; /* �ձ���Ϊ0 */
    L.listsize=LIST_INIT_SIZE; /* ��ʼ�洢���� */
    return OK;
}
Status DestroyList(SqList &L)
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������˳�����Ա�L */
    free(L.elem);
    L.elem=NULL;
    L.length=0;
    L.listsize=0;
    return OK;
}
Status ClearList(SqList &L)
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
    L.length=0;
    return OK;
}
Status ListEmpty(SqList L)
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}
int ListLength(SqList L)
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
    return L.length;
}
Status GetElem(SqList &L,int i,ElemType *e)
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
    /* �����������e����L�е�i������Ԫ�ص�ֵ */
    if(i<1||i>L.length)
        exit(ERROR);
    *e=*(L.elem+i-1);
    return OK;
}
int LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����(����Ϊ1,����Ϊ0) */
    /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
    /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0���㷨2.6 */
    ElemType *p;
    int i=1; /* i�ĳ�ֵΪ��1��Ԫ�ص�λ�� */
    p=L.elem; /* p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ�� */
    while(i<=L.length&&!compare(*p++,e))
        ++i;
    if(i<=L.length)
        return i;
    else
        return 0;
}

Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
{
    /* ��ʼ������˳�����Ա�L�Ѵ��� */
    /* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
    /*           �������ʧ�ܣ�pre_e�޶��� */
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
    /* ��ʼ������˳�����Ա�L�Ѵ��� */
    /* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
    /*           �������ʧ�ܣ�next_e�޶��� */
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
Status ListInsert(SqList &L,int i,ElemType e) /* �㷨2.4 */
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1 */
    /* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
    ElemType *newbase,*q,*p;
    if(i<1||i>L.length+1) /* iֵ���Ϸ� */
        return ERROR;
    if(L.length>=L.listsize) /* ��ǰ�洢�ռ�����,���ӷ��� */
    {
        newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW); /* �洢����ʧ�� */
        L.elem=newbase; /* �»�ַ */
        L.listsize+=LISTINCREMENT; /* ���Ӵ洢���� */
    }
    q=L.elem+i-1; /* qΪ����λ�� */
    for(p=L.elem+L.length-1; p>=q; --p) /* ����λ�ü�֮���Ԫ������ */
        *(p+1)=*p;
    *q=e; /* ����e */
    ++L.length; /* ����1 */
    return OK;
}
Status ListDelete(SqList &L,int i,ElemType &e) /* �㷨2.5 */
{
    // ��ʼ������˳�����Ա�L�~??��1��i��ListLength(L) */
    // ���������ɾ��L�ĵ�i��??Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
    ElemType *p,*q;
    if(i<1||i>L.length) /* iֵ���Ϸ� */
        return ERROR;
    p=L.elem+i-1; /* pΪ��ɾ��Ԫ�ص�λ�� */
    e=*p; /* ��ɾ��Ԫ�ص�ֵ����e */
    q=L.elem+L.length-1; /* ��βԪ�ص�λ�� */
    for(++p; p<=q; ++p) /* ��ɾ��Ԫ��֮���Ԫ������ */
        *(p-1)=*p;
    L.length--; /* ����1 */
    return OK;
}
Status ListTraverse(const SqList &L,void(*vi)(ElemType&))
{
    /* ��ʼ������˳�����Ա�L�Ѵ��� */
    /* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
    /*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
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
    /* �ж��Ƿ���ȵĺ�����Union()�õ� */
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
void Union(SqList &La,SqList Lb) /* �㷨2.1 */
{
    /* �����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La�� */
    ElemType e;
    int La_len,Lb_len;
    int i;
    La_len=ListLength(La); /* �����Ա�ĳ��� */
    Lb_len=ListLength(Lb);
    for(i=1; i<=Lb_len; i++)
    {
        GetElem(Lb,i,&e); /* ȡLb�е�i������Ԫ�ظ���e */
        if(!LocateElem(La,e,equal)) /* La�в����ں�e��ͬ��Ԫ��,�����֮ */
            ListInsert(La,++La_len,e);
    }
}
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
//�ϲ���û���ظ���Ԫ��
void MergeList(SqList La,SqList Lb,SqList &Lc)
{
    /* ��һ�ֺϲ����Ա�ķ����������㷨2.7�µ�Ҫ���޸��㷨2.7�� */
    ElemType  *pa,*pa_last,*pb,*pb_last,*pc;
    pa=La.elem;
    pb=Lb.elem;
    Lc.listsize=La.length+Lb.length; /* �˾����㷨2.7��ͬ */
    pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
    if(!Lc.elem)
        exit(OVERFLOW);
    pa_last=La.elem+La.length-1;
    pb_last=Lb.elem+Lb.length-1;
    while(pa<=pa_last&&pb<=pb_last) /* ��La�ͱ�Lb���ǿ� */
        switch(comp(*pa,*pb)) /* �˾����㷨2.7��ͬ */
        {
        case  0:
            pb++;
        case  1:
            *pc++=*pa++;
            break;
        case -1:
            *pc++=*pb++;
        }
    while(pa<=pa_last) /* ��La�ǿ��ұ�Lb�� */
        *pc++=*pa++;
    while(pb<=pb_last) /* ��Lb�ǿ��ұ�La�� */
        *pc++=*pb++;
    Lc.length=pc-Lc.elem; /* �Ӵ˾� */
}
//�ϲ������ظ���Ԫ��
// void MergeList(SqList La,SqList Lb,SqList &Lc) /* �㷨2.7 */
// { /* ��֪˳�����Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С� */
//   // �鲢La��Lb�õ��µ�˳���b?hLc,Lc��Ԫ��Ҳ��ֵ�ǵݼ����� */
//   ElemType *pa,*pa_last,*pb,*pb_last,*pc;
//   pa=La.elem;
//   pb=Lb.elem;
//   Lc.listsize=Lc.length=La.length+Lb.length;/*����InitList()�����ձ�Lc */
//   pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
//   if(!Lc.elem) /* �洢����ʧ�� */
//     exit(OVERFLOW);
//   pa_last=La.elem+La.length-1;
//   pb_last=Lb.elem+Lb.length-1;
//   while(pa<=pa_last&&pb<=pb_last) /* ��La�ͱ�Lb���ǿ� */
//   { /* �鲢 */
//     if(*pa<=*pb)
//       *pc++=*pa++;
//     else
//       *pc++=*pb++;
//   }
//   while(pa<=pa_last) /* ��La�ǿ��ұ�Lb�� */
//     *pc++=*pa++; /* ����La��ʣ��Ԫ�� */
//   while(pb<=pb_last) /* ��Lb�ǿ��ұ�La�� */
//     *pc++=*pb++; /* ����Lb��ʣ��Ԫ�� */

// }
    void print(ElemType &c)
    {
        printf("%d ",c);
    }
//������Ϊ��֤����
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
    if(i==1) /* �����ձ�La�ɹ� */
        for(j=1; j<=5; j++) /* �ڱ�La�в���5��Ԫ�� */
            i=ListInsert(La,j,j);
    printf("La= "); /* �����La������ */
    ListTraverse(La,print);
    DestroyList(La);
    printf("����˳���La "); /* �����La������ */
    ListTraverse(La,print);
    InitList(La); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(La,j,a[j-1]);
    printf("�½�La= "); /* �����Lb������ */
    ListTraverse(La,print);
    ClearList(La);
    printf("���La "); /* �����La������ */
    ListTraverse(La,print);
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(La,j,a[j-1]);
    printf("�½�La= "); /* �����Lb������ */
    ListTraverse(La,print);
    printf("La����Ԫ�ظ���Ϊ %d\n",ListLength(La));
    printf("�����Ԫ��λ�� 2\n");
    GetElem(La,2,&e);
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
    ListTraverse(La,print);
    printf("ɾ��La�ڶ���Ԫ��\n");
    ListDelete(La,2,e);
    ListTraverse(La,print);
    InitList(Lb); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=11; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(Lb,j,b[j-1]);
    printf("�½�Lb= "); /* �����Lb������ */
    ListTraverse(Lb,print);
    Union(La,Lb);
    printf("new La= "); /* ����±�La������ */
    ListTraverse(La,print);
    InitList(Lc); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=7; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(Lc,j,c[j-1]);
    printf("�½�Lc= "); /* �����Lb������ */
    ListTraverse(Lc,print);
    InitList(Ld); /* Ҳ�ɲ��ж��Ƿ񴴽��ɹ� */
    for(j=1; j<=8; j++) /* �ڱ�Lb�в���5��Ԫ�� */
        i=ListInsert(Ld,j,d[j-1]);
    printf("�½�Ld= "); /* �����Lb������ */
    ListTraverse(Ld,print);
    InitList(Le);
    MergeList(Lc,Ld,Le);
    printf("�ϲ���Ϊ ");
    ListTraverse(Le,print);
}
