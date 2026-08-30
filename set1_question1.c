#include <stdio.h>
#include <string.h>

#define N 256
char st[N]; int top=-1;

int pr(char c){return c=='/'||c=='*'?2:c=='+'||c=='-'?1:0;}

void push(char c){st[++top]=c;}
char pop(){return st[top--];}
char peek(){return top<0?0:st[top];}

int conv(char *in, char *out){
    int i=0,j=0,op=1;
    while(in[i]){
        char c=in[i++];
        if(c==' ') continue;
        if(c>='0'&&c<='9'){ if(!op){puts("Invalid expression"); return 0;} out[j++]=c; op=0; }
        else if(c=='('){ if(!op){puts("Invalid expression"); return 0;} push(c); }
        else if(c==')'){
            if(op){puts("Invalid expression"); return 0;}
            while(top>=0 && peek()!='(') out[j++]=pop();
            if(top<0){puts("Invalid expression"); return 0;}
            pop(); op=0;
        }
        else if(c=='+'||c=='-'||c=='*'||c=='/'){
            if(op){puts("Invalid expression"); return 0;}
            while(top>=0 && peek()!='(' && pr(peek())>=pr(c)) out[j++]=pop();
            push(c); op=1;
        }
        else {printf("Invalid character: %c\n",c); return 0;}
    }
    if(op){puts("Invalid expression"); return 0;}
    while(top>=0){ if(peek()=='('){puts("Invalid expression"); return 0;} out[j++]=pop(); }
    out[j]='\0'; return 1;
}

int main(){
    char in[N], out[N];
    printf("Enter infix expression: ");
    fgets(in,N,stdin);
    in[strcspn(in,"\r\n")]='\0';
    if(!conv(in,out)) return 1;
    printf("Postfix: %s\n",out);
    return 0;
}
