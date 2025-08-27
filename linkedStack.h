#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <stdexcept>

// Generic element
template <typename T>
struct LinkedS_TElement {
    T data;
    LinkedS_TElement<T> *next;
};

// Points to the first element of the Generic Linked Stack
template <typename T>
struct LinkedS_TList {
    LinkedS_TElement<T> *top;
};

// Boot Generic Linked Stack
template <typename T>
bool LinkedS_boot(LinkedS_TList<T> &list) {
    list.top = nullptr;
    return true;
}

// Insert at the top of the stack
template <typename T>
bool LinkedS_push(LinkedS_TList<T> &list, const T &data) {
    LinkedS_TElement<T> *e = new LinkedS_TElement<T>;
    e->data = data;
    e->next = list.top; // Points to stack's top element
    list.top = e; // New element becomes top element of the stack
    return true;
}

// Remove top element of the stack
template <typename T>
T LinkedS_pop(LinkedS_TList<T> &list) {
    if (list.top == nullptr) // Check if stack is empty
        throw std::underflow_error("Error: empty stack.");

    LinkedS_TElement<T> *temp = list.top;
    T data = list.top->data; // Save data of the top element
    list.top = list.top->next; // list.top points to second element
    delete temp;
    return data; // Return data from top element
}

// Check if stack is empty
template <typename T>
bool LinkedS_isEmpty(const LinkedS_TList<T> &list) {
    return list.top == nullptr;
}

// Delete all elements of the stack
template <typename T>
void LinkedS_destroyStack(LinkedS_TList<T> &list) {
    while (list.top != nullptr) {
        LinkedS_TElement<T> *temp = list.top;
        list.top = list.top->next;
        delete temp;
    }
    list.top = nullptr;
}

#endif // LINKED_STACK_H
