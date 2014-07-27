typedef struct QNode  //结点类型
{
    int      data;
    struct QNode  *next;
} QNode,*QueuePtr;
typedef struct   // 链队列类型
{
    QueuePtr  front;  // 队头指针
    QueuePtr  rear;   // 队尾指针
} LinkQueue;
int  InitQueue (LinkQueue &Q)
{
    // 构造一个空队列Q
    Q.front = Q.rear =(QueuePtr)malloc(sizeof(QNode));
    if (Q.front==NULL) exit (0);            //存储分配失败
    Q.front->next = NULL;
    return 1;
}
int EnQueue(LinkQueue &Q,int e)
{
    // 插入元素e为Q的新的队尾元素
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if (p==NULL) exit(0);//存储分配失败
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return 1;
}
int DeQueue (LinkQueue &Q,int &e)
{
    // 删除Q的队头元素，用 e 返回其值。
    if (Q.front ==Q.rear) return 0;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free (p);
    return 1;
}

