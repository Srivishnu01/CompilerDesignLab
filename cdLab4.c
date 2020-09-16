#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX 50
char in[MAX], nt[MAX],tm[MAX],pd[MAX][MAX],q, firstA[MAX]={0}, followA[MAX]={0},fi=0,fo=0, M[256][256][MAX],done[MAX];
int n,d=0;
char notin(char *arr, char key)
{
    for(int i=0;arr[i];i++)
        if (arr[i]==key)return 0;
    return 1;
}
int first(char key) //returns 1 if FIRST(key) is $ somewhere
{
    int i,ret=0;
  for(i=0;i<n;i++)
    {
        if(nt[i]==key)
            {
            if(pd[i][0]=='$'){ret=1;continue;}
                for(int j=0;pd[i][j];j++){
	if(isupper(pd[i][j]))  { if(first(pd[i][j])) continue;}
    else if(notin(firstA,pd[i][j]))	printf("%c ",firstA[fi++]=pd[i][j]);
		break;}
		}
    }return ret;
}
int follow(char key)
{
    int ret=0;
    for(int i=0;i<n;i++)
    {
        int j;
        for(j=0;pd[i][j+1];j++)
        {
            if(pd[i][j]==key){do{
                    if(isupper(pd[i][j+1]))
                {if(first(pd[i][j+1])) continue;}
            else if(notin(followA,pd[i][j+1]))
                printf("%c ",followA[fo++]=pd[i][j+1]);
                break;
            }while(pd[i][++j+1]);
            }
        }
        if(nt[i]!=key&&pd[i][j]==key)follow(nt[i]);
    }
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
            if(!notin(done,q))continue;
done[d++]=q;
    printf("\n%c\t\t|{",q);
    first(q);
    printf("}\t|\t{",q);
    if(pd[i][0]!='$')
    for(int j=0;j<fi;j++)
    strcpy(M[nt[i]][firstA[j]],pd[i]);

    follow(q);
    printf("}\t");
    if(pd[i][0]=='$')
    for(int j=0;j<fo;j++)
    strcpy(M[nt[i]][followA[j]],pd[i]);
    fi=fo=0;
    for(int k=0;k<MAX;k++){
        firstA[k]=followA[k]=0;
    }
    }
    for(int i=0;i<d;i++)done[i]=0;
d=0;
    printf("\n___________________________________________________________\npp.table");
int ti=0;
    for (int i=0;i<n;i++)
        for(int j=0;pd[i][j];j++)
            if(!isupper(pd[i][j])&&notin(tm,pd[i][j]))
                printf("| %c \t",tm[ti++]=pd[i][j]);
    printf("\n_______________________________________________________________");
    for(int i=0;i<n;i++)
        {
            if(!notin(done,nt[i]))continue;
            done[d++]=nt[i];
            printf("\n%c\t",nt[i]);
            strcpy(M['A']['h'],"hi");
            for(int j=0;j<ti;j++)   printf("| %s\t",M[nt[i]][tm[j]]);
    }
    return 0;
}
