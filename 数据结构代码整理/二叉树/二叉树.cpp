#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
typedef struct BiTNode { // 结点结构
    int     data;
    struct BiTNode  *lchild, *rchild;
                                 // 左右孩子指针
} BiTNode, *BiTree;
void PreOrderTraverse (BiTree T){
  //T为树根的指针
   if (T!=NULL) {
     printf("%c",T->data); // 访问结点
     PreOrderTraverse(T->lchild);
     PreOrderTraverse(T->rchild);
    }
}
//int CreateBiTree(BiTree &T) {
////按前序次序输入结点信息
//    char ch;
//    scanf("%c",&ch);
//    if (ch==' ') T = NULL;
//    else {
//  if ((T =(BiTNode *)malloc(sizeof(BiTNode)))==NULL) exit(0);
//
//      T->data = ch;              // 生成根结点
//      CreateBiTree(T->lchild);   // 构造左子树
//      CreateBiTree(T->rchild);   // 构造右子树
//    }
//    return 0;  } // CreateBiTree ,无头结点

BiTNode *GoFarLeft(BiTree T,SqStack &S)
{// T为树根结点的指针
   if (T=NULL )  return NULL;
   while (T->lchild ){
      Push(S, T);
      T = T->lchild;
   }
   return T;
 }//得到树T最左叶子结点的指针


int main()
{

  BiTree t;
  SqStack sta;
  InitStack(sta);
  GoFarLeft()(t,sta);
  PreOrderTraverse(t);
}
