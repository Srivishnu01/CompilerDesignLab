#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX 50
char in[MAX], nt[MAX],tm[MAX],pd[MAX][MAX],q, A[MAX]={0},fi=0, M[256][256][MAX],done[MAX];
int n,d=0;
char notin(char *arr, char key)
{
    for(int i=0;arr[i];i++)
        if (arr[i]==key)return 0;
    return 1;
}
int first(char key,int ii) //returns 1 if FIRST(key) is epsilon somewhere
{

    int i,ret=0;
  for(i=(ii>=0?ii:0);i<(ii>=0?ii+1:n);i++)
    {
        if(nt[i]==key)
            {
            if(pd[i][0]=='-'){ret=1;continue;}
                for(int j=0;pd[i][j];j++){
if(isupper(pd[i][j]))  { if(first(pd[i][j],-1)){continue;}}
    else if(notin(A,pd[i][j])) printf("%c,",A[fi++]=pd[i][j]);

break;}
}
    }return ret;

}
int follow(char key)
{
    int ret=(key==nt[0]);
    for(int i=0;i<n;i++)
    {
        int j;
        for(j=0;pd[i][j+1];j++)
        {
            if(pd[i][j]==key){do{
                    if(isupper(pd[i][j+1]))
                {if(pd[i][j+1]==nt[0])ret=1;
                    if(first(pd[i][j+1],-1)){
                        if(follow(nt[i]))ret=1;
                            continue;}}
            else if(notin(A,pd[i][j+1]))
                printf("%c,",A[fi++]=pd[i][j+1]);
                break;
            }while(pd[i][++j+1]);
            }
        }
        if(nt[i]!=key&&pd[i][j]==key)if(follow(nt[i]))ret=1;
    }
    return ret;
}

int main()
{
    printf("Enter no. of productions :");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
    scanf("%s",in);
    nt[i]=in[0];
    strcpy(pd[i],in+2);
    }
        printf("\nNON-TERMINAL\t|FIRST\t|\tFOLLOW\t|\n_________________________________________________________________________");
    for(int i=0;q=nt[i];i++)
        {
done[d++]=q;
    printf("\n%c\t\t|{",q);
    if(first(q,i))printf("-");

    printf("}\t|\t{",q);
    if(pd[i][0]!='-')
    for(int j=0;j<fi;j++)
    strcpy(M[q][A[j]],pd[i]);
    fi=0;
    for(int k=0;k<MAX;k++){
        A[k]=0;
    }
    if(follow(q)){printf("%c",A[fi++]='$');}
    printf("}\t");
    if(pd[i][0]=='-')
    {int temp=(q==nt[0]);
        for(int j=0;j<fi;j++)
    {
        strcpy(M[q][A[j]],"-");
    }
    }
    fi=0;
    for(int k=0;k<MAX;k++){
        A[k]=0;
    }
    }
    for(int i=0;i<d;i++)done[i]=0;
d=0;
    printf("\n___________________________________________________________\npp.table");
int ti=0;
    for (int i=0;i<n;i++)
        for(int j=0;pd[i][j];j++)
            if(!isupper(pd[i][j])&&notin(tm,pd[i][j])&&pd[i][j]!='-')
                printf("| %c \t",tm[ti++]=pd[i][j]);
    printf("| %c ",tm[ti++]='$');
    printf("\n_______________________________________________________________");
    for(int i=0;i<n;i++)
        {
            if(!notin(done,nt[i]))continue;
            done[d++]=nt[i];
            printf("\n%c\t",nt[i]);

            for(int j=0;j<ti;j++)   printf("| %s\t",M[nt[i]][tm[j]]);
    }
    return 0;
}

/*Enter no. of productions :8
E=TZ
Z=+TZ
Z=-
T=FY
Y=*FY
Y=-
F=i
F=(E)

NON-TERMINAL    |FIRST  |       FOLLOW  |
_________________________________________________________________________
E               |{i,(,} |       {),$}
Z               |{+,}   |       {),$}
Z               |{-}    |       {),$}
T               |{i,(,} |       {+,),$}
Y               |{*,}   |       {+,),$}
Y               |{-}    |       {+,),$}
F               |{i,}   |       {*,+,),$}
F               |{(,}   |       {*,+,),$}
___________________________________________________________
pp.table| +     | *     | i     | (     | )     | $
_______________________________________________________________
E       |       |       | TZ    | TZ    |       |
Z       | +TZ   |       |       |       | -     | -
T       |       |       | FY    | FY    |       |
Y       | -     | *FY   |       |       | -     | -
F       |       |       | i     | (E)   |       |
Process returned 0 (0x0)   execution time : 14.171 s
Press any key to continue.
*/
