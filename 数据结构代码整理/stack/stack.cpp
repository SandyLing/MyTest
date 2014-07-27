#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
void display(SqStack &sq)
{
    int *p;
    p=sq.base;
    while(p!=sq.top)
    {
        printf("%d",*p);
        p++;
    }
    printf("\n");
}
int main()
{
  SqStack sta;
  InitStack(sta);
  int a,b=0;
  printf("请输入5个数字");
  for(int i=0;i<5;i++)
   {
    scanf("%d",&a);
    Push(sta,a);
   }
  printf("输入的元素为: ");
  display(sta);
  Pop(sta,b);
  printf("弹出的元素为%d\n",b);
  display(sta);
}
