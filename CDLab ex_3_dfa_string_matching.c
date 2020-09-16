#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nt,na,nf,state[100][256]={-1},init,fin[100],cur;
    char alpha[100],string[1000];
    printf("Enter no. of transition states : ");
    scanf("%d",&nt);
    printf("Enter no. of input symbols : ");
    scanf("%d",&na);
    printf("Enter the input symbols :");
    for(int i=0;i<na;i++)
        {getchar();//input enter key
     alpha[i]=getchar();}
    printf("\nKindly enter -1 for having NO TRANSITION \n");
    for(int i=0;i<nt;i++)
        for(int j=0;j<na;j++)
    {
        printf("transition(%d,%c) = ",i,alpha[j]);
        scanf("%d",&state[i][alpha[j]]);
    }
    printf("enter initial state :");scanf("%d",&init);
    printf("enter no. of final states :");scanf("%d",&nf);
    printf("enter final states :");
    for(int i=0;i<nf;i++)scanf("%d",&fin[i]);
    printf("Enter the String to be checked : ");
    scanf("%s",string);
    cur=init;
    for(int i=0;string[i];i++)
    {
        if( (cur=state[cur][string[i]]) == -1 ){
            printf("\nGiven string is REJECTED by DFA");return 0;
        }
    }
    for(int i=0;i<nf;i++)   if(cur==fin[i]) {printf("\nGiven string is ACCEPTED by DFA");return 0;}
    printf("\nGiven string is REJECTED by DFA");
    return 0;
}
