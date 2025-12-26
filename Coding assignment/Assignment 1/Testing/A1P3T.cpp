#include <iostream>
#include <vector>
#include <string>

using namespace std;
#define SIZE_STACK 100

// Using a struct Stack to store it's top element's index + 1.
struct Stack
{
    char arr[SIZE_STACK];
    int top;
};

// Function to check if the Stack is empty or not by checking if it's top value is 0 which means the no of elements in the stack = 0.
bool isEmpty(Stack stack)
{
    if (stack.top == 0)
    {
        return true;
    }
    return false;
}

// Function to check if the Stack is full or not by checking if it's top value is SIZE_STACK which means the no of elements in the stack
// = max no of possible elements in the stack = SIZE_STACK.
bool isFull(Stack stack)
{
    if (stack.top == SIZE_STACK)
    {
        return true;
    }
    return false;
}

// Function to insert an element into the stack.
void Push(Stack &stack, char ele)
{
    // Checking if the stack is full as we cannot any element into a full stack.
    if (isFull(stack))
    {
        cout << "Cannot insert an element into a full stack." << endl;
        return;
    }
    // If the stack is not full, we add the integer ele at the top's position and increase stack.top by 1 as we have added an element to the stack.
    *(stack.arr + stack.top) = ele;
    stack.top++;
}

// Function to delete an element from the stack.
char Pop(Stack &stack)
{
    // Checking if the stack is empty as we cannot remove an element from an empty stack.
    if (isEmpty(stack))
    {
        // cout << "Cannot delete an element from an empty stack." << endl;
        char c = '\0';
        return c; // Returning INT_MIN means that we have got an underflow error.
    }
    // Normal case when the stack is not empty, we decrease stack.top by 1 as we are removing an element.
    char x = *(stack.arr + stack.top - 1);
    stack.top--;
    return x;
}

int prec(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    return 3;
}

bool is_op(Stack stac)
{
    return stac.arr[stac.top - 1] == '+' || stac.arr[stac.top - 1] == '-' || stac.arr[stac.top - 1] == '*' ||
           stac.arr[stac.top - 1] == '/' || stac.arr[stac.top - 1] == '^';
}

string infix_to_postfix(string s)
{
    Stack stac;
    stac.top = 0;
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            ans = ans + s[i];
        }
        else if (s[i] == '(')
        {
            Push(stac, s[i]);
        }
        else if (s[i] == ')')
        {
            while (!isEmpty(stac) && stac.arr[stac.top - 1] != '(')
            {
                ans = ans + Pop(stac);
            }
            Pop(stac);
        }
        else
        {
            while (!isEmpty(stac) && is_op(stac))
            {
                if (prec(stac.arr[stac.top - 1]) > prec(s[i]))
                {
                    ans = ans + Pop(stac);
                }
                else if (prec(stac.arr[stac.top - 1]) == prec(s[i]) && prec(s[i]) != 3)
                {
                    ans = ans + Pop(stac);
                }
                else
                {
                    break;
                }
            }
            Push(stac, s[i]);
        }
    }
    while (!isEmpty(stac))
    {
        ans = ans + Pop(stac);
    }
    return ans;
}

void test()
{
    vector<pair<string, string>> cases = {
        {"a+b", "ab+"},
        {"a+b*c", "abc*+"},
        {"(a+b)*c", "ab+c*"},
        {"a+b*(c^d-e)^(f+g*h)-i", "abcd^e-fgh*+^*+i-"},
        {"a*(b+c)", "abc+*"},
        {"a+b-c", "ab+c-"},
        {"a*(b+c*(d-e))", "abcde-*+*"}};

    for (auto &p : cases)
    {
        string infix = p.first;
        string expected = p.second;
        string result = infix_to_postfix(infix);

        cout << "Infix: " << infix << endl;
        cout << "Postfix (expected): " << expected << endl;
        cout << "Postfix (result):   " << result << endl;

        if (result == expected)
        {
            cout << "✅ Test Passed!" << endl;
        }
        else
        {
            cout << "❌ Test Failed!" << endl;
        }
        cout << "-----------------------" << endl;
    }
    cout << "All Test cases passed" << endl;
}

int main()
{
    test();
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        string s, out;
        cin >> s;
        out = infix_to_postfix(s);
        cout << out << endl;
    }
}