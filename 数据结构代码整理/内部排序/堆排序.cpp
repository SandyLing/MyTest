#include <stdio.h>
#include <stdlib.h>
typedef  int  ElemType;
typedef struct HeapType{
    ElemType elem[100];
    int length;
}HeapType;
void HeapAdjust(HeapType &h,int s,int m){//������[s,m]�Ĵ��
    ElemType rc = h.elem[s];
    for(int j=2*s;j<=m;j*=2){
        if(j<m&&h.elem[j]<h.elem[j+1]) ++j;
        if(rc>=h.elem[j]) break;
        h.elem[s] = h.elem[j];
        s =j;
    }
    h.elem[s] =rc;
}
void swap(ElemType &a,ElemType &b){
    ElemType temp;
    temp=a;
    a=b;
    b=temp;
}
void HeapSort(HeapType &h){
    for(int i=h.length/2;i>0;--i)//�������
        HeapAdjust(h,i,h.length);
    for(int i=h.length;i>1;--i){//�����������䣬��öѶ�����h.elem[i]β����˳����
        swap(h.elem[1],h.elem[i]);
        HeapAdjust(h,1,i-1);
    }
}
void SorttInsert(HeapType &s,int j,ElemType e){
    s.elem[j]=e;
    s.length++;
}
void print(ElemType e){
    printf("%d ",e);
}
void SortTraverse(HeapType &s,void(*vf)(ElemType)){
    for(int j=1;j<=s.length;j++)
        print(s.elem[j]);
}

int main()
{
    ElemType d[]= {100,2,4,5,622,232,8,90,43,55};
    HeapType m;
    int j;
    m.length=0;
    for(j=1; j<=10; j++)
        SorttInsert(m,j,d[j-1]);
    printf("���ڵ�Ԫ��Ϊ��\n");
    SortTraverse(m,print);
    j=10;
    HeapSort(m);
    printf("\n������ ");
      SortTraverse(m,print);
}
