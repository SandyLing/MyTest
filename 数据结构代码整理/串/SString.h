#include <stdio.h>
#include <stdlib.h>
#define  MAXSTRLEN  255 //用户可在255以内定义最大串长
typedef unsigned char  SString[MAXSTRLEN + 1];// 0号单元存放串的长度
int Concat(SString &T, SString S1, SString S2) { // 算法4.2
   // 用T返回由S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE。
   int i;
   int uncut;
   if (S1[0]+S2[0] <= MAXSTRLEN) {  // 未截断
      for (i=1; i<=S1[0]; i++) T[i] = S1[i];
      for (i=1; i<=S2[0]; i++) T[i+S1[0]] = S2[i];
      T[0] = S1[0]+S2[0];
      uncut = 1;
   } else if (S1[0] < MAXSTRLEN) {  // 截断
      for (i=1; i<=S1[0]; i++) T[i] = S1[i];
      for (i=S1[0]+1; i<=MAXSTRLEN; i++) T[i] = S2[i-S1[0]];
      T[0] = MAXSTRLEN;
      uncut = 0;
   } else {                         // 截断(仅取S1)
      for (i=0; i<=MAXSTRLEN; i++) T[i] = S1[i];
      uncut = 0;
   }
   return uncut;
} // Concat
int SubString(SString &Sub, SString S, int pos, int len) {
   // 算法4.3
   // 用Sub返回串S的第pos个字符起长度为len的子串。
   // 其中，1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1。
   int i;
   if (pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1)
      return 0;
   for(i=1; i<=len; i++)
      Sub[i] = S[pos+i-1];
   Sub[0] = len;
   return 1;
} // SubString
int Index(SString S, SString T, int pos) {  // 算法4.1
   // T为非空串。若主串S中第pos个字符之后存在与T相等的子串，
   // 则返回第一个这样的子串在S中的位置，否则返回0
   int n,m,i;
   SString sub;
   if (pos > 0) {
      n = StrLength(S);
      m = StrLength(T);
      i = pos;
      while (i <= n-m+1) {
         SubString (sub, S, i, m);
         if (StrCompare(sub,T) == 0) ++i;
         else return i;
      } // while
   } // if
   return 0;
}
int Index(SString S, SString T, int pos) {  // 算法4.5
   // 返回子串T在主串S中第pos个字符之后的位置。
   // 若不存在，则函数值为0。
   // 其中，T非空，1≤pos≤StrLength(S)。
   int i = pos;
   int j = 1;
   while (i <= S[0] && j <= T[0]) {
      if (S[i] == T[j]) {  // 继续比较后继字符
         ++i;
         ++j;
      } else {  // 指针后退重新开始匹配
         i = i-j+2;
         j = 1;
      }
   }
   if (j > T[0]) return i-T[0];
   else return 0;
} // Index
