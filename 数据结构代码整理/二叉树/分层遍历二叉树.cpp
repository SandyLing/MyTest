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
Status PrintNodeAtLevel (BiTree T, Status(*visit)(ElemType&),int level)
{
    // ���������������TΪ������ָ��
    if (!T||level<0) return 0;
    if(level==0)
    {
        visit(T->data) ;// ���ʽ��
        return 0;
    }
    level--;
    PrintNodeAtLevel(T->lchild, visit,level);// ����������
    PrintNodeAtLevel(T->rchild, visit,level);// ����������
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
    PrintNodeAtLevel(t,print,2);
}
