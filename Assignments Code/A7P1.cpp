#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <cmath>

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

Node *create_new_node(Node *ext_1, Node *ext_2, int key)
{
    Node *root = (Node *)malloc(sizeof(Node));
    if (!root)
    {
        cerr << "Memory allocation failed for root!" << endl;
        exit(1);
    }
    root->data = key;
    root->left = ext_1;
    root->right = ext_2;
    root->parent = nullptr;
    root->color = RED;
    // Red node is represented by the numerical value 1 while black nodes are represented by the numerical value 0.
    return root;
}

Node *create_ext_node()
{
    Node *root = (Node *)malloc(sizeof(Node));
    if (!root)
    {
        cerr << "Memory allocation failed for root!" << endl;
        exit(1);
    }
    root->data = INT_MIN;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    root->color = BLACK;
    // In theory, external (NIL) nodes are not real nodes, so they are said to be uncolored.
    // But for defining black-height and ensuring balance, they're treated as black.
    return root;
}

bool is_ext_node(Node *node)
{
    if (node->data == INT_MIN && node->color == BLACK)
    {
        return 1;
    }
    return 0;
}

void printpreorder(Node *root)
{
    if (root == nullptr || is_ext_node(root))
    {
        return;
    }
    else
    {
        cout << root->data << " ";
        printpreorder(root->left);
        printpreorder(root->right);
    }
}

void printinorder(Node *root)
{
    if (root == nullptr || is_ext_node(root))
    {
        return;
    }
    else
    {
        printinorder(root->left);
        cout << root->data << " ";
        printinorder(root->right);
    }
}

Node *search(Node *root, int key)
{
    if (root == nullptr)
    {
        // cout << "Key not found!" << endl;
        return nullptr;
    }
    if (root->data == key)
    {
        // cout << "Found" << endl;
        return root;
    }
    else if (root->data > key)
    {
        return search(root->left, key);
    }
    else
    {
        return search(root->right, key);
    }
}

// int black_depth(Node *node)
// {
//     int d = 0;
//     while (node->parent != nullptr)
//     {
//         if (node->parent->color == BLACK)
//         {
//             d++;
//         }
//     }
//     return d;
// }

bool child_dir(Node *root)
{
    if (root == nullptr)
    {
        cout << "Node is nullptr" << endl;
        return 0;
    }
    else if (root->parent == nullptr)
    {
        cout << "Node is the root of the tree" << endl;
        return 0;
    }
    if (root->parent->left == root)
    {
        return 0;
    }
    return 1;
}

Node *rotate_RB(Node *grandparent, Node *parent, Node *child)
{
    Node *root = grandparent;
    if (grandparent->left == parent && parent->left == child)
    {
        grandparent->left = parent->right;
        parent->right = grandparent;

        parent->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = parent;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = parent;
        }
        grandparent->parent = parent;
        grandparent->left->parent = grandparent;

        root = parent;
    }
    else if (grandparent->right == parent && parent->right == child)
    {
        grandparent->right = parent->left;
        parent->left = grandparent;

        parent->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = parent;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = parent;
        }
        grandparent->parent = parent;
        grandparent->right->parent = grandparent;

        root = parent;
    }
    else if (grandparent->left == parent && parent->right == child)
    {
        if (child == nullptr)
        {
            cout << "Child is null" << endl;
            return nullptr;
        }
        grandparent->left = child;
        parent->right = child->left;
        child->left = parent;

        child->parent = grandparent;
        parent->parent = child;
        parent->right->parent = parent;

        grandparent->left = child->right;
        if (child->right != nullptr)
        {
            child->right->parent = grandparent;
        }
        child->right = grandparent;

        child->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = child;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = child;
        }
        grandparent->parent = child;

        root = child;
    }
    else if (grandparent->right == parent && parent->left == child)
    {
        if (child == nullptr)
        {
            cout << "Child is null" << endl;
            return nullptr;
        }
        grandparent->right = child;
        parent->left = child->right;
        child->right = parent;

        child->parent = grandparent;
        parent->parent = child;
        parent->left->parent = parent;

        grandparent->right = child->left;
        if (child->left != nullptr)
        {
            child->left->parent = grandparent;
        }
        child->left = grandparent;

        child->parent = grandparent->parent;
        if (grandparent->parent != nullptr && grandparent->parent->left == grandparent)
        {
            grandparent->parent->left = child;
        }
        else if (grandparent->parent != nullptr)
        {
            grandparent->parent->right = child;
        }
        grandparent->parent = child;

        root = child;
    }
    return root;
}

