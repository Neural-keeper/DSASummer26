/*
Tuesday June 30th, 2026 - Session 13 - Binary Trees
*/

// Github repo link: https://github.com/Neural-keeper/DSASummer26

// Attendance Form Link: https://forms.cloud.microsoft/r/vtcsR1e0bN
// Small reminder - you need to attend the session for 30 minutes AND complete this form for 
// attendance credit, email me if you have concerns. I will be more understanding the sooner 
// you email me.

// day 12 was updated to include methods for height of tree and depth of a node

// instead of writing too much code, we're going to discuss the code for binary trees, then talk
// about their properties and hopefully do a leetcode question on them

// this is a linked structure
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <queue> // for level order traversal (same as breadth first)

// Binary Tree - each node, has 0, 1, or 2 children; is an ordered tree

using namespace std;

template <typename E>
class Tree {
private:
    struct Node {
        E data;
        Node* parent;

        Node* left;
        Node* right;
        
        Node(E value) {
            data = value;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
        }
    };

public:
    // Position class
    class Position {
    private:
        Node* node;
    public:
        Position(Node* n = nullptr) { node = n; }
        E& operator*() { return node->data; } 
        bool isRoot() { return node->parent == nullptr; }
        bool isExternal() { return node->left == nullptr && node->right == nullptr; }
        Position getLeft() { return Position(node->left); }
        Position getRight() { return Position(node->right); }
        Position getParent() { return Position(node->parent); }

        Position sibling() {
            if (node == nullptr || node->parent == nullptr) {
                return Position(nullptr); 
            }
            Node* p = node->parent;
            if (node == p->left) {
                return Position(p->right);
            } else {
                return Position(p->left);
            }
        } // added sibling getter

        Node* getNode() { return node; }
        bool isNull() const { return node == nullptr; }
    };

// the actual tree stuff
private:
    Node* rootNode;
    int treeSize;

    // DESTRUCTOR HELPER: Recursively deletes a subtree (Post-order)
    void deleteSubtree(Node* n) {
        if (n == nullptr) return;
        deleteSubtree(n->left);
        deleteSubtree(n->right);
        delete n;
    }

    // HELPER: Helps recursively print the a tree
    void printHelper(Node* n, const string& prefix, bool isLeft) const {
        if (n == nullptr) return;

        cout << prefix;
        cout << (isLeft ? "|-- (L) " : "\\-- (R) ");
        cout << n->data << endl;

        string newPrefix = prefix + (isLeft ? "|   " : "    ");
        
        if (n->left || n->right) {
            if (n->left) {
                printHelper(n->left, newPrefix, true);
            } else {
                cout << newPrefix << "|-- (L) [Null]" << endl;
            }
            
            if (n->right) {
                printHelper(n->right, newPrefix, false);
            } else {
                cout << newPrefix << "\\-- (R) [Null]" << endl;
            }
        }
    } // slightly more complex tree printer than last time, just looks better

    bool hasPathSumHelper(Node* n, int targetSum) const {
        if (n == nullptr) return false; // null node, leave tree

        int remainingSum = targetSum - n->data;

        //base case 2 - is external leaf node
        if (n->left == nullptr && n->right == nullptr) {
            return (remainingSum == 0);
        }

        return hasPathSumHelper(n->left, remainingSum) || hasPathSumHelper(n->right, remainingSum);
    } // recursive haspathhelper (checks every path to external node)

    // Pre-Order: Node -> Left -> Right
    void preOrderHelper(Node* n) const {
        if (!n) return; 
        cout << n->data << " - ";
        preOrderHelper(n->left);
        preOrderHelper(n->right);
    }

    // In-Order: Left -> Node -> Right
    void inOrderHelper(Node* n) const {
        if (!n) return; 
        inOrderHelper(n->left);
        cout << n->data << " - ";
        inOrderHelper(n->right);
    }

    // Post-Order: Left -> Right -> Node
    void postOrderHelper(Node* n) const {
        if (!n) return; 
        postOrderHelper(n->left);
        postOrderHelper(n->right);
        cout << n->data << " - ";
    }

public:
    Tree() { 
        rootNode = nullptr; 
        treeSize = 0; 
    } //constructor

    // DESTRUCTOR: Cleans up memory to prevent memory leaks
    ~Tree() { 
        deleteSubtree(rootNode); 
    }

    int size() const { return treeSize; }
    bool empty() const { return treeSize == 0; }
    
    Position addRoot(E value) {
        rootNode = new Node(value);
        treeSize++;
        return Position(rootNode);
    }

    Position addChildLeft(Position p, E value) {
        Node* parent = p.getNode();
        if (parent->left != nullptr) {
            throw runtime_error("Error: Left child already exists for this node.");
        }
        Node* child = new Node(value);
        child->parent = parent;
        parent->left = child;
        treeSize++;
        return Position(child);
    }

    Position addChildRight(Position p, E value) {
        Node* parent = p.getNode();
        if (parent->right != nullptr) {
            throw runtime_error("Error: Right child already exists for this node.");
        }
        Node* child = new Node(value);
        child->parent = parent;
        parent->right = child;
        treeSize++;
        return Position(child);
    }

    Position root() {
        return Position(rootNode);
    }

    void printChildren(Position p) {
        Node* parent = p.getNode();
        if (parent == nullptr) return;

        cout << "Left Child: ";
        if (parent->left != nullptr) cout << parent->left->data;
        else cout << "None";
        
        cout << "; Right Child: ";
        if (parent->right != nullptr) cout << parent->right->data;
        else cout << "None";
        
        cout << endl;
    }

    // REPLACE METHOD - returns old data
    E replace(Position p, const E& e) {
        Node* n = p.getNode();
        if (!n) throw runtime_error("Error: Invalid position.");
        E oldData = n->data;
        n->data = e;
        return oldData;
    }

    // REMOVE METHOD (Named 'remove' instead of 'delete' because delete is a keyword)
    // Standard rule: Can only cleanly remove a node if it has 0 or 1 children.
    Position remove(Position p) {
        Node* v = p.getNode();
        if (!v) throw runtime_error("Error: Invalid position.");
        if (v->left != nullptr && v->right != nullptr) {
            throw runtime_error("Error: Cannot remove a node with two children directly.");
        }

        // Find the remaining child (if any)
        Node* child = (v->left != nullptr) ? v->left : v->right;
        
        if (v == rootNode) {
            rootNode = child;
            if (child) child->parent = nullptr;
        } else {
            Node* parent = v->parent;
            if (v == parent->left) parent->left = child;
            else parent->right = child;
            if (child) child->parent = parent;
        }

        Position parentPos(v->parent);
        delete v;
        treeSize--;
        return parentPos; // Returns the parent of the removed node
    }

    // ATTACH METHOD
    // Attaches T1 and T2 as subtrees of an external (leaf) node p
    void attach(Position p, Tree<E>& T1, Tree<E>& T2) {
        Node* n = p.getNode();
        if (!n) throw runtime_error("Error: Invalid position.");
        if (!p.isExternal()) throw runtime_error("Error: Must attach to a leaf node.");

        // Attach T1 to Left
        if (!T1.empty()) {
            n->left = T1.rootNode;
            T1.rootNode->parent = n;
            treeSize += T1.treeSize;
            T1.rootNode = nullptr; // Reset T1 so its destructor doesn't clear our memory
            T1.treeSize = 0;
        }

        // Attach T2 to Right
        if (!T2.empty()) {
            n->right = T2.rootNode;
            T2.rootNode->parent = n;
            treeSize += T2.treeSize;
            T2.rootNode = nullptr; // Reset T2 so its destructor doesn't clear our memory
            T2.treeSize = 0;
        }
    }

    // PUBLIC INTERFACE: Prints the tree structure
    void print() const {
        if (rootNode == nullptr) {
            cout << "[Empty Tree]" << endl;
            return;
        }
        cout << rootNode->data << " (Root)" << endl;
        if (rootNode->left || rootNode->right) {
            if (rootNode->left) printHelper(rootNode->left, "", true);
            else cout << "|-- (L) [Null]" << endl;

            if (rootNode->right) printHelper(rootNode->right, "", false);
            else cout << "/-- (R) [Null]" << endl;
        }
    }

