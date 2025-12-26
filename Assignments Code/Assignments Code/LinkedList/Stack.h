#ifndef STACK_H
#define STACK_H
#include <iostream>
#include "LinkedList.h"

template <typename T>
class Stack;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &list);

template <typename T>
class Stack
{
private:
    LinkedList<T> list;

public:
    Stack();
    Stack(const Stack &other);
    ~Stack();
    void push(float val);
    bool pop();
    bool isEmpty() const;
    float top() const;
    int size() const;
    Stack &operator=(const Stack &other);
    friend std::ostream &operator<< <>(std::ostream &os, const Stack<T> &s);
    void print();
};

template <typename T>
Stack<T>::Stack()
{
}
template <typename T>
Stack<T>::Stack(const Stack &other)
{
    list = other.list;
}
template <typename T>
Stack<T>::~Stack()
{
}
template <typename T>
void Stack<T>::push(float val)
{
    list.push_front(val);
}
template <typename T>
bool Stack<T>::pop()
{
    // list.print();
    return list.pop_front();
}
template <typename T>
bool Stack<T>::isEmpty() const
{
    return list.isEmpty();
}
template <typename T>
float Stack<T>::top() const
{
    return list.GetHeadValue();
}
template <typename T>
int Stack<T>::size() const
{
    return list.length();
}
template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
    list = other.list;
    return *this;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &s)
{
    os << s.list;
    return os;
}
template <typename T>
void Stack<T>::print()
{
    list.print();
}
#endif