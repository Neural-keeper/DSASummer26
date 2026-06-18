//simple implementation, only has what we need for a stack
//updated to also include methods to support queue
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
    Node* tail;
    int listSize;

public:
    LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

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
        if (tail == nullptr) { // Fix: If list was empty, tail must also point to the new node
            tail = newNode;
        }
        listSize++;
    }

    // Insert at the end of the list: O(1) because we keep track of tail
    void insertBack(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) { // Fix: Handle empty list edge case to avoid dereferencing nullptr
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
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

        if (head == nullptr) {
            tail = nullptr;
        }

        listSize--;
    }

    // Remove from the very back of the list: O(n) 
    void removeBack() {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        if (tail == head) {
            removeFront();
            return;
        }
        Node* curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        curr->next = nullptr;
        delete tail;
        tail = curr;
        listSize--;
    }

    // Peek at the front element: O(1)
    const T& getFront() const {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        return head->data;
    }

    const T& getBack() const {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        return tail->data;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return listSize; }

    //you'll generally want a few more methods here, as discussed in day7
};

#endif // LINKEDLIST_H