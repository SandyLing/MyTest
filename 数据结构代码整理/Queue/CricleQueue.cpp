#include <stdlib.h>
#include <stdio.h>
#include "CircularQueue.h"
void display(SqQueue &sq)
{
    for(int i=0;i<QueueLength(sq);i++)
     printf("%d",sq.base[i]);
    printf("\n");
}
int main()
{
   SqQueue sta;
  InitQueue(sta);
  int a,b=0;
  printf("请输入5个数字");
  for(int i=0;i<5;i++)
   {
    scanf("%d",&a);
    EnQueue(sta,a);
   }
  printf("输入的元素为: ");
  display(sta);
  DeQueue(sta,b);
  printf("弹出的元素为%d\n",b);
  display(sta);
}
