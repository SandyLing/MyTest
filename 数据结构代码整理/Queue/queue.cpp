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
  printf("������5������");
  for(int i=0;i<5;i++)
   {
    scanf("%d",&a);
    EnQueue(sta,a);
   }
  printf("�����Ԫ��Ϊ: ");
  display(sta);
  DeQueue(sta,b);
  printf("������Ԫ��Ϊ%d\n",b);
  display(sta);
}
