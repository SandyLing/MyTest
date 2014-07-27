#include <stdlib.h>
#include <stdio.h>
#include "ListQueue.h"
void display(LinkQueue &sq)
{
    QueuePtr p;
    p=sq.front->next;
    while(p!=NULL)
    {
        printf("%d",p->data);
        p=p->next;
    }
    printf("\n");
}
int main()
{
  LinkQueue sta;
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
