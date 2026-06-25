/*
Thursday June 26th, 2026 - Session 12 - Trees Intro
*/

//Attendance Form Link: https://forms.cloud.microsoft/r/C1L7SV2H19

// We're doing the textbook outlined version (for the most part)

/*
      A
    /   \
   B     C
   |   
   D
*/

/*
RULES FOR TREES
1. every node has one parent and however many children (0-n) except for the root, which has no parent
- a tree is a acyclic (doesn't have any cycles)
2. n nodes in a tree, n-1 edges
*/

/*
TREE TERMINOLOGY
Parent - the node above the current node
Child - the nodes below the current node
Ancestors - every node above the current node
Descendants - every node below the current node
Edge - connects a parent to its child - (A, B), (A, C), (B, D)
Root - basically the start of a tree - A
Degree - of a node, this is the number of children it had - A has degree 2, B has degree 1, C has degree 0, D - 0
       - of a tree, this is the maximum degree of all of its nodes (2)
Depth - the length of the path to a node from the root - B had depth of 1
Height - the maximum depth in a tree - the longest path to a leaf - height of tree here is 2
Leaf (External node) - this is a node in a tree without any children - C, D
Internal node - a node that has children (not external) - B
*/

#include <iostream>
#include <string>
#include <vector> // used for a list of each node's children
#include <list> // STL List
#include <stdexcept> // for std exceptions

using namespace std;

// Forward declarations - when we tell the compiler what exists ahead of time
template <typename E> struct Node;
template <typename E> class Position; //from the textbook, use positions for abstraction
template <typename E> class LinkedTree; 

// Node Struct
template <typename E>
struct Node {
    E element; //stores the data we want
    Node* parent; //stores the parent of the node
    vector<Node*> children; //stores vector of this ndoe's children
    Node(const E& elem = E(), Node* par = nullptr) : element(elem), parent(par) {}
} 

// Position Class (references to nodes)
template <typename E>
class Position { 
private:
    Node<E>* v; //pointer to the node
    const LinkedTree<E>* tree;

    //private constructor so that only the LinkedTree can create Positions
    Position(Node<E>* node, const LinkedTree<E>* t) : v(node), tree(t) {}

public:
    Position() : v(nullptr), tree(nullptr) {}

    E& operator*() {
        if (!v) throw runtime_error("Error: Null position!");
        return v->element;
    } //read and write privilages

    const E& operator*() const {
        if (!v) throw runtime_error("Error: Null position!");
        return v->element;
    } //read-only privilages

    Position parent() const {
        if(!v) throw runtime_error("Error: Null position!");
        return Position(v->parent, tree);
    } // returns the parent's position

    list<Position<E>> children() const {
        if(!v) throw runtime_error("Error: Null position!");
        list<Position<E>> result;
        for (Node<E>* child : v->children) {
            result.push_back(Position<E>(child, tree));
        }
        return result;
    } // return a list of the children's positions

    bool isRoot() const { return (v != nullptr && tree != nullptr && v == tree->rootNode); }
    bool isExternal() const { return (v == nullptr || v->children.empty()); }
    bool isInternal() const { return !isExternal(); }

    bool operator==(const Position& p) const { return v = p.v && tree = p.tree; }
    bool operator!=(const Position& p) const { return !(*this == p); }

    friend class LinkedTree<E>;
} // we created our own pointers just now

// linked tree class
template <typename E>
class LinkedTree {
private:
    Node<E>* rootNode;
    int treeSize;

    void deleteSubtree(Node<E>* v) {
        if (!v) return;
        for (Node<E>* child : v->children) {
            deleteSubtree(child);
        }
        delete v;
    } // our delete helper - recursive post order deletion

public:
    LinkedTree() : rootNode(nullptr), treeSize(0) {}
    ~LinkedTree() { deleteSubtree(rootNode); }

    int size() const { return treeSize; }
    bool empty() const { return treeSize == 0; }

    Position<E> root() const {
        return Position<E>(rootNode, this);
    }

    Position<E> addRoot(const E& e) {
        if (rootNode != nullptr) throw runtime_error("Root already exists.");
        rootNode = new Node<E>(e);
        treeSize = 1;
        return Position<E>(rootNode, this);
    } // set a node as the root using the value

    Position<E> addChild(const Position<E>& p, const E& e) {
        if (p.v == nullptr) throw runtime_error("Invalid parent.");
        Node<E>* parentNode = p.v;
        Node<E>* childNode = new Node<E>(e, parentNode);
        parentNode->children.push_back(childNode);
        treeSize++;
        return Position<E>(childNode, this);
    }

    friend class Position<E>;
}

// main execution
int main() {
    LinkedTree<string> tree;

    Position<string> root = tree.addRoot("Computer");
    Position<string> driveC = tree.addChild(root, "Drive_C");
    Position<string> driveD = tree.addChild(root, "Drive_D");

    tree.addChild(driveC, "Program_Files");
    tree.addChild(driveC, "Users");



    return 0;
}