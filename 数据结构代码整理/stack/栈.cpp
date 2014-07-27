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
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int ElemType;
typedef int SElemType; /* 定义栈元素类型 */
 #define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
 #define STACKINCREMENT 2 /* 存储空间分配增量 */
 typedef struct SqStack
 {
   SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
   SElemType *top; /* 栈顶指针 */
   int stacksize; /* 当前已分配的存储空间，以元素为单位 */
 }SqStack; /* 顺序栈 */

 Status InitStack(SqStack *S)
 { /* 构造一个空栈S */
   (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   if(!(*S).base)
     exit(OVERFLOW); /* 存储分配失败 */
   (*S).top=(*S).base;
   (*S).stacksize=STACK_INIT_SIZE;
   return OK;
 }

 Status DestroyStack(SqStack *S)
 { /* 销毁栈S，S不再存在 */
   free((*S).base);
   (*S).base=NULL;
   (*S).top=NULL;
   (*S).stacksize=0;
   return OK;
 }

 Status ClearStack(SqStack *S)
 { /* 把S置为空栈 */
   (*S).top=(*S).base;
   return OK;
 }

 Status StackEmpty(SqStack S)
 { /* 若栈S为空栈，则返回TRUE，否则返回FALSE */
   if(S.top==S.base)
     return TRUE;
   else
     return FALSE;
 }

 int StackLength(SqStack S)
 { /* 返回S的元素个数，即栈的长度 */
   return S.top-S.base;
 }

 Status GetTop(SqStack S,SElemType *e)
 { /* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
   if(S.top>S.base)
   {
     *e=*(S.top-1);
     return OK;
   }
   else
     return ERROR;
 }

 Status Push(SqStack *S,SElemType e)
 { /* 插入元素e为新的栈顶元素 */
   if((*S).top-(*S).base>=(*S).stacksize) /* 栈满，追加存储空间 */
   {
     (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
     if(!(*S).base)
       exit(OVERFLOW); /* 存储分配失败 */
     (*S).top=(*S).base+(*S).stacksize;
     (*S).stacksize+=STACKINCREMENT;
   }
   *((*S).top)++=e;
   return OK;
 }

 Status Pop(SqStack *S,SElemType *e)
 { /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
   if((*S).top==(*S).base)
     return ERROR;
   *e=*--(*S).top;
   return OK;
 }

 Status StackTraverse(SqStack S,Status(*visit)(SElemType))
 { /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
   /* 一旦visit()失败，则操作失败 */
   while(S.top>S.base)
     visit(*S.base++);
   printf("\n");
   return OK;
 }

 Status visit(SElemType c)
 {
   printf("%d ",c);
   return OK;
 }
int main()
 {
   int j;
   SqStack s;
   SElemType e;
   if(InitStack(&s)==OK)
     for(j=1;j<=12;j++)
       Push(&s,j);
   printf("The ElemType in this status are:");
   StackTraverse(s,visit);
   Pop(&s,&e);
   printf("the pop ElemType is e=%d\n",e);
   printf("empty or not:%d(1:empty 0:not empty)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("The top ElemType is e=%d  The length of status is %d\n",e,StackLength(s));
   ClearStack(&s);
   printf("After clear the status,empty or not:%d(1:empty 0:not empty)\n",StackEmpty(s));
   DestroyStack(&s);
   printf("After destory the status,s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
 }

