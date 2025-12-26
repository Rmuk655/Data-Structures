#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <iostream>
#include <optional>

template <typename T>
class DNode
{
public:
    T data;
    DNode<T> *next;
    DNode<T> *prev;
    DNode() : data(), next(nullptr) {} // TBD 2:initialize prev
    DNode(T val) : data(val), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &os, const DoublyLinkedList<T> &other);

template <typename T>
class DoublyLinkedList
{
private:
    DNode<T> *head;
    void swap_with_next(DNode<T> *a);

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T> &other);
    ~DoublyLinkedList();
    void push_back(const T &val);
    void push_front(const T &val);
    void pop_front();
    void pop_back();
    bool isEmpty() const;
    int length() const;
    void printForward() const;
    void printBackward() const;
    T getHeadValue() const;
    DoublyLinkedList<T> reverse(const DoublyLinkedList<T> &other);
    friend std::ostream &operator<< <>(std::ostream &os, const DoublyLinkedList<T> &other);
    DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &other);
    bool operator==(const DoublyLinkedList<T> &other);
    void testSwapWithNext(DNode<T> *a)
    {
        swap_with_next(a);
    } // For testing purposes
    void insertion_sort();
    DNode<T> *getHead()
    {
        return head;
    } // Accessor for head
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    head = nullptr;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &other)
    : head(nullptr)
{
    if (other.head == nullptr)
        return;

    DNode<T> *src = other.head;
    DNode<T> *last = nullptr;

    while (src != nullptr)
    {
        DNode<T> *newNode = new DNode<T>(src->data);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            last->next = newNode;
            newNode->prev = last;
        }
        last = newNode;
        src = src->next;
    }
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    while (head != nullptr)
    {
        DNode<T> *temp = head;
        head = head->next;
        delete temp; // Free the memory of the node
    }
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T &val)
{
    if (head == nullptr)
    {
        head = new DNode<T>(val);
        head->next = nullptr;
        head->prev = nullptr;
    }
    else if (head != nullptr && head->next == nullptr)
    {
        head->next = new DNode<T>(val);
        head->next->prev = head;
        head->next->next = nullptr;
    }
    else
    {
        DNode<T> *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = new DNode<T>(val);
        DNode<T> *NodeDL = temp;
        temp = temp->next;
        temp->next = nullptr;
        temp->prev = NodeDL;
    }
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T &val)
{
    if (head == nullptr)
    {
        head = new DNode<T>(val);
        head->next = nullptr;
        head->prev = nullptr;
    }
    else
    {
        head->prev = new DNode<T>(val);
        head->prev->next = head;
        head->prev->prev = nullptr;
        head = head->prev;
    }
}

template <typename T>
void DoublyLinkedList<T>::pop_front()
{
    if (head == nullptr)
    {

        printf("Cannot pop an empty Doubly Linked List!");
        return;
    }
    else if (head != nullptr && head->next == nullptr)
    {
        DNode<T> *temp = head;
        head = nullptr;
        // head->prev = nullptr;
        // head->next = nullptr;
        delete temp;
        return;
    }
    DNode<T> *temp1 = head;
    head = head->next;
    head->prev = nullptr;
    temp1->next = nullptr;
    delete temp1;
}

template <typename T>
void DoublyLinkedList<T>::pop_back()
{
    if (head == nullptr)
    {
        printf("Cannot pop an empty Doubly Linked List!");
        return;
    }
    else if (head != nullptr && head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }
    DNode<T> *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp = temp->prev;
    delete temp->next;
    temp->next = nullptr;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
    if (head == nullptr)
    {
        return true;
    }
    return false;
}

template <typename T>
int DoublyLinkedList<T>::length() const
{
    if (head == nullptr)
    {
        return 0;
    }
    int c = 0;
    DNode<T> *temp = head;
    while (temp != nullptr)
    {
        c = c + 1;
        temp = temp->next;
    }
    return c;
}

template <typename T>
void DoublyLinkedList<T>::printForward() const
{
    if (head == nullptr)
    {
        printf("Empty Doubly Linked List");
        return;
    }
    DNode<T> *temp = head;
    while (temp->next != nullptr)
    {
        std::cout << temp->data << "-->";
        temp = temp->next;
    }
    std::cout << temp->data << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::printBackward() const
{
    if (head == nullptr)
    {
        printf("Empty Doubly Linked List");
        return;
    }
    DNode<T> *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    while (temp->prev != nullptr)
    {
        std::cout << temp->data << "-->";
        temp = temp->prev;
    }
    std::cout << temp->data << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const DoublyLinkedList<T> &other)
{
    if (other.head == nullptr)
    {
        os << "Empty Doubly Linked List";
        return os;
    }
    DNode<T> *temp = other.head;
    while (temp->next != nullptr)
    {
        os << temp->data << "-->";
        temp = temp->next;
    }
    os << temp->data;
    os << "\n";
    return os;
}

template <typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &other)
{
    if (this == &other)
    {
        return *this; // Handle self-assignment
    }

    // Step 1: Delete existing list
    while (head != nullptr)
    {
        DNode<T> *temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;

    // Step 2: Copy nodes from other
    if (other.head == nullptr)
    {
        return *this; // Other list is empty
    }

    DNode<T> *src = other.head;
    DNode<T> *last = nullptr;

    while (src != nullptr)
    {
        DNode<T> *newNode = new DNode<T>(src->data);

        if (!head)
        {
            head = newNode;
        }
        else
        {
            last->next = newNode;
            newNode->prev = last;
        }

        last = newNode;
        src = src->next;
    }

    return *this;
}

template <typename T>
bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T> &other)
{
    if (this->length() != other.length())
    {
        return false;
    }
    DNode<T> *temp = head;
    DNode<T> *temp1 = other.head;
    while (temp != nullptr && temp1 != nullptr)
    {
        if (temp->data != temp1->data)
        {
            return false;
        }
        temp = temp->next;
        temp1 = temp1->next;
    }
    return true;
}

template <typename T>
T DoublyLinkedList<T>::getHeadValue() const
{
    if (head == nullptr)
    {
        return T();
    }
    return head->data;
}

template <typename T>
void DoublyLinkedList<T>::swap_with_next(DNode<T> *curr_node)
{
    if (curr_node == nullptr || curr_node->next == nullptr)
    {
        return; // Cannot swap if 'a' is null or 'a' has no next node
    }
    DNode<T> *next_node = curr_node->next;
    T temp = curr_node->data;
    curr_node->data = next_node->data;
    next_node->data = temp;
}

template <typename T>
DoublyLinkedList<T> DoublyLinkedList<T>::reverse(const DoublyLinkedList<T> &other)
{
    if (other.head == nullptr || other.head->next == nullptr)
    {
        return other; // Nothing to reverse if there are no nodes or there is only one node
    }
    DNode<T> *current = other.head;
    DNode<T> *temp = nullptr;
    while (current != nullptr)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    head = temp->prev;
    return *this;
}

template <typename T>
void DoublyLinkedList<T>::insertion_sort()
{
    if (head == nullptr)
    {
        return;
    }
    DNode<T> *current = head->next;
    while (current != nullptr)
    {
        DNode<T> *key = current;
        DNode<T> *prev = current->prev;
        while (prev != nullptr && prev->data > key->data)
        {
            swap_with_next(prev);
            key = prev;
            prev = prev->prev;
        }
        current = current->next;
    }
}
#endif // DOUBLY_LINKED_LIST_H
