/*
Tuesday June 16th, 2026 - Session 9 - Stacks
*/

// Session Attendance Form: https://forms.cloud.microsoft/r/tKLs8s7rF9
// Only counts if you were in the meeting for 30 minutes

#include <iostream>
#include <string>
#include <vector> //standard library dynamic array
#include <stack> //standard library stack (STL Stack)
#include <stdexcept> //exceptions

#include "LinkedList.h" //importing our local linked list implementation

using namespace std;

/*
Helper for later (hopefully we have enough time for that)
*/
// Templated print helper function
template <typename T>
void printVector(const vector<T>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", "; // Only print a comma if it's not the last element
        }
    }
    cout << "]" << endl;
}

/*
---Array Implementation---
Note - This Stack has fixed size, it's determined at construction, cannot be changed
*/
template <typename T>
class ArrayStack {
private:
    T* arr;
    int maxCapacity;
    int topIndex;

public:
    //constructor
    explicit ArrayStack(int capacity = 10) : maxCapacity(capacity), topIndex(-1) {
        if (capacity <= 0) {
            throw invalid_argument("Capacity has be to greater than 0.");
        }
        arr = new T[capacity];
    }

    // Disable copying to keep the lecture examplesafe
    ArrayStack(const ArrayStack&) = delete;
    ArrayStack& operator=(const ArrayStack&) = delete;

    //destructor 
    ~ArrayStack() {
        delete[] arr;
    }

    bool empty() const {
        return (topIndex == -1);
    }

    int size() const {
        return (topIndex + 1);
    }

    // add to top of stack
    void push(const T& elem) {
        if (topIndex == (maxCapacity - 1)) {
            cout << "Stack Overflow: Max Capacity reached!" << endl;
            return;
        }
        arr[++topIndex] = elem;
    }

    // remove from top of stack
    void pop() {
        if (empty()) {
            cout << "Stack Underflow: Nothing to remove!" << endl;
            return;
        }
        arr[topIndex] = 0;
        topIndex--;
    }

    // see top
    const T& top() const {
        if (empty()) {
            throw underflow_error("Stack is empty!");
        } else {
            return (arr[topIndex]);
        }
    }
};


/*
---Vector Implementation---
*/
template <typename T>
class VectorStack {
private:
    vector<T> vec;
public:
    VectorStack() = default;
    ~VectorStack() = default;

    bool empty() const{
        return vec.empty();
    }

    int size() const{
        return vec.size();
    }

    // add to stack
    void push(const T& elem) {
        vec.push_back(elem);
    }

    // remove from stack
    void pop() {
        if (empty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        vec.pop_back();
    }

    // see top
    const T& top() const {
        if (empty()) {
            throw underflow_error("Stack is empty!");
        } else {
        return vec.back();
        }
    }
};


/*
---Linked List Implementation---
*/
template <typename T>
class LinkedStack {
private:
    LinkedList<T> list;

public:
    LinkedStack() = default;
    ~LinkedStack() = default;

    bool empty() const{
        return list.isEmpty();
    }

    int size() const{
        return list.size();
    }

    void push(const T& elem) {
        list.insertFront(elem);
    }

    void pop() {
        list.removeFront();
    }

    const T& top() const {
        return list.getFront();
    }
};


/*
---LeetCode Style Question---
*/
// PROBLEM
/*
You are a game dev who randomly got sucked into their video game after one too many energy drinks 
at 3 am. Now, you're the master of the Grand Archive because of all your knowledge about your game. 
You have a list (array) of the power level of the most powerful adventurer for every month that 
you train and send off on their first quest. But here's the thing: to the Grand Archive, an 
adventurer is useless if the new adventurer of the month surpasses their power. Your job is to 
track the "shelf life" of each month's hero using your records. 0 here means they've yet to be 
overpowered.
*/
//TEST CASES
/*
- Input: [73, 74, 75, 71, 69, 72, 76, 73]
- Output: [1, 1, 4, 2, 1, 1, 0, 0]

- Input: [50, 80, 30, 45, 60]
- Output: [1, 0, 1, 1, 0]

- Input: [99, 70, 40, 10]
- Output: [0, 0, 0, 0]

- Input: [10, 20, 30, 40]
- Output: [1, 1, 1, 0]`
*/

//SOLUTION
/*
Waiting room stack - for every month, if there's nothing on the waiting room less than this, we push it.
if not, we pop until the number in the waiting room is greater than the current number, then add it. 
every month will be addedd to the waiting room stack at some point.
*/
vector<int> monthlyPower(vector<int>& powers) {
    int n = powers.size();
    vector<int> results(n, 0);

    stack<int> st;

    for(int i = 0; i < n; i++) {
        while(!st.empty() && powers[i] > powers[st.top()]) {
            int prevIndex = st.top();
            st.pop();
            results[prevIndex] = i - prevIndex;
        }
        st.push(i);
    }
    return results;
}


/*MAIN*/

int main() {
    cout << "=== DEMOING THREE STACK IMPLEMENTATIONS ===\n\n";

    // 1. Test Fixed Array Stack
    cout << "[1] Testing Fixed Array Stack (Initialized with capacity of 2)...\n";
    ArrayStack<int> fixedStack(2);
    fixedStack.push(10);
    fixedStack.push(20);
    
    try {
        fixedStack.push(30); // This should fail!
    } catch (const overflow_error& e) {
        cout << " -> Caught expected exception: " << e.what() << "\n";
    }
    cout << "Top of Fixed: " << fixedStack.top() << " | Size: " << fixedStack.size() << "\n\n";


    // 2. Test Vector Stack
    cout << "[2] Testing Vector Stack (Completely dynamic)...\n";
    VectorStack<string> dynamicStack;
    dynamicStack.push("Alpha");
    dynamicStack.push("Beta");
    dynamicStack.push("Gamma"); 
    cout << "Top of Vector: " << dynamicStack.top() << " | Size: " << dynamicStack.size() << "\n\n";
    dynamicStack.pop(); 
    cout << "Top of Vector: " << dynamicStack.top() << " | Size: " << dynamicStack.size() << "\n\n";


    // 3. Test Linked List Stack (using imported methods)
    cout << "[3] Testing Linked List Stack (Wrapping LinkedList.h)...\n";
    LinkedStack<double> listStack;
    listStack.push(3.14);
    listStack.push(2.71);
    cout << "Top of Linked List: " << listStack.top() << " | Size: " << listStack.size() << "\n";
    listStack.pop();
    cout << "After pop, new top: " << listStack.top() << "\n\n";

    cout << "All implementations successfully instantiated and verified!" << endl;

    cout << "Test Cases: " << endl;
    /*
    - Input: [73, 74, 75, 71, 69, 72, 76, 73]
    - Output: [1, 1, 4, 2, 1, 1, 0, 0]

    - Input: [50, 80, 30, 45, 60]
    - Output: [1, 0, 1, 1, 0]

    - Input: [99, 70, 40, 10]
    - Output: [0, 0, 0, 0]

    - Input: [10, 20, 30, 40]
    - Output: [1, 1, 1, 0]`
    */

    vector<int> input1 = {73, 74, 75, 71, 69, 72, 76, 73};

    cout << "Input 1: ";
    printVector(input1);

    vector<int> out1 = monthlyPower(input1);
    
    cout << "Out 1: ";
    printVector(out1);

    vector<int> input2 = {50, 80, 30, 45, 60};

    cout << "Input 2: ";
    printVector(input2);

    vector<int> out2 = monthlyPower(input2);
    
    cout << "Out 1: ";
    printVector(out2);

    vector<int> input3 = {99, 70, 40, 10};

    cout << "Input 3: ";
    printVector(input3);

    vector<int> out3 = monthlyPower(input3);
    
    cout << "Out 3: ";
    printVector(out3);

    vector<int> input4 = {10, 20, 30, 40};

    cout << "Input 4: ";
    printVector(input4);

    vector<int> out4 = monthlyPower(input4);
    
    cout << "Out 4: ";
    printVector(out4);

    return 0;
}