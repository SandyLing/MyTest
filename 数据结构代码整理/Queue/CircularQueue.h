#define MAXQSIZE  100  //最大队列长度
typedef struct
{
    int  *base;// 动态分配存储空间
    int  front;  // 头指针，若队列不空，指向队列头元素
    int  rear;  // 尾指针，若队列不空，指向队列尾元素 的下一个位置
} SqQueue;
int InitQueue (SqQueue &Q)
{
    // 构造一个空队列Q
    Q.base = (int *) malloc(MAXQSIZE *sizeof (int));
    if (Q.base==NULL) exit (0);// 存储分配失败
    Q.front = Q.rear = 0;
    return 1;
}
int QueueLength(SqQueue Q){
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}
int EnQueue(SqQueue &Q, int e) {
 // 插入元素e为Q的新的队尾元素
      if((Q.rear+1)%MAXQSIZE==Q.front)
           return 0;
      Q.base[Q.rear] = e;
      Q.rear = (Q.rear+1) % MAXQSIZE;
      return 1;
}
int DeQueue (SqQueue &Q, int &e){
    // 若队列不空，则删除Q的队头元素，
    // 用e返回其值
       if (Q.front==Q.rear) return 0;
         e = Q.base[Q.front];
         Q.front = (Q.front+1) % MAXQSIZE;
         return 1;
}
