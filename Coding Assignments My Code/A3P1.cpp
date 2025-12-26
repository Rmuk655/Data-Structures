#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>

#define MAX 10
#define MIN 0

using namespace std;

struct BTreeNode
{
    int key[MAX + 1], count;
    /* count stores the number of keys in the current node */
    struct BTreeNode *children[MAX + 1];
};

int main()
{
}