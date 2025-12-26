#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>

using namespace std;

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

node *createNode(int key)
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->data = key;
    head->left = nullptr;
    head->right = nullptr;
    return head;
}

node *insertleft(node *root, int key)
{
    struct node *n = createNode(key);
    root->left = n;
    return n;
}

node *insertright(node *root, int key)
{
    struct node *n = createNode(key);
    root->right = n;
    return n;
}

void printpreorder(node *head)
{
    if (head == nullptr)
    {
        return;
    }
    else
    {
        cout << head->data << " ";
        printpreorder(head->left);
        printpreorder(head->right);
    }
}

void printinorder(node *head)
{
    if (head == nullptr)
    {
        return;
    }
    else
    {
        printinorder(head->left);
        cout << head->data << " ";
        printinorder(head->right);
    }
}

void printpostorder(node *head)
{
    if (head == nullptr)
    {
        return;
    }
    else
    {
        printpostorder(head->left);
        printpostorder(head->right);
        cout << head->data << " ";
    }
}

int search(int key, vector<int> vec)
{
    int n = -1;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == key)
        {
            n = i;
        }
    }
    return n;
}

node *buildtree(vector<int> &preorder, vector<int> &inorder)
{
    if (preorder.size() == 0 && inorder.size() == 0)
    {
        return nullptr;
    }
    int len = preorder.size(), index = search(preorder[0], inorder);
    node *root = createNode(preorder[0]);
    if (preorder.size() == 1 && inorder.size() == 1)
    {
        return root;
    }
    vector<int> preorder_left, preorder_right, inorder_left, inorder_right;
    for (int i = 0; i < index; i++)
    {
        preorder_left.push_back(preorder[i + 1]);
        inorder_left.push_back(inorder[i]);
    }
    for (int i = index; i < preorder.size() - 1; i++)
    {
        preorder_right.push_back(preorder[i + 1]);
        inorder_right.push_back(inorder[i + 1]);
    }
    root->left = buildtree(preorder_left, inorder_left);
    root->right = buildtree(preorder_right, inorder_right);
    return root;
}

string capture_output(void (*print_func)(node *), node *root)
{
    stringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf()); // redirect cout to buffer
    print_func(root);                            // call your print function
    cout.rdbuf(old);                             // restore original cout
    return buffer.str();
}

void test()
{
    // ---- Case 1: Normal Tree ----
    {
        vector<int> preorder = {1, 2, 4, 5, 3, 6};
        vector<int> inorder = {4, 2, 5, 1, 3, 6};
        node *root = buildtree(preorder, inorder);

        assert(capture_output(printpreorder, root) == "1 2 4 5 3 6 ");
        assert(capture_output(printinorder, root) == "4 2 5 1 3 6 ");
        assert(capture_output(printpostorder, root) == "4 5 2 6 3 1 ");
    }

    // ---- Case 2: Empty Tree ----
    {
        vector<int> preorder = {};
        vector<int> inorder = {};
        node *root = buildtree(preorder, inorder);

        assert(capture_output(printpreorder, root) == "");
        assert(capture_output(printinorder, root) == "");
        assert(capture_output(printpostorder, root) == "");
    }

    // ---- Case 3: Single Node Tree ----
    {
        vector<int> preorder = {42};
        vector<int> inorder = {42};
        node *root = buildtree(preorder, inorder);

        assert(capture_output(printpreorder, root) == "42 ");
        assert(capture_output(printinorder, root) == "42 ");
        assert(capture_output(printpostorder, root) == "42 ");
    }

    // ---- Case 4: Left-Skewed Tree ----
    {
        vector<int> preorder = {4, 3, 2, 1};
        vector<int> inorder = {1, 2, 3, 4};
        node *root = buildtree(preorder, inorder);

        assert(capture_output(printpreorder, root) == "4 3 2 1 ");
        assert(capture_output(printinorder, root) == "1 2 3 4 ");
        assert(capture_output(printpostorder, root) == "1 2 3 4 ");
    }

    // ---- Case 5: Right-Skewed Tree ----
    {
        vector<int> preorder = {1, 2, 3, 4};
        vector<int> inorder = {1, 2, 3, 4};
        node *root = buildtree(preorder, inorder);

        assert(capture_output(printpreorder, root) == "1 2 3 4 ");
        assert(capture_output(printinorder, root) == "1 2 3 4 ");
        assert(capture_output(printpostorder, root) == "4 3 2 1 ");
    }

    // ---- Case 6: Search Tests ----
    {
        vector<int> vec = {10, 20, 30, 40, 50};
        assert(search(30, vec) == 2);
        assert(search(10, vec) == 0);
        assert(search(60, vec) == -1);

        vector<int> empty = {};
        assert(search(5, empty) == -1);

        vector<int> dup = {1, 2, 3, 2, 1};
        assert(search(2, dup) == 3); // last match
    }

    cout << "All test cases passed.\n";
}

int main()
{
    test();
    struct node *head;
    int no_of_test_cases, no_of_elements;
    vector<int> preorder, inorder;
    cout << "Enter the number of test cases: ";
    cin >> no_of_test_cases;
    for (int i = 0; i < no_of_test_cases; i++)
    {
        cout << "Enter the number of elements in test case: " << i + 1 << " : ";
        cin >> no_of_elements;
        for (int j = 0; j < no_of_elements; j++)
        {
            int a;
            cin >> a;
            preorder.push_back(a);
        }
        for (int j = 0; j < no_of_elements; j++)
        {
            int b;
            cin >> b;
            inorder.push_back(b);
        }
        head = buildtree(preorder, inorder);
        cout << "\n";
        printpreorder(head);
        cout << "\n";
        printpostorder(head);
        cout << "\n";
        printinorder(head);
        cout << "\n";
        preorder.clear();
        inorder.clear();
    }
    return 0;
}