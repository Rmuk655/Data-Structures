// #include <iostream>
// #include "LinkedList.h"
// template <typename T>
// LinkedList<T>::LinkedList() // Constructor
// {
//     head = nullptr;
//     size = 0;
// }
// template <typename T>
// LinkedList<T>::LinkedList(LinkedList &other)
// {
//     head = other.head;
//     if (head)
//     {
//         Node<T> *newNode = new Node<T>();
//         newNode->data = head->data;
//         head = newNode;
//         // printf("Copying node with value: %f\n", newNode->data);
//         while (head->next)
//         {
//             Node<T> *nextNode = new Node<T>();
//             nextNode->data = head->next->data;
//             // printf("Copying node with value: %f\n", nextNode->data);
//             newNode->next = nextNode;
//             // printf("Copying node with value: %f\n", newNode->next->data);
//             head = head->next;
//         }
//     }
// }
// template <typename T>
// LinkedList<T>::~LinkedList() // Destructor
// {
//     while (head)
//     {
//         Node<T> *temp = head;
//         // printf("Deleted node with value: %f\n", head->data);
//         head = head->next;
//         delete temp;
//     }
// }
// template <typename T>
// void LinkedList<T>::push_back(float val)
// {
//     Node<T> *newN = new Node<T>;
//     newN->data = val;
//     newN->next = nullptr;
//     Node<T> *temp = head;
//     if (head == nullptr)
//     {
//         head = newN;
//     }
//     else
//     {
//         while (head->next != nullptr)
//         {
//             head = head->next;
//         }
//         head->next = newN;
//         head = temp;
//     }
// }
// template <typename T>
// void LinkedList<T>::push_front(float val)
// {
//     Node<T> *newN = new Node<T>;
//     newN->data = val;
//     newN->next = head;
//     head = newN;
// }
// template <typename T>
// bool LinkedList<T>::pop_front()
// {
//     if (head)
//     {
//         Node<T> *temp = head;
//         // printf("Deleting: %f\n", head->data);
//         head = head->next;
//         delete temp;
//         // printf("Points to: %f\n", head->data);
//         return true;
//     }
//     else
//     {
//         printf("List is empty, cannot pop front\n");
//         return false;
//     }
// }
// template <typename T>
// bool LinkedList<T>::isEmpty() const
// {
//     if (head)
//     {
//         return false;
//     }
//     return true;
// }
// template <typename T>
// int LinkedList<T>::length() const
// {
//     int c = 0;
//     Node<T> *temp = head;
//     while (temp)
//     {
//         temp = temp->next;
//         c++;
//     }
//     return c;
// }
// template <typename T>
// void LinkedList<T>::print() const
// {
//     Node<T> *temp = this->head;
//     while (temp)
//     {
//         printf("%f ", temp->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }
// template <typename T>
// LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other)
// {
//     Node<T> *temp = other.head;
//     if (temp)
//     {
//         Node<T> *newNode = new Node<T>();
//         newNode->data = temp->data;
//         head = newNode;
//         // printf("Copying node with value: %f\n", head->data);
//         while (temp->next)
//         {
//             Node<T> *nextNode = new Node<T>();
//             nextNode->data = temp->next->data;
//             // printf("Copying node with value: %f\n", nextNode->data);
//             newNode->next = nextNode;
//             // printf("Copying node with value: %f\n", newNode->next->data);
//             temp = temp->next;
//             newNode = newNode->next;
//         }
//     }
//     // this->print();
//     return *this;
// }
// template <typename T>
// bool LinkedList<T>::search(float val)
// {
//     Node<T> *temp = head;
//     while (temp)
//     {
//         if (temp->data == val)
//         {
//             return true;
//         }
//         temp = temp->next;
//     }
//     return false;
// }
// template <typename T>
// bool LinkedList<T>::del(float val)
// {
//     Node<T> *temp = head;
//     Node<T> *prev = nullptr;
//     if (!temp)
//     {
//         return false;
//     }
//     if (temp->data == val)
//     {
//         // printf("The value deleted = %f\n", temp->data);
//         head = head->next;
//         delete temp;
//         return true;
//     }
//     while (temp)
//     {
//         prev = temp;
//         temp = temp->next;
//         if (!temp)
//         {
//             return false;
//         }
//         if (temp->data == val)
//         {
//             // printf("The value deleted = %f\n", temp->data);
//             prev->next = temp->next;
//             delete temp;
//             return true;
//         }
//     }
//     return false;
// }
// template <typename T>
// float LinkedList<T>::GetHeadValue() const
// {
//     if (head)
//     {
//         return head->data;
//     }
//     return 0;
// }
// template <typename T>
// std::ostream &operator<<(std::ostream &os, const LinkedList<T> &l)
// {
//     Node<T> *temp = l.head;
//     while (temp)
//     {
//         os << temp->data << "-->";
//         temp = temp->next;
//     }
//     os << "\n";
//     return os;
// }
// template <typename T>
// void LinkedList<T>::insertionSort()
// {
//     if (head == nullptr || head->next == nullptr)
//     {
//         return; // List is empty or has only one element
//     }
//     for (int i = 0; i < size; i++)
//     {
//         for (int j = i + 1; j < size; j++)
//         {
//             if (head->data > head->next->data)
//             {
//                 Node<T> *temp = head;
//                 head = head->next;
//             }
//         }
//     }
// }