#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define RED true
#define BLACK false

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