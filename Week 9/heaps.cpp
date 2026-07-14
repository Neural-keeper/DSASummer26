#include <iostream>
#include <vector>


// 7. Quick Overview of Heaps (Time Permitting)

class MinHeap {
private:
    std::vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    void upheap(int i) {
        // While not at root, and parent is greater than current node
        while (i != 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    void push(int key) {
        heap.push_back(key); // Insert at bottom
        upheap(heap.size() - 1); // Bubble up
    }

    void printHeap() {
        for (int val : heap) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    std::cout << "--- 7. Min-Heap Demo ---\n";
    MinHeap myHeap;

    myHeap.push(30);
    myHeap.push(20);
    myHeap.push(10); 

    std::cout << "Inserted 30, 20, 10.\n";
    std::cout << "Underlying Array State: ";
    myHeap.printHeap(); // Expected output: 10 30 20 (or 10 20 30 depending on swap logic)

    return 0;
}