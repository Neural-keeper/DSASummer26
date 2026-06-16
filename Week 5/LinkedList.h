//simple implementation, only has what we need for a stack
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    int listSize;

public:
    LinkedList() : head(nullptr), listSize(0) {}

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert at the very front of the list: O(1)
    void insertFront(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    // Remove from the very front of the list: O(1)
    void removeFront() {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        listSize--;
    }

    // Peek at the front element: O(1)
    const T& getFront() const {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        return head->data;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return listSize; }

    //you'll generally want a few more methods here, as discussed in day7
};

#endif // LINKEDLIST_H