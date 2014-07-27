#define   STACK_INIT_SIZE 100 //��ʼ����������ռ�
#define   STACKINCREMENT 10 //����ռ��������
typedef struct {
 int *base;//����Ԫ��SElemType ջ��ָ��a1
 int *top;//����Ԫ��SElemType ջ��ָ��an
 int stacksize;//��ǰ�ѷ���Ĵ洢�ռ�
}SqStack;
int InitStack(SqStack &S)//��ʼ������һ����ջ
{
    S.base=(int*)malloc(STACK_INIT_SIZE *sizeof(int));
    if(!S.base) exit(0);//����ʧ��
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 2;
}
int GetTop(SqStack S,int &e)//����ջ��Ԫ�أ�����ֵ��ֵ��e
{
    if(S.top == S.base) return 0;//���ջΪ�գ�����ERROR
    e = *(S.top-1);
    return 1;
}
int Push(SqStack &S,BiTree e)//ѹջ
{
    if(S.top-S.base>=S.stacksize)//ջ����׷�Ӵ���ռ�
    {
        S.base = (int *)realloc(S.base,
                  (S.stacksize+STACKINCREMENT)*sizeof (int));
    if (!S.base) return 0;   // �洢����ʧ��
    S.top =S.base+S.stacksize;          //ָ���·�����ڴ���λ
    S.stacksize += STACKINCREMENT;  // ���Ӵ洢����
    }
    S.top = e;
     S.top++;
    return 1;
}
int Pop(SqStack &S, int &e) {
   // ��ջ���գ���ɾ��S��ջ��Ԫ�أ�
     // ��e������ֵ��������OK��
     // ���򷵻�ERROR
    if (S.top == S.base) return 0;
    e =*(--S.top);
    return 1;
}