    bool hasPathSum(int targetSum) {
        return hasPathSumHelper(rootNode, targetSum);
    }

    void printPreOrder() const {
        preOrderHelper(rootNode);
        cout << endl;
    }

    void printInOrder() const {
        inOrderHelper(rootNode);
        cout << endl;
    }

    void printPostOrder() const {
        postOrderHelper(rootNode);
        cout << endl;
    }

    // Level-Order (Breadth-First): Explores level by level using a queue
    void printLevelOrder() const {
        if (!rootNode) return;

        queue<Node*> q;
        q.push(rootNode);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->data << " - ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        cout << endl;
    }
};

/*
Binary trees are sometimes stored as arrays (level order if you go by index)
 1  2  3  4  5  6  7
[A, B, C, D, E, F, G, ...]

         A
        / \ 
       B   C
      / \ / \
     D  E F  G

here, you have to define rules. if you are index i in the array (1-indexed array), 
- your left child is at index 2*i
- your right child is at index 2*i + 1
- your parent is at index i / 2 (the integer part)

This waste memory if the tree is sparse (has few external nodes, or too much depth vs density)
It's fast because you just access through indexing. 
*/

/*
// DEMONSTRATION
int main() {
    cout << "=========================================" << endl;
    cout << "   BINARY TREE ADT VISUAL DEMONSTRATION  " << endl;
    cout << "=========================================\n" << endl;

    cout << "--- 1. BUILDING TREE T1 ---" << endl;
    Tree<string> T1;
    auto A = T1.addRoot("A");
    
    auto B = T1.addChildLeft(A, "B");
    auto C = T1.addChildRight(A, "C");
    auto D = T1.addChildLeft(B, "D");
    auto E = T1.addChildRight(B, "E");
    
    T1.print();
    cout << "Current Size: " << T1.size() << "\n" << endl;

    cout << "--- 2. PERFORMING REPLACE (D -> Z) ---" << endl;
    T1.replace(D, "Z");
    T1.print();
    cout << "\n" << endl;

    cout << "--- 3. REMOVING NODE (E) ---" << endl;
    T1.remove(E);
    T1.print();
    cout << "Current Size: " << T1.size() << "\n" << endl;

    cout << "--- 4. ATTACHING SUBTREES TO LEAF NODE C ---" << endl;
    Tree<string> leftSubTree;
    auto subRootL = leftSubTree.addRoot("L1");
    leftSubTree.addChildLeft(subRootL, "L2");

    Tree<string> rightSubTree;
    rightSubTree.addRoot("R1");

    cout << "Tree to attach left (leftSubTree):" << endl;
    leftSubTree.print();
    
    cout << "\nAttaching both leftSubTree and rightSubTree to position C..." << endl;
    T1.attach(C, leftSubTree, rightSubTree);

    cout << "\n--- FINAL STRUCTURAL TREE OUTPUT ---" << endl;
    T1.print();
    cout << "Final Size: " << T1.size() << endl;

    return 0;
}
*/

/*
// LeetCode Demo
int main() {
    Tree<int> T;

    auto A = T.addRoot(2);

    auto B = T.addChildLeft(A, 4);
    auto C = T.addChildRight(A, 6);
    auto D = T.addChildLeft(B, 8);
    auto E = T.addChildRight(B, 10);
    auto F = T.addChildLeft(C, 12);

        //     2
        //    / \
        //   4   6
        //  / \  / 
        // 8  10 12


    cout << "--- CURRENT TREE STRUCTURE ---" << endl;
    T.print();
    cout << "-----------------------------\n" << endl;

    cout << "Does path 22 exist? " << T.hasPathSum(22) << endl; // false (0)
    cout << "Does path 18 exist? " << T.hasPathSum(16) << endl; // 1
    cout << "Does path 10 exist? " << T.hasPathSum(20) << endl; // 1
    cout << "Does path 3 exist? " << T.hasPathSum(3) << endl; // 0

    return 0;
}
*/

