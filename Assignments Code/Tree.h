#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>

using namespace std;

struct node
{
    int data;
    // int height;
    struct node *left;
    struct node *right;
    struct node *parent;
};

class Tree
{
private:
    node *root;
    void inorderHelper(node *root, vector<int> &result);

public:
    node *create_node(int key);
    Tree(node *root) : root(root) {};
    void freemem(node *root);
    ~Tree() {};
    vector<int> inorder(node *root);
    void printpreorder(node *node);
    void printinorder(node *node);
    int getheight(node *root);
    int getbalance(node *node);
    node *rotate(node *root, int balance);
    node *search(node *root, int key);
    node *child(node *root);
    node *insert(node *root, int key);
};
#endif