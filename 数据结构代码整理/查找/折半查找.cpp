#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define TABLE_INIT_SIZE 100
#define OVERFLOW -2
#define MAXSIZE  1000
typedef  int  keyType;
typedef  int  InfoType;
typedef int   Status;
//************************�۰����***********************
typedef struct
{
    keyType key;    // �ؼ�����
} ElemType ;
typedef  struct
{
    ElemType *elem;
    int       length;    // ��ĳ���
} SSTable;
Status InitTable(SSTable &S)
{
    S.elem=(ElemType*)malloc(TABLE_INIT_SIZE*sizeof(ElemType));
    if(!S.elem)
        exit(OVERFLOW);
    S.length=0;
    return OK;
}
Status TableInsert(SSTable &S,int i,keyType e)
{
    ElemType *q,*p;
    if(i<1||i>S.length+1) /* iֵ���Ϸ� */
        return ERROR;
    q=S.elem+i; /* qΪ����λ�� */
    for(p=S.elem+S.length; p>=q; --p) /* ����λ�ü�֮���Ԫ������ */
        (p+1)->key=p->key;
    q->key=e; /* ����e */
    ++S.length; /* ����1 */
    return OK;
}
//�۰����
int Search_Bin(SSTable &ST, keyType key)
{
    int low, high, mid;
    low = 1;
    high = ST.length;    // �������ֵ
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key==ST.elem[mid].key) return mid;    // �ҵ�����Ԫ��
        else if (key <= ST.elem[mid].key) high = mid - 1;// ������ǰ��������в���
        else low = mid + 1;    // �����ں��������в���
    }
    return 0;                 // ˳����в����ڴ���Ԫ��
} // Search_Bin
Status TableTraverse(const SSTable &L,void(*vi)(keyType&))
{
    ElemType *p;
    int i;
    p=L.elem+1;
    for(i=1; i<=L.length; i++,p++)
        vi(p->key);
    printf("\n");
    return OK;
}
//------------------����������----------------------
typedef struct BiTNode   // ���ṹ
{
    ElemType     data;
    struct BiTNode  *lchild, *rchild;
    // ���Һ���ָ��
} BiTNode, *BiTree;
Status SearchBST(BiTree T, keyType key, BiTree f, BiTree &p)
{
    if (!T)
    {
        p = f;       // ���Ҳ��ɹ�
        return FALSE;
    }
    else if (key==T->data.key)
    {
        p = T;      // ���ҳɹ�
        return TRUE;
    }
    else if (key<T->data.key)return SearchBST(T->lchild, key, T, p);
    // ���������м�������
    else return SearchBST(T->rchild, key, T, p);
    printf("f");
    // ���������м�������
}
//�������
Status InOrderTraverse (BiTree T, void(*visit)(keyType&))
{
    // ���������������TΪ������ָ��
    if (T)
    {
        InOrderTraverse(T->lchild, visit);// ����������
        visit(T->data.key) ;// ���ʽ��
        InOrderTraverse(T->rchild, visit);// ����������
    }
}
Status InsertBST(BiTree &T, int e)
{
    BiTree p=NULL,s;
    if (!SearchBST(T, e, NULL, p))     // ���Ҳ��ɹ�
    {
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data.key = e;
        s->lchild = s->rchild = NULL;
        if (!p) T = s;        // ���� s Ϊ�µĸ����
        else if (e < p->data.key) p->lchild=s; // ����sΪ����
        else p->rchild = s;   // ���� s Ϊ�Һ���
        return TRUE;
    }
    else return FALSE;    // �������йؼ�����ͬ�Ľ�㣬���ٲ���
} // Insert BST
//------------------����-------------------
typedef  struct
{
    keyType   key;             // �ؼ�����
    InfoType  otherinfo;     // ����������
} RcdType;
typedef  struct
{
    RcdType    r[MAXSIZE+1]; //r[0]����
    int        length;       //˳�����
} SqList;
void InsertionSort (SqList &L )
{
    // ��˳��� L ��ֱ�Ӳ�������
    int i,j;
    for ( i=2; i<=L.length; ++i )
        if (L.r[i].key < L.r[i-1].key)
        {
            L.r[0] = L.r[i];           // ����Ϊ������
            for ( j=i-1; L.r[0].key < L.r[j].key;  -- j )
                L.r[j+1] = L.r[j]; // ��¼����
            L.r[j+1] = L.r[0];       // ���뵽��ȷλ��
        }
} // InsertSort
Status SorttInsert(SqList &L,int i,keyType e) //ֱ�Ӳ�������
{
    RcdType *q,*p;
    q=L.r+i; /* qΪ����λ�� */
    for(p=L.r+L.length; p>=q; --p) /* ����λ�ü�֮���Ԫ������ */
        *(p+1)=*p;
    q->key=e; /* ����e */
    ++L.length; /* ����1 */
    return OK;
}
Status SortTraverse(SqList &L,void(*vi)(keyType&))
{
    RcdType *p;
    int i;
    p=L.r+1;
    for(i=1; i<=L.length; i++,p++)
        vi(p->key);
    printf("\n");
    return OK;
}
Status BubbleSort(SqList &L, int n)
{
   int i,j;
   keyType temp;
   for(i=0;i<n-1;i++)
     for(j=1;j<n-i;j++)
      if(L.r[j].key>L.r[j+1].key)
      {
          temp=L.r[j].key;
          L.r[j].key=L.r[j+1].key;
          L.r[j+1].key=temp;
      }
} // BubbleSort
//---------------��������----------------
int Partition(SqList &L, int low, int high) {
   // ����˳���L��������L.r[low..high]�ļ�¼��ʹ�����¼��λ��
   // ������������λ�ã���ʱ������֮ǰ���󣩵ļ�¼������С������
   keyType pivotkey;
   L.r[0] = L.r[low];            // ���ӱ�ĵ�һ����¼�������¼
   pivotkey = L.r[low].key;      // �����¼�ؼ���
   while (low<high) {            // �ӱ�����˽�������м�ɨ��
      while (low<high && L.r[high].key>=pivotkey) --high;
      L.r[low] = L.r[high];      // ���������¼С�ļ�¼�Ƶ��Ͷ�
      while (low<high && L.r[low].key<=pivotkey) ++low;
      L.r[high] = L.r[low];      // ���������¼��ļ�¼�Ƶ��߶�
   }
   L.r[low] = L.r[0];            // �����¼��λ
   return low;                   // ��������λ��
} // Partition
void QSort(SqList &L, int low, int high) {
  // ��˳���L�е�������L.r[low..high]���п�������
  int pivotloc;
  if (low < high) {                      // ���ȴ���1
    pivotloc = Partition(L, low, high);  // ��L.r[low..high]һ��Ϊ��
    QSort(L, low, pivotloc-1); // �Ե��ӱ�ݹ�����pivotloc������λ��
    QSort(L, pivotloc+1, high);          // �Ը��ӱ�ݹ�����
  }
} // QSort
void QuickSort(SqList &L) {
   // ��˳���L���п�������
   QSort(L, 1, L.length);
} // QuickSort

//˳�������
void print(keyType &c)
{
    printf("%d ",c);
}
int main()
{
    keyType a[]= {2,4,6,8,11,13,15,16,19,21,24};
    keyType b[]= {1,4,6,8,5,3,8,49,34,2};
    keyType c[]= {99,4,3,23,5,6,100,7,9,56,43};
    keyType d[]= {100,2,4,5,622,232,8,90,43,55};
    keyType e[]= {45,21,43,25,62,22,88,91,23,55};
    int j,e1,location;
    SSTable s;
    InitTable(s);
    for(j=1; j<=11; j++)
        TableInsert(s,j,a[j-1]);
    printf("���ڵ�Ԫ��Ϊ��\n");
    TableTraverse(s,print);//�������ұ�
    printf("--------------�۰����-------------------\n");
    printf("������Ҫ���ҵ����� ");
    scanf("%d",&e);
    location=Search_Bin(s,e1);
    if(location==0) printf("\nδ�ҵ���Ԫ��!");
    else printf("\n��Ԫ���ڱ��е�λ��Ϊ %d",location);
    printf("\n--------------����������-------------------\n");
    BiTree t=NULL;
    for(j=1; j<=10; j++)
        InsertBST(t,b[j-1]);
    printf("\n�����Ԫ��Ϊ1,4,6,8,5,3,8,49,34,2\n");
    printf("���ڵ�Ԫ��Ϊ��\n");
    InOrderTraverse(t,print);
    printf("\n--------------ֱ������-------------------\n");
    SqList z;
    z.length=0;
    for(j=1; j<=11; j++)
        SorttInsert(z,j,c[j-1]);
    printf("���ڵ�Ԫ��Ϊ��\n");
    SortTraverse(z,print);
    printf("\nֱ������ ");
    InsertionSort(z);
    SortTraverse(z,print);
     printf("\n--------------ð������-------------------\n");
     SqList m;
    m.length=0;
    for(j=1; j<=10; j++)
        SorttInsert(m,j,d[j-1]);
    printf("���ڵ�Ԫ��Ϊ��\n");
    SortTraverse(m,print);
    j=10;
    BubbleSort(m,j);
    printf("\nð������ ");
      SortTraverse(m,print);
      printf("\n--------------��������-------------------\n");
     SqList k;
    k.length=0;
    for(j=1; j<=10; j++)
        SorttInsert(k,j,d[j-1]);
    printf("���ڵ�Ԫ��Ϊ��\n");
    SortTraverse(k,print);
    QuickSort(k);
    printf("\�������� ");
      SortTraverse(k,print);
    return 0;
}
