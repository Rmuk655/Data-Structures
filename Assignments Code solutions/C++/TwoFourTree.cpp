#include <iostream>
#include <queue>
using namespace std;

struct node {
    int data[3];
    node* children[4];
    int numKeys;
    bool isLeaf;

    node() {
        numKeys = 0;
        isLeaf = true;
        for (int i = 0; i < 4; i++) children[i] = nullptr;
    }
};

// Function to search a key
node* search(node* root, int key) {
    int i = 0;
    while (i < root->numKeys && key > root->data[i]) i++;

    if (i < root->numKeys && key == root->data[i]) {
        cout << key << " present" << endl;
        return root;
    }

    if (root->isLeaf) {
        cout << key << " not present" << endl;
        return nullptr;
    }

    return search(root->children[i], key);
}

// Split child
void splitChild(node* x, int i, node* y) {
    node* z = new node();
    z->isLeaf = y->isLeaf;
    z->numKeys = 1;
    z->data[0] = y->data[2];

    if (!y->isLeaf) {
        z->children[0] = y->children[2];
        z->children[1] = y->children[3];
    }

    y->numKeys = 1;

    for (int j = x->numKeys; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;

    for (int j = x->numKeys - 1; j >= i; j--)
        x->data[j + 1] = x->data[j];
    x->data[i] = y->data[1];
    x->numKeys++;
}

// Insert non-full
void insertNonFull(node* x, int key) {
    int i = x->numKeys - 1;

    if (x->isLeaf) {
        while (i >= 0 && x->data[i] > key) {
            x->data[i + 1] = x->data[i];
            i--;
        }
        x->data[i + 1] = key;
        x->numKeys++;
    } else {
        while (i >= 0 && x->data[i] > key) i--;
        i++;
        if (x->children[i]->numKeys == 3) {
            splitChild(x, i, x->children[i]);
            if (key > x->data[i]) i++;
        }
        insertNonFull(x->children[i], key);
    }
}

// Insert key into tree
node* insert(node* root, int key) {
    if (search(root, key)) {
        cout << key << " already present. So no need to insert." << endl;
        return root;
    }

    if (root->numKeys == 3) {
        node* s = new node();
        s->isLeaf = false;
        s->children[0] = root;
        splitChild(s, 0, root);
        insertNonFull(s, key);
        cout << key << " inserted" << endl;
        return s;
    } else {
        insertNonFull(root, key);
        cout << key << " inserted" << endl;
        return root;
    }
}

// Pretty print
void prettyPrint(node* root, int indent = 0) {
    if (!root) return;
    for (int i = root->numKeys; i >= 0; --i) {
        if (i < root->numKeys)
            cout << string(indent, ' ') << root->data[i] << endl;
        if (!root->isLeaf && root->children[i])
            prettyPrint(root->children[i], indent + 6);
    }
}

// Level-order display
void displayLevelOrder(node* root) {
    if (!root) return;
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            node* curr = q.front(); q.pop();
            for (int i = 0; i < curr->numKeys; i++) {
                cout << curr->data[i] << " ";
            }
            cout << "| ";
            if (!curr->isLeaf) {
                for (int i = 0; i <= curr->numKeys; i++) {
                    if (curr->children[i])
                        q.push(curr->children[i]);
                }
            }
        }
        cout << endl;
    }
}

void runTests() {
    cout << "=== Running Test Set 1 ===\n";
    vector<int> initialElements = {9, 8, 5, 4, 99, 78, 31, 34, 89, 90, 21, 23, 45, 77, 88, 112, 32};
    node* root = new node();
    for (int val : initialElements) {
        root = insert(root, val);
    }

    vector<pair<int, int>> testQueries1 = {
        {1, 56}, // search
        {2, 21}, // insert
        {2, 56}, // insert
        {2, 90}, // insert
        {3, 51}, // delete (not implemented)
        {1, 32}, // search
        {3, 32}  // delete (not implemented)
    };

    for (auto [qtype, key] : testQueries1) {
        if (qtype == 1) {
            cout << "Query: search " << key << "\n";
            search(root, key);
        } else if (qtype == 2) {
            cout << "Query: insert " << key << "\n";
            root = insert(root, key);
        } else if (qtype == 3) {
            cout << "Query: delete " << key << "\n";
            cout << key << " not present. So it can not be deleted (delete not implemented).\n";
        }
    }

    cout << "Level Order:\n";
    displayLevelOrder(root);
    cout << "Pretty Print:\n";
    prettyPrint(root);

    // Test Set 2
    cout << "\n=== Running Test Set 2 ===\n";
    root = new node(); // Fresh tree
    vector<int> testSet2 = {100, 50, 150, 25, 75, 125, 175, 60, 110};
    for (int val : testSet2) {
        root = insert(root, val);
    }

    vector<pair<int, int>> testQueries2 = {
        {1, 60},
        {1, 200},
        {2, 125},
        {2, 200},
        {3, 75}
    };

    for (auto [qtype, key] : testQueries2) {
        if (qtype == 1) {
            cout << "Query: search " << key << "\n";
            search(root, key);
        } else if (qtype == 2) {
            cout << "Query: insert " << key << "\n";
            root = insert(root, key);
        } else if (qtype == 3) {
            cout << "Query: delete " << key << "\n";
            cout << key << " not present. So it can not be deleted (delete not implemented).\n";
        }
    }

    cout << "Level Order:\n";
    displayLevelOrder(root);
    cout << "Pretty Print:\n";
    prettyPrint(root);
}


int main() {

    runTests();
    return 1;

    int n;
    cin >> n;
    node* root = new node();
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        root = insert(root, x);
    }

    int qtype, key;
    while (true) {
        string line;
        getline(cin >> ws, line);
        if (line.empty()) continue;

        if (line == "4") {
            displayLevelOrder(root);
            cout << "Pretty Print:\n";
            prettyPrint(root);
        } else {
            sscanf(line.c_str(), "%d %d", &qtype, &key);
            if (qtype == 1) search(root, key);
            else if (qtype == 2) root = insert(root, key);
            else cout << "Invalid query type or delete not implemented." << endl;
        }
    }
}
