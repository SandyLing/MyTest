#include<stdio.h>
#include<stdlib.h>
#define keyType int
typedef int Status;
typedef struct BiTNode{
    keyType data;
    BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
Status print(keyType e){
    printf("%d ",e);
}
Status SearchBST(BiTree T,keyType e,BiTree f,BiTree &p){
    if(!T){p=f;return 0;}
    else if(T->data==e) {p=T;return 1;}
    else if(e<T->data) return SearchBST(T->lchild,e,T,p);
    else return SearchBST(T->rchild,e,T,p);

}
Status InsertBST(BiTree &t,keyType e){
    BiTree s,p;
    if(!SearchBST(t,e,NULL,p)){
        s = (BiTNode*)malloc(sizeof(BiTNode));
        s->lchild=NULL;
        s->rchild=NULL;
        s->data=e;
        if(!p) t=s;
        else if(e< p->data) p->lchild=s;
        else p->rchild=s;
        return 0;
    }
}
Status Delete(BiTree &t){
    BiTree p,s;
    if(!t->rchild){
        p=t;
        t=t->lchild;
        free(p);
    }else if(!t->lchild){
        p=t;
        t=t->rchild;
        free(p);
    }else{
        p=t;
        s=t->lchild;
        while(s->rchild){
            p=s;
            s=s->rchild;
        }
        t->data=s->data;
        if(p!=t) p->rchild = s->lchild;
        else p->lchild = s->lchild;
    }
}
Status deleteBST(BiTree &T,keyType e){
    if(!T) return 0;
    else{
        if(e==T->data) Delete(T);
        else if(e<T->data)deleteBST(T->lchild,e);
        else deleteBST(T->rchild,e);
    }
}
Status InOrderTraverse(BiTree &t,Status(*vf)(keyType)){
    if(t){
        InOrderTraverse(t->lchild,vf);
         vf(t->data);
        InOrderTraverse(t->rchild,vf);
    }
}

int main()
{
    keyType b[]= {1,4,6,8,5,3,8,49,34,2};
    int j;
    printf("\n--------------二叉排序树-------------------\n");
    BiTree t=NULL;
    for(j=1; j<=10; j++)
        InsertBST(t,b[j-1]);
    printf("表内的元素为：");
    InOrderTraverse(t,print);
    deleteBST(t,49);
    printf("\n");
    InOrderTraverse(t,print);
    deleteBST(t,5);
    printf("\n");
    InOrderTraverse(t,print);
    deleteBST(t,1);
    printf("\n");
    InOrderTraverse(t,print);


}
