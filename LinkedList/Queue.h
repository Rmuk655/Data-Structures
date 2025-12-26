#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "DoublyLinkedList.h"

template <typename T>
class Queue; // Forward declaration of class

template <typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q);

template <typename T>
class Queue
{
private:
    DoublyLinkedList<T> Dlist;

public:
    Queue();
    Queue(const Queue<T> &other);
    ~Queue();
    void enqueue(const T &val);
    void dequeue();
    T front() const;
    bool isEmpty() const;
    int size() const;
    Queue<T> &operator=(const Queue<T> &other);
    bool operator==(const Queue<T> &other);
    friend std::ostream &operator<< <>(std::ostream &os, const Queue<T> &q);
};

template <typename T>
Queue<T>::Queue()
{
}

template <typename T>
Queue<T>::Queue(const Queue<T> &other)
{
    Dlist = other.Dlist;
}

template <typename T>
Queue<T>::~Queue()
{
}

template <typename T>
void Queue<T>::enqueue(const T &val)
{
    Dlist.push_back(val);
}

template <typename T>
void Queue<T>::dequeue()
{
    Dlist.pop_front();
}

template <typename T>
T Queue<T>::front() const
{
    return Dlist.getHeadValue();
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return Dlist.isEmpty();
}

template <typename T>
int Queue<T>::size() const
{
    return Dlist.length();
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &other)
{
    Dlist = other.Dlist;
    return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q)
{
    os << q.Dlist;
    return os;
}

template <typename T>
bool Queue<T>::operator==(const Queue<T> &other)
{
    return Dlist == other.Dlist;
}
#endif // QUEUE_H