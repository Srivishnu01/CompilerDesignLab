/*  CD LAB EX.NO:10  INTERMEDIATE CODE GENERATION FOR ARITHMETIC EXPRESSION*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef struct move move;
struct move
{
    enum type{blank=0,go_to,shift,reduce,accept} type;
    int val;
    int proj;
}M[MAX][256]={0};
int main()
{
    char in[MAX];
    int stack1[MAX]={0},si=0;
    char stack2[MAX];
    /*E=E+T
E=T
T=T*F
T=F
F=i
F=(E)

COPY THIS PRODUCTION STRING LENGTH TO len[][]*/
int len[27][2]={0};
len[5][0]=3;
len[5][1]=1;
len[20][0]=3;
len[20][1]=1;
len[6][0]=1;
len[6][1]=3;
    /*                       ACTION                                  GOTO
I       | + -   | i     | (     | )     | * / % | $     | E     | F     | T
0       |       | S6    | S7    |       |       |       | 1     | 11    | 10
1       | S2    |       |       |       |       | Acc   |       |       |
2       |       | S6    | S7    |       |       |       |       | 11    | 3
3       | r5,0  |       |       | r5,0  | S4    | r5,0  |       |       |
4       |       | S6    | S7    |       |       |       |       | 5     |
5       | r20,0 |       |       | r20,0 | r20,0 | r20,0 |       |       |
6       | r6,0  |       |       | r6,0  | r6,0  | r6,0  |       |       |
7       |       | S6    | S7    |       |       |       | 8     | 11    | 10
8       | S2    |       |       | S9    |       |       |       |       |
9       | r6,1  |       |       | r6,1  | r6,1  | r6,1  |       |       |
10      | r5,1  |       |       | r5,1  | S4    | r5,1  |       |       |
11      | r20,1 |       |       | r20,1 | r20,1 | r20,1 |       |       |
COPY THIS PARSING TABLE TO M[][]
*/

    M[0]['i'].type=M[2]['i'].type=M[4]['i'].type=M[7]['i'].type=M[0]['('].type=M[2]['('].type=M[4]['('].type=M[7]['('].type
=M[1]['+'].type=M[1]['-'].type=M[8]['+'].type=M[8]['-'].type=M[8][')'].type=M[3]['*'].type=M[3]['/'].type=M[10]['*'].type=M[3]['%'].type=M[10]['%'].type=M[10]['/'].type=shift;

M[3]['+'].type=M[3]['-'].type=M[5]['+'].type=M[6]['+'].type=M[9]['+'].type=M[10]['+'].type=M[11]['+'].type=M[5]['-'].type=M[6]['-'].type
=M[9]['-'].type=M[10]['-'].type=M[11]['-'].type=M[3][')'].type=M[5][')'].type=M[6][')'].type=M[9][')'].type=M[10][')'].type=M[11][')'].type
=M[5]['*'].type=M[6]['*'].type=M[9]['*'].type=M[11]['*'].type=M[5]['/'].type=M[6]['/'].type=M[9]['/'].type=M[11]['/'].type
=M[3]['$'].type=M[5]['$'].type=M[6]['$'].type=M[9]['$'].type=M[10]['$'].type=M[11]['$'].type=M[5]['%'].type=M[6]['%'].type=M[9]['%'].type=M[11]['%'].type=reduce;

M[0]['E'].type=M[0]['F'].type=M[0]['T'].type=M[2]['F'].type=M[2]['T'].type=M[4]['F'].type=M[7]['E'].type=M[7]['F'].type=M[7]['T'].type=go_to;
M[1]['$'].type=accept;

M[1]['+'].val=2;    M[1]['-'].val=2;	M[3]['+'].val=5;	M[3]['+'].proj=0;   M[3]['-'].val=5;	M[3]['-'].proj=0;	M[5]['+'].val=20;	M[5]['+'].proj=0;   M[5]['-'].val=20;	M[5]['-'].proj=0;
M[6]['+'].val=6;	M[6]['+'].proj=0;   M[6]['-'].val=6;	M[6]['-'].proj=0;	M[8]['+'].val=2;    M[8]['-'].val=2;
M[9]['+'].val=6;	M[9]['-'].proj=1; 	M[10]['+'].val=5; 	M[10]['-'].proj=1;	M[11]['+'].val=20;	M[11]['-'].proj=1;
M[9]['-'].val=6;	M[9]['+'].proj=1; 	M[10]['-'].val=5; 	M[10]['+'].proj=1;	M[11]['-'].val=20;	M[11]['+'].proj=1;

M[0]['i'].val=6;	M[2]['i'].val=6;	M[4]['i'].val=6;	M[7]['i'].val=6;

M[0]['('].val=7;	M[2]['('].val=7;	M[4]['('].val=7;	M[7]['('].val=7;

M[3][')'].val=5;	M[3][')'].proj=0;	M[5][')'].val=20;	M[5][')'].proj=0;	M[6][')'].val=6;	M[6][')'].proj=0;	M[8][')'].val=9;	M[9][')'].val=6;
M[9][')'].proj=1;	M[10][')'].val=5;	M[10][')'].proj=1;	M[11][')'].val=20;	M[11][')'].proj=1;

M[3]['*'].val=4;    M[3]['/'].val=4;	M[5]['*'].val=20;	M[5]['*'].proj=0;   M[5]['/'].val=20;	M[5]['/'].proj=0;	M[6]['*'].val=6;	M[6]['/'].proj=0;	M[9]['*'].val=6;	M[9]['/'].proj=1;	M[10]['*'].val=4;
M[11]['*'].val=20;	M[11]['/'].proj=1;  M[6]['/'].val=6;	M[6]['*'].proj=0;	M[9]['/'].val=6;	M[9]['*'].proj=1;	M[11]['/'].val=20;	M[11]['*'].proj=1;  M[10]['/'].val=4;
M[3]['%'].val=4;    M[5]['%'].val=20;	M[5]['%'].proj=0;  	M[6]['%'].val=6;	M[9]['%'].val=6;	M[10]['%'].val=4;
M[11]['%'].val=20;	M[6]['%'].proj=0;	M[9]['%'].proj=1;	M[11]['%'].proj=1;

M[3]['$'].val=5;	M[3]['$'].proj=0;	M[5]['$'].val=20;	M[5]['$'].proj=0;	M[6]['$'].val=6;	M[6]['$'].proj=0;	M[9]['$'].val=6;
M[9]['$'].proj=1;	M[10]['$'].val=5;	M[10]['$'].proj=1;	M[11]['$'].val=20;	M[11]['$'].proj=1;

M[0]['E'].val=1;	M[7]['E'].val=8;

M[0]['F'].val=11;	M[2]['F'].val=11;	M[4]['F'].val=5;	M[7]['F'].val=11;

