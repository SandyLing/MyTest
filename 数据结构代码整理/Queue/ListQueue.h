typedef struct QNode  //�������
{
    int      data;
    struct QNode  *next;
} QNode,*QueuePtr;
typedef struct   // ����������
{
    QueuePtr  front;  // ��ͷָ��
    QueuePtr  rear;   // ��βָ��
} LinkQueue;
int  InitQueue (LinkQueue &Q)
{
    // ����һ���ն���Q
    Q.front = Q.rear =(QueuePtr)malloc(sizeof(QNode));
    if (Q.front==NULL) exit (0);            //�洢����ʧ��
    Q.front->next = NULL;
    return 1;
}
int EnQueue(LinkQueue &Q,int e)
{
    // ����Ԫ��eΪQ���µĶ�βԪ��
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if (p==NULL) exit(0);//�洢����ʧ��
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return 1;
}
int DeQueue (LinkQueue &Q,int &e)
{
    // ɾ��Q�Ķ�ͷԪ�أ��� e ������ֵ��
    if (Q.front ==Q.rear) return 0;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free (p);
    return 1;
}

