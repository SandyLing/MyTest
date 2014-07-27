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
typedef int SElemType; /* ����ջԪ������ */
 #define STACK_INIT_SIZE 10 /* �洢�ռ��ʼ������ */
 #define STACKINCREMENT 2 /* �洢�ռ�������� */
 typedef struct SqStack
 {
   SElemType *base; /* ��ջ����֮ǰ������֮��base��ֵΪNULL */
   SElemType *top; /* ջ��ָ�� */
   int stacksize; /* ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ */
 }SqStack; /* ˳��ջ */

 Status InitStack(SqStack *S)
 { /* ����һ����ջS */
   (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   if(!(*S).base)
     exit(OVERFLOW); /* �洢����ʧ�� */
   (*S).top=(*S).base;
   (*S).stacksize=STACK_INIT_SIZE;
   return OK;
 }

 Status DestroyStack(SqStack *S)
 { /* ����ջS��S���ٴ��� */
   free((*S).base);
   (*S).base=NULL;
   (*S).top=NULL;
   (*S).stacksize=0;
   return OK;
 }

 Status ClearStack(SqStack *S)
 { /* ��S��Ϊ��ջ */
   (*S).top=(*S).base;
   return OK;
 }

 Status StackEmpty(SqStack S)
 { /* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
   if(S.top==S.base)
     return TRUE;
   else
     return FALSE;
 }

 int StackLength(SqStack S)
 { /* ����S��Ԫ�ظ�������ջ�ĳ��� */
   return S.top-S.base;
 }

 Status GetTop(SqStack S,SElemType *e)
 { /* ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR */
   if(S.top>S.base)
   {
     *e=*(S.top-1);
     return OK;
   }
   else
     return ERROR;
 }

 Status Push(SqStack *S,SElemType e)
 { /* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
   if((*S).top-(*S).base>=(*S).stacksize) /* ջ����׷�Ӵ洢�ռ� */
   {
     (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
     if(!(*S).base)
       exit(OVERFLOW); /* �洢����ʧ�� */
     (*S).top=(*S).base+(*S).stacksize;
     (*S).stacksize+=STACKINCREMENT;
   }
   *((*S).top)++=e;
   return OK;
 }

 Status Pop(SqStack *S,SElemType *e)
 { /* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
   if((*S).top==(*S).base)
     return ERROR;
   *e=*--(*S).top;
   return OK;
 }

 Status StackTraverse(SqStack S,Status(*visit)(SElemType))
 { /* ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()�� */
   /* һ��visit()ʧ�ܣ������ʧ�� */
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