Node *gethead(Node *node)
{
    if (node == nullptr)
    {
        cout << "Node is nullptr" << endl;
        return node;
    }
    else if (node->parent == nullptr)
    {
        return node;
    }
    return gethead(node->parent);
}

Node *insert(Node *root, int key)
{
    if (search(root, key))
    {
        cout << key << " already present. So no need to insert." << endl;
        return root;
    }
    if (root == nullptr)
    {
        Node *ext_1 = create_ext_node(), *ext_2 = create_ext_node();
        root = create_new_node(ext_1, ext_2, key);
        root->color = BLACK; // Root is always colored black
        ext_1->parent = root;
        ext_2->parent = root;
        return root;
    }

    if (is_ext_node(root))
    {
        Node *ext_1 = create_ext_node(), *ext_2 = create_ext_node();
        Node *parent = root->parent;
        free(root);
        root = create_new_node(ext_1, ext_2, key);
        ext_1->parent = root;
        ext_2->parent = root;
        root->parent = parent;
        return root;
    }

    if (root->data > key)
    {
        root->left = insert(root->left, key);
    }
    else
    {
        root->right = insert(root->right, key);
    }

    if (root != nullptr && root->left != nullptr && root->right != nullptr)
    {
        if (root->left->color == RED && root->right->color == BLACK)
        {
            if (root->left->left != nullptr && root->left->left->color == RED)
            {
                root = rotate_RB(root, root->left, root->left->left);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
            else if (root->left->right != nullptr && root->left->right->color == RED)
            {
                root = rotate_RB(root, root->left, root->left->right);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
        }
        else if (root->right->color == RED && root->left->color == BLACK)
        {
            if (root->right->left != nullptr && root->right->left->color == RED)
            {
                root = rotate_RB(root, root->right, root->right->left);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
            else if (root->right->right != nullptr && root->right->right->color == RED)
            {
                root = rotate_RB(root, root->right, root->right->right);
                root->color = BLACK;
                root->left->color = RED;
                root->right->color = RED;
            }
        }
        else if (root->left->color == RED && root->right->color == RED)
        {
            if (root->left->left != nullptr && root->left->left->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else if (root->left->right != nullptr && root->left->right->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else if (root->right->left != nullptr && root->right->left->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else if (root->right->right != nullptr && root->right->right->color == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
        }
    }
    Node *node = gethead(root);
    node->color = BLACK;
    return root;
}

int heightoftree(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else if (is_ext_node(root))
    {
        return 0;
    }
    return 1 + max(heightoftree(root->left), heightoftree(root->right));
}

void print_tree(Node *root)
{
    cout << "Displaying the elements in level order" << endl;
    if (root == nullptr)
    {
        return;
    }
    else if (root->parent == nullptr && root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << endl;
        return;
    }
    int height = heightoftree(root);
    vector<struct Node *> node_vec;
    node_vec.push_back(root);
    for (int i = 0; i < height; i++)
    {
        int size = node_vec.size();
        for (int j = 0; j < size; j++)
        {
            Node *temp = node_vec[0];
            cout << node_vec[0]->data << " ";
            node_vec.erase(node_vec.begin() + 0);
            if (!is_ext_node(temp->left))
            {
                node_vec.push_back(temp->left);
            }
            if (!is_ext_node(temp->right))
            {
                node_vec.push_back(temp->right);
            }
        }
        cout << endl;
    }
}

void Left_rotate(Node *root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (!is_ext_node(y->left))
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Right_rotate(Node *root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (!is_ext_node(x->right))
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr)
    {
        root = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

Node *transplant(Node *root, Node *node1, Node *node2)
{
    if (node1->parent == nullptr)
    {
        root = node2;
    }
    else if (node1 == node1->parent->left)
    {
        node1->parent->left = node2;
    }
    else
    {
        node1->parent->right = node2;
    }
    node2->parent = node1->parent;
    return root;
}

void treefixup(Node *root, Node *node)
{
    while (node != root && node->color == BLACK)
    {
        Node *sibling;
        if (node == node->parent->left)
        {
            sibling = node->parent->right;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                Left_rotate(root, node->parent);
                sibling = node->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    Right_rotate(root, sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                Left_rotate(root, node->parent);
                node = root;
            }
        }
        else
        {
            sibling = node->parent->left;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                Right_rotate(root, node->parent);
                sibling = node->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    Left_rotate(root, sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                Right_rotate(root, node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}

Node *find_root(Node *node)
{
    while (node->parent != nullptr)
    {
        node = node->parent;
    }
    return node;
}

Node *del(Node *root, int key)
{
    Node *z = search(root, key);
    if (z == nullptr)
    {
        cout << key << " not present. " << "So it cannot be deleted" << endl;
        return root;
    }
    Node *y = z, *x;
    bool y_original_color = y->color;
    if (is_ext_node(z->left))
    {
        x = z->right;
        root = transplant(root, z, z->right);
    }
    else if (is_ext_node(z->right))
    {
        x = z->left;
        root = transplant(root, z, z->left);
    }
    else
    {
        Node *temp = z->right;
        while (!is_ext_node(temp->left))
        {
            temp = temp->left;
        }
        y = temp;
        y_original_color = y->color;
        x = y->right;
        if (y != z->right)
        {
            root = transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        else
        {
            x->parent = y;
        }
        root = transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
    {
        treefixup(root, x);
    }
    return find_root(root);
}

void freemem(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    freemem(root->left);
    freemem(root->right);
    free(root);
}

// Helper for checking presence
bool isPresent(Node *root, int val)
{
    return search(root, val) != nullptr;
}

vector<int> get_inorder(Node *root)
{
    vector<int> result;
    function<void(Node *)> inorder = [&](Node *node)
    {
        if (!node || is_ext_node(node))
            return;
        inorder(node->left);
        result.push_back(node->data);
        inorder(node->right);
    };
    inorder(root);
    return result;
}

void assert_inorder(Node *root, vector<int> expected)
{
    vector<int> actual = get_inorder(root);
    assert(actual == expected);
}

vector<int> get_preorder(Node *root)
{
    vector<int> result;
    function<void(Node *)> preorder = [&](Node *node)
    {
        if (!node || is_ext_node(node))
            return;
        result.push_back(node->data);
        preorder(node->left);
        preorder(node->right);
    };
    preorder(root);
    return result;
}

void assert_preorder(Node *root, vector<int> expected)
{
    vector<int> actual = get_preorder(root);
    assert(actual == expected);
}

vector<int> get_level_order(Node *root)
{
    vector<int> result;
    if (!root || is_ext_node(root))
        return result;

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        if (is_ext_node(curr))
            continue;

        result.push_back(curr->data);

        if (curr->left)
            q.push(curr->left);
        if (curr->right)
            q.push(curr->right);
    }

    return result;
}

void assert_level_order(Node *root, const vector<int> &expected)
{
    vector<int> actual = get_level_order(root);

    if (actual != expected)
    {
        cerr << "Level order mismatch!\nExpected: ";
        for (int val : expected)
            cerr << val << " ";
        cerr << "\nActual:   ";
        for (int val : actual)
            cerr << val << " ";
        cerr << "\n";
        assert(false);
    }
}

void test()
{
    Node *root = nullptr;

    // ----------- Test 1 -----------
    root = insert(nullptr, 10);
    assert_inorder(root, {10});
    assert_preorder(root, {10});
    assert_level_order(root, {10});
    cout << "Test 1 passed\n";

    // ----------- Test 2 -----------
    root = insert(root, 5);
    assert_inorder(root, {5, 10});
    assert_preorder(root, {10, 5});
    assert_level_order(root, {10, 5});
    cout << "Test 2 passed\n";

    // ----------- Test 3 -----------
    root = insert(root, 15);
    assert_inorder(root, {5, 10, 15});
    assert_preorder(root, {10, 5, 15});
    assert_level_order(root, {10, 5, 15});
    cout << "Test 3 passed\n";

    // ----------- Test 4 -----------
    root = insert(root, 1);
    assert_inorder(root, {1, 5, 10, 15});
    assert_level_order(root, get_level_order(root));
    assert_preorder(root, get_preorder(root));
    cout << "Test 4 passed\n";

    // ----------- Test 5 -----------
    root = insert(root, 7);
    assert_inorder(root, {1, 5, 7, 10, 15});
    assert_level_order(root, get_level_order(root));
    assert_preorder(root, get_preorder(root));
    cout << "Test 5 passed\n";

    // ----------- Test 6 -----------
    root = insert(root, 12);
    root = insert(root, 20);
    assert_inorder(root, {1, 5, 7, 10, 12, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 6 passed\n";

    // ----------- Test 7 -----------
    root = insert(root, 0);
    root = insert(root, 2);
    assert_inorder(root, {0, 1, 2, 5, 7, 10, 12, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 7 passed\n";

    // ----------- Test 8 -----------
    root = insert(root, 6);
    assert_inorder(root, {0, 1, 2, 5, 6, 7, 10, 12, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 8 passed\n";

    // ----------- Test 9 -----------
    assert(search(root, 6));
    assert(!search(root, 1000));
    cout << "Test 9 passed\n";

    // ----------- Test 10 -----------
    root = del(root, 6);
    assert_inorder(root, {0, 1, 2, 5, 7, 10, 12, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 10 passed\n";

    // ----------- Test 11 -----------
    root = del(root, 5);
    assert_inorder(root, {0, 1, 2, 7, 10, 12, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 11 passed\n";

    // ----------- Test 12 -----------
    root = del(root, 10);
    assert_inorder(root, {0, 1, 2, 7, 12, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 12 passed\n";

    // ----------- Test 13 -----------
    root = insert(root, 11);
    root = insert(root, 13);
    assert_inorder(root, {0, 1, 2, 7, 11, 12, 13, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 13 passed\n";

    // ----------- Test 14 -----------
    root = del(root, 12);
    assert_inorder(root, {0, 1, 2, 7, 11, 13, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 14 passed\n";

    // ----------- Test 15 -----------
    root = insert(root, 7);  // Already present
    root = insert(root, 13); // Already present
    assert_inorder(root, {0, 1, 2, 7, 11, 13, 15, 20});
    assert_preorder(root, get_preorder(root));
    assert_level_order(root, get_level_order(root));
    cout << "Test 15 passed\n";

    freemem(root);

    cout << "All Red-Black Tree test cases passed!" << endl;
}

int main()
{
    test();
    Node *root = nullptr;
    int oper = 0, n, element, number;
    cout << "Enter the number of elements to be inserted" << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> element;
        root = insert(root, element);
    }
    while (true)
    {
        cout << "Enter the option: 1 for search (1 112); 2 for insertion (2 100); 3 for delete (3 100); 4 for printing the tree"
             << endl;
        cin >> oper;
        if (oper == 1)
        {
            cin >> number;
            Node *temp = search(root, number);
            if (temp == nullptr)
            {
                cout << number << " not present" << endl;
            }
            else
            {
                cout << number << " present" << endl;
            }
        }
        else if (oper == 2)
        {
            cin >> number;
            if (!search(root, number))
            {
                cout << number << " inserted" << endl;
                root = insert(root, number);
            }
            else
            {
                cout << number << " already present. So no need to insert." << endl;
            }
        }
        else if (oper == 3)
        {
            cin >> number;
            root = del(root, number);
        }
        else if (oper == 4)
        {
            print_tree(root);
        }
        else
        {
            cout << "Enter a valid option: 1 for search (1 112); 2 for insertion (2 100); 3 for delete (3 100); 4 for printing the tree"
                 << endl;
            cin >> oper;
        }
    }
    free(root);
}