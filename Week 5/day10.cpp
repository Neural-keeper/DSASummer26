/*
Thursday June 18th, 2026 - Session 10 - Queues
*/

// Session Attendance Form: https://forms.cloud.microsoft/r/P84scuw4me
// Only counts if you were in the meeting for 30 minutes

#include <iostream>
#include <string>
#include <queue> //standard library queue (STL Queue)
#include <deque> //standard library deque (Douhle Ended Queue, pronounced "deck")
#include <stdexcept> //exceptions

// might need these for the leetcode question at the end
#include <cassert>
#include <cmath>
#include <vector>

#include "LinkedList.h" //importing our local linked list implementation
#include "CLinkedList.h" //importing our local circularly linked list implementation

using namespace std;

/*-------------------------------
Linked List Implementation
---------------------------------*/
template <typename T>
class LinkedQueue {
private:
    LinkedList<T> slist;
public:
    LinkedQueue() {}

    bool isEmpty() const {
        return slist.isEmpty();
    }

    int size() const {
        return slist.size();
    }

    void enqueue(const T& val) {
        slist.insertBack(val);
    }

    void dequeue() {
        if (isEmpty()) {
            throw underflow_error("List is Empty");
        }
        slist.removeFront();
    }

    const T& front() const {
        if (isEmpty()) {
            throw underflow_error("List is Empty");
        }
        return slist.getFront();
    }
};



/*-------------------------------
Circularly Linked List Implementation
---------------------------------*/
template <typename T>
class CLinkedQueue {
private:
    CircularLinkedList<T> clist;
public:
    CLinkedQueue() {}

    bool isEmpty() const {
        return clist.isEmpty();
    }

    int size() const {
        return clist.size();
    }

    void enqueue(const T& val) {
        clist.insertBack(val);
    }

    void dequeue() {
        if (isEmpty()) {
            throw underflow_error("List is Empty");
        }
        clist.removeFront();
    }

    const T& front() const {
        if (isEmpty()) {
            throw underflow_error("List is Empty");
        }
        return clist.getFront();
    }
};


/*-------------------------------
Circular Array Implementation
---------------------------------*/
template <typename T, int CAPACITY>
class CArrayQueue {
private:
    T arr[CAPACITY];
    int frontid; //the index of the "front" of the queue
    int rear; //the index of the "back" of the queue - the index at which new elements can be added
    int qsize; //keep track, for O(1) retrieval

public:
    CArrayQueue() : frontid(0), rear(0), qsize(0) {}

    bool isEmpty() const {
        return (qsize == 0);
    }

    bool isFull() const {
        return (qsize == CAPACITY);
    }

    int size() const {
        return qsize;
    }

    void enqueue(const T& val) {
        if (isFull()) {
            throw overflow_error("Queue is fully filled!");
        }
        arr[rear] = val;
        rear = (rear + 1) % CAPACITY;
        qsize++;
    }

    void dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty!");
        }
        frontid = (frontid + 1) % CAPACITY;
        qsize--;
    }

    const T& front() const {
        if (isEmpty()) {
            throw underflow_error("Queue is empty!");
        }
        return arr[frontid];
    }
};





/*-------------------------------
LeetCode Style Question
---------------------------------*/
/*
 * ============================================================================
 * ENGINEERING CONTEXT: Real-Time DevOps Server Telemetry
 * ============================================================================
 * You are an infrastructure engineer building an automated alert system for a 
 * cloud platform. Servers constantly stream metrics such as "CPU Utilization %" 
 * or "Requests Per Second" to your monitoring service.
 * * Aggregating individual raw values causes false positive alerts due to short,
 * harmless performance spikes. To solve this, your team uses a "Sliding Window 
 * Moving Average" to smooth out the data stream. If the running average over the 
 * last 'W' intervals crosses a threshold, an automated alert fires.
 * * ============================================================================
 * SYSTEM SPECIFICATION
 * ============================================================================
 * Implement a highly efficient telemetry aggregator component.
 * * Class Template:
 * MovingAverage(int window_size) 
 * - Initializes the tracking engine with a static maximum history window.
 * * double next(int value) 
 * - Ingests the latest raw metric value from the data stream.
 * - Returns the calculated rolling average of the last 'window_size' metrics.
 * * Algorithmic Constraints:
 * - Memory Consumption: Must remain constant relative to the stream length.
 * - Execution Speed: O(1) per evaluation. Traversal of the history window 
 * on every incoming packet is prohibited due to high throughput requirements.
 * ============================================================================
 */

/*
STL Queues:
enqueue - push(val)
dequeue - pop() - returns void - won't print anything or give values
front()
empty()
*/

class MovingAverage {
private:
    queue<int> stream;
    int maxSize;
    double rollingSum;

public:
    MovingAverage(int window_size) {
        maxSize = window_size;
        rollingSum = 0.0;
    }

    double next(int value) {
        stream.push(value);
        rollingSum += value;
        if (stream.size() > maxSize) {
            rollingSum -= stream.front();
            stream.pop();
        }
        return (rollingSum / stream.size());
    }
};

// ============================================================================
// AUTOMATED TEST SUITE (VALIDATION ENVIRONMENT)
// ============================================================================

/*
bool verifyResult(double actual, double expected, double tolerance = 0.0001) {
    return std::abs(actual - expected) < tolerance;
}

int main() {
    std::cout << "===================================================\n";
    std::cout << " STARTING SERVICE TELEMETRY VALIDATION CHECKS       \n";
    std::cout << "===================================================\n\n";

    // --- TEST SCENARIO 1: CPU Monitoring Window (Size = 3) ---
    std::cout << "[SCENARIO 1] Monitoring Active CPU Utilization (Window = 3)...\n";
    MovingAverage cpuTracker(3);
    
    double t1 = cpuTracker.next(10); // Current window: [10]
    std::cout << "   -> Ingested: 10%  | Moving Avg: " << t1 << "% (Expected: 10.0%)\n";
    assert(verifyResult(t1, 10.0));

    double t2 = cpuTracker.next(20); // Current window: [10, 20]
    std::cout << "   -> Ingested: 20%  | Moving Avg: " << t2 << "% (Expected: 15.0%)\n";
    assert(verifyResult(t2, 15.0));

    double t3 = cpuTracker.next(60); // Current window: [10, 20, 60] (Spike detected)
    std::cout << "   -> Ingested: 60%  | Moving Avg: " << t3 << "% (Expected: 30.0%)\n";
    assert(verifyResult(t3, 30.0));

    double t4 = cpuTracker.next(40); // Current window: [20, 60, 40] (10% drops out)
    std::cout << "   -> Ingested: 40%  | Moving Avg: " << t4 << "% (Expected: 40.0%)\n";
    assert(verifyResult(t4, 40.0));
    std::cout << ">> [SUCCESS] Scenario 1 Telemetry Processing Confirmed.\n\n";


    // --- TEST SCENARIO 2: Strict Real-Time Window (Size = 1) ---
    std::cout << "[SCENARIO 2] Microsecond Ticker Processing (Window = 1)...\n";
    MovingAverage directTicker(1);
    
    double t5 = directTicker.next(100);
    std::cout << "   -> Ingested: 100  | Moving Avg: " << t5 << " (Expected: 100.0)\n";
    assert(verifyResult(t5, 100.0));

    double t6 = directTicker.next(250);
    std::cout << "   -> Ingested: 250  | Moving Avg: " << t6 << " (Expected: 250.0)\n";
    assert(verifyResult(t6, 250.0));
    std::cout << ">> [SUCCESS] Scenario 2 Boundary Conditions Verified.\n\n";


    // --- TEST SCENARIO 3: Thermal Telemetry with Negative Offsets (Window = 2) ---
    std::cout << "[SCENARIO 3] Environmental Cold-Storage Thermostat (Window = 2)...\n";
    MovingAverage thermalSensor(2);
    
    double t7 = thermalSensor.next(-5); // Current window: [-5]
    std::cout << "   -> Ingested: -5C  | Moving Avg: " << t7 << "C (Expected: -5.0C)\n";
    assert(verifyResult(t7, -5.0));

    double t8 = thermalSensor.next(15); // Current window: [-5, 15]
    std::cout << "   -> Ingested: 15C  | Moving Avg: " << t8 << "C (Expected: 5.0C)\n";
    assert(verifyResult(t8, 5.0));

    double t9 = thermalSensor.next(-1); // Current window: [15, -1] (-5C drops out)
    std::cout << "   -> Ingested: -1C  | Moving Avg: " << t9 << "C (Expected: 7.0C)\n";
    assert(verifyResult(t9, 7.0));
    std::cout << ">> [SUCCESS] Scenario 3 Negative Data Parsing Verified.\n\n";

    std::cout << "===================================================\n";
    std::cout << " STATUS: ALL ALGORITHMIC PIPELINES PASSED!         \n";
    std::cout << "===================================================\n";
    return 0;
}

*/

int main() {
    /*Expected Output*/
    cout << "EXPECTED" << endl;
    cout << "90" << endl;
    cout << "100" << endl;
    cout << "100" << endl;

    /*Linked List Implementation*/
    cout << "LinkedQueue" << endl;
    LinkedQueue<int> rideLine;
    rideLine.enqueue(90);
    rideLine.enqueue(100);
    rideLine.enqueue(10);
    cout << rideLine.front() << endl;
    rideLine.dequeue();
    cout << rideLine.front() << endl;
    rideLine.enqueue(50);
    cout << rideLine.front() << endl;

    /*Circularly Linked List Implementation*/
    cout << "CircLinkedQueue" << endl;
    CLinkedQueue<int> CrideLine;
    CrideLine.enqueue(90);
    CrideLine.enqueue(100);
    CrideLine.enqueue(10);
    cout << CrideLine.front() << endl;
    CrideLine.dequeue();
    cout << CrideLine.front() << endl;
    CrideLine.enqueue(50);
    cout << CrideLine.front() << endl;

    /*Circular Array Implementaiton*/
    cout << "CircArrQueue" << endl;
    CArrayQueue<int, 10> arideLine;
    arideLine.enqueue(90);
    arideLine.enqueue(100);
    arideLine.enqueue(10);
    cout << arideLine.front() << endl;
    arideLine.dequeue();
    cout << arideLine.front() << endl;
    arideLine.enqueue(50);
    cout << arideLine.front() << endl;

    return 0;
}