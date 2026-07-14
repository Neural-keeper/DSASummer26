#include <iostream>
#include <algorithm>

// AVL Trees Implementation 
// Also - Balance Factors & Differences

/*
AVL is a balanced binary search tree - useful for when added in order [1, 2, 3, 4, 5, 6, 7]
*/
/*
BST - height avg O(log n) worst case O(n), worst case search O(n)
AVL Tree - height is capped at O(log n), search O(log n)
*/

struct AVLNode {
    int key; // key is the same as the value
    AVLNode* left;
    AVLNode* right;
    int height; // main difference from BST

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLNode* root;
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

private:
    int height(AVLNode* N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    // Balance factor must be -1, 0, or 1.
    int getBalance(AVLNode* N) {
        if (N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights (Must update y first, then x!)
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x; // New root
    }

    AVLNode* insert(AVLNode* node, int key) {
        // 1. Standard BST insertion (Base Case)
        if (node == nullptr) return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // Duplicates not allowed in this set

        // 2. Update height of this ancestor node
        node->height = 1 + std::max(height(node->left), height(node->right));

        // 3. Get the balance factor
        int balance = getBalance(node);

        // If node becomes unbalanced, there are 4 cases:
        
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            // node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // (Right Right and Right Left omitted for brevity, logic mirrors above), will add later
        return node;
    }
};

int main() {
    std::cout << "--- AVL Tree Demo ---\n";
    AVLTree tree;

    std::cout << "Inserting 30...\n";
    tree.insert(30);
    
    std::cout << "Inserting 20...\n";
    tree.insert(20);
    
    // TA HIGHLIGHT: This triggers the Left-Left Case and forces a Right Rotation!
    std::cout << "Inserting 10 (Triggers Right Rotation)...\n";
    tree.insert(10);

    // If rotation worked, 20 should now be the root.
    std::cout << "\nTree stabilized.\n";
    if (tree.root != nullptr) {
        std::cout << "New Root is: " << tree.root->key << " (Expected: 20)\n";
        std::cout << "Root's Left Child is: " << tree.root->left->key << " (Expected: 10)\n";
        std::cout << "Root's Right Child is: " << tree.root->right->key << " (Expected: 30)\n";
    }

    return 0;
}