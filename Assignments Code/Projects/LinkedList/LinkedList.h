#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "../Rational/Rational.h"
#include <iostream>
template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list);

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    int size;
    void sortedInsert(Node<T> *newNode, Node<T> *&sorted);

public:
    LinkedList();                        // Default constructor
    LinkedList(const LinkedList &other); // Copy constructor
    ~LinkedList();                       // Destructor
    void push_front(T val);
    void push_back(T val);
    bool pop_front();
    bool isEmpty() const;
    int length() const;
    void print() const;
    bool search(T val);
    bool del(T val);
    void insertionSort();                     // new
    Node<T> *getHead() const { return head; } // Accessor for head
    LinkedList<T> &operator=(const LinkedList<T> &other);
    bool operator==(const LinkedList<T> &other);
    T GetHeadValue() const;
    friend std::ostream &operator<< <>(std::ostream &os, const LinkedList<T> &l);
};

template <typename T>
LinkedList<T>::LinkedList() // Constructor
{
    head = nullptr;
    size = 0;
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList &other)
{
    head = other.head;
    if (head)
    {
        Node<T> *newNode = new Node<T>(head->data);
        // newNode->data = head->data;
        head = newNode;
        // printf("Copying node with value: %f\n", newNode->data);
        while (head->next)
        {
            Node<T> *nextNode = new Node<T>(head->next->data);
            // nextNode->data = head->next->data;
            //  printf("Copying node with value: %f\n", nextNode->data);
            newNode->next = nextNode;
            // printf("Copying node with value: %f\n", newNode->next->data);
            head = head->next;
        }
    }
}
template <typename T>
LinkedList<T>::~LinkedList() // Destructor
{
    while (head)
    {
        Node<T> *temp = head;
        // printf("Deleted node with value: %f\n", head->data);
        head = head->next;
        delete temp;
    }
}
template <typename T>
void LinkedList<T>::push_back(T val)
{
    Node<T> *newN = new Node<T>(val);
    // newN->data = val;
    newN->next = nullptr;
    Node<T> *temp = head;
    if (head == nullptr)
    {
        head = newN;
    }
    else
    {
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newN;
    }
}
template <typename T>
void LinkedList<T>::push_front(T val)
{
    Node<T> *newN = new Node<T>(val);
    // newN->data = val;
    newN->next = head;
    head = newN;
}
template <typename T>
bool LinkedList<T>::pop_front()
{
    if (head)
    {
        Node<T> *temp = head;
        // printf("Deleting: %f\n", head->data);
        head = head->next;
        delete temp;
        // printf("Points to: %f\n", head->data);
        return true;
    }
    else
    {
        printf("List is empty, cannot pop front\n");
        return false;
    }
}
template <typename T>
bool LinkedList<T>::isEmpty() const
{
    if (head)
    {
        return false;
    }
    return true;
}
template <typename T>
int LinkedList<T>::length() const
{
    int c = 0;
    Node<T> *temp = head;
    while (temp)
    {
        temp = temp->next;
        c++;
    }
    return c;
}
template <typename T>
void LinkedList<T>::print() const
{
    Node<T> *temp = this->head;
    while (temp)
    {
        std::cout << temp->data << "-->";
        temp = temp->next;
    }
    printf("\n");
}
template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this == &other)
        return *this;
    Node<T> *temp = other.head;
    if (temp)
    {
        Node<T> *newNode = new Node<T>(temp->data);
        // newNode->data = temp->data;
        head = newNode;
        // printf("Copying node with value: %f\n", head->data);
        while (temp->next)
        {
            Node<T> *nextNode = new Node<T>(temp->next->data);
            // nextNode->data = temp->next->data;
            //  printf("Copying node with value: %f\n", nextNode->data);
            newNode->next = nextNode;
            // printf("Copying node with value: %f\n", newNode->next->data);
            temp = temp->next;
            newNode = newNode->next;
        }
    }
    // this->print();
    return *this;
}
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &other)
{
    Node<T> *temp1 = this->head;
    Node<T> *temp2 = other.head;
    while (temp1 && temp2)
    {
        if (temp1->data != temp2->data)
        {
            return false; // Not equal
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return (temp1 == nullptr && temp2 == nullptr); // Both should be null for equality
}
template <typename T>
bool LinkedList<T>::search(T val)
{
    Node<T> *temp = head;
    while (temp)
    {
        if (temp->data == val)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
template <typename T>
bool LinkedList<T>::del(T val)
{
    Node<T> *temp = head;
    Node<T> *prev = nullptr;
    if (!temp)
    {
        return false;
    }
    if (temp->data == val)
    {
        // printf("The value deleted = %f\n", temp->data);
        head = head->next;
        delete temp;
        return true;
    }
    while (temp)
    {
        prev = temp;
        temp = temp->next;
        if (!temp)
        {
            return false;
        }
        if (temp->data == val)
        {
            // printf("The value deleted = %f\n", temp->data);
            prev->next = temp->next;
            delete temp;
            return true;
        }
    }
    return false;
}
template <typename T>
T LinkedList<T>::GetHeadValue() const
{
    if (head)
    {
        return head->data;
    }
    return T();
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &l)
{
    Node<T> *temp = l.head;
    while (temp)
    {
        os << temp->data << "-->";
        temp = temp->next;
    }
    os << "\n";
    return os;
}
template <typename T>
void LinkedList<T>::sortedInsert(Node<T> *newNode, Node<T> *&sorted)
{
    if (sorted == nullptr || sorted->data >= newNode->data)
    {
        newNode->next = sorted;
        sorted = newNode;
    }
    else
    {
        Node<T> *current = sorted;
        while (current->next != nullptr && current->next->data < newNode->data)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
template <typename T>
void LinkedList<T>::insertionSort()
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }
    Node<T> *sorted = nullptr;
    Node<T> *current = head;
    while (current != nullptr)
    {
        Node<T> *next = current->next;
        sortedInsert(current, sorted);
        current = next;
    }
    head = sorted;
}
#endif // LINKEDLIST_H