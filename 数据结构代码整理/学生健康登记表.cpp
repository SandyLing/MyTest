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
#define NAMELEN 8 /* ������󳤶� */
#define CLASSLEN 4 /* �༶����󳤶� */
typedef struct stud/* ��¼�Ľṹ */
 {
   char name[NAMELEN+1];
   long num;
   char sex;
   int age;
   char Class[CLASSLEN+1];
   int health;
 }ElemType;
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
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
void visit(ElemType c) /* ListTraverse()���õĺ���(����Ҫһ��) */
{
    printf("%d ",c);
}
char sta[3][9]={"����  ","һ��  ","��˥��"}; /* ����״��(3��) */
 FILE *fp;

 Status InitList(LinkList *L) /* ����bo2-2.c */
 { /* �������������һ���յ����Ա�L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ���,��ʹLָ���ͷ��� */
   if(!*L) /* �洢����ʧ�� */
     exit(OVERFLOW);
   (*L)->next=NULL; /* ָ����Ϊ�� */
   return OK;
 }
 void InsertAscend(LinkList L,ElemType e) /* �˺�������bo2-9.c�е�ͬ��������д */
 { /* ��ѧ�ŷǽ������ */
   LinkList q=L,p=L->next;
   while(p&&e.num>p->data.num)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* ����q�� */
   q->next->data=e;
   q->next->next=p;
 }
 void Print(struct stud e)
 { /* ��ʾ��¼e������ */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" ��");
   else
     printf(" Ů");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

 void ReadIn(struct stud *e)
 { /* �ɼ�����������Ϣ */
   printf("����������(<=%d���ַ�): ",NAMELEN);
   scanf("%s",e->name);
   printf("������ѧ��: ");
   scanf("%ld",&e->num);
   printf("�������Ա�(m:�� f:Ů): ");
   scanf("%*c%c",&e->sex);
   printf("����������: ");
   scanf("%d",&e->age);
   printf("������༶(<=%d���ַ�): ",CLASSLEN);
   scanf("%s",e->Class);
   printf("�����뽡��״��(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   scanf("%d",&e->health);
 }
 void WriteToFile(struct stud e)
 { /* �������Ϣд��fpָ�����ļ� */
   fwrite(&e,sizeof(struct stud),1,fp);
 }

 Status ReadFromFile(struct stud *e)
 { /* ��fpָ�����ļ���ȡ�����Ϣ��e */
   int i;
   i=fread(e,sizeof(struct stud),1,fp);
   if(i==1) /* ��ȡ�ļ��ɹ� */
     return OK;
   else
     return ERROR;
 }
 Status FindFromNum(LinkList L,long num,LinkList *p,LinkList *q)
 { /* ���ұ���ѧ��Ϊnum�Ľ��,���ҵ�,qָ��˽��,pָ��q��ǰ��, */
   /* ������TRUE;���޴�Ԫ��,�򷵻�FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&(*q)->data.num>num) /* ��Ϊ�ǰ�ѧ�ŷǽ������� */
       break;
     if(*q&&(*q)->data.num==num) /* �ҵ���ѧ�� */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }
 Status FindFromName(LinkList L,char name[],LinkList *p,LinkList *q)
 { /* ���ұ�������Ϊname�Ľ��,���ҵ�,qָ��˽��,pָ��q��ǰ��, */
   /* ������TRUE;���޴�Ԫ��,�򷵻�FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&!strcmp((*q)->data.name,name)) /* �ҵ������� */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }
 Status DeleteElemNum(LinkList L,long num)
 { /* ɾ������ѧ��Ϊnum��Ԫ�أ�������TRUE�����޴�Ԫ�أ��򷵻�FALSE */
   LinkList p,q;
   if(FindFromNum(L,num,&p,&q)) /* �ҵ��˽��,��qָ����,pָ����ǰ�� */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }
 Status DeleteElemName(LinkList L,char name[])
 { /* ɾ����������Ϊname��Ԫ�أ�������TRUE�����޴�Ԫ�أ��򷵻�FALSE */
   LinkList p,q;
   if(FindFromName(L,name,&p,&q)) /* �ҵ��˽��,��qָ����,pָ����ǰ�� */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }
 void Modify(ElemType *e)
 { /* �޸Ľ������ */
   char s[80];
   Print(*e); /* ��ʾԭ���� */
   printf("��������޸�������ݣ����޸ĵ���س�������ԭֵ:\n");
   printf("����������(<=%d���ַ�): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e->name,s);
   printf("������ѧ��: ");
   gets(s);
   if(strlen(s))
     e->num=atol(s);
   printf("�������Ա�(m:�� f:Ů): ");
   gets(s);
   if(strlen(s))
     e->sex=s[0];
   printf("����������: ");
   gets(s);
   if(strlen(s))
     e->age=atoi(s);
   printf("������༶(<=%d���ַ�): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e->Class,s);
   printf("�����뽡��״��(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e->health=atoi(s); /* �޸���� */
 }
 #define N 4 /* student��¼�ĸ��� */
 int main()
 {
   struct stud student[N]={{"��С��",790631,'m',18,"��91",0},
                           {"�º�",790632,'f',20,"��91",1},
                           {"����ƽ",790633,'m',21,"��91",0},
                           {"������",790634,'m',17,"��91",2}}; /* ��ĳ�ʼ��¼ */
   int i,j,flag=1;
   long num;
   char filename[13],name[NAMELEN+1];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* ��ʼ������ */
   while(flag)
   {
     printf("1:���ṹ������student�еļ�¼��ѧ�ŷǽ����������\n");
     printf("2:���ļ��еļ�¼��ѧ�ŷǽ����������\n");
     printf("3:���������¼�¼�������䰴ѧ�ŷǽ����������\n");
     printf("4:ɾ�������е�һ���и���ѧ�ŵļ�¼\n");
     printf("5:ɾ�������е�һ���и��������ļ�¼\n");
     printf("6:�޸������е�һ���и���ѧ�ŵļ�¼\n");
     printf("7:�޸������е�һ���и��������ļ�¼\n");
     printf("8:���������е�һ���и���ѧ�ŵļ�¼\n");
     printf("9:���������е�һ���и��������ļ�¼\n");
     printf("10:��ʾ���м�¼ 11:�������е����м�¼�����ļ� 12:����\n");
     printf("��ѡ���������: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
                 InsertAscend(T,student[j]);
               break;
       case 2: printf("�������ļ���: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("���ļ�ʧ��!\n");
               else
               {
                 while(ReadFromFile(&e))
                   InsertAscend(T,e);
                 fclose(fp);
               }
               break;
       case 3: ReadIn(&e);
               InsertAscend(T,e);
               break;
       case 4: printf("�������ɾ����¼��ѧ��: ");
               scanf("%ld",&num);
               if(!DeleteElemNum(T,num))
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
               break;
       case 5: printf("�������ɾ����¼������: ");
               scanf("%s",name);
               if(!DeleteElemName(T,name))
                 printf("û������Ϊ%s�ļ�¼\n",name);
               break;
       case 6: printf("��������޸ļ�¼��ѧ��: ");
               scanf("%ld%*c",&num); /* %*c�Ե��س��� */
               if(!FindFromNum(T,num,&p,&q))
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
               else
               {
                 Modify(&q->data);
                 if(q->data.num!=num) /* ѧ�ű��޸� */
                 {
                   p->next=q->next; /* ��q��ָ�Ľ���L��ɾ�� */
                   InsertAscend(T,q->data); /* ��Ԫ�ز���L */
                   free(q); /* ɾ��q */
                 }
               }
               break;
       case 7: printf("��������޸ļ�¼������: ");
               scanf("%s%*c",name); /* %*c�Ե��س��� */
               if(!FindFromName(T,name,&p,&q))
                 printf("û������Ϊ%s�ļ�¼\n",name);
               else
               {
                 num=q->data.num; /* ѧ�Ŵ���num */
                 Modify(&q->data);
                 if(q->data.num!=num) /* ѧ�ű��޸� */
                 {
                   p->next=q->next; /* ��q��ָ�Ľ���L��ɾ�� */
                   InsertAscend(T,q->data); /* ��Ԫ�ز���L */
                   free(q); /* ɾ��q */
                 }
               }
               break;
       case 8: printf("����������Ҽ�¼��ѧ��: ");
               scanf("%ld",&num);
               if(!FindFromNum(T,num,&p,&q))
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
               else
                 Print(q->data);
               break;
       case 9: printf("����������Ҽ�¼������: ");
               scanf("%s",name);
               if(!FindFromName(T,name,&p,&q))
                 printf("û������Ϊ%s�ļ�¼\n",name);
               else
               Print(q->data);
               break;
       case 10:printf("  ����    ѧ�� �Ա� ���� �༶ ����״��\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("�������ļ���: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("���ļ�ʧ��!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
 }


