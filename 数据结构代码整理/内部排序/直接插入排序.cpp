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
//˳�������
void print(int c)
{
    printf("%d ",c);
}
int main()
{
    int c[]= {99,4,3,23,5,6,100,7,9,56,43};
    printf("\n--------------ֱ������-------------------\n");
    Sqlist z;
    z.length=0;
    for(int j=1; j<=11; j++)
        SorttInsert(z,j,c[j-1]);
    printf("���ڵ�Ԫ��Ϊ��\n");
    SortTraverse(z,print);
    printf("\nֱ������ ");
    //InsertionSort(z);
    SortTraverse(z,print);

    return 0;
}
