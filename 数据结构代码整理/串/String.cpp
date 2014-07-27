#include <stdio.h>
#include <stdlib.h>
 typedef struct {
       char *ch;
      // ���Ƿǿմ�,�򰴴�������洢����
       //  ����chΪNULL
      int  length;   // ������
}Hstring;//HeapString.
int StrInsert(Hstring &S, int pos, Hstring T) {  // �㷨4.4
   // 1��pos��StrLength(S)��1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T��
   int i;
   if (pos < 1 || pos > S.length+1)  // pos���Ϸ�
      return 0;
   if (T.length) {    // T�ǿ�,�����·���ռ�,����T
      if (!(S.ch = (char *)realloc(S.ch,(S.length+T.length+1)*sizeof(char))))
         return 0;
      for (i=S.length-1; i>=pos-1; --i)  // Ϊ����T���ڳ�λ��
         S.ch[i+T.length] = S.ch[i];
      for (i=0; i<T.length; i++)         // ����T
         S.ch[pos-1+i] = T.ch[i];
      S.length += T.length;
   }
   return 1;
} // StrInsert
int StrAssign(Hstring t,char *chars){
      //����һ����ֵ���ڴ�����chars�Ĵ�T
      char *c;
      if(t.ch) free(t.ch);
      int i=0;
      c=chars;
      for(; *c ; ++i,++c);    //��chars�ĳ���
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
       // ��T������S1��S2���Ӷ��ɵ��´�
       if (T.ch)  free(T.ch);        // �ͷžɿռ�
      if (!(T.ch = (char *)malloc((S1.length+S2.length)*sizeof(char))))
        exit (0);
        for(int i=0;i<S1.length-1;i++)
        T.ch[i] = S1.ch[i];
        T.length = S1.length + S2.length;
        for(int i=0;i<S1.length-1;i++)
        T.ch[i+S1.length] = S1.ch[i];
        return 0;
} // Concat
void get_next(Hstring T, int *next) {  // �㷨4.7
  int i=1;
  next[0]=0;
  int j=0;
  while (i<T.length) {
    if(j==0 || T.ch[i-1]== T.ch[j-1]) {
      ++i;  ++j;  next[i-1] = j;
    } else j= next[j-1];
  }
}
int Index_KMP(Hstring S, Hstring T, int pos) {  // �㷨4.6
  // ����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�
  // KMP�㷨�����У�T�ǿգ�1��pos��StrLength(S)��
  int next[255];
  int i = pos;
  int j = 1;
  get_next(T, next);
  while (i <= S.length && j <= T.length) {
    if (j == 0 || S.ch[i-1] == T.ch[j-1]) {  // �����ȽϺ���ַ�
      ++i;  ++j;
    } else j = next[j-1]; // ģʽ�������ƶ�
  }
  int a=i-T.length;
  if (j > T.length) return  i-T.length;   // ƥ��ɹ�
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

