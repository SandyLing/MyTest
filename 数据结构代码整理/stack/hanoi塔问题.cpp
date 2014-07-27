#include "stdio.h" //基础输入输出用的头文件
void hanoi(int n,int x,int y,int z) //打印移动盘子的函数，递归调用的
{
if (n==1) //如果只有一个盘子，很简单，直接把盘子从X移动到Z就结束了
printf("%c-->%c\n",x,z); //打印“x-->z”，就是上面说的
else //否则，盘子数大于1
{
hanoi(n-1,x,z,y); //我们首先要用hanoi函数把n-1个盘子借助Z，从X移动到Y上
printf("%c-->%c\n",x,z); //再把最后一个盘子，从X直接移动到Z上
hanoi(n-1,y,x,z); //然后把n-1个盘子，借助X，从Y移动到Z上
}
}//这个函数就是不断递归调用，把n个盘子的问题递归到n-1，个盘子的问题，递归到n-2个的问题.....知道最后一次是只有一个盘子的问题，问题就解决了

int main() //主函数
{
int n; //定义n个盘子
printf("请输入n的值:\n"); //打印提示用户输入
scanf("%d",&n); //获取用户输入
printf("the step to moving %2d diskes:\n",n); //打印提示，下面要输出结果了
hanoi(n,'a','b','c'); //调用函数，打印盘子移动步骤
}
