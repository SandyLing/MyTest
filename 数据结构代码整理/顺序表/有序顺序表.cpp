#include <stdio.h>
#include <stdlib.h>
#define   LIST_INIT_SIZE 100
#define   LISTINCREMENT 10
typedef struct SqList
{
  int     *elem;
  int     length;//��ǰ����
  int     listsize;//����Ŀռ��С
}SqList;
int InitList_Sq(SqList &L) {  // �㷨2.3
  // ����һ���յ����Ա�L��
  L.elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
  if (!L.elem) return 1;        // �洢����ʧ��
  L.length = 0;                  // �ձ���Ϊ0
  L.listsize = LIST_INIT_SIZE;   // ��ʼ�洢����
  return 1;
} // InitList_Sq
int compare_position(SqList &L,int e)
{
    int i=1;
    int *q;
    q=L.elem;
    for(;*q<e;q++)
     i++;
     return i;
}
int ListInsert_Sq(SqList &L,int e) {  // �㷨2.4
  // ��˳�����Ա�L�ĵ�i��Ԫ��֮ǰ�����µ�Ԫ��e��
  // i�ĺϷ�ֵΪ1��i��ListLength_Sq(L)+1
  int *p;
  if (L.length >= L.listsize) {   // ��ǰ�洢�ռ���������������
    int *newbase = (int *)realloc(L.elem,
                  (L.listsize+LISTINCREMENT)*sizeof (int));
    if (!newbase) return 0;   // �洢����ʧ��
    L.elem = newbase;             // �»�ַ
    L.listsize += LISTINCREMENT;  // ���Ӵ洢����
  }
  int i=compare_position(L,e);
  int *q = &(L.elem[i-1]);   // qΪ����λ��
  for (p = &(L.elem[L.length-1]); p>=q; --p) *(p+1) = *p;
                                  // ����λ�ü�֮���Ԫ������
  *q = e;       // ����e
  ++L.length;   // ����1
  return 1;
} // ListInsert_Sq
int ListDelete_Sq(SqList &L, int i, int &e) {  // �㷨2.5
  // ��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ��
  // i�ĺϷ�ֵΪ1��i��ListLength_Sq(L)��
  int *p, *q;
  if (i<1 || i>L.length)

  {
      printf("\nerror!\n");
      return 0;
  }   // iֵ���Ϸ� // iֵ���Ϸ�
  p = &(L.elem[i-1]);                   // pΪ��ɾ��Ԫ�ص�λ��
  e = *p;                               // ��ɾ��Ԫ�ص�ֵ����e
  q = L.elem+L.length-1;                // ��βԪ�ص�λ��
  for (++p; p<=q; ++p) *(p-1) = *p;     // ��ɾ��Ԫ��֮���Ԫ������
  --L.length;                           // ����1
  return 1;
} // ListDelete_Sq
int compare(int a,int b)
{
    if (a==b)
     return 1;
     return 0;
}
int LocateElem_Sq(SqList L, int e) {  // �㷨2.6
  // ��˳�����Ա�L�в��ҵ�1��ֵ��e����compare()��Ԫ�ص�λ��
  // ���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0��
  int i;
  int *p;
  i = 1;        // i�ĳ�ֵΪ��1��Ԫ�ص�λ��
  p = L.elem;   // p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
  while (i <= L.length && !(*compare)(*p++, e))
    ++i;
  if (i <= L.length) return i;
  else return 0;
} // LocateElem_Sq
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc) {  // �㷨2.7
  // ��֪˳�����Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С�
  // �鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С�
  int *pa,*pb,*pc,*pa_last,*pb_last;
  pa = La.elem;  pb = Lb.elem;
  Lc.listsize = Lc.length = La.length+Lb.length;
  pc = Lc.elem = (int *)malloc(Lc.listsize*sizeof(int));
  if (!Lc.elem)
    exit (9);   // �洢����ʧ��
  pa_last = La.elem+La.length-1;
  pb_last = Lb.elem+Lb.length-1;
  while (pa <= pa_last && pb <= pb_last) {  // �鲢
    if (*pa <= *pb) *pc++ = *pa++;
    else *pc++ = *pb++;
  }
  while (pa <= pa_last) *pc++ = *pa++;      // ����La��ʣ��Ԫ��
  while (pb <= pb_last) *pc++ = *pb++;      // ����Lb��ʣ��Ԫ��
} // MergeList

void display(SqList &l)
{
  for(int i=0;i<l.length;i++)
    printf("%d ",l.elem[i]);
    printf("\n");
}
int main()
{
    SqList la;
    SqList lb;
    SqList lc;
    int temp[20],a,d=0,b;
    InitList_Sq(la);
    InitList_Sq(lb);
    InitList_Sq(lc);
    printf("����˳���laһЩ��ʼ����������^z)��\n");
    while(scanf("%d",&a)!=EOF)
    {
     ListInsert_Sq(la,a);
    }
    display(la);
    printf("\n������Ҫ�����Ԫ��λ�ã�������^z)\n");
    while(scanf("%d",&a)!=EOF)
    {
     ListInsert_Sq(la,a);
     printf("Ԫ���б�Ϊ��\n");
     display(la);
    }
    printf("\n������Ҫɾ����Ԫ��λ�ã�������^z)");
    while(scanf("%d",&a)!=EOF)
    {
      ListDelete_Sq(la,a,temp[d]);
      //printf("\n��ɾ����Ԫ��Ϊ��%d\n",temp);
      d++;
      printf("ʣ�µ�Ԫ��Ϊ��\n");
      display(la);
    }
    for(int i=0;i<d;i++)
    printf("\n��ɾ����Ԫ��Ϊ��%d\n",temp[i]);
    printf("\n������Ҫ��ѯ��Ԫ�أ�������^z)\n");
    while(scanf("%d",&a)!=EOF)
    {
        int g;
        g=LocateElem_Sq(la,a);
     if(!g)
     printf("�������Ԫ��δ���֣�\n");
     else
     printf("�������Ԫ�������Ա��е�%dλ��\n",g);
    }
    printf("����˳���lb��ʼ����������^z)��\n");
    while(scanf("%d",&a)!=EOF)
    {
     ListInsert_Sq(lb,a);
    }
     printf("���Ա�lbΪ�� ");
     display(lb);
     MergeList_Sq(la,lb,lc);
     printf("�ϲ�l��lb���Ա��ϲ���lcΪ��\n");
     display(lc);
    return 0;
}
