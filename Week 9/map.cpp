#include <iostream>
#include <string>
#include <map>

// Map ADT via Doubly Linked List

struct Entry {
    int key;
    std::string value;
    Entry* prev;
    Entry* next;
    Entry(int k, std::string v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class DLLMap {
private:
    Entry* head;
    Entry* tail;

public:
    DLLMap() : head(nullptr), tail(nullptr) {}

    void put(int k, std::string v) {
        Entry* curr = head;
        while (curr != nullptr) {
            if (curr->key == k) {
                curr->value = v; // Update existing
                return;
            }
            curr = curr->next;
        }
        
        // If not found, append to tail
        Entry* newEntry = new Entry(k, v);
        if (!head) {
            head = tail = newEntry;
        } else {
            tail->next = newEntry;
            newEntry->prev = tail;
            tail = newEntry;
        }
    } // time complexity O(n)

    // Returns the value if found, or an empty string if not found
    // Also takes O(n) time
    std::string find(int k) {
        Entry* curr = head;
        while (curr != nullptr) {
            if (curr->key == k) {
                return curr->value;
            }
            curr = curr->next;
        }
        return ""; // Not found
    }

    // Removes the entry with the given key. Returns true if successful, false if not found.
    // Takes O(n) time to find the node, but O(1) time to remove it once found.
    bool remove(int k) {
        Entry* curr = head;
        while (curr != nullptr) {
            if (curr->key == k) {
                
                // 1. Rewire the previous node (or update head)
                if (curr->prev != nullptr) {
                    curr->prev->next = curr->next;
                } else {
                    head = curr->next; 
                }

                // 2. Rewire the next node (or update tail)
                if (curr->next != nullptr) {
                    curr->next->prev = curr->prev;
                } else {
                    tail = curr->prev; 
                }

                // 3. Delete the isolated node
                delete curr;
                return true;
            }
            curr = curr->next;
        }
        return false; // Key not found
    }
};

// Map STL Important Methods (2 mins)

void stlMapDemo() {
    std::map<int, std::string> studentScores;
    
    studentScores[101] = "Alice"; // [] can add if key doesn't exist, update if it does
    studentScores.insert({102, "Bob"}); // add Bob
    studentScores[101] = "Alezanddria";
    studentScores[103]; // use default constructor, ""
}

int main() {
    std::cout << "--- 1. DLL Map Implementation ---\n";
    DLLMap myMap;
    
    myMap.put(1, "Alice");
    myMap.put(2, "Bob");
    myMap.put(3, "Charlie");
    
    // you update the key, not create a new one
    myMap.put(1, "Alice Updated"); 
    std::cout << "Operations complete. (Added Alice, Bob, Charlie, updated Alice)\n";

    // Test find
    std::cout << "Find Key 1: " << myMap.find(1) << "\n";
    std::cout << "Find Key 3: " << myMap.find(3) << "\n";
    std::cout << "Find Key 99 (doesn't exist): " << (myMap.find(99).empty() ? "Not Found" : myMap.find(99)) << "\n\n";

    // Test remove
    std::cout << "Removing Key 2 (Bob)...\n";
    myMap.remove(2);
    std::cout << "Find Key 2 after removal: " << (myMap.find(2).empty() ? "Not Found" : myMap.find(2)) << "\n\n";

    std::cout << "--- 2. STL Map Demo ---\n";
    stlMapDemo();
    std::cout << "STL Map demo complete.\n";

    return 0;
}