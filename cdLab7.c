/*  CD LAB EX.NO:7  COMPUTATION OF LR(0) ITEMS <in canonical collections or states> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
int n,np[27]={0},coli=0;
char in[MAX],pd[27][MAX][MAX];
typedef struct can_col can_col;
typedef struct lr0_item lr0_item;
struct lr0_item
{
    int i,j,dot_pos;
};
struct can_col
{
    int count;
    lr0_item item[MAX];
}col[MAX];
char notin(char key,int di,char *done)
{
    for(int i=0;i<di;i++)
        if (done[i]==key)return 0;
    return 1;
}
char isEqual(can_col x, can_col y)
{
    if(x.count!=y.count)return 0;
        for(int i=0;i<x.count;i++)
            if (x.item[i].i!=y.item[i].i ||x.item[i].j!=y.item[i].j ||x.item[i].dot_pos!=y.item[i].dot_pos )
                return 0;
    return 1;
}
char Collected(can_col x)
{
     for(int i=0;i<coli;i++)
        if (isEqual(x,col[i]))return 1;
    return 0;
}
void closure_goto(int pcoli)
{
    int di=0;
    char done[MAX];
    for(int i=0;i<col[pcoli].count;i++)
    {
        lr0_item x=col[pcoli].item[i];
        char c=pd[x.i][x.j][x.dot_pos];
        if(notin(c,di,done))
        {
        if (isupper(c))
            for(int j=0;j<np[c-'@'];j++)
            {
                lr0_item x={c-'@',j,0};
                col[pcoli].item[col[pcoli].count++]=x;
            }
        done[di++]=c;
        }
    }
if(Collected(col[pcoli])){coli--;return;}
   for(int i=0;i<di;i++)
        {
            can_col temp;
            temp.count=0;
            for(int j=0;j<col[pcoli].count;j++)
            {
                lr0_item x=col[pcoli].item[j];
                if(x.dot_pos<strlen(pd[x.i][x.j])&&done[i]==pd[x.i][x.j][x.dot_pos])
                {
                    temp.item[temp.count]=x;
                    temp.item[temp.count].dot_pos++;
                    temp.count++;
                }
            }
            if(temp.count )
            {
                coli++;
                col[coli]=temp;
                closure_goto(coli);
            }
        }
}
int main()
{
    char parent[1];
    int index;
    can_col f={1,{0,0,0}};
    printf("(Input the Grammar)Enter no.of productions :");
    scanf("%d",&n);
    printf("Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):");
    for(int i=0;i<n;i++){
    scanf("%s",in);
    index=in[0]-'@';
    strcpy(pd[index][np[index]++],in[2]=='#'?"":in+2);
    }
    printf("Enter initial production non-terminal :");
    scanf("%s",parent);
    strcpy(pd[0][np[0]++],parent);
    col[0]=f;
    closure_goto(0);
    for(int i=0;i<=coli;i++)
    {
        printf("\n-----------\nI%d\n-----------\n",i);
        for(int j=0;j<col[i].count;j++)
        {
            lr0_item x=col[i].item[j];
            printf("%c->",x.i+'@');
            for(int k=0;;k++)
                {
                    if(k==x.dot_pos)printf(".");
                    if(!pd[x.i][x.j][k])break;
                    printf("%c",pd[x.i][x.j][k]);
                }
                printf("\n");
        }
    }
    return 0;
}
/*SAMPLE TESTCASE 0:

(Input the Grammar)Enter no.of productions :3
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):S=AA
A=aA
A=b
Enter initial production non-terminal :S

-----------
I0
-----------
@->.S
S->.AA
A->.aA
A->.b

-----------
I1
-----------
@->S.

-----------
I2
-----------
S->A.A
A->.aA
A->.b

-----------
I3
-----------
S->AA.

-----------
I4
-----------
A->a.A
A->.aA
A->.b

-----------
I5
-----------
A->aA.

-----------
I6
-----------
A->b.

Process returned 0 (0x0)   execution time : 12.057 s
Press any key to continue.

SAMPLE TESTCASE 1:

(Input the Grammar)Enter no.of productions :4
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):S=AaA
A=aB
B=AB
B=bb
Enter initial production non-terminal :S

-----------
I0
-----------
@->.S
S->.AaA
A->.aB

-----------
I1
-----------
@->S.

-----------
I2
-----------
S->A.aA

-----------
I3
-----------
S->Aa.A
A->.aB

-----------
I4
-----------
S->AaA.

-----------
I5
-----------
A->a.B
B->.AB
B->.bb
A->.aB

-----------
I6
-----------
A->aB.

-----------
I7
-----------
B->A.B
B->.AB
B->.bb
A->.aB

-----------
I8
-----------
B->AB.

-----------
I9
-----------
B->b.b

-----------
I10
-----------
B->bb.

Process returned 0 (0x0)   execution time : 26.619 s
Press any key to continue.
PROGRAMMED BY SRIVISHNU GCE-SALEM CSE BATCH 2021
*/
