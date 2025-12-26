#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>

#define RED true
#define BLACK false

using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    bool color;
};

int main()
{
}