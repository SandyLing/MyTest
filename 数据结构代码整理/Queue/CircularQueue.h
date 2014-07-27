#define MAXQSIZE  100  //�����г���
typedef struct
{
    int  *base;// ��̬����洢�ռ�
    int  front;  // ͷָ�룬�����в��գ�ָ�����ͷԪ��
    int  rear;  // βָ�룬�����в��գ�ָ�����βԪ�� ����һ��λ��
} SqQueue;
int InitQueue (SqQueue &Q)
{
    // ����һ���ն���Q
    Q.base = (int *) malloc(MAXQSIZE *sizeof (int));
    if (Q.base==NULL) exit (0);// �洢����ʧ��
    Q.front = Q.rear = 0;
    return 1;
}
int QueueLength(SqQueue Q){
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}
int EnQueue(SqQueue &Q, int e) {
 // ����Ԫ��eΪQ���µĶ�βԪ��
      if((Q.rear+1)%MAXQSIZE==Q.front)
           return 0;
      Q.base[Q.rear] = e;
      Q.rear = (Q.rear+1) % MAXQSIZE;
      return 1;
}
int DeQueue (SqQueue &Q, int &e){
    // �����в��գ���ɾ��Q�Ķ�ͷԪ�أ�
    // ��e������ֵ
       if (Q.front==Q.rear) return 0;
         e = Q.base[Q.front];
         Q.front = (Q.front+1) % MAXQSIZE;
         return 1;
}
