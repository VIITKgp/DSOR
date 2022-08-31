#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include<math.h>

char stack[50]; //initializing stack
int top=-1;

push(char stack[],char opnd)
{
    stack[++top]=opnd;
}

char pop(char stack[])
{
    return(stack[top--]);
}


//function for evaluating postfix expression
int evaluatePostfix(char* exp)
{
    // Scan all characters one by one
    int i;
    for (i = 0; exp[i]; ++i)
    {
        // If the scanned character is an operand,push it into stack
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');

        // If the scanned character is an operator, pop two values
        else
        {
            int opnd2 = pop(stack);
            int opnd1 = pop(stack);
            switch (exp[i])
            {
            case '+': push(stack, opnd1 + opnd2); break;
            case '-': push(stack, opnd1 - opnd2); break;
            case '*': push(stack, opnd1 * opnd2); break;
            case '/': push(stack, opnd1/opnd2); break;
            case '$': push(stack, pow(opnd1,opnd2)); break;
            }
        }
    }
    return pop(stack);
}

int main()
{
    printf("Enter Postfix Expression : ");
    char exp[] ={0};
    scanf("%s",exp);
    printf ("Postfix evaluation: %d", evaluatePostfix(exp));
    return 0;
}

