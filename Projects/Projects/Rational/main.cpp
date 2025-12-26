#include <iostream>
#include "Rational.h"
#include "test.h"
using namespace std;
int main()
{
    test t;
    t.runtests();
    return 0;
    char o;
    cout << "Enter a fraction: ";
    Rational r1(0, 1); // Prompt the user for input
    cin >> r1;         // Read two integers from the user
    cout << "Enter another fraction: ";
    Rational r2(0, 1); // Prompt the user for input
    cin >> r2;
    cout << "Enter an operator (+, -, *, /): ";
    cin >> o;          // Prompt the user for an operator
    Rational r3(0, 1); // Initialize r3 to a default value
    if (o == '+')
    {
        r3 = r1 + r2;
    }
    else if (o == '-')
    {
        r3 = r1 - r2;
    }
    else if (o == '*')
    {
        r3 = r1 * r2;
    }
    else if (o == '/')
    {
        r3 = r1 / r2;
    }
    cout << r3;
}