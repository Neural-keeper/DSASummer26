/*
Thursday June 4th, 2026 - Session 6 - Templates and Linked Lists
*/
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

//node class
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T value, Node<T>* n = nullptr) : data(value), next(n) {}
};


//singly linked list
template <typename T>
class SLinkedList {
private:
    Node<T>* head;
    int length = 0;

public:
    SLinkedList() : head(nullptr), length(0) {}

    ~SLinkedList() {
        Node<T>* curr = head;
        while (curr != nullptr) {
            Node<T>* nextptr = curr;
            delete curr;
            curr = nextptr;
        }
        head = nullptr;
    } // destructor for memory clearing and management

    bool isEmpty() {
        return head == nullptr;
    }

    void pushFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void removeFront() {
        if(isEmpty())
            throw runtime_error("List is empty!");
        Node<T>* oldH = head;
        head = head->next;
        delete oldH;
        length--;
    }

    T front() {
        if (isEmpty()) 
            throw runtime_error("Linked List is empty!");
        return head->data;
    }

    void print() const {
        Node<T>* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << "Null \n";
    }

    int Length() {
        return length;
    }
};
/*
Typical operations:
create a list
insert item at head
insert item at tail
insert item at specified position
insert in order
retrieve for all of those
delete item
traverse
determine if its empty
determine number of items
destroy list
*/

class DLinkedList; //forward declaration, so we can reference it before defining it

class DNode {
private:
    int data;
    DNode* prev;
    DNode* next;
    friend class DLinkedList;
};

//here, we're pretty much defining all the functions we want, and creating an interface
class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();

    bool empty() const;
    int front() const;
    int back() const;

    void addFront(int x);
    void addBack(int x);
    void removeFront();
    void removeBack();

    void printForward() const;
    void printBackward() const;

private:
    DNode* head;
    DNode* tail;
};

//I'll add these by next class, enjoy the weekend!

int main() {
    SLinkedList<int> stable;

    // //singly linked list
    // stable.pushFront(7);
    // stable.pushFront(8);
    // stable.pushFront(9);
    // stable.print();
    // cout << "Length: " << stable.Length() << endl;
    // stable.removeFront();
    // stable.print();
    // cout << "Length: " << stable.Length() << endl;

    // doubly linked list


    return 0;
}