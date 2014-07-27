#include <stdio.h>
#include <stdlib.h>
#define  MAXSTRLEN  255 //�û�����255���ڶ�����󴮳�
typedef unsigned char  SString[MAXSTRLEN + 1];// 0�ŵ�Ԫ��Ŵ��ĳ���
int Concat(SString &T, SString S1, SString S2) { // �㷨4.2
   // ��T������S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�TRUE������FALSE��
   int i;
   int uncut;
   if (S1[0]+S2[0] <= MAXSTRLEN) {  // δ�ض�
      for (i=1; i<=S1[0]; i++) T[i] = S1[i];
      for (i=1; i<=S2[0]; i++) T[i+S1[0]] = S2[i];
      T[0] = S1[0]+S2[0];
      uncut = 1;
   } else if (S1[0] < MAXSTRLEN) {  // �ض�
      for (i=1; i<=S1[0]; i++) T[i] = S1[i];
      for (i=S1[0]+1; i<=MAXSTRLEN; i++) T[i] = S2[i-S1[0]];
      T[0] = MAXSTRLEN;
      uncut = 0;
   } else {                         // �ض�(��ȡS1)
      for (i=0; i<=MAXSTRLEN; i++) T[i] = S1[i];
      uncut = 0;
   }
   return uncut;
} // Concat
int SubString(SString &Sub, SString S, int pos, int len) {
   // �㷨4.3
   // ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���
   // ���У�1��pos��StrLength(S)��0��len��StrLength(S)-pos+1��
   int i;
   if (pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1)
      return 0;
   for(i=1; i<=len; i++)
      Sub[i] = S[pos+i-1];
   Sub[0] = len;
   return 1;
} // SubString
int Index(SString S, SString T, int pos) {  // �㷨4.1
   // TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���
   // �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0
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
int Index(SString S, SString T, int pos) {  // �㷨4.5
   // �����Ӵ�T������S�е�pos���ַ�֮���λ�á�
   // �������ڣ�����ֵΪ0��
   // ���У�T�ǿգ�1��pos��StrLength(S)��
   int i = pos;
   int j = 1;
   while (i <= S[0] && j <= T[0]) {
      if (S[i] == T[j]) {  // �����ȽϺ���ַ�
         ++i;
         ++j;
      } else {  // ָ��������¿�ʼƥ��
         i = i-j+2;
         j = 1;
      }
   }
   if (j > T[0]) return i-T[0];
   else return 0;
} // Index
