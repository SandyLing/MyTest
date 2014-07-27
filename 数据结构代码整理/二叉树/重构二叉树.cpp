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
char a[]={'a','b','d','c','e','f'};
char b[]={'d','b','a','e','c','f'};
int a_len=sizeof(a);
int index(char c,int start,int end)
{
	for(int i = start;i<end;i++)
	{
		if(c==b[i])
		{
			return i;
		}
	}
	return -1;
}

Status Rebuild(BiTree &T,int &i,int start,int end)
{
	if(i==a_len+1)	return 0;
    int position =index(a[i],start,end);
   // printf("%d:%d %d %d\n",i,start,end,position);
    if(position!=-1)
    {
    	if ((T =(BiTNode *)malloc(sizeof(BiTNode)))==NULL) exit(OVERFLOW);
		T->data = a[i];              // 生成根结点
  		i++;
  		Rebuild(T->lchild,i,start,position);
 		Rebuild(T->rchild,i,position,end);
    }
    else
    {
        T=NULL;
    }

    return 0;
}
Status PreOrderTraverse(BiTree T, Status(*visit)(ElemType&))
{
    //T为树根的指针,先序遍历
    if (T)
    {
        visit(T->data); // 访问结点
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
}
Status print(ElemType &c)
{
    printf("%c ",c);
}
int main(int argc, char const *argv[])
{
	BiTree t;
	int i=0;
	int start = 0;
	int end = sizeof(b);
	Rebuild(t,i,start,end);
	PreOrderTraverse(t,print);
	return 0;
}
