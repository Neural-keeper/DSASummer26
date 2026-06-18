#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include <stdexcept>

template <typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* cursor; // Points to the tail/back of the list. cursor->next is the head.
    int listSize;

public:
    CircularLinkedList() : cursor(nullptr), listSize(0) {}

    ~CircularLinkedList() {
        while (listSize > 0) {
            removeFront();
        }
    }

    // Insert at the very front of the list: O(1)
    void insertFront(const T& value) {
        Node* newNode = new Node(value);
        if (cursor == nullptr) {
            cursor = newNode;
            cursor->next = cursor; // Node points to itself
        } else {
            newNode->next = cursor->next; // New node points to old head
            cursor->next = newNode;       // Tail points to new head
        }
        listSize++;
    }

    // Insert at the end of the list: O(1)
    void insertBack(const T& value) {
        // Fun trick: inserting back is identical to inserting front, 
        // you just advance the cursor to the newly added node!
        insertFront(value);
        cursor = cursor->next;
    }

    // Remove from the very front of the list: O(1)
    void removeFront() {
        if (cursor == nullptr) {
            throw std::underflow_error("List is empty");
        }
        
        Node* head = cursor->next;
        if (cursor == head) { // Only one element in the list
            delete cursor;
            cursor = nullptr;
        } else {
            cursor->next = head->next; // Tail bypasses the old head
            delete head;
        }
        listSize--;
    }

    // Remove from the very back of the list: O(n)
    void removeBack() {
        if (cursor == nullptr) {
            throw std::underflow_error("List is empty");
        }
        
        Node* head = cursor->next;
        if (cursor == head) { // Only one element in the list
            removeFront();
            return;
        }
        
        // Find the node right before the cursor (the new tail)
        Node* curr = head;
        while (curr->next != cursor) {
            curr = curr->next;
        }
        
        curr->next = head;   // New tail points to head
        delete cursor;       // Free old tail
        cursor = curr;       // Update cursor to new tail
        listSize--;
    }

    // Peek at the front element: O(1)
    const T& getFront() const {
        if (cursor == nullptr) {
            throw std::underflow_error("List is empty");
        }
        return cursor->next->data; // Head is cursor->next
    }

    // Peek at the back element: O(1)
    const T& getBack() const {
        if (cursor == nullptr) {
            throw std::underflow_error("List is empty");
        }
        return cursor->data; // Tail is the cursor itself
    }

    bool isEmpty() const { return cursor == nullptr; }
    int size() const { return listSize; }
    
    // Optional utility: Step through the list explicitly
    void advance() {
        if (cursor != nullptr) {
            cursor = cursor->next;
        }
    }
};

#endif // CLINKEDLIST_H