#include <stdio.h>
#include <stdlib.h>
#define keyType int
#define init_size 100
typedef int Status;
//typedef int keyType;
typedef struct SSTable{
    keyType* key;
    int length;
}SSTable;
Status InitTable(SSTable &s){
    s.key = (keyType*)malloc(init_size*sizeof(keyType));
    if(!s.key) return -1;
    s.length=0;
}
Status TableInsert(SSTable &s,int j,keyType e){
    if(j>s.length+1) return -1;
    s.key[j]=e;
    s.length++;
    return -1;
}
Status print(keyType e){
    printf("%d ",e);
}
Status TableTraverse(const SSTable &L,Status(*vi)(keyType))
{
    keyType *p;
    int i;
    p=L.key+1;
    for(i=1; i<=L.length; i++,p++)
        vi(*p);
    printf("\n");
    return 1;
}
//折半查找
Status Search_Bin(SSTable &s,keyType e){
    int low,high,mid;
    low = 1;
    high =s.length;
    //s.key[0] = e;
    while(low<=high){
        mid = (high+low)/2;
        if(s.key[mid]==e) return mid;
        else if(s.key[mid]<e) low =mid+1;
        else high =mid-1;
    }
    return 0;
}
int main()
{
    keyType a[]= {2,4,6,8,11,13,15,16,19,21,24};
    int j,e1,location;
    SSTable s;
    InitTable(s);
    for(j=1; j<=11; j++)
        TableInsert(s,j,a[j-1]);
    printf("表内的元素为：\n");
    TableTraverse(s,print);//遍历查找表
    printf("--------------折半查找-------------------\n");
    printf("请输入要查找的数字 ");
    scanf("%d",&e1);
    location=Search_Bin(s,e1);
    if(location==0) printf("\n未找到该元素!");
    else printf("\n该元素在表中的位置为 %d",location);
    return 0;
}
