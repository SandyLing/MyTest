#include <stdio.h>
#include <stdlib.h>
typedef  int  ElemType;
typedef struct HeapType
{
    ElemType elem[100];
    int length;
} HeapType;
void HeapAdjust(HeapType &h,int i,int nLength)
{
    int nChild;
    int nTemp;
    for(; 2*i<nLength; i=nChild)
    {
//�ӽ���λ��=2*�������λ�ã�+1
        nChild=2*i+1;
//�õ��ӽ���нϴ�Ľ��
        if(nChild<nLength-1&&array[nChild+1]>array[nChild])
            ++nChild;
//����ϴ���ӽ����ڸ������ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
        if(array[i]<array[nChild])
        {
            nTemp=array[i];
            array[i]=array[nChild];
            array[nChild]=nTemp;
        }
        else
//�����˳�ѭ��
            break;
    }
}
void swap(ElemType &a,ElemType &b)
{
    ElemType temp;
    temp=a;
    a=b;
    b=temp;
}
//�������㷨
void HeapSort(HeapType &h)
{
    int tmp;
    int length = h.length;
//�������е�ǰ�벿��Ԫ�أ�������֮���һ��Ԫ�������е�����Ԫ��
//length/2-1�����һ����Ҷ�ڵ㣬�˴�"/"Ϊ����
    for(int i=length/2; i>=0; --i)
        HeapAdjust(array,i,length);
//�����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
    for(int i=length; i>0; --i)
    {
//�ѵ�һ��Ԫ�غ͵�ǰ�����һ��Ԫ�ؽ�����
//��֤��ǰ�����һ��λ�õ�Ԫ�ض��������ڵ��������֮������
//Swap(&array[0],&array[i]);
        tmp=array[i];
        array[i]=array[1];
        array[1]=tmp;
//������С����heap�ķ�Χ��ÿһ�ε�����ϱ�֤��һ��Ԫ���ǵ�ǰ���е����ֵ
        HeapAdjust(array,1,i);
    }
}
void SorttInsert(HeapType &s,int j,ElemType e)
{
    s.elem[j]=e;
    s.length++;
}
void print(ElemType e)
{
    printf("%d ",e);
}
void SortTraverse(HeapType &s,void(*vf)(ElemType))
{
    for(int j=1; j<=s.length; j++)
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
