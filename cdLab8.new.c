/*  CD LAB EX.NO:8  CONSTRUCTION OF SLR PARSING TABLE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
int n,np[27]={0},nf[27]={0},coli=0,fi=0, ti=0, ni=0,ri=0;
char in[MAX],pd[27][MAX][MAX], A[MAX]={0}, parent[1],Follow[27][MAX], tm[MAX], nt[MAX], rec[MAX];
typedef struct can_col can_col;
typedef struct lr0_item lr0_item;
typedef struct move move;
struct move
{
    enum type{blank,go_to,shift,reduce,accept} type;
    int val;
    int proj;
}M[MAX][256]={0};
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
int first(char key) //returns 1 if FIRST(key) is epsilon somewhere
{

    int i,ret=0;
  for(i=0;i<np[key-'@'];i++)
    {
            if(pd[key-'@'][i][0]=='\0'){ret=1;continue;}
            for(int j=0;pd[key-'@'][i][j];j++)
            {
                if(isupper(pd[key-'@'][i][j]))
                {
                    if(first(pd[key-'@'][i][j]))continue;
                }
                else if(notin(pd[key-'@'][i][j],fi,A)) printf("%c,",A[fi++]=pd[key-'@'][i][j]);
            break;
            }
    }
    return ret;
}
int follow(char key) //returns 1 if FOLLOW(key) is $ somewhere
{
    rec[ri++]=key;
    int ret=(key==parent[0]);
    for(int k=1;k<27;k++)
    for(int i=0;i<np[k];i++)
    {
        int j;
        for(j=0;pd[k][i][j+1];j++)
        {
            if(pd[k][i][j]==key){
            do{
                if(isupper(pd[k][i][j+1]))
                        {if(first(pd[k][i][j+1]))   continue;}
                else if(notin(pd[k][i][j+1],fi,A))
                    printf("%c,",A[fi++]=pd[k][i][j+1]);
                break;
            }while(pd[k][i][++j+1]);
            if(!pd[k][i][j+1]&&notin(k+'@',ri,rec))if(follow(k+'@'))ret=1;
            }
        }
        if(notin(k+'@',ri,rec)&&pd[k][i][j]==key)if(follow(k+'@'))ret=1;
    }
    return ret;
}
void find_follows()
{
    for(int i=1;i<=26;i++)
    {
        if(!np[i])continue;
        fi=ri=0;
        printf("\nFollow(%c)=",i+'@');
        if(follow(i+'@'))printf("%c",A[fi++]='$');
        nf[i]=fi;
        for(int j=0;j<fi;j++)
        {
            Follow[i][j]=A[j];
        }
    }
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
        if (isEqual(x,col[i]))return i;
    return -1;
}
int closure_goto(int pcoli)
{
    int di=0,ret;
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
    ret=Collected(col[pcoli]);
    if(ret>=0){coli--;return ret;}
   for(int i=0;i<di;i++)
        {
            can_col temp;
            temp.count=0;
            for(int j=0;j<col[pcoli].count;j++)
            {
                lr0_item x=col[pcoli].item[j];
                if(x.dot_pos==strlen(pd[x.i][x.j]))
                {
                    for(int q=0;q<nf[x.i];q++)
                    {
                        char c=Follow[x.i][q];
                        M[pcoli][c].val=x.i;
                        M[pcoli][c].proj=x.j;
                        M[pcoli][c].type=reduce;
                    }
                    }
                else if(done[i]==pd[x.i][x.j][x.dot_pos])
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
                ret=closure_goto(coli);
                M[pcoli][done[i]].val=ret;
                M[pcoli][done[i]].type=isupper(done[i])?go_to:shift;
            }
        }
        return pcoli;
}
int main()
{
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
    find_follows();
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
    M[1]['$'].type=accept;
    printf("\n\t\t\tACTION\t\t\t\t\tGOTO\nI\t");
    for(int k=1;k<27;k++)
        for (int l=0;l<np[k];l++)
        {if(l==0)nt[ni++]=k+'@';
        for(int j=0;pd[k][l][j];j++)
            if(!isupper(pd[k][l][j])&&notin(pd[k][l][j],ti,tm))
                printf("| %c \t",tm[ti++]=pd[k][l][j]);
        } printf("| %c\t",tm[ti++]='$');
    for(int i=0;i<ni;i++)
        printf("| %c \t",nt[i]);
    for(int i=0;i<=coli;i++)
    {
        printf("\n%d\t",i);
        for(int j=0;j<ti;j++)
            switch(M[i][tm[j]].type)
            {
            case shift:
                printf("| S%d\t",M[i][tm[j]].val);
                break;
            case reduce:
                printf("| r%d,%d\t",M[i][tm[j]].val, M[i][tm[j]].proj);
                break;
            case accept:
            	printf("| Acc\t");
            	break;
            default:
                printf("|\t");
            }
        for(int j=0;j<ni;j++)
            if(M[i][nt[j]].type==go_to)
                printf("| %d\t",M[i][nt[j]].val);
            else
                printf("| \t");
    }

    return 0;
}
/*
OUTPUT 0:
(Input the Grammar)Enter no.of productions :6
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):E=E+T
E=T
T=T*F
T=F
F=(E)
F=i
Enter initial production non-terminal :E

Follow(E)=+,),$
Follow(F)=+,),*,$
Follow(T)=+,),*,$
-----------
I0
-----------
@->.E
E->.E+T
E->.T
T->.T*F
T->.F
F->.(E)
F->.i

-----------
I1
-----------
@->E.
E->E.+T

-----------
I2
-----------
E->E+.T
T->.T*F
T->.F
F->.(E)
F->.i

-----------
I3
-----------
E->E+T.
T->T.*F

-----------
I4
-----------
T->T*.F
F->.(E)
F->.i

-----------
I5
-----------
T->T*F.

-----------
I6
-----------
F->(.E)
E->.E+T
E->.T
T->.T*F
T->.F
F->.(E)
F->.i

-----------
I7
-----------
F->(E.)
E->E.+T

-----------
I8
-----------
F->(E).

-----------
I9
-----------
E->T.
T->T.*F

-----------
I10
-----------
T->F.

-----------
I11
-----------
F->i.

                        ACTION                                  GOTO
I       | +     | (     | )     | i     | *     | $     | E     | F     | T
0       |       | S6    |       | S11   |       |       | 1     | 10    | 9
1       | S2    |       |       |       |       | Acc   |       |       |
2       |       | S6    |       | S11   |       |       |       | 10    | 3
3       | r5,0  |       | r5,0  |       | S4    | r5,0  |       |       |
4       |       | S6    |       | S11   |       |       |       | 5     |
5       | r20,0 |       | r20,0 |       | r20,0 | r20,0 |       |       |
6       |       | S6    |       | S11   |       |       | 7     | 10    | 9
7       | S2    |       | S8    |       |       |       |       |       |
8       | r6,0  |       | r6,0  |       | r6,0  | r6,0  |       |       |
9       | r5,1  |       | r5,1  |       | S4    | r5,1  |       |       |
10      | r20,1 |       | r20,1 |       | r20,1 | r20,1 |       |       |
11      | r6,1  |       | r6,1  |       | r6,1  | r6,1  |       |       |
Process returned 0 (0x0)   execution time : 4.296 s
Press any key to continue.


NOTE: r6,1 means reduce move 6th alphabet 'F' non-terminal 2nd production (index starts from 0)==> F->i
Sameway r20,0 means 'T' first production T->T*F

OUTPUT 1:

(Input the Grammar)Enter no.of productions :3
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):S=AA
A=aA
A=bb
Enter initial production non-terminal :S

Follow(A)=a,b,$
Follow(S)=$
-----------
I0
-----------
@->.S
S->.AA
A->.aA
A->.bb

-----------
I1
-----------
@->S.

-----------
I2
-----------
S->A.A
A->.aA
A->.bb

-----------
I3
-----------
S->AA.

-----------
I4
-----------
A->a.A
A->.aA
A->.bb

-----------
I5
-----------
A->aA.

-----------
I6
-----------
A->b.b

-----------
I7
-----------
A->bb.

                        ACTION                                  GOTO
I       | a     | b     | $     | A     | S
0       | S4    | S6    |       | 2     | 1
1       |       |       | Acc   |       |
2       | S4    | S6    |       | 3     |
3       |       |       | r19,0 |       |
4       | S4    | S6    |       | 5     |
5       | r1,0  | r1,0  | r1,0  |       |
6       |       | S7    |       |       |
7       | r1,1  | r1,1  | r1,1  |       |
Process returned 0 (0x0)   execution time : 48.552 s
Press any key to continue.

OUTPUT 2:

(Input the Grammar)Enter no.of productions :8
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):E=TZ
Z=+TZ
Z=#
T=FY
Y=*FY
Y=#
F=i
F=(E)
Enter initial production non-terminal :E

Follow(E)=),$
Follow(F)=*,+,),$
Follow(T)=+,),$
Follow(Y)=+,),$
Follow(Z)=),$
-----------
I0
-----------
@->.E
E->.TZ
T->.FY
F->.i
F->.(E)

-----------
I1
-----------
@->E.

-----------
I2
-----------
E->T.Z
Z->.+TZ
Z->.

-----------
I3
-----------
E->TZ.

-----------
I4
-----------
Z->+.TZ
T->.FY
F->.i
F->.(E)

-----------
I5
-----------
Z->+T.Z
Z->.+TZ
Z->.

-----------
I6
-----------
Z->+TZ.

-----------
I7
-----------
T->F.Y
Y->.*FY
Y->.

-----------
I8
-----------
T->FY.

-----------
I9
-----------
Y->*.FY
F->.i
F->.(E)

-----------
I10
-----------
Y->*F.Y
Y->.*FY
Y->.

-----------
I11
-----------
Y->*FY.

-----------
I12
-----------
F->i.

-----------
I13
-----------
F->(.E)
E->.TZ
T->.FY
F->.i
F->.(E)

-----------
I14
-----------
F->(E.)

-----------
I15
-----------
F->(E).

                        ACTION                                  GOTO
I       | i     | (     | )     | *     | +     | $     | E     | F     | T     | Y     | Z
0       | S12   | S13   |       |       |       |       | 1     | 7     | 2     |       |
1       |       |       |       |       |       | Acc   |       |       |       |       |
2       |       |       | r26,1 |       | S4    | r26,1 |       |       |       |       | 3
3       |       |       | r5,0  |       |       | r5,0  |       |       |       |       |
4       | S12   | S13   |       |       |       |       |       | 7     | 5     |       |
5       |       |       | r26,1 |       | S4    | r26,1 |       |       |       |       | 6
6       |       |       | r26,0 |       |       | r26,0 |       |       |       |       |
7       |       |       | r25,1 | S9    | r25,1 | r25,1 |       |       |       | 8     |
8       |       |       | r20,0 |       | r20,0 | r20,0 |       |       |       |       |
9       | S12   | S13   |       |       |       |       |       | 10    |       |       |
10      |       |       | r25,1 | S9    | r25,1 | r25,1 |       |       |       | 11    |
11      |       |       | r25,0 |       | r25,0 | r25,0 |       |       |       |       |
12      |       |       | r6,0  | r6,0  | r6,0  | r6,0  |       |       |       |       |
13      | S12   | S13   |       |       |       |       | 14    | 7     | 2     |       |
14      |       |       | S15   |       |       |       |       |       |       |       |
15      |       |       | r6,1  | r6,1  | r6,1  | r6,1  |       |       |       |       |
Process returned 0 (0x0)   execution time : 4.142 s
Press any key to continue.



PROGRAMMED BY SRIVISHNU GCE-SALEM CSE BATCH 2021
*/
