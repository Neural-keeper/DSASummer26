/*
Thursday July 2nd, 2026 - Session 14 - Binary Search Trees
*/

// Attendance form link: https://forms.cloud.microsoft/r/VrJ823uah5
// Github repo link: https://github.com/Neural-keeper/DSASummer26

// to keep the code shorter and simpler, I'm not using abstraction through Positions, and working
// with the Node pointers directly


#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
struct Node {
    int key;
    T data;
    Node *left, *right;
    Node(int k, T val) : key(k), data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
    Node<T>* root;

    // Helper function for recursive deletion (post order)
    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node; 
        }
    }
public:
    BST() : root(nullptr) {}
    ~BST() {
        destroyTree(root);
    }
    Node<T>* getRoot() { return root; }

    // recursive search
    Node<T>* search(Node<T>* n, int key) {
        // Base case - we found the node, or we are outside the tree
        if (n == nullptr || n->key == key) { 
            return n; 
        }
        if (key < n->key) {
            return search(n->left, key);
        } else {
            return search(n->right, key);
        }
    }

    // iterative insert
    void insert(int key, T data) {
        if (root == nullptr) {
            root = new Node<T>(key, data);
            return;
        }

        Node<T>* curr = root;
        while (curr != nullptr) {
            if (key < curr->key) {
                if (curr->left == nullptr) {
                    curr->left = new Node<T>(key, data);
                    break;
                }
                curr = curr->left;
            } else if (key > curr->key) {
                if (curr->right == nullptr) {
                    curr->right = new Node<T>(key, data);
                    break;
                }
                curr = curr->right;
            } else {
                curr->data = data;
                break;
            }
        }
    }

    // iterative
    Node<T>* findMin(Node<T>* n) {
        if (n == nullptr) return nullptr;
        while (n->left != nullptr) n = n->left;
        return n;
    }

    Node<T>* findMax(Node<T>* n) {
        if (n == nullptr) return nullptr;
        while (n->right != nullptr) n = n->right;
        return n;
    }

    // a little too complicated for this session, lmk if you want it explained
    Node<T>* deleteNode(Node<T>* n, int key) {
        if (n == nullptr) return nullptr;

        // 1. Search for the node
        if (key < n->key) {
            n->left = deleteNode(n->left, key);
        } else if (key > n->key) {
            n->right = deleteNode(n->right, key);
        } else {
            // 2. Found the node! Handle the 3 cases
            
            // Case A & B: Zero or one child
            if (n->left == nullptr) {
                Node<T>* temp = n->right;
                delete n;
                return temp;
            } else if (n->right == nullptr) {
                Node<T>* temp = n->left;
                delete n;
                return temp;
            }

            // inorder successor - smallest element in the right subtree (findMin(right))
            // inorder precedessor - largest element in the left subtree (findMax(left))

            // Case C: Two children
            // Get the inorder successor (smallest in the right subtree)
            Node<T>* temp = findMin(n->right);
            
            // Copy the successor's content to this node
            n->key = temp->key;
            n->data = temp->data;
            
            // Delete the successor
            n->right = deleteNode(n->right, temp->key);
        }
        return n;
    }
};

// Array based BST Search goes here
// index i has children at 2*i+1 and 2*i+2
int arrayBSTSearch(const vector<int>& tree, int index, int targetKey) {
    // BASE CASE: If index is out of bounds or we hit a placeholder (-1), 
    // the key isn't in this branch.
    if (index >= tree.size() || tree[index] == -1) return -1;
    
    // SUCCESS: If the current index holds our key, return the index.
    if (tree[index] == targetKey) return index;
    
    // RECURSION: 
    // If target < current node, move to the left child's index.
    if (targetKey < tree[index]) {
        return arrayBSTSearch(tree, index * 2 + 1, targetKey);
    } else {
        return arrayBSTSearch(tree, index * 2 + 2, targetKey);
    }
    // If target > current node, move to the right child's index.
}

int main() {
    // BST Demo
    cout << "Demo 1 - Students, using student ID as key." << endl;
    BST<string> studentTree;
    
    studentTree.insert(101, "Alice");
    studentTree.insert(50, "Bob");
    studentTree.insert(150, "Charlie");

    Node<string>* found = studentTree.search(studentTree.getRoot(), 50);
    if (found) {
        cout << "Found ID 50: " << found->data << endl;
    }

    Node<string>* min = studentTree.findMin(studentTree.getRoot());
    if (min) {
        cout << "Found minimum: " << min->key << "; " << min->data << endl;
    } else {
        cout << "Tree is empty!" << endl;
    }

    cout << "Demo 2 - Gods, using order of birth as key." << endl;

    BST<string> godTree;

    godTree.insert(4, "Poseidon");
    godTree.insert(6, "Zeus");
    godTree.insert(5, "Hades");
    godTree.insert(1, "Hestia");
    godTree.insert(3, "Hera");
    godTree.insert(2, "Demeter");

    Node<string>* youngest = godTree.findMax(godTree.getRoot());
    if (youngest) {
        cout << "Found youngest: " << youngest->key << "; " << youngest->data << endl;
    } else {
        cout << "Tree is empty!" << endl;
    }

    Node<string>* foundGod = godTree.search(godTree.getRoot(), 50);
    if (foundGod) {
        cout << "Found key 50: " << foundGod->data << endl;
    } else {
        cout << "Did not find that key in the tree." << endl;
    }

    foundGod = godTree.search(godTree.getRoot(), 5);
    if (foundGod) {
        cout << "Found key 5: " << foundGod->data << endl;
    } else {
        cout << "Did not find that key in the tree." << endl;
    }

    // Array BST Search Demo
    vector<int> arrayTree = {10, 5, 15, 2, 8, -1, -1}; // here, -1 implies placeholder
    // this is already a BST, btw.
    
    int resultIndex = arrayBSTSearch(arrayTree, 0, 8);
    cout << "8 found at index: " << resultIndex << endl;

    return 0;
}