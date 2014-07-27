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
typedef struct BiTNode   // 结点结构
{
    ElemType     data;
    struct BiTNode  *lchild, *rchild;
    // 左右孩子指针
} BiTNode, *BiTree;
int CreateBiTree(BiTree &T)
{
//按前序次序输入结点信息
    char ch;
    scanf("%c",&ch);
    if (ch=='#') T = NULL;
    else
    {
        if ((T =(BiTNode *)malloc(sizeof(BiTNode)))==NULL) exit(OVERFLOW);
        T->data = ch;              // 生成根结点
        CreateBiTree(T->lchild);   // 构造左子树
        CreateBiTree(T->rchild);   // 构造右子树
    }
    return OK;
} // CreateBiTree ,无头结点
Status PrintNodeAtLevel (BiTree T, Status(*visit)(ElemType&),int level)
{
    // 中序遍历二叉树，T为树根的指针
    if (!T||level<0) return 0;
    if(level==0)
    {
        visit(T->data) ;// 访问结点
        return 0;
    }
    level--;
    PrintNodeAtLevel(T->lchild, visit,level);// 遍历左子树
    PrintNodeAtLevel(T->rchild, visit,level);// 遍历右子树
}
Status print(ElemType &c)
{
    printf("%c ",c);
}
int main()
{
	int depth,num=0;
    printf("输入ABC##DE#G##F###建立二叉树\n");
    BiTree t;
    CreateBiTree(t);
    PrintNodeAtLevel(t,print,2);
}