M[0]['T'].val=10;	M[2]['T'].val=3;	M[7]['T'].val=10;

        move m;
        int i=0;
        printf("Enter an arithmetic expression using only lower cases,(),+,-,*,/,%% : ");
        scanf("%s",in);    strcat(in,"$");
        for(int i=0;in[i];i++)
        {
            printf("%c",in[i]);
            if(islower(in[i]))
            {
                M[0][in[i]].type=M[2][in[i]].type=M[4][in[i]].type=M[7][in[i]].type=shift;
                M[0][in[i]].val=M[2][in[i]].val=M[4][in[i]].val=M[7][in[i]].val=6;
            }
        }
        m=M[0][in[0]];
        do{
            switch(m.type)
            {
            case go_to:
                stack1[si]=m.val;
                break;
            case reduce:
                {
                    printf("\n");
                    if(m.val==5)
                    {
                        if(m.proj==0)
                            switch(stack2[si-2])
                            {
                                case '+':
                                    printf("ADD R2,R1");break;
                                case '-':
                                    printf("SUB R2,R1");break;
                            }
                        else
                            printf("MOV R2,R1");
                    }
                    else if(m.val==6)
                    {
                        if(m.proj==0)
                            printf("MVI R0,%c",stack2[si-1]);
                        else
                            printf("MOV R0,R2");
                    }
                    else if(m.val==20)
                    {
                        if(m.proj==0)
                            switch(stack2[si-2])
                            {
                                case '*':
                                    printf("MUL R1,R0");break;
                                case '/':
                                    printf("DIV R1,R0");break;
                                case '%':
                                    printf("MOD R1,R0");break;
                            }
                        else
                            printf("MOV R1,R0");
                    }
                }
                si-=len[m.val][m.proj];
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
                printf("\nMOV R0,R2\nSUCCESS, Evaluation result is stored in R0.");
                return 0;
            default:
                printf("\nInvalid arithmetic expression");
                return 0;
            }
            m=M[stack1[si]][in[i]];
        }while(in[i]);
    return 0;
}
/*
OUTPUT 0:

Enter an arithmetic expression using only lower cases,(),+,-,*,/,% : a-b%c+d*e/a
a-b%c+d*e/a$
MVI R0,a
MOV R1,R0
MOV R2,R1
MVI R0,b
MOV R1,R0
MVI R0,c
MOD R1,R0
SUB R2,R1
MVI R0,d
MOV R1,R0
MVI R0,e
MUL R1,R0
MVI R0,a
DIV R1,R0
ADD R2,R1
MOV R0,R2
SUCCESS, Evaluation result is stored in R0.
Process returned 0 (0x0)   execution time : 68.940 s
Press any key to continue.

OUTPUT 1:

Enter an arithmetic expression using only lower cases,(),+,-,*,/,% : a+b-c%k--i
a+b-c%k--i$
MVI R0,a
MOV R1,R0
MOV R2,R1
MVI R0,b
MOV R1,R0
ADD R2,R1
MVI R0,c
MOV R1,R0
MVI R0,k
MOD R1,R0
SUB R2,R1
Invalid arithmetic expression
Process returned 0 (0x0)   execution time : 26.163 s
Press any key to continue.

OUTPUT 2:

Enter an arithmetic expression using only lower cases,(),+,-,*,/,% : (a+b*c)/(b*a+c/d)%a-(y-((x+y)*z))
(a+b*c)/(b*a+c/d)%a-(y-((x+y)*z))$
MVI R0,a
MOV R1,R0
MOV R2,R1
MVI R0,b
MOV R1,R0
MVI R0,c
MUL R1,R0
ADD R2,R1
MOV R0,R2
MOV R1,R0
MVI R0,b
MOV R1,R0
MVI R0,a
MUL R1,R0
MOV R2,R1
MVI R0,c
MOV R1,R0
MVI R0,d
DIV R1,R0
ADD R2,R1
MOV R0,R2
DIV R1,R0
MVI R0,a
MOD R1,R0
MOV R2,R1
MVI R0,y
MOV R1,R0
MOV R2,R1
MVI R0,x
MOV R1,R0
MOV R2,R1
MVI R0,y
MOV R1,R0
ADD R2,R1
MOV R0,R2
MOV R1,R0
MVI R0,z
MUL R1,R0
MOV R2,R1
MOV R0,R2
MOV R1,R0
SUB R2,R1
MOV R0,R2
MOV R1,R0
SUB R2,R1
MOV R0,R2
SUCCESS, Evaluation result is stored in R0.
Process returned 0 (0x0)   execution time : 132.076 s
Press any key to continue.

OUTPUT 3:

Enter an arithmetic expression using only lower cases,(),+,-,*,/,% : (a+b)*c)
(a+b)*c)$
MVI R0,a
MOV R1,R0
MOV R2,R1
MVI R0,b
MOV R1,R0
ADD R2,R1
MOV R0,R2
MOV R1,R0
MVI R0,c
MUL R1,R0
MOV R2,R1
Invalid arithmetic expression
Process returned 0 (0x0)   execution time : 15.971 s
Press any key to continue.

PROGRAMMED BY SRIVISHNU CSE-GCE SALEM BATCH 2021
*/
