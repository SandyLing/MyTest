#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LIST_INIT_SIZE 10 /* ���Ա�洢�ռ�ĳ�ʼ������ */
#define LISTINCREMENT 2 /* ���Ա�洢�ռ�ķ������� */
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;
Status InitList(SqList &L)
{
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW);
    L.length=0; /* �ձ���Ϊ0 */
    L.listsize=LIST_INIT_SIZE; /* ��ʼ�洢���� */
    return OK;
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
int compare(ElemType c1,ElemType c2)//�Ƚ����ߵĴ�С
{
    int i;
    if(c1<c2)
        i=1;
    else
        i=0;
    return i;
}
Status ListInsert(SqList &L,ElemType e,int(*vf)(ElemType,ElemType))
{
    ElemType *newbase,*p;
    if(L.length>=L.listsize) /* ��ǰ�洢�ռ�����,���ӷ��� */
    {
        newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW);
        L.elem=newbase;
        L.listsize+=LISTINCREMENT;
    }
    int i=1;
    ElemType *q1;
    for(q1=L.elem;i<=L.length+1&&vf(*q1,e);q1++)
     i++;
    ElemType *q = &(L.elem[i-1]);   // qΪ����λ��
    for(p=L.elem+L.length-1; p>=q; --p) /* ����λ�ü�֮���Ԫ������ */
        *(p+1)=*p;
    *q=e;
    ++L.length;
    return OK;
}
Status ListDelete(SqList &L,int i,ElemType &e)
{
    ElemType *p,*q;
    if(i<1||i>L.length)
        return ERROR;
    p=L.elem+i-1; /* pΪ��ɾ��Ԫ�ص�λ�� */
    e=*p; /* ��ɾ��Ԫ�ص�ֵ����e */
    q=L.elem+L.length-1; /* ��βԪ�ص�λ�� */
    for(++p; p<=q; ++p) /* ��ɾ��Ԫ��֮���Ԫ������ */
        *(p-1)=*p;
    L.length--;
    return OK;
}
void MergeList(SqList La,SqList Lb,SqList &Lc)
{
    ElemType  *pa,*pa_last,*pb,*pb_last,*pc;
    pa=La.elem;
    pb=Lb.elem;
    Lc.listsize=La.length+Lb.length;
    pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
    if(!Lc.elem)
        exit(OVERFLOW);
    pa_last=La.elem+La.length-1;
    pb_last=Lb.elem+Lb.length-1;
    while(pa<=pa_last&&pb<=pb_last)
        switch(comp(*pa,*pb))
        {
        case  0:
            pb++;
        case  1:
            *pc++=*pa++;
            break;
        case -1:
            *pc++=*pb++;
        }
    while(pa<=pa_last)
        *pc++=*pa++;
    while(pb<=pb_last)
        *pc++=*pb++;
    Lc.length=pc-Lc.elem;
}
Status ListTraverse(const SqList &L,void(*vi)(ElemType&))
{
    ElemType *p;
    int i;
    p=L.elem;
    for(i=1; i<=L.length; i++)
        vi(*p++);
    printf("\n");
    return OK;
}
void print(ElemType &c)
    {
        printf("%d ",c);
    }
int main()
{
    SqList La,Lb,Lc;
    int a[]= {9,7,6,4,3,5,1};
    int b[]= {2,3,6,5,87,4,9,55,32};
    ElemType e;
    InitList(La);
    int j;
    for(j=1; j<=7; j++)
        ListInsert(La,a[j-1],compare);
    printf("�½�La= ");
    ListTraverse(La,print);
    printf("ɾ��La�ڶ���Ԫ��\n");
    ListDelete(La,2,e);
    printf("ɾ����Ԫ��Ϊ%d\nɾ�����˳���Ϊ��\n",e);
    ListTraverse(La,print);
    InitList(Lb);
    for(j=1; j<=9; j++)
         ListInsert(Lb,b[j-1],compare);
    printf("�½�Lb= ");
    ListTraverse(Lb,print);
    printf("�ϲ��� Lc= ");
    MergeList(La,Lb,Lc);
    ListTraverse(Lc,print);
}
