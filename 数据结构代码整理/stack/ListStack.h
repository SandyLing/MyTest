#define   STACK_INIT_SIZE 100 //��ʼ����������ռ�
#define   STACKINCREMENT 10 //����ռ��������
//��ջ�Ľṹ˵��
typedef struct Snode{
	 int data;
    struct Snode *next;
}Snode,*Slink;
int push(Slink &L,int x) {
       //����ͷ�����ջ��PUSH����
      P=(SLink)malloc(sizeof(Snode)); //���µĽ��
      P->data=x;
      P->next=L; // ���ӵ�ԭ����ջ��
      L=P; ��// �ƶ�ջ��ָ��
      return 1;
} // PUSH
int pop(Slink &L,int &x) {
   //����ͷ�����ջ��pop����
   if (L==NULL) return 0;
    else {
             x=L->data; // ����ջ��Ԫ��
	         p=L;
             L=L->next; // �޸�ջ��ָ��
             free(p); // �ͷű�ɾ���Ľ��ռ�
    }
    return 1;
 }
int InitStack(Slink &S)//��ʼ������һ����ջ
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
int Push(SqStack &S, int e)//ѹջ
{
    if(S.top-S.base>=S.stacksize)//ջ����׷�Ӵ���ռ�
    {
        S.base = (int *)realloc(S.base,
                  (S.stacksize+STACKINCREMENT)*sizeof (int));
    if (!S.base) return 0;   // �洢����ʧ��
    S.top =S.base+S.stacksize;          //ָ���·�����ڴ���λ
    S.stacksize += STACKINCREMENT;  // ���Ӵ洢����
    }
    *S.top = e;
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