/*
// Print version
int main() {
    cout << boolalpha;
    
    Tree<int> T;
    auto root = T.addRoot(5);
    
    auto left = T.addChildLeft(root, 4);
    auto right = T.addChildRight(root, 8);
    
    auto left_left = T.addChildLeft(left, 11);
    T.addChildLeft(left_left, 7);
    T.addChildRight(left_left, 2); // Path: 5 -> 4 -> 11 -> 2 = 22
    
    T.addChildLeft(right, 13);
    auto right_right = T.addChildRight(right, 4);
    T.addChildRight(right_right, 1); // Path: 5 -> 8 -> 4 -> 1 = 18

    cout << "--- CURRENT TREE STRUCTURE ---" << endl;
    T.print();
    cout << "-----------------------------\n" << endl;

    cout << "Testing Target Sum: 22" << endl;
    bool ans1 = T.hasPathSum(22);
    cout << "Result: " << ans1 << "\n" << endl;

    cout << "Testing Target Sum: 18" << endl;
    bool ans2 = T.hasPathSum(18);
    cout << "Result: " << ans2 << "\n" << endl;

    cout << "Testing Target Sum: 10 (Sub-path exists, but doesn't end at a leaf)" << endl;
    bool ans3 = T.hasPathSum(10);
    cout << "Result: " << ans3 << "\n" << endl;

    return 0;
}
*/

int main() {
    cout << "=========================================" << endl;
    cout << "      TREE TRAVERSALS DEMONSTRATION      " << endl;
    cout << "=========================================\n" << endl;

    // --- 1. BUILDING THE SPECIFIED TREE ---
    //             A
    //            / \
    //           B   C
    //          / \   \
    //         D   E   F
    //            / \ / \
    //           G  H I  J
    
    Tree<string> T;
    auto A = T.addRoot("A");
    
    // Level 1
    auto B = T.addChildLeft(A, "B");
    auto C = T.addChildRight(A, "C");
    
    // Level 2
    auto D = T.addChildLeft(B, "D");
    auto E = T.addChildRight(B, "E");
    auto F = T.addChildRight(C, "F");
    
    // Level 3
    T.addChildLeft(E, "G");
    T.addChildRight(E, "H");
    T.addChildLeft(F, "I");
    T.addChildRight(F, "J");

    cout << "--- VISUAL HIERARCHY ---" << endl;
    T.print();
    cout << "------------------------\n" << endl;

    // --- 2. EXECUTING THE TRAVERSALS ---
    
    cout << "Pre-Order (Node -> Left -> Right):" << endl;
    cout << ">> ";
    T.printPreOrder();
    cout << "   (Expected: A - B - D - E - G - H - C - F - I - J)\n" << endl;

    cout << "In-Order (Left -> Node -> Right):" << endl;
    cout << ">> ";
    T.printInOrder();
    cout << "   (Expected: D B G E H A C I F J)\n" << endl;

    cout << "Post-Order (Left -> Right -> Node):" << endl;
    cout << ">> ";
    T.printPostOrder();
    cout << "   (Expected: D G H E B I J F C A)\n" << endl;

    cout << "Level-Order (BFS / Level by Level):" << endl;
    cout << ">> ";
    T.printLevelOrder();
    cout << "   (Expected: A B C D E F G H I J)\n" << endl;

    return 0;
}


// LEETCODE STYLE QUESTION
/*
Given a binary tree and a target integer `sum`, return `true` if the tree has a root-to-leaf path 
such that adding up all the values along the path equals the target sum. Return false otherwise.
*/

// TRAVERSAL
/*
Add methods to demonstrate preorder traversal, postorder traversal, inorder traversal, and level
order traversal.
Tree to demonstrate:
    //             A
    //            / \
    //           B   C
    //          / \   \
    //         D   E   F
    //            / \ / \
    //           G  H I  J

preorder: root -> left -> right : A - B - D - E - G - H - C - F - I - J
inorder: left -> root -> right : D - B - G - E - H - A - C - I - F - J
postorder: left -> right -> root : D - G - H - E - B - I - J - F - C - A
levelorder: A - B - C - D - E - F - G - H - I - J
*/