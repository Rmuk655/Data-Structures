// #include <iostream>
// #include "LinkedList.h"
// #include "Stack.h"
// using namespace std;
// template <typename T>
// Stack<T>::Stack()
// {
// }
// template <typename T>
// Stack<T>::Stack(const Stack &other)
// {
//     list = other.list;
// }
// template <typename T>
// void Stack<T>::push(float val)
// {
//     list.push_front(val);
// }
// template <typename T>
// bool Stack<T>::pop()
// {
//     // list.print();
//     return list.pop_front();
// }
// template <typename T>
// bool Stack<T>::isEmpty() const
// {
//     return list.isEmpty();
// }
// template <typename T>
// float Stack<T>::top() const
// {
//     return list.GetHeadValue();
// }
// template <typename T>
// int Stack<T>::size() const
// {
//     return list.length();
// }
// template <typename T>
// Stack<T> &Stack<T>::operator=(const Stack<T> &other)
// {
//     list = other.list;
//     return *this;
// }
// template <typename T>
// std::ostream &operator<<(std::ostream &os, const Stack<T> &s)
// {
//     os << s.list;
//     return os;
// }
// template <typename T>
// void Stack<T>::print()
// {
//     list.print();
// }