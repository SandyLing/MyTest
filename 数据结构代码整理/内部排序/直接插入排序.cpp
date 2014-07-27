#include<stdio.h>
#include<stdlib.h>
typedef int   Status;
typedef struct Sqlist{
    int elem[100];
    int length;
}Sqlist;
Status SorttInsert(Sqlist &s,int i,int e){
    s.elem[i]=e;
    s.length++;
}
Status SortTraverse(Sqlist s,void(*vf)(int)){
     for(int j=1; j<=s.length; j++)
        vf(s.elem[j]);
}
Status InsertionSort(Sqlist s);
//顺序表类型
void print(int c)
{
    printf("%d ",c);
}
int main()
{
    int c[]= {99,4,3,23,5,6,100,7,9,56,43};
    printf("\n--------------直接排序-------------------\n");
    Sqlist z;
    z.length=0;
    for(int j=1; j<=11; j++)
        SorttInsert(z,j,c[j-1]);
    printf("表内的元素为：\n");
    SortTraverse(z,print);
    printf("\n直接排序 ");
    //InsertionSort(z);
    SortTraverse(z,print);

    return 0;
}
