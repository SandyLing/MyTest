#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    unsigned int Weight;
    unsigned int Parent;
    unsigned int lChild;
    unsigned int rChild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

int LookFor(char *str,char letter,int count);
void OutputWeight(char *Data,int Length,
                  char **WhatLetter,
                  int **Weight,int *Count);
void HuffmanCoding(HuffmanTree *HT,
                   HuffmanCode *HC,
                   int *Weight,
                   int Count);
void Select(HuffmanTree HT,int Count,int *s1,int *s2);
int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    char Data[100];
    char *WhatLetter;
    int *Weight;
    int Count;
    int i;

    printf("Please input the line:");
    /* Example: aaaaaaaaaaaaaabcccccc*/
    scanf("%s",Data);
    printf("\n");

    OutputWeight(Data,strlen(Data),
                 &WhatLetter,
                 &Weight,
                 &Count);

    HuffmanCoding(&HT,&HC,Weight,Count);

    printf(" Letter Weight Code\n");
    for(i=0;i<Count;i++)
    {
        printf(" %c ",WhatLetter[i]);
        printf("%d ",Weight[i]);
        printf("%s\n",HC[i+1]);
    }
    printf("\n");
    getch();
    return 0;
}

void HuffmanCoding(HuffmanTree *HT,
                   HuffmanCode *HC,
                   int *Weight,
                   int Count)
{
    int i;
    int s1,s2;
    int TotalLength;
    HuffmanTree p;
    char* cd;
    unsigned int c;
    unsigned int f;
    int start;

    if(Count<=1) return;
    TotalLength=Count*2-1;
    (*HT)=(HuffmanTree)malloc((TotalLength+1)*sizeof(HTNode));

    p=((*HT)++);
    for(i=1;i<=Count;i++)
    {
        (*HT)[i].Parent=0;
        (*HT)[i].rChild=0;
        (*HT)[i].lChild=0;
        (*HT)[i].Weight=(*Weight);
        Weight++;
    }
    for(i=Count+1;i<=TotalLength;i++)
    {
        (*HT)[i].Weight=0;
        (*HT)[i].Parent=0;
        (*HT)[i].lChild=0;
        (*HT)[i].rChild=0;
    }
    /*///////////////////Create HuffmanTree////////////////*/
    for(i=Count+1;i<=TotalLength;++i)
    {
        Select((*HT),i-1,&s1,&s2);
       (*HT)[s1].Parent=i;
       (*HT)[s2].Parent=i;
       (*HT)[i].lChild=s1;
       (*HT)[i].rChild=s2;
       (*HT)[i].Weight=(*HT)[s1].Weight+(*HT)[s2].Weight;
    }
    /*///////////////////Output Huffman Code///////////////*/
    (*HC)=(HuffmanCode)malloc((Count+1)*sizeof(char*));
    cd=(char*)malloc(Count*sizeof(char));
    cd[Count-1]='\0';
    for(i=1;i<=Count;++i)
    {
        start=Count-1;
        for(c=i,f=(*HT)[i].Parent;f!=0;c=f,f=(*HT)[f].Parent)
        {
            if((*HT)[f].lChild==c)
                cd[--start]='0';
            else
                cd[--start]='1';
            (*HC)[i]=(char*)malloc((Count-start)*sizeof(char));
            strcpy((*HC)[i],&cd[start]);
        }
    }
}
void Select(HuffmanTree HT,int Count,int *s1,int *s2)
/*/(*s1) is smallest,(*s2) is smaller.*/
{
    int i;
    unsigned int temp1=0;
    unsigned int temp2=0;
    unsigned int temp3;
    for(i=1;i<=Count;i++)
    {
        if(HT[i].Parent==0)
        {
            if(temp1==0)
            {
                temp1=HT[i].Weight;
                (*s1)=i;
            }
            else
            {
                if(temp2==0)
                {
                    temp2=HT[i].Weight;
                    (*s2)=i;
                    if(temp2<temp1)
                    {
                        temp3=temp2;
                        temp2=temp1;
                        temp1=temp3;

                        temp3=(*s2);
                        (*s2)=(*s1);
                        (*s1)=temp3;
                    }
                }
                else
                {
                    if(HT[i].Weight<temp1)
                    {
                        temp2=temp1;
                        temp1=HT[i].Weight;

                        (*s2)=(*s1);
                        (*s1)=i;
                    }
                    if(HT[i].Weight>temp1&&HT[i].Weight<temp2)
                    {
                        temp2=HT[i].Weight;
                        (*s2)=i;
                    }
                }
            }
        }
    }
}
ss
int LookFor(char *str,char letter,int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        if(str[i]==letter) return i;
    }
    return -1;
}
void OutputWeight(char *Data,int Length,
                  char **WhatLetter,
                  int **Weight,int *Count)
{
    int i;
    char* Letter=(char*)malloc(Length);
    int* LetterCount=(int *)malloc(Length);
    int AllCount=0;
    int Index;
    int Sum=0;
    float Persent=0;

    for(i=0;i<Length;i++)
    {
        if(i==0)
        {
            Letter[0]=Data[i];
            LetterCount[0]=1;
            AllCount++;
        }
        else
        {
            Index=LookFor(Letter,Data[i],AllCount);
            if(Index==-1)
            {
                Letter[AllCount]=Data[i];
                LetterCount[AllCount]=1;
                AllCount++;
            }
            else
            {
                LetterCount[Index]++;
            }
        }
    }
    for(i=0;i<AllCount;i++)
    {
        Sum=Sum+LetterCount[i];
    }
    (*Weight)=(int*)malloc(AllCount);
    (*WhatLetter)=(char*)malloc(AllCount);

    for(i=0;i<AllCount;i++)
    {
        Persent=(float)LetterCount[i]/(float)Sum;
        (*Weight)[i]=(int)(1000*Persent);
        (*WhatLetter)[i]=Letter[i];
    }
    (*Count)=AllCount;
}
