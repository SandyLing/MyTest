#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
typedef struct BiTNode { // ���ṹ
    int     data;
    struct BiTNode  *lchild, *rchild;
                                 // ���Һ���ָ��
} BiTNode, *BiTree;
void PreOrderTraverse (BiTree T){
  //TΪ������ָ��
   if (T!=NULL) {
     printf("%c",T->data); // ���ʽ��
     PreOrderTraverse(T->lchild);
     PreOrderTraverse(T->rchild);
    }
}
//int CreateBiTree(BiTree &T) {
////��ǰ�������������Ϣ
//    char ch;
//    scanf("%c",&ch);
//    if (ch==' ') T = NULL;
//    else {
//  if ((T =(BiTNode *)malloc(sizeof(BiTNode)))==NULL) exit(0);
//
//      T->data = ch;              // ���ɸ����
//      CreateBiTree(T->lchild);   // ����������
//      CreateBiTree(T->rchild);   // ����������
//    }
//    return 0;  } // CreateBiTree ,��ͷ���

BiTNode *GoFarLeft(BiTree T,SqStack &S)
{// TΪ��������ָ��
   if (T=NULL )  return NULL;
   while (T->lchild ){
      Push(S, T);
      T = T->lchild;
   }
   return T;
 }//�õ���T����Ҷ�ӽ���ָ��


int main()
{

  BiTree t;
  SqStack sta;
  InitStack(sta);
  GoFarLeft()(t,sta);
  PreOrderTraverse(t);
}
