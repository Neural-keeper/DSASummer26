#include <iostream>
#include <vector>

/*
capacity: 11

 0  1  2  3  4  5  6  7  8  9   10
22           4              31  10
22           4  15          31  10
22           4  15          31  10
22           4  15          31  10

Insert: 10, 22, 31, 4, 15
hash function: h(i) = i % n

10: 10 % 11 = 10
22: 22 % 11 = 0
31: 31 % 11 = 9
4: 4 % 11 = 4
15: 15 % 11 = 4
    linear probing: h(i, k) = (h(i) + k) % n 
*/


// Open Addressing 

class OpenAddressingMap {
private:
    struct Entry {
        int key;
        int value;
        bool isDefunct; 
        
        Entry(int k, int v) : key(k), value(v), isDefunct(false) {}
    };

    std::vector<Entry*> table;
    int capacity;

    int hash(int key) { return key % capacity; }
    int hash2(int key) { return 7 - (key % 7); } // Must be prime, non-zero

public:
    OpenAddressingMap(int cap) : capacity(cap) {}
    // i, starting at 0, represents the attempt number

    int getLinearProbeIndex(int key, int i) {
        return (hash(key) + i) % capacity;
    }

    int getQuadraticProbeIndex(int key, int i) {
        // Primary clustering is fixed, but 
        // secondary clustering can still happen.
        return (hash(key) + (i * i)) % capacity;
    }

    int getDoubleHashIndex(int key, int i) {
        // hash2(key) can never return 0.
        // If it returns 0, we'd get stuck in an infinite loop checking the same index.
        return (hash(key) + i * hash2(key)) % capacity;
    }
};

int main() {
    // Initializing with a capacity of 11 for the whiteboard exercise
    OpenAddressingMap oam(11); 
    
    std::cout << "--- 4. Open Addressing Probing Demo ---\n";
    std::cout << "Array Capacity: 11\n\n";
    
    std::cout << "Scenario: We just inserted 4 at index 4.\n";
    std::cout << "Now we want to insert 15. Hash(15) = 15 % 11 = 4.\n";
    std::cout << "Collision at index 4!\n\n";
    
    // TA HIGHLIGHT: Run the code to prove the math you just did on the board.
    std::cout << "Where does 15 go next? (Attempt i=1)\n";
    std::cout << "Linear Probing Index:    " << oam.getLinearProbeIndex(15, 1) << "\n";
    std::cout << "Quadratic Probing Index: " << oam.getQuadraticProbeIndex(15, 1) << "\n";
    std::cout << "Double Hashing Index:    " << oam.getDoubleHashIndex(15, 1) << "\n";

    return 0;
}