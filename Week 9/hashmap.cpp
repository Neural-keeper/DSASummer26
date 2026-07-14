#include <iostream>
#include <vector>
#include <list>

/*
     0    |    1      |      2      |      3      |      4
________________________________________________________________
     a         b            c              d             e
                                           f
                                           g


h(i) = i % n
f
i = 13
h(13) = 13 % 5 = 3
g
i = 8
h(8) = 8 % 5 = 3
*/


// Hash Map implementation

class HashMap {
private:
    struct Entry {
        int key;
        std::string value;
    };

    int numBuckets;
    std::vector<std::list<Entry>> table; // Array of doubly-linked lists

    // Hash function + Compression map
    int hashFunc(int key) {
        return key % numBuckets; // h(i) = i % n
        // h(i) = (3i + 5) % n
    }

public:
    HashMap(int buckets = 13) : numBuckets(buckets) {
        table.resize(numBuckets);
    }

    void put(int k, std::string v) {
        int index = hashFunc(k);
        
        // we must search the chain first 
        // to ensure we don't insert duplicate keys.
        for (auto& entry : table[index]) {
            if (entry.key == k) {
                entry.value = v; // Update
                return;
            }
        }
        table[index].push_back({k, v}); // Insert at end of chain
    }
}; // highly simplified version for time, I can add other methods if you want

int main() {
    std::cout << "---  Hash Map (Separate Chaining) ---\n";
    HashMap hMap(13); // 13 buckets
    
    hMap.put(10, "Ten");
    std::cout << "Inserted key 10.\n";
    
    hMap.put(23, "Twenty-Three"); 
    std::cout << "Inserted key 23 (Collides with 10!).\n";

    hMap.put(35, "Thirty-Five");
    std::cout << "Inserted key 35. \n";
    
    hMap.put(10, "Ten Updated");
    std::cout << "Updated key 10.\n";

    return 0;
}