#include <stdio.h>
#include <ctype.h>
#define SIZE 50

char stack[SIZE];
int top=-1;

push(char opnd)
{
    stack[++top]=opnd;
}

char pop()
{
    return(stack[top--]);
}

int pre(char symbol) //for precedence
{
	if(symbol == '$')// highest precedence
	{
		return(3);
	}
	else if(symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if(symbol == '+' || symbol == '-')      // lowest precedence
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void main()
{
    char infix[50],postfix[50],symb,opnd;
    int i=0,k=0;
    printf("Enter Infix Expression : ");
    scanf("%s",infix);
    while( (symb=infix[i++]) != '\0')
    {
        if( symb == '(') push(symb);
        else
            if(isalnum(symb)) postfix[k++]=symb;
            else
                if( symb == ')')
                {
                    while( stack[top] != '(')
                        postfix[k++]=pop();
                    opnd=pop(); // Removing ( from stack
                }
                else
                {
                    while( pre(stack[top]) >= pre(symb) )//for operator
                        postfix[k++]=pop();
                    push(symb);
                }
    }
    while( stack[top] != '\0')  //till stack is empty
        postfix[k++]=pop();
    postfix[k]='\0';  //adding to make string valid
    printf("\nPostfix Expression =  %s\n",postfix);
}

