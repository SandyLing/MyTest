#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW -2
#define OK 1
#define QElemType BiTNode
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef int Status;
typedef char ElemType;
typedef struct BiTNode   // ���ṹ
{
    ElemType     data;
    struct BiTNode  *lchild, *rchild;
    // ���Һ���ָ��
} BiTNode, *BiTree;

typedef struct QNode  //���нڵ�
{
    BiTNode data;
    struct QNode *next;
} QNode,*QueuePtr;
typedef struct
{
    QueuePtr front,rear; /* ��ͷ����βָ�� */
} LinkQueue;
//���ڶ��еĺ���
Status InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q.front)
        exit(OVERFLOW);
    Q.front->next=NULL;
    return OK;
}
Status QueueEmpty(LinkQueue Q)
{
    /* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}
Status EnQueue(LinkQueue &Q,QElemType e)
{
    /* ����Ԫ��eΪQ���µĶ�βԪ�� */
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) /* �洢����ʧ�� */
        exit(OVERFLOW);
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    return OK;
}
Status DeQueue(LinkQueue &Q,QElemType &e)
{
    /* �����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
    QueuePtr p;
    if(Q.front==Q.rear)
        return ERROR;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    free(p);
    return OK;
}

Status PreOrderTraverse(BiTree T, Status(*visit)(ElemType&))
{
    //TΪ������ָ��,�������
    if (T)
    {
        visit(T->data); // ���ʽ��
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
}
Status InOrderTraverse (BiTree T, Status(*visit)(ElemType&))
{
    // ���������������TΪ������ָ��
    if (T)
    {
        InOrderTraverse(T->lchild, visit);// ����������
        visit(T->data) ;// ���ʽ��
        InOrderTraverse(T->rchild, visit);// ����������
    }
}
Status PostOrderTraverse (BiTree T, Status(*visit)(ElemType&))
{
    // ���������������TΪ������ָ��
    if (T)
    {
        PostOrderTraverse(T->lchild, visit);//����������
        PostOrderTraverse(T->rchild, visit);//����������
        visit(T->data); // ���ʽ��
    }
}
int CreateBiTree(BiTree &T)
{
//��ǰ�������������Ϣ
    char ch;
    scanf("%c",&ch);
    if (ch=='#') T = NULL;
    else
    {
        if ((T =(BiTNode *)malloc(sizeof(BiTNode)))==NULL) exit(OVERFLOW);
        T->data = ch;              // ���ɸ����
        CreateBiTree(T->lchild);   // ����������
        CreateBiTree(T->rchild);   // ����������
    }
    return OK;
} // CreateBiTree ,��ͷ���
// ������������
int BiTDepth(BiTree& T)
{
    int l,r;
    if(!T) return 0;
    else
    {
        l=BiTDepth(T->lchild)+1;
        r=BiTDepth(T->rchild)+1;
        return l>r?l:r;
    }
}
// ���������Ҷ�ӽ�����Ŀ
Status POLeafNodeNum(int& i,BiTree& T)
{
    if(T)
    {
        i++;
        POLeafNodeNum(i,T->lchild);
        POLeafNodeNum(i,T->rchild);
    }
    return OK;
}
int HierarchyBiTree(BiTree& tr, Status(*visit)(ElemType&))//����������
{
    LinkQueue Q;
    InitQueue(Q);  // ��ʼ������
    if (!tr) return 0; //��Ϊ���򷵻�
    BiTNode p;
    EnQueue(Q,*tr);
    while (!QueueEmpty(Q))  // �����в��գ���������
    {
        DeQueue(Q, p); // ������
        visit(p.data);// ���ʵ�ǰ�ڵ�
        if (p.lchild)
          EnQueue(Q, *(p.lchild)); // ���������ӣ����ӽ�����
        if (p.rchild)
          EnQueue(Q, *(p.rchild)); // �������Һ��ӣ��Һ��ӽ�����
    }
}
Status print(ElemType &c)
{
    printf("%c ",c);
}
int main()
{
    int depth,num=0;
    printf("����ABC##DE#G##F###����������\n");
    BiTree t;
    CreateBiTree(t);
    printf("������� ��");
    PreOrderTraverse(t,print);
    printf("\n");
    printf("������� ��");
    InOrderTraverse(t,print);
    printf("\n");
    printf("������� ��");
    PostOrderTraverse(t,print);
    printf("\n");
    depth=BiTDepth(t);
    printf("�����������Ϊ ��%d",depth);
    POLeafNodeNum(num,t);
    printf("\n��������Ҷ�ӽ�����ĿΪ :%d",num);
    printf("\n���������� ");
    HierarchyBiTree(t,print);

}
