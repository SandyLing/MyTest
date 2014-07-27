#define   STACK_INIT_SIZE 100 //初始分配量储存空间
#define   STACKINCREMENT 10 //储存空间分配增量
//链栈的结构说明
typedef struct Snode{
	 int data;
    struct Snode *next;
}Snode,*Slink;
int push(Slink &L,int x) {
       //不含头结点链栈的PUSH操作
      P=(SLink)malloc(sizeof(Snode)); //建新的结点
      P->data=x;
      P->next=L; // 链接到原来的栈顶
      L=P; 　// 移动栈顶指针
      return 1;
} // PUSH
int pop(Slink &L,int &x) {
   //不含头结点链栈的pop操作
   if (L==NULL) return 0;
    else {
             x=L->data; // 返回栈顶元素
	         p=L;
             L=L->next; // 修改栈顶指针
             free(p); // 释放被删除的结点空间
    }
    return 1;
 }
int InitStack(Slink &S)//初始化或构造一个空栈
{
    S.base=(int*)malloc(STACK_INIT_SIZE *sizeof(int));
    if(!S.base) exit(0);//分配失败
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 2;
}
int GetTop(SqStack S,int &e)//返回栈顶元素，返回值赋值给e
{
    if(S.top == S.base) return 0;//如果栈为空，返回ERROR
    e = *(S.top-1);
    return 1;
}
int Push(SqStack &S, int e)//压栈
{
    if(S.top-S.base>=S.stacksize)//栈满，追加储存空间
    {
        S.base = (int *)realloc(S.base,
                  (S.stacksize+STACKINCREMENT)*sizeof (int));
    if (!S.base) return 0;   // 存储分配失败
    S.top =S.base+S.stacksize;          //指向新分配的内存首位
    S.stacksize += STACKINCREMENT;  // 增加存储容量
    }
    *S.top = e;
     S.top++;
    return 1;
}
int Pop(SqStack &S, int &e) {
   // 若栈不空，则删除S的栈顶元素，
     // 用e返回其值，并返回OK；
     // 否则返回ERROR
    if (S.top == S.base) return 0;
    e =*(--S.top);
    return 1;
}
