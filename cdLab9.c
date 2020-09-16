/*  CD LAB EX.NO:9  BOTTOM UP PARSING OF STRINGS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
int n,np[27]={0},nf[27]={0},coli=0,fi=0, ti=0, ni=0,ri=0;
char in[MAX],pd[27][MAX][MAX], A[MAX]={0}, parent[1],Follow[27][MAX], tm[MAX], nt[MAX], rec[MAX];
int stack1[MAX]={0},si=0;
char stack2[MAX];
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
            default:
                printf("|\t");
            }
        for(int j=0;j<ni;j++)
            if(M[i][nt[j]].type==go_to)
                printf("| %d\t",M[i][nt[j]].val);
            else
                printf("| \t");
    }
    {
        move m;
        int i=0;
        printf("\n\nEnter a String to validate :");
        scanf("%s",&in);    strcat(in,"$");
        printf("%s",in);
        m=M[0][in[0]];
        do{
                printf("\nCurrent stack: %d",stack1[0]);
                for(int i=0;i<si;i++)
                printf(",%c,%d",stack2[i],stack1[i+1]);
            switch(m.type)
            {
            case go_to:
                stack1[si]=m.val;
                break;
            case reduce:
                si-=strlen(pd[m.val][m.proj]);
                stack2[si]=m.val+'@';
                m=M[stack1[si]][m.val+'@'];
                si++;
                continue;
            case shift:
                stack2[si]=in[i];
                si++;
                stack1[si]=m.val;
                i++;
                break;
            case accept:
                printf("\nString is accepted.");
                return 0;
            default:
                printf("\nString is rejected");
                return 0;
            }
            m=M[stack1[si]][in[i]];
        }while(in[i]);

    }
    return 0;
}
/*
(Input the Grammar)Enter no.of productions :3
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):S=AA
A=aA
A=b
Enter initial production non-terminal :S

Follow(A)=a,b,$
Follow(S)=$
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

                        ACTION                                  GOTO
I       | a     | b     | $     | A     | S
0       | S4    | S6    |       | 2     | 1
1       |       |       | Acc   |       |       |
2       | S4    | S6    |       | 3     |
3       |       |       | r19,0 |       |
4       | S4    | S6    |       | 5     |
5       | r1,0  | r1,0  | r1,0  |       |
6       | r1,1  | r1,1  | r1,1  |       |

Enter a String to validate :aabb
aabb$
Current stack: 0
Current stack: 0,a,4
Current stack: 0,a,4,a,4
Current stack: 0,a,4,a,4,b,6
Current stack: 0,a,4,a,4,A,6
Current stack: 0,a,4,a,4,A,5
Current stack: 0,a,4,A,4
Current stack: 0,a,4,A,5
Current stack: 0,A,4
Current stack: 0,A,2
Current stack: 0,A,2,b,6
Current stack: 0,A,2,A,6
Current stack: 0,A,2,A,3
Current stack: 0,S,2
Current stack: 0,S,1
String is accepted.
Process returned 0 (0x0)   execution time : 22.880 s
Press any key to continue.

OUTPUT 1:
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
1       |       |       |       |       |       | Acc   |       |       |       |       |       |
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

Enter a String to validate :((i*(i+i*i)))+(i+i)*i+i
((i*(i+i*i)))+(i+i)*i+i$
Current stack: 0
Current stack: 0,(,13
Current stack: 0,(,13,(,13
Current stack: 0,(,13,(,13,i,12
Current stack: 0,(,13,(,13,F,12
Current stack: 0,(,13,(,13,F,7
Current stack: 0,(,13,(,13,F,7,*,9
Current stack: 0,(,13,(,13,F,7,*,9,(,13
Current stack: 0,(,13,(,13,F,7,*,9,(,13,i,12
Current stack: 0,(,13,(,13,F,7,*,9,(,13,F,12
Current stack: 0,(,13,(,13,F,7,*,9,(,13,F,7
Current stack: 0,(,13,(,13,F,7,*,9,(,13,F,7,Y,0
Current stack: 0,(,13,(,13,F,7,*,9,(,13,F,7,Y,8
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,7
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,i,12
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,12
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,*,9
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,*,9,i,12
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,*,9,F,12
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,*,9,F,10
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,*,9,F,10,Y,0
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,*,9,F,10,Y,11
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,Y,9
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,F,7,Y,8
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,T,7
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,T,5
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,T,5,Z,8
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,+,4,T,5,Z,6
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,Z,4
Current stack: 0,(,13,(,13,F,7,*,9,(,13,T,2,Z,3
Current stack: 0,(,13,(,13,F,7,*,9,(,13,E,2
Current stack: 0,(,13,(,13,F,7,*,9,(,13,E,14
Current stack: 0,(,13,(,13,F,7,*,9,(,13,E,14,),15
Current stack: 0,(,13,(,13,F,7,*,9,F,13
Current stack: 0,(,13,(,13,F,7,*,9,F,10
Current stack: 0,(,13,(,13,F,7,*,9,F,10,Y,14
Current stack: 0,(,13,(,13,F,7,*,9,F,10,Y,11
Current stack: 0,(,13,(,13,F,7,Y,9
Current stack: 0,(,13,(,13,F,7,Y,8
Current stack: 0,(,13,(,13,T,7
Current stack: 0,(,13,(,13,T,2
Current stack: 0,(,13,(,13,T,2,Z,8
Current stack: 0,(,13,(,13,T,2,Z,3
Current stack: 0,(,13,(,13,E,2
Current stack: 0,(,13,(,13,E,14
Current stack: 0,(,13,(,13,E,14,),15
Current stack: 0,(,13,F,13
Current stack: 0,(,13,F,7
Current stack: 0,(,13,F,7,Y,14
Current stack: 0,(,13,F,7,Y,8
Current stack: 0,(,13,T,7
Current stack: 0,(,13,T,2
Current stack: 0,(,13,T,2,Z,8
Current stack: 0,(,13,T,2,Z,3
Current stack: 0,(,13,E,2
Current stack: 0,(,13,E,14
Current stack: 0,(,13,E,14,),15
Current stack: 0,F,13
Current stack: 0,F,7
Current stack: 0,F,7,Y,14
Current stack: 0,F,7,Y,8
Current stack: 0,T,7
Current stack: 0,T,2
Current stack: 0,T,2,+,4
Current stack: 0,T,2,+,4,(,13
Current stack: 0,T,2,+,4,(,13,i,12
Current stack: 0,T,2,+,4,(,13,F,12
Current stack: 0,T,2,+,4,(,13,F,7
Current stack: 0,T,2,+,4,(,13,F,7,Y,10
Current stack: 0,T,2,+,4,(,13,F,7,Y,8
Current stack: 0,T,2,+,4,(,13,T,7
Current stack: 0,T,2,+,4,(,13,T,2
Current stack: 0,T,2,+,4,(,13,T,2,+,4
Current stack: 0,T,2,+,4,(,13,T,2,+,4,i,12
Current stack: 0,T,2,+,4,(,13,T,2,+,4,F,12
Current stack: 0,T,2,+,4,(,13,T,2,+,4,F,7
Current stack: 0,T,2,+,4,(,13,T,2,+,4,F,7,Y,15
Current stack: 0,T,2,+,4,(,13,T,2,+,4,F,7,Y,8
Current stack: 0,T,2,+,4,(,13,T,2,+,4,T,7
Current stack: 0,T,2,+,4,(,13,T,2,+,4,T,5
Current stack: 0,T,2,+,4,(,13,T,2,+,4,T,5,Z,8
Current stack: 0,T,2,+,4,(,13,T,2,+,4,T,5,Z,6
Current stack: 0,T,2,+,4,(,13,T,2,Z,4
Current stack: 0,T,2,+,4,(,13,T,2,Z,3
Current stack: 0,T,2,+,4,(,13,E,2
Current stack: 0,T,2,+,4,(,13,E,14
Current stack: 0,T,2,+,4,(,13,E,14,),15
Current stack: 0,T,2,+,4,F,13
Current stack: 0,T,2,+,4,F,7
Current stack: 0,T,2,+,4,F,7,*,9
Current stack: 0,T,2,+,4,F,7,*,9,i,12
Current stack: 0,T,2,+,4,F,7,*,9,F,12
Current stack: 0,T,2,+,4,F,7,*,9,F,10
Current stack: 0,T,2,+,4,F,7,*,9,F,10,Y,5
Current stack: 0,T,2,+,4,F,7,*,9,F,10,Y,11
Current stack: 0,T,2,+,4,F,7,Y,9
Current stack: 0,T,2,+,4,F,7,Y,8
Current stack: 0,T,2,+,4,T,7
Current stack: 0,T,2,+,4,T,5
Current stack: 0,T,2,+,4,T,5,+,4
Current stack: 0,T,2,+,4,T,5,+,4,i,12
Current stack: 0,T,2,+,4,T,5,+,4,F,12
Current stack: 0,T,2,+,4,T,5,+,4,F,7
Current stack: 0,T,2,+,4,T,5,+,4,F,7,Y,11
Current stack: 0,T,2,+,4,T,5,+,4,F,7,Y,8
Current stack: 0,T,2,+,4,T,5,+,4,T,7
Current stack: 0,T,2,+,4,T,5,+,4,T,5
Current stack: 0,T,2,+,4,T,5,+,4,T,5,Z,8
Current stack: 0,T,2,+,4,T,5,+,4,T,5,Z,6
Current stack: 0,T,2,+,4,T,5,Z,4
Current stack: 0,T,2,+,4,T,5,Z,6
Current stack: 0,T,2,Z,4
Current stack: 0,T,2,Z,3
Current stack: 0,E,2
Current stack: 0,E,1
String is accepted.
Process returned 0 (0x0)   execution time : 174.112 s
Press any key to continue.

OUTPUT 2:

(Input the Grammar)Enter no.of productions :5
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):S=ABCd
A=aaBA
B=bAc
C=BAe
A=f
Enter initial production non-terminal :S

Follow(A)=c,e,b,
Follow(B)=a,f,b,
Follow(C)=d,
Follow(S)=$
-----------
I0
-----------
@->.S
S->.ABCd
A->.aaBA
A->.f

-----------
I1
-----------
@->S.

-----------
I2
-----------
S->A.BCd
B->.bAc

-----------
I3
-----------
S->AB.Cd
C->.BAe
B->.bAc

-----------
I4
-----------
S->ABC.d

-----------
I5
-----------
S->ABCd.

-----------
I6
-----------
C->B.Ae
A->.aaBA
A->.f

-----------
I7
-----------
C->BA.e

-----------
I8
-----------
C->BAe.

-----------
I9
-----------
A->a.aBA

-----------
I10
-----------
A->aa.BA
B->.bAc

-----------
I11
-----------
A->aaB.A
A->.aaBA
A->.f

-----------
I12
-----------
A->aaBA.

-----------
I13
-----------
A->f.

-----------
I14
-----------
B->b.Ac
A->.aaBA
A->.f

-----------
I15
-----------
B->bA.c

-----------
I16
-----------
B->bAc.

                        ACTION                                  GOTO
I       | a     | f     | b     | c     | e     | d     | $     | A     | B     | C     | S
0       | S9    | S13   |       |       |       |       |       | 2     |       |       | 1
1       |       |       |       |       |       |       | Acc   |       |       |       |       |
2       |       |       | S14   |       |       |       |       |       | 3     |       |
3       |       |       | S14   |       |       |       |       |       | 6     | 4     |
4       |       |       |       |       |       | S5    |       |       |       |       |
5       |       |       |       |       |       |       | r19,0 |       |       |       |
6       | S9    | S13   |       |       |       |       |       | 7     |       |       |
7       |       |       |       |       | S8    |       |       |       |       |       |
8       |       |       |       |       |       | r3,0  |       |       |       |       |
9       | S10   |       |       |       |       |       |       |       |       |       |
10      |       |       | S14   |       |       |       |       |       | 11    |       |
11      | S9    | S13   |       |       |       |       |       | 12    |       |       |
12      |       |       | r1,0  | r1,0  | r1,0  |       |       |       |       |       |
13      |       |       | r1,1  | r1,1  | r1,1  |       |       |       |       |       |
14      | S9    | S13   |       |       |       |       |       | 15    |       |       |
15      |       |       |       | S16   |       |       |       |       |       |       |
16      | r2,0  | r2,0  | r2,0  |       |       |       |       |       |       |       |

Enter a String to validate :aabfcfbfcfd
aabfcfbfcfd$
Current stack: 0
Current stack: 0,a,9
Current stack: 0,a,9,a,10
Current stack: 0,a,9,a,10,b,14
Current stack: 0,a,9,a,10,b,14,f,13
Current stack: 0,a,9,a,10,b,14,A,13
Current stack: 0,a,9,a,10,b,14,A,15
Current stack: 0,a,9,a,10,b,14,A,15,c,16
Current stack: 0,a,9,a,10,B,14
Current stack: 0,a,9,a,10,B,11
Current stack: 0,a,9,a,10,B,11,f,13
Current stack: 0,a,9,a,10,B,11,A,13
Current stack: 0,a,9,a,10,B,11,A,12
Current stack: 0,A,9
Current stack: 0,A,2
Current stack: 0,A,2,b,14
Current stack: 0,A,2,b,14,f,13
Current stack: 0,A,2,b,14,A,13
Current stack: 0,A,2,b,14,A,15
Current stack: 0,A,2,b,14,A,15,c,16
Current stack: 0,A,2,B,14
Current stack: 0,A,2,B,3
String is rejected
Process returned 0 (0x0)   execution time : 233.595 s
Press any key to continue.

OUTPUT 3:

(Input the Grammar)Enter no.of productions :4
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):S=AbCd
A=aaA
C=Ac
A=#
Enter initial production non-terminal :S

Follow(A)=c,b,
Follow(C)=d,
Follow(S)=$
-----------
I0
-----------
@->.S
S->.AbCd
A->.aaA
A->.

-----------
I1
-----------
@->S.

-----------
I2
-----------
S->A.bCd

-----------
I3
-----------
S->Ab.Cd
C->.Ac
A->.aaA
A->.

-----------
I4
-----------
S->AbC.d

-----------
I5
-----------
S->AbCd.

-----------
I6
-----------
C->A.c

-----------
I7
-----------
C->Ac.

-----------
I8
-----------
A->a.aA

-----------
I9
-----------
A->aa.A
A->.aaA
A->.

-----------
I10
-----------
A->aaA.

                        ACTION                                  GOTO
I       | a     | c     | b     | d     | $     | A     | C     | S
0       | S8    | r1,1  | r1,1  |       |       | 2     |       | 1
1       |       |       |       |       | Acc   |       |       |       |
2       |       |       | S3    |       |       |       |       |
3       | S8    | r1,1  | r1,1  |       |       | 6     | 4     |
4       |       |       |       | S5    |       |       |       |
5       |       |       |       |       | r19,0 |       |       |
6       |       | S7    |       |       |       |       |       |
7       |       |       |       | r3,0  |       |       |       |
8       | S9    |       |       |       |       |       |       |
9       | S8    | r1,1  | r1,1  |       |       | 10    |       |
10      |       | r1,0  | r1,0  |       |       |       |       |

Enter a String to validate :aaaaaaaaabhjnjk
aaaaaaaaabhjnjk$
Current stack: 0
Current stack: 0,a,8
Current stack: 0,a,8,a,9
Current stack: 0,a,8,a,9,a,8
Current stack: 0,a,8,a,9,a,8,a,9
Current stack: 0,a,8,a,9,a,8,a,9,a,8
Current stack: 0,a,8,a,9,a,8,a,9,a,8,a,9
Current stack: 0,a,8,a,9,a,8,a,9,a,8,a,9,a,8
Current stack: 0,a,8,a,9,a,8,a,9,a,8,a,9,a,8,a,9
Current stack: 0,a,8,a,9,a,8,a,9,a,8,a,9,a,8,a,9,a,8
String is rejected
Process returned 0 (0x0)   execution time : 65.913 s
Press any key to continue.


OUTPUT 4:

(Input the Grammar)Enter no.of productions :5
Enter the productions (consider UPPERCASE ALPHABET as non-terminal, epsilon as # symbol, S' as @):S=ABCd
A=aaBA
B=bAc
C=BAe
A=f
Enter initial production non-terminal :S

Follow(A)=c,e,b,
Follow(B)=a,f,b,
Follow(C)=d,
Follow(S)=$
-----------
I0
-----------
@->.S
S->.ABCd
A->.aaBA
A->.f

-----------
I1
-----------
@->S.

-----------
I2
-----------
S->A.BCd
B->.bAc

-----------
I3
-----------
S->AB.Cd
C->.BAe
B->.bAc

-----------
I4
-----------
S->ABC.d

-----------
I5
-----------
S->ABCd.

-----------
I6
-----------
C->B.Ae
A->.aaBA
A->.f

-----------
I7
-----------
C->BA.e

-----------
I8
-----------
C->BAe.

-----------
I9
-----------
A->a.aBA

-----------
I10
-----------
A->aa.BA
B->.bAc

-----------
I11
-----------
A->aaB.A
A->.aaBA
A->.f

-----------
I12
-----------
A->aaBA.

-----------
I13
-----------
A->f.

-----------
I14
-----------
B->b.Ac
A->.aaBA
A->.f

-----------
I15
-----------
B->bA.c

-----------
I16
-----------
B->bAc.

                        ACTION                                  GOTO
I       | a     | f     | b     | c     | e     | d     | $     | A     | B     | C     | S
0       | S9    | S13   |       |       |       |       |       | 2     |       |       | 1
1       |       |       |       |       |       |       | Acc   |       |       |       |       |
2       |       |       | S14   |       |       |       |       |       | 3     |       |
3       |       |       | S14   |       |       |       |       |       | 6     | 4     |
4       |       |       |       |       |       | S5    |       |       |       |       |
5       |       |       |       |       |       |       | r19,0 |       |       |       |
6       | S9    | S13   |       |       |       |       |       | 7     |       |       |
7       |       |       |       |       | S8    |       |       |       |       |       |
8       |       |       |       |       |       | r3,0  |       |       |       |       |
9       | S10   |       |       |       |       |       |       |       |       |       |
10      |       |       | S14   |       |       |       |       |       | 11    |       |
11      | S9    | S13   |       |       |       |       |       | 12    |       |       |
12      |       |       | r1,0  | r1,0  | r1,0  |       |       |       |       |       |
13      |       |       | r1,1  | r1,1  | r1,1  |       |       |       |       |       |
14      | S9    | S13   |       |       |       |       |       | 15    |       |       |
15      |       |       |       | S16   |       |       |       |       |       |       |
16      | r2,0  | r2,0  | r2,0  |       |       |       |       |       |       |       |

Enter a String to validate :aabfcfbfcbfcfed
aabfcfbfcbfcfed$
Current stack: 0
Current stack: 0,a,9
Current stack: 0,a,9,a,10
Current stack: 0,a,9,a,10,b,14
Current stack: 0,a,9,a,10,b,14,f,13
Current stack: 0,a,9,a,10,b,14,A,13
Current stack: 0,a,9,a,10,b,14,A,15
Current stack: 0,a,9,a,10,b,14,A,15,c,16
Current stack: 0,a,9,a,10,B,14
Current stack: 0,a,9,a,10,B,11
Current stack: 0,a,9,a,10,B,11,f,13
Current stack: 0,a,9,a,10,B,11,A,13
Current stack: 0,a,9,a,10,B,11,A,12
Current stack: 0,A,9
Current stack: 0,A,2
Current stack: 0,A,2,b,14
Current stack: 0,A,2,b,14,f,13
Current stack: 0,A,2,b,14,A,13
Current stack: 0,A,2,b,14,A,15
Current stack: 0,A,2,b,14,A,15,c,16
Current stack: 0,A,2,B,14
Current stack: 0,A,2,B,3
Current stack: 0,A,2,B,3,b,14
Current stack: 0,A,2,B,3,b,14,f,13
Current stack: 0,A,2,B,3,b,14,A,13
Current stack: 0,A,2,B,3,b,14,A,15
Current stack: 0,A,2,B,3,b,14,A,15,c,16
Current stack: 0,A,2,B,3,B,14
Current stack: 0,A,2,B,3,B,6
Current stack: 0,A,2,B,3,B,6,f,13
Current stack: 0,A,2,B,3,B,6,A,13
Current stack: 0,A,2,B,3,B,6,A,7
Current stack: 0,A,2,B,3,B,6,A,7,e,8
Current stack: 0,A,2,B,3,C,6
Current stack: 0,A,2,B,3,C,4
Current stack: 0,A,2,B,3,C,4,d,5
Current stack: 0,S,2
Current stack: 0,S,1
String is accepted.
Process returned 0 (0x0)   execution time : 19.551 s
Press any key to continue.

PROGRAMMED BY SRIVISHNU CSE IN GCE-SALEM 2021
*/
