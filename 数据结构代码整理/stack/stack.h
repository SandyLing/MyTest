#define   STACK_INIT_SIZE 100 //初始分配量储存空间
#define   STACKINCREMENT 10 //储存空间分配增量
typedef struct {
 int *base;//抽象元素SElemType 栈底指针a1
 int *top;//抽象元素SElemType 栈顶指针an
 int stacksize;//当前已分配的存储空间
}SqStack;
int InitStack(SqStack &S)//初始化或构造一个空栈
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
int Push(SqStack &S,BiTree e)//压栈
{
    if(S.top-S.base>=S.stacksize)//栈满，追加储存空间
    {
        S.base = (int *)realloc(S.base,
                  (S.stacksize+STACKINCREMENT)*sizeof (int));
    if (!S.base) return 0;   // 存储分配失败
    S.top =S.base+S.stacksize;          //指向新分配的内存首位
    S.stacksize += STACKINCREMENT;  // 增加存储容量
    }
    S.top = e;
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
