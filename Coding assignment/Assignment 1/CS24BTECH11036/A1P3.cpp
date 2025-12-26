#include <iostream>
#include <vector>
#include <string>

using namespace std;
#define SIZE_STACK 100

// Time complexity = O(n)
// Space complexity = O(n)
// Using a struct Stack to store it's top element's index + 1.
struct Stack
{
    char arr[SIZE_STACK];
    int top;
};

// Function to check if the Stack is empty or not by checking if it's top value is 0 which means the no of elements in the stack = 0.
bool isEmpty(Stack *stack)
{
    if (stack->top == 0)
    {
        return true;
    }
    return false;
}

// Function to check if the Stack is full or not by checking if it's top value is SIZE_STACK which means the no of elements in the
// stack = max no of possible elements in the stack = SIZE_STACK.
bool isFull(Stack *stack)
{
    if (stack->top == SIZE_STACK)
    {
        return true;
    }
    return false;
}

// Function to insert an element into the stack.
void Push(Stack *&stack, char ele)
{
    // Checking if the stack is full as we cannot any element into a full stack.
    if (isFull(stack))
    {
        cout << "Cannot insert an element into a full stack." << endl;
        return;
    }
    // If the stack is not full, we add the integer ele at the top's position and increase stack.top by 1 as we have added an
    // element to the stack.
    *(stack->arr + stack->top) = ele;
    stack->top++;
}

// Function to delete an element from the stack.
char Pop(Stack *&stack)
{
    // Checking if the stack is empty as we cannot remove an element from an empty stack.
    if (isEmpty(stack))
    {
        // cout << "Cannot delete an element from an empty stack." << endl;
        char c = '\0';
        return c; // Returning INT_MIN means that we have got an underflow error.
    }
    // Normal case when the stack is not empty, we decrease stack.top by 1 as we are removing an element.
    char x = *(stack->arr + stack->top - 1);
    stack->top--;
    return x;
}

// This function returns the precedence of a given operator (in char c).
int prec(char c)
{
    // Addition and Subtraction have the least precedence, randomly assigned 1.
    if (c == '+' || c == '-')
    {
        return 1;
    }
    // Multiplication and Division have the second least precedence, randomly assigned 2.
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    // Exponentiation operator is assigned the highest precedence, 3.
    return 3;
}

// This function is used for checking if an operator is present at the top of the stack.
bool is_op(Stack *stac)
{
    return stac->arr[stac->top - 1] == '+' || stac->arr[stac->top - 1] == '-' || stac->arr[stac->top - 1] == '*' ||
           stac->arr[stac->top - 1] == '/' || stac->arr[stac->top - 1] == '^';
}

// This function is used to perform the conversion of an infix expression in string s to a postfix expression.
string infix_to_postfix(string s)
{
    // We create a new Stack which we will use for converting an infix expression to a postfix expression.
    Stack *stac = new Stack();
    // We initialize it's top to 0.
    stac->top = 0;
    // We store the answer in the string ans. So, we initialize it as "" and subsequently append elements to it consecutively.
    string ans = "";
    // We loop through the string s and append the necessary elements in ans.
    for (int i = 0; i < s.length(); i++)
    {
        // If the ith character of s is a lowercase letter (variable name), we append it directly.
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            ans = ans + s[i];
        }
        // If the ith character of s is '(', then we append it to the stac.
        else if (s[i] == '(')
        {
            Push(stac, s[i]);
        }
        // If the ith character of s is ')', then we start popping the stac till we hit '(' indicating we have successfully
        // handled the brackets case.
        else if (s[i] == ')')
        {
            // Popping till we hit '(' and appending the expression enclosed within the () brackets to the ans.
            while (!isEmpty(stac) && stac->arr[stac->top - 1] != '(')
            {
                ans = ans + Pop(stac);
            }
            // Removing the left bracket for we have handled the bracket case.
            Pop(stac);
        }
        // This is the case when s[i] is an operator.
        else
        {
            // If the top element of the stac is an operator too then we have to check for precedence.
            while (!isEmpty(stac) && is_op(stac))
            {
                // If the precedence of the stac.top operator is greater than the precedence of the s[i] operator we Pop the stack
                // and append the elements in it to the string ans.
                if (prec(stac->arr[stac->top - 1]) > prec(s[i]))
                {
                    ans = ans + Pop(stac);
                }
                // If the precedence of the stac.top operator is equal than the precedence of the s[i] operator and s[i] != '^',
                // then we Pop the stack and append the elements in it to the string ans.
                else if (prec(stac->arr[stac->top - 1]) == prec(s[i]) && prec(s[i]) != 3)
                {
                    ans = ans + Pop(stac);
                }
                // Otherwise we break and just push the given operator onto the stack and wait for the stack to unwind further on.
                else
                {
                    break;
                }
            }
            // Pushing the higher precedence operator and waiting for the stack to unwind.
            Push(stac, s[i]);
        }
    }
    // Unwinding the remaining elements present in the stack and adding it to the string ans.
    while (!isEmpty(stac))
    {
        ans = ans + Pop(stac);
    }
    return ans;
}

// // Test function to check if the code's validity.
// void test()
// {
//     vector<pair<string, string>> cases = {
//         {"a+b", "ab+"},
//         {"a+b*c", "abc*+"},
//         {"(a+b)*c", "ab+c*"},
//         {"a+b*(c^d-e)^(f+g*h)-i", "abcd^e-fgh*+^*+i-"},
//         {"a*(b+c)", "abc+*"},
//         {"a+b-c", "ab+c-"},
//         {"a*(b+c*(d-e))", "abcde-*+*"}};

//     for (auto &p : cases)
//     {
//         string infix = p.first;
//         string expected = p.second;
//         string result = infix_to_postfix(infix);

//         cout << "Infix: " << infix << endl;
//         cout << "Postfix (expected): " << expected << endl;
//         cout << "Postfix (result):   " << result << endl;

//         if (result == expected)
//         {
//             cout << "Test Passed!" << endl;
//         }
//         else
//         {
//             cout << "Test Failed!" << endl;
//         }
//     }
// }

int main()
{
    // test();
    // Input the number of test cases k.
    int k;
    cin >> k;
    while (k > 0)
    {
        // Input infix string and postfix string is stored in out and printed on screen.
        string s, out;
        cin >> s;
        out = infix_to_postfix(s);
        cout << out << endl;
        k--;
    }
}