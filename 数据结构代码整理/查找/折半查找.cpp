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
//************************折半查找***********************
typedef struct
{
    keyType key;    // 关键字域
} ElemType ;
typedef  struct
{
    ElemType *elem;
    int       length;    // 表的长度
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
    if(i<1||i>S.length+1) /* i值不合法 */
        return ERROR;
    q=S.elem+i; /* q为插入位置 */
    for(p=S.elem+S.length; p>=q; --p) /* 插入位置及之后的元素右移 */
        (p+1)->key=p->key;
    q->key=e; /* 插入e */
    ++S.length; /* 表长增1 */
    return OK;
}
//折半查找
int Search_Bin(SSTable &ST, keyType key)
{
    int low, high, mid;
    low = 1;
    high = ST.length;    // 置区间初值
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key==ST.elem[mid].key) return mid;    // 找到待查元素
        else if (key <= ST.elem[mid].key) high = mid - 1;// 继续在前半区间进行查找
        else low = mid + 1;    // 继续在后半区间进行查找
    }
    return 0;                 // 顺序表中不存在待查元素
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
//------------------二叉排序树----------------------
typedef struct BiTNode   // 结点结构
{
    ElemType     data;
    struct BiTNode  *lchild, *rchild;
    // 左右孩子指针
} BiTNode, *BiTree;
Status SearchBST(BiTree T, keyType key, BiTree f, BiTree &p)
{
    if (!T)
    {
        p = f;       // 查找不成功
        return FALSE;
    }
    else if (key==T->data.key)
    {
        p = T;      // 查找成功
        return TRUE;
    }
    else if (key<T->data.key)return SearchBST(T->lchild, key, T, p);
    // 在左子树中继续查找
    else return SearchBST(T->rchild, key, T, p);
    printf("f");
    // 在右子树中继续查找
}
//中序遍历
Status InOrderTraverse (BiTree T, void(*visit)(keyType&))
{
    // 中序遍历二叉树，T为树根的指针
    if (T)
    {
        InOrderTraverse(T->lchild, visit);// 遍历左子树
        visit(T->data.key) ;// 访问结点
        InOrderTraverse(T->rchild, visit);// 遍历右子树
    }
}
Status InsertBST(BiTree &T, int e)
{
    BiTree p=NULL,s;
    if (!SearchBST(T, e, NULL, p))     // 查找不成功
    {
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data.key = e;
        s->lchild = s->rchild = NULL;
        if (!p) T = s;        // 插入 s 为新的根结点
        else if (e < p->data.key) p->lchild=s; // 插入s为左孩子
        else p->rchild = s;   // 插入 s 为右孩子
        return TRUE;
    }
    else return FALSE;    // 树中已有关键字相同的结点，不再插入
} // Insert BST
//------------------排序-------------------
typedef  struct
{
    keyType   key;             // 关键字项
    InfoType  otherinfo;     // 其它数据项
} RcdType;
typedef  struct
{
    RcdType    r[MAXSIZE+1]; //r[0]闲置
    int        length;       //顺序表长度
} SqList;
void InsertionSort (SqList &L )
{
    // 对顺序表 L 作直接插入排序。
    int i,j;
    for ( i=2; i<=L.length; ++i )
        if (L.r[i].key < L.r[i-1].key)
        {
            L.r[0] = L.r[i];           // 复制为监视哨
            for ( j=i-1; L.r[0].key < L.r[j].key;  -- j )
                L.r[j+1] = L.r[j]; // 记录后移
            L.r[j+1] = L.r[0];       // 插入到正确位置
        }
} // InsertSort
Status SorttInsert(SqList &L,int i,keyType e) //直接插入排序
{
    RcdType *q,*p;
    q=L.r+i; /* q为插入位置 */
    for(p=L.r+L.length; p>=q; --p) /* 插入位置及之后的元素右移 */
        *(p+1)=*p;
    q->key=e; /* 插入e */
    ++L.length; /* 表长增1 */
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
//---------------快速排序----------------
int Partition(SqList &L, int low, int high) {
   // 交换顺序表L中子序列L.r[low..high]的记录，使枢轴记录到位，
   // 并返回其所在位置，此时，在它之前（后）的记录均不大（小）于它
   keyType pivotkey;
   L.r[0] = L.r[low];            // 用子表的第一个记录作枢轴记录
   pivotkey = L.r[low].key;      // 枢轴记录关键字
   while (low<high) {            // 从表的两端交替地向中间扫描
      while (low<high && L.r[high].key>=pivotkey) --high;
      L.r[low] = L.r[high];      // 将比枢轴记录小的记录移到低端
      while (low<high && L.r[low].key<=pivotkey) ++low;
      L.r[high] = L.r[low];      // 将比枢轴记录大的记录移到高端
   }
   L.r[low] = L.r[0];            // 枢轴记录到位
   return low;                   // 返回枢轴位置
} // Partition
void QSort(SqList &L, int low, int high) {
  // 对顺序表L中的子序列L.r[low..high]进行快速排序
  int pivotloc;
  if (low < high) {                      // 长度大于1
    pivotloc = Partition(L, low, high);  // 将L.r[low..high]一分为二
    QSort(L, low, pivotloc-1); // 对低子表递归排序，pivotloc是枢轴位置
    QSort(L, pivotloc+1, high);          // 对高子表递归排序
  }
} // QSort
void QuickSort(SqList &L) {
   // 对顺序表L进行快速排序
   QSort(L, 1, L.length);
} // QuickSort

//顺序表类型
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
    printf("表内的元素为：\n");
    TableTraverse(s,print);//遍历查找表
    printf("--------------折半查找-------------------\n");
    printf("请输入要查找的数字 ");
    scanf("%d",&e);
    location=Search_Bin(s,e1);
    if(location==0) printf("\n未找到该元素!");
    else printf("\n该元素在表中的位置为 %d",location);
    printf("\n--------------二叉排序树-------------------\n");
    BiTree t=NULL;
    for(j=1; j<=10; j++)
        InsertBST(t,b[j-1]);
    printf("\n输入的元素为1,4,6,8,5,3,8,49,34,2\n");
    printf("表内的元素为：\n");
    InOrderTraverse(t,print);
    printf("\n--------------直接排序-------------------\n");
    SqList z;
    z.length=0;
    for(j=1; j<=11; j++)
        SorttInsert(z,j,c[j-1]);
    printf("表内的元素为：\n");
    SortTraverse(z,print);
    printf("\n直接排序 ");
    InsertionSort(z);
    SortTraverse(z,print);
     printf("\n--------------冒泡排序-------------------\n");
     SqList m;
    m.length=0;
    for(j=1; j<=10; j++)
        SorttInsert(m,j,d[j-1]);
    printf("表内的元素为：\n");
    SortTraverse(m,print);
    j=10;
    BubbleSort(m,j);
    printf("\n冒泡排序 ");
      SortTraverse(m,print);
      printf("\n--------------快速排序-------------------\n");
     SqList k;
    k.length=0;
    for(j=1; j<=10; j++)
        SorttInsert(k,j,d[j-1]);
    printf("表内的元素为：\n");
    SortTraverse(k,print);
    QuickSort(k);
    printf("\快速排序 ");
      SortTraverse(k,print);
    return 0;
}
