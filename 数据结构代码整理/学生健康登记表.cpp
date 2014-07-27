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
#define NAMELEN 8 /* 姓名最大长度 */
#define CLASSLEN 4 /* 班级名最大长度 */
typedef struct stud/* 记录的结构 */
 {
   char name[NAMELEN+1];
   long num;
   char sex;
   int age;
   char Class[CLASSLEN+1];
   int health;
 }ElemType;
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
struct LNode
{
    ElemType data;
    struct LNode *next;
};
typedef struct LNode *LinkList; /* 另一种定义LinkList的方法 */
Status InitList(LinkList &L)
{
    /* 操作结果：构造一个空的线性表L */
    L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
    if(!L) /* 存储分配失败 */
        exit(OVERFLOW);
    L->next=NULL; /* 指针域为空 */
    return OK;
}
Status DestroyList(LinkList &L)
{
    /* 初始条件：线性表L已存在。操作结果：销毁线性表L */
    LinkList q;
    while(L)
    {
        q=L->next;
        free(L);
        L=q;
    }
    return OK;
}
Status ClearList(LinkList &L) /* 不改变L */
{
    /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
    LinkList p,q;
    p=L->next; /* p指向第一个结点 */
    while(p) /* 没到表尾 */
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL; /* 头结点指针域为空 */
    return OK;
}
Status ListEmpty(LinkList &L)
{
    /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
    if(L->next) /* 非空 */
        return FALSE;
    else
        return TRUE;
}
int ListLength(LinkList L)
{
    /* 初始条件：线性表L已存在。操作结果：返回L中数据元素个数 */
    int i=0;
    LinkList p=L->next; /* p指向第一个结点 */
    while(p) /* 没到表尾 */
    {
        i++;
        p=p->next;
    }
    return i;
}
Status GetElem(LinkList L,int i,ElemType &e) /* 算法2.8 */
{
    /* L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
    int j=1; /* j为计数器 */
    LinkList p=L->next; /* p指向第一个结点 */
    while(p&&j<i) /* 顺指针向后查找,直到p指向第i个元素或p为空 */
    {
        p=p->next;
        j++;
    }
    if(!p||j>i) /* 第i个元素不存在 */
        return ERROR;
    e=p->data; /* 取第i个元素 */
    return OK;
}
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    /* 初始条件: 线性表L已存在,compare()是数据元素判定函数(满足为1,否则为0) */
    /* 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序。 */
    /*           若这样的数据元素不存在,则返回值为0 */
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(compare(p->data,e)) /* 找到这样的数据元素 */
            return i;
        p=p->next;
    }
    return 0;
}
Status ListInsert(LinkList L,int i,ElemType e) /* 算法2.9。不改变L */
{
    /* 在带头结点的单链线性表L中第i个位置之前插入元素e */
    int j=0;
    LinkList p=L,s;
    while(p&&j<i-1) /* 寻找第i-1个结点 */
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1) /* i小于1或者大于表长 */
        return ERROR;
    s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
    s->data=e; /* 插入L中 */
    s->next=p->next;
    p->next=s;
    return OK;
}
Status ListDelete(LinkList L,int i,ElemType &e) /* 算法2.10。不改变L */
{
    /* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
    int j=0;
    LinkList p=L,q;
    while(p->next&&j<i-1) /* 寻找第i个结点,并令p指向其前趋 */
    {
        p=p->next;
        j++;
    }
    if(!p->next||j>i-1) /* 删除位置不合理 */
        return ERROR;
    q=p->next; /* 删除并释放结点 */
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}
Status ListTraverse(LinkList L,void(*vi)(ElemType))
/* vi的形参类型为ElemType，与bo2-1.c中相应函数的形参类型ElemType&不同 */
{
    /* 初始条件：线性表L已存在 */
    /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
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
void CreateList(LinkList &L,int n) /* 算法2.11 */
{
    /* 逆位序(插在表头)输入n个元素的值，建立带表头结构的单链线性表L */
    int i;
    LinkList p;
    L=(LinkList)malloc(sizeof(struct LNode));
    L->next=NULL; /* 先建立一个带头结点的单链表 */
    printf("请输入%d个数据\n",n);
    for(i=n; i>0; --i)
    {
        p=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
        scanf("%d",&p->data); /* 输入元素值 */
        p->next=L->next; /* 插入到表头 */
        L->next=p;
    }
}
void CreateList2(LinkList &L,int n)
{
    /* 正位序(插在表尾)输入n个元素的值，建立带表头结构的单链线性表 */
    int i;
    LinkList p,q;
    L=(LinkList)malloc(sizeof(struct LNode)); /* 生成头结点 */
    L->next=NULL;
    q=L;
    printf("请输入%d个数据\n",n);
    for(i=1; i<=n; i++)
    {
        p=(LinkList)malloc(sizeof(struct LNode));
        scanf("%d",&p->data);
        q->next=p;
        q=q->next;
    }
    p->next=NULL;
}
void visit(ElemType c) /* ListTraverse()调用的函数(类型要一致) */
{
    printf("%d ",c);
}
char sta[3][9]={"健康  ","一般  ","神经衰弱"}; /* 健康状况(3类) */
 FILE *fp;

 Status InitList(LinkList *L) /* 拷自bo2-2.c */
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=NULL; /* 指针域为空 */
   return OK;
 }
 void InsertAscend(LinkList L,ElemType e) /* 此函数是由bo2-9.c中的同名函数改写 */
 { /* 按学号非降序插入 */
   LinkList q=L,p=L->next;
   while(p&&e.num>p->data.num)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }
 void Print(struct stud e)
 { /* 显示记录e的内容 */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" 男");
   else
     printf(" 女");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

 void ReadIn(struct stud *e)
 { /* 由键盘输入结点信息 */
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   scanf("%s",e->name);
   printf("请输入学号: ");
   scanf("%ld",&e->num);
   printf("请输入性别(m:男 f:女): ");
   scanf("%*c%c",&e->sex);
   printf("请输入年龄: ");
   scanf("%d",&e->age);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   scanf("%s",e->Class);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   scanf("%d",&e->health);
 }
 void WriteToFile(struct stud e)
 { /* 将结点信息写入fp指定的文件 */
   fwrite(&e,sizeof(struct stud),1,fp);
 }

 Status ReadFromFile(struct stud *e)
 { /* 由fp指定的文件读取结点信息到e */
   int i;
   i=fread(e,sizeof(struct stud),1,fp);
   if(i==1) /* 读取文件成功 */
     return OK;
   else
     return ERROR;
 }
 Status FindFromNum(LinkList L,long num,LinkList *p,LinkList *q)
 { /* 查找表中学号为num的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&(*q)->data.num>num) /* 因为是按学号非降序排列 */
       break;
     if(*q&&(*q)->data.num==num) /* 找到该学号 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }
 Status FindFromName(LinkList L,char name[],LinkList *p,LinkList *q)
 { /* 查找表中姓名为name的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&!strcmp((*q)->data.name,name)) /* 找到该姓名 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }
 Status DeleteElemNum(LinkList L,long num)
 { /* 删除表中学号为num的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromNum(L,num,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }
 Status DeleteElemName(LinkList L,char name[])
 { /* 删除表中姓名为name的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromName(L,name,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }
 void Modify(ElemType *e)
 { /* 修改结点内容 */
   char s[80];
   Print(*e); /* 显示原内容 */
   printf("请输入待修改项的内容，不修改的项按回车键保持原值:\n");
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e->name,s);
   printf("请输入学号: ");
   gets(s);
   if(strlen(s))
     e->num=atol(s);
   printf("请输入性别(m:男 f:女): ");
   gets(s);
   if(strlen(s))
     e->sex=s[0];
   printf("请输入年龄: ");
   gets(s);
   if(strlen(s))
     e->age=atoi(s);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e->Class,s);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e->health=atoi(s); /* 修改完毕 */
 }
 #define N 4 /* student记录的个数 */
 int main()
 {
   struct stud student[N]={{"王小林",790631,'m',18,"计91",0},
                           {"陈红",790632,'f',20,"计91",1},
                           {"刘建平",790633,'m',21,"计91",0},
                           {"张立立",790634,'m',17,"计91",2}}; /* 表的初始记录 */
   int i,j,flag=1;
   long num;
   char filename[13],name[NAMELEN+1];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* 初始化链表 */
   while(flag)
   {
     printf("1:将结构体数组student中的记录按学号非降序插入链表\n");
     printf("2:将文件中的记录按学号非降序插入链表\n");
     printf("3:键盘输入新记录，并将其按学号非降序插入链表\n");
     printf("4:删除链表中第一个有给定学号的记录\n");
     printf("5:删除链表中第一个有给定姓名的记录\n");
     printf("6:修改链表中第一个有给定学号的记录\n");
     printf("7:修改链表中第一个有给定姓名的记录\n");
     printf("8:查找链表中第一个有给定学号的记录\n");
     printf("9:查找链表中第一个有给定姓名的记录\n");
     printf("10:显示所有记录 11:将链表中的所有记录存入文件 12:结束\n");
     printf("请选择操作命令: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
                 InsertAscend(T,student[j]);
               break;
       case 2: printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("打开文件失败!\n");
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
       case 4: printf("请输入待删除记录的学号: ");
               scanf("%ld",&num);
               if(!DeleteElemNum(T,num))
                 printf("没有学号为%ld的记录\n",num);
               break;
       case 5: printf("请输入待删除记录的姓名: ");
               scanf("%s",name);
               if(!DeleteElemName(T,name))
                 printf("没有姓名为%s的记录\n",name);
               break;
       case 6: printf("请输入待修改记录的学号: ");
               scanf("%ld%*c",&num); /* %*c吃掉回车符 */
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
               {
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 7: printf("请输入待修改记录的姓名: ");
               scanf("%s%*c",name); /* %*c吃掉回车符 */
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               {
                 num=q->data.num; /* 学号存入num */
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 8: printf("请输入待查找记录的学号: ");
               scanf("%ld",&num);
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
                 Print(q->data);
               break;
       case 9: printf("请输入待查找记录的姓名: ");
               scanf("%s",name);
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               Print(q->data);
               break;
       case 10:printf("  姓名    学号 性别 年龄 班级 健康状况\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("打开文件失败!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
 }


