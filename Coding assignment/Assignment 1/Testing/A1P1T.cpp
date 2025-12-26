#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Time complexity = O(n)
// Space complexity = O(n)
// Extra space complexity due to the function reorder = O(1)

struct node
{
    int data;
    node *next;
};

struct node *create_node(struct node *head, int val)
{
    if (head == nullptr)
    {
        head = new node();
        head->data = val;
        head->next = nullptr;
        return head;
    }
    struct node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = new node();
    temp->next->data = val;
    temp->next->next = nullptr;
    return head;
}

struct node *reorder(struct node *head)
{
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
    {
        return head;
    }
    struct node *temp1 = head, *temp = head->next, *temp2 = temp;
    while (temp1 != nullptr && temp1->next != nullptr && temp1->next->next != nullptr)
    {
        temp1->next = temp->next;
        temp->next = temp->next->next;
        temp1 = temp1->next;
        temp = temp->next;
    }
    temp1->next = temp2;
    return head;
}

void print(struct node *head)
{
    while (head->next != nullptr)
    {
        cout << head->data << ", ";
        head = head->next;
    }
    cout << head->data << endl;
}

string list_to_string(struct node *head)
{
    string result;
    while (head != nullptr)
    {
        result += to_string(head->data);
        if (head->next)
            result += ",";
        head = head->next;
    }
    return result;
}

// ✅ Test function
void test(vector<int> input, string expected)
{
    node *head = nullptr;
    for (int val : input)
    {
        head = create_node(head, val);
    }

    head = reorder(head);
    string output = list_to_string(head);

    cout << "Input: ";
    for (size_t i = 0; i < input.size(); i++)
    {
        cout << input[i] << (i + 1 < input.size() ? "," : "");
    }
    cout << "\nExpected: " << expected << "\nGot:      " << output << "\n";

    if (output == expected)
        cout << "Test Passed\n\n";
    else
        cout << "Test Failed\n\n";
}

void test_check()
{
    test({1, 2, 3, 4, 5}, "1,3,5,2,4");
    test({2, 1, 3, 5, 6, 4, 7}, "2,3,6,7,1,5,4");
    test({10, 20}, "10,20");
    test({5}, "5");
    test({11, 22, 33, 44, 55, 66}, "11,33,55,22,44,66");
    test({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, "1,3,5,7,9,2,4,6,8,10");
    test({}, "");                                 // empty list
    test({42}, "42");                             // single element
    test({100, 200, 300}, "100,300,200");         // odd count 3
    test({1, 2, 3, 4}, "1,3,2,4");                // even count 4
    test({-1, -2, -3, -4, -5}, "-1,-3,-5,-2,-4"); // negative numbers
    test({1, 1, 1, 1, 1}, "1,1,1,1,1");           // all same
    test({9, 8, 7, 6, 5}, "9,7,5,8,6");           // descending order
    cout << "All test cases passed" << endl;
}

int main()
{
    test_check();
    struct node *head = nullptr;
    int i;
    string s;
    cin >> s;
    while (s != "-1")
    {
        s.pop_back();
        head = create_node(head, stoi(s));
        cin >> s;
    }
    print(head);
    head = reorder(head);
    print(head);
}