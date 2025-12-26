// #include <iostream>
// #include "DoublyLinkedList.h"
// #include "LinkedList.h"
// #include "../Rational/Rational.h"

// template <typename T>
// DoublyLinkedList<T>::DoublyLinkedList()
// {
//     DNode<T> *head = nullptr;
//     head->next = nullptr;
//     head->prev = nullptr;
// }

// template <typename T>
// DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &other)
// {
//     DNode<T> *temp = other->head;
//     head = temp;
//     head->prev = nullptr;
//     while (temp != nullptr)
//     {
//         head->next = new DNode<T>(other.head->data);
//         head = head->next;
//         head->prev = temp;
//         temp = temp->next;
//     }
// }

// template <typename T>
// DoublyLinkedList<T>::~DoublyLinkedList()
// {
//     while (head != nullptr)
//     {
//         DNode<T> *temp = head;
//         head = head->next;
//         delete temp; // Free the memory of the node
//     }
// }

// template <typename T>
// void DoublyLinkedList<T>::push_back(const T &val)
// {
//     if (head == nullptr)
//     {
//         head = new DNode<T>(val);
//         head->next = nullptr;
//         head->prev = nullptr;
//     }
//     else if (head != nullptr && head->next == nullptr)
//     {
//         head->next = new DNode<T>(val);
//         head->next->prev = head;
//     }
//     else
//     {
//         DNode<T> temp = head;
//         while (head->next != nullptr)
//         {
//             head = head->next;
//         }
//         head = new DNode<T>(val);
//         head->next = nullptr;
//         head->prev = head->prev->next;
//         head = temp;
//     }
// }

// template <typename T>
// void DoublyLinkedList<T>::push_front(const T &val)
// {
//     if (head == nullptr)
//     {
//         head = new DNode<T>(val);
//         head->next = nullptr;
//         head->prev = nullptr;
//     }
//     else
//     {
//         head->prev = new DNode<T>(val);
//         head->prev->next = head;
//         head->prev->prev = nullptr;
//     }
// }

// template <typename T>
// void DoublyLinkedList<T>::pop_front()
// {
//     if (head == nullptr)
//     {
//         printf("Cannot pop an empty Doubly Linked List!");
//     }
//     DNode<T> *temp = head;
//     head = head->next;
//     head->prev = nullptr;
//     temp->next = nullptr;
//     delete temp;
// }

// template <typename T>
// void DoublyLinkedList<T>::pop_back()
// {
//     if (head == nullptr)
//     {
//         printf("Cannot pop an empty Doubly Linked List!");
//     }
//     DNode<T> temp1 = head;
//     while (head != nullptr)
//     {
//         head = head->next;
//     }
//     DNode<T> *temp = head;
//     head = head->prev;
//     head->next = nullptr;
//     temp->prev = nullptr;
//     delete *temp;
//     head = temp1;
// }

// template <typename T>
// bool DoublyLinkedList<T>::isEmpty() const
// {
//     if (head == nullptr)
//     {
//         return true;
//     }
//     return false;
// }

// template <typename T>
// int DoublyLinkedList<T>::length() const
// {
//     if (head == nullptr)
//     {
//         return 0;
//     }
//     int c = 0;
//     DNode<T> *temp = head;
//     while (temp != nullptr)
//     {
//         c = c + 1;
//         temp = temp->next;
//     }
//     return c;
// }

// template <typename T>
// void DoublyLinkedList<T>::printForward() const
// {
//     if (head == nullptr)
//     {
//         printf("Empty Doubly Linked List");
//         return;
//     }
//     DNode<T> *temp = head;
//     while (temp != nullptr)
//     {
//         std::cout << temp->data << "-->" << std::endl;
//         temp = temp->next;
//     }
// }

// template <typename T>
// void DoublyLinkedList<T>::printBackward() const
// {
//     if (head == nullptr)
//     {
//         printf("Empty Doubly Linked List");
//         return;
//     }
//     DNode<T> *temp = head;
//     while (temp != nullptr)
//     {
//         temp = temp->next;
//     }
//     while (temp != nullptr)
//     {
//         std::cout << temp->data << "-->" << std::endl;
//         temp = temp->prev;
//     }
// }

// template <typename T>
// DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &other)
// {
//     DNode<T> *temp = other->head;
//     head = temp;
//     head->prev = nullptr;
//     while (temp != nullptr)
//     {
//         head->next = new DNode<T>(other.head->data);
//         head = head->next;
//         head->prev = temp;
//         temp = temp->next;
//     }
// }

// template <typename T>
// bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T> &other)
// {
//     if (this.length() != other.length())
//     {
//         return false;
//     }
//     DNode<T> *temp = head;
//     DNode<T> *temp1 = other->head;
//     while (temp != nullptr && temp1 != nullptr)
//     {
//         if (temp->data != temp1->data)
//         {
//             return false;
//         }
//         temp = temp->next;
//         temp1 = temp1->next;
//     }
//     return true;
// }

// template <typename T>
// DoublyLinkedList<T> DoublyLinkedList<T>::swap_with_next(DNode<T> &a)
// {
//     DNode<T> *temp = head;
//     while (head->data != a)
//     {
//         head = head->next;
//     }
//     DNode<T> *temp1 = head->prev;
//     head->next = head->next->next;
//     head->prev = head->next;
//     head->next->next = head;
//     head->next->prev = temp1;
//     head = temp;
// }

// template <typename T>
// DoublyLinkedList<T> DoublyLinkedList<T>::reverse(const DoublyLinkedList<T> &other)
// {
//     if (other->head == nullptr)
//     {
//         return nullptr;
//     }
// }

// template <typename T>
// DoublyLinkedList<T> DoublyLinkedList<T>::insertion_sort()
// {
//     if (head == nullptr)
//     {
//         return nullptr;
//     }
// }