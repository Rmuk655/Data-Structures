#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 100

struct Stack
{
    int top;
    double array[MAX_SIZE];
};

bool isEmpty(struct Stack stack)
{
    return stack.top == -1;
}

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

void push(struct Stack *stack, double item)
{
    if (stack == NULL)
    {
        printf("Stack is not initialized\n");
        return;
    }
    if (stack->top == MAX_SIZE - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    stack->top++;
    stack->array[stack->top] = item;
}

double pop(struct Stack *stack)
{
    if (stack == NULL)
    {
        printf("Stack is not initialized\n");
        return -1;
    }
    if (isEmpty(*stack))
    {
        printf("Stack underflow\n");
        return -1;
    }
    double item = stack->array[stack->top];
    stack->top--;
    return item;
}

double oper(char op, double op1, double op2)
{
    switch (op)
    {
    case '+':
        return op1 + op2;
        break;
    case '-':
        return op1 - op2;
        break;
    case '*':
        return op1 * op2;
        break;
    case '/':
        if (op2 == 0)
        {
            printf("Division by zero error\n");
            return 0;
        }
        return op1 / op2;
        break;
    case '^':
        return pow(op1, op2);
        break;
    default:
        printf("Invalid operator\n");
        return 0;
    }
}

double eval(char str[])
{
    struct Stack stac;
    stac.top = -1;
    int num = strlen(str);
    double op1 = 0, op2 = 0, value = 0;
    for (int i = 0; i < num; i++)
    {
        if (isDigit(str[i]))
        {
            str[i] = str[i] - '0'; // Convert char to int
            push(&stac, str[i]);
        }
        else
        {
            op2 = pop(&stac);
            op1 = pop(&stac);
            value = oper(str[i], op1, op2);
            push(&stac, value);
        }
    }
    return value;
}

void runtestsbasic()
{
    // Test cases to check postfix evaluation
    char test1[] = "23+5*";   // (2 + 3) * 5 = 25
    char test2[] = "34+56-*"; // (3 + 4) * (5 - 6) = -7
    char test3[] = "12+34+*"; // (1 + 2) * (3 + 4) = 21
    char test4[] = "123+*";   // 1 * (2 + 3) = 5
    assert(fabs(eval(test1) - 25.0) < 1e-9);
    assert(fabs(eval(test2) + 7.0) < 1e-9);
    assert(fabs(eval(test3) - 21.0) < 1e-9);
    assert(fabs(eval(test4) - 5.0) < 1e-9);
    printf("Basic tests passed.\n");
}

void runtestsadvanced()
{
    // Advanced test cases for more complex postfix expressions (include division and exponentiation)
    char test1[] = "23^5*";   // (2 ^ 3) * 5 = 40
    char test2[] = "34/56-*"; // (3 / 4) * (5 - 6) = -0.75
    char test3[] = "12-34/*"; // (1 - 2) * (3 / 4) = -0.75
    char test4[] = "123/*";   // 1 * (2 / 3) = 0.67
    char test5[] = "23/";     // 2 / 3 = 0.67
    char test6[] = "23^";     // 2 ^ 3 = 8
    // use asserts to validate the results
    assert(fabs(eval(test1) - 40.0) < 1e-9);
    assert(fabs(eval(test2) + 0.75) < 1e-9);
    assert(fabs(eval(test3) + 0.75) < 1e-9);
    assert(fabs(eval(test4) - 0.6666666666666666666666667) < 1e-9);
    assert(fabs(eval(test5) - 0.6666666666666666666666667) < 1e-9);
    assert(fabs(eval(test6) - 8.0) < 1e-9);
    printf("Advanced tests passed.\n");
}

int main()
{
    char str[MAX_SIZE];
    printf("Enter a postfix string to be evaluated: ");
    scanf("%s", str);
    if (isDigit(str[0]) == 0)
    {
        printf("Wrong syntax for postfix expression\n");
        return 1;
    }
    double val = eval(str);
    printf("The result of the postfix expression is: %.2lf\n", val);
    runtestsbasic();
    runtestsadvanced();
    printf("All tests passed successfully.\n");
    return 0;
}