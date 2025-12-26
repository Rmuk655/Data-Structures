#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//Problem 1: Postfix Expression Evaluation
//The solution uses a stack to evaluate postfix expressions. It processes each character:
//If it's a digit, push it onto the stack
//If it's an operator, pop two operands, perform the operation, and push the result back

#define MAX_SIZE 100

// Stack structure
typedef struct {
    float data[MAX_SIZE];
    int top;
} Stack;

// Initialize stack
void initStack(Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// Push element to stack
void push(Stack* s, float value) {
    if (!isFull(s)) {
        s->data[++s->top] = value;
    }
}

// Pop element from stack
int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[s->top--];
    }
    return -1; // Error case
}

// Check if character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Perform operation
int performOperation(float operand1, float operand2, int operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) return operand1 / operand2;
            else {
                printf("Error: Division by zero\n");
                exit(1);
            }
        case '^':
            return (int)pow(operand1, operand2);
        default:
            return 0;
    }
}

// Evaluate postfix expression
float evaluatePostfix(char* expression) {
    Stack s;
    initStack(&s);

    char* token = strtok(expression, " \t\n");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            int num = atoi(token);
            push(&s, num);
        }
        else if (strlen(token) == 1 && isOperator(token[0])) {
            float b = pop(&s);
            float a = pop(&s);
            int res = performOperation(a, b, token[0]);
            push(&s, res);
        } else {
            printf("Error: Invalid token '%s'\n", token);
            exit(1);
        }

        token = strtok(NULL, " \t\n");
    }

    float result = pop(&s);

    if (!isEmpty(&s)) {
        printf("Error: Too many operands\n");
        exit(1);
    }

    return result;
}

int main() {
    char expression[MAX_SIZE * 2]; // allow room for full line

    while (1) {
        printf("Enter the postfix expression to evaluate:\n");
        if (fgets(expression, sizeof(expression), stdin) == NULL) {
            printf("Error reading input. Exiting.\n");
            break;
        }

        if (strlen(expression) <= 1) continue;  // ignore empty lines

        double result = evaluatePostfix(expression);
        printf("Result is: %f\n\n", result);
    }

    return 0;
}