#include <stdio.h>
#include <stdlib.h>
 typedef struct {
       char *ch;
      // 若是非空串,则按串长分配存储区，
       //  否则ch为NULL
      int  length;   // 串长度
}Hstring;//HeapString.
int StrInsert(Hstring &S, int pos, Hstring T) {  // 算法4.4
   // 1≤pos≤StrLength(S)＋1。在串S的第pos个字符之前插入串T。
   int i;
   if (pos < 1 || pos > S.length+1)  // pos不合法
      return 0;
   if (T.length) {    // T非空,则重新分配空间,插入T
      if (!(S.ch = (char *)realloc(S.ch,(S.length+T.length+1)*sizeof(char))))
         return 0;
      for (i=S.length-1; i>=pos-1; --i)  // 为插入T而腾出位置
         S.ch[i+T.length] = S.ch[i];
      for (i=0; i<T.length; i++)         // 插入T
         S.ch[pos-1+i] = T.ch[i];
      S.length += T.length;
   }
   return 1;
} // StrInsert
int StrAssign(Hstring t,char *chars){
      //生成一个其值等于串常量chars的串T
      char *c;
      if(t.ch) free(t.ch);
      int i=0;
      c=chars;
      for(; *c ; ++i,++c);    //求chars的长度
      if (!i) { t.ch=NULL; t.length=0;}
      else { t.ch=(char *)malloc(i*sizeof(char));
                if (!(t.ch)) exit(0);
                for(int i=0;i<t.length-1;i++)
                t.ch[i]=chars[i];
                t.length=i;
       }
      return 1;
}
int Concat(Hstring & T, Hstring S1, Hstring S2){
       // 用T返回由S1和S2联接而成的新串
       if (T.ch)  free(T.ch);        // 释放旧空间
      if (!(T.ch = (char *)malloc((S1.length+S2.length)*sizeof(char))))
        exit (0);
        for(int i=0;i<S1.length-1;i++)
        T.ch[i] = S1.ch[i];
        T.length = S1.length + S2.length;
        for(int i=0;i<S1.length-1;i++)
        T.ch[i+S1.length] = S1.ch[i];
        return 0;
} // Concat
void get_next(Hstring T, int *next) {  // 算法4.7
  int i=1;
  next[0]=0;
  int j=0;
  while (i<T.length) {
    if(j==0 || T.ch[i-1]== T.ch[j-1]) {
      ++i;  ++j;  next[i-1] = j;
    } else j= next[j-1];
  }
}
int Index_KMP(Hstring S, Hstring T, int pos) {  // 算法4.6
  // 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的
  // KMP算法。其中，T非空，1≤pos≤StrLength(S)。
  int next[255];
  int i = pos;
  int j = 1;
  get_next(T, next);
  while (i <= S.length && j <= T.length) {
    if (j == 0 || S.ch[i-1] == T.ch[j-1]) {  // 继续比较后继字符
      ++i;  ++j;
    } else j = next[j-1]; // 模式串向右移动
  }
  int a=i-T.length;
  if (j > T.length) return  i-T.length;   // 匹配成功
  else return 0;
} // Index_KMP
int main()
{
    Hstring s;
    Hstring t;
    s.ch="0000001";
    t.ch="001";
    s.length=7;
    t.length=3;
    int a=Index_KMP(s,t,2);
    printf("%d",a);
}

