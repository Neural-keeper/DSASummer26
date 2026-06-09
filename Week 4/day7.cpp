/*
Tuesday June 9th, 2026 - Session 7 - Linked Lists (Single, Double, and Circular)
*/

#include <iostream>
#include <string>

using namespace std;

// Assignment link: https://forms.cloud.microsoft/r/dXjiC5nK4t

// ============================================================================
// ACT I: THE JOURNAL LOGS (Singly Linked List)
// Focus: Reverse a Linked List (In-Place Reversal)
//
// PROBLEM STATEMENT: 
// "Cathy's journal logs were reversed by an evil sorceress. Implement a function
// to reverse the direction of a singly linked list completely IN-PLACE 
// using O(1) extra space to demonstrate what happened."
// ============================================================================
/*
a) create a singly linked list to represent her journal
b) add to the end of the linked list
c) remove from anywhere 
d) create a method to reverse the linked list in place (LeetCode Type Problem)
e) display the logs from front to back
*/

struct EventNode {
    string event;
    EventNode* next = nullptr;

    EventNode(string evnt) : event(evnt) {}
};
//they're just like classes without access specifiers - all public

//default access specifier for a class is 'private'
class Log {
public:
    EventNode* head = nullptr;

    // destructor - clean up memory
    ~Log() {
        EventNode* current = head;
        while (current != nullptr) {
            EventNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    // add event node to end of linked list
    void addEvent(string evnt) {
        EventNode* newNode = new EventNode(evnt);

        if (!head) {
            head = newNode;
            return;
        }

        EventNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
        cout << "New event node '" << evnt << "' added!\n";
    }

    // remove node from anywhere
    void removeEvent(string item) {
        if (!head) {
            cout << "[System] No event to remove, journal is empty!" << endl;
            return;
        }

        if (head->event == item) {
            EventNode* temp = head;
            head = head->next;
            delete temp;
            cout << "[System] Requested item '" << item << "' was removed!" << endl;
            return;
        }

        EventNode* prev = head;
        EventNode* curr = head->next;
        while (curr != nullptr) {
            if (curr->event == item) {
                prev->next = curr->next;
                delete curr;
                cout << "[System] Requested item '" << item << "' was removed!" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        
        cout << "[System] Requested item '" << item << "' was not found." << endl;
    }

    // display log
    void displayLog() {
        EventNode* temp = head;
        while (temp != nullptr) {
            cout << " -> [" << temp->event << "]";
            temp = temp->next;
        }
        cout << " -> (End of Log)\n";
    }

    // reverse linked list in place
    void reverseLog() {
        EventNode* prev = nullptr;
        EventNode* curr = head;
        EventNode* next = nullptr;

        while (curr != nullptr) {
            next = curr->next; //save our current traversal progression
            curr->next = prev;
            prev = curr;
            curr = next; 
        }

        head = prev; // reassign the head to the new head
    } // space complexity O(1), whatever added (pointers) are constant, regardless of how big the linked list is
};




// ============================================================================
// ACT II: THE INVENTORY TOOLBELT (Doubly Linked List)
// Focus: Deleting an arbitrary node from the middle of a Doubly LL
//
// PROBLEM STATEMENT: 
// "Cathy needs to store items to build a magic staff in the magical inventory
// toolbelt Martha gave her. When she uses an item from the middle of her 
// inventory. Safely sever the item's node from the list and reconnect
// its neighbors without dropping items or leaking memory."
// ============================================================================
/*
OBJECTIVES:
a) implement a doubly linked list
b) add to end
c) MAIN - remove from anywhere in a doubly linked list
*/

struct ItemNode {
    string itemName;
    ItemNode* next = nullptr;
    ItemNode* prev = nullptr;

    ItemNode(string name) : itemName(name) {}
}; //node for each item

class InventoryBelt {
public:
    ItemNode* head = nullptr;
    ItemNode* tail = nullptr;

    // Destructor: Prevent memory leaks
    ~InventoryBelt() {
        ItemNode* current = head;
        while (current != nullptr) {
            ItemNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    // Standard Doubly LL Insertion (Push to Tail)
    void equipItem(string name) {
        ItemNode* newItem = new ItemNode(name);
        if (!head) {
            head = tail = newItem;
            return;
        }
        tail->next = newItem;
        newItem->prev = tail;
        tail = newItem;
    }

    // Remove from DLL (anywhere)
    void removeItem(string name) {
        ItemNode* curr = head;

        while (curr != nullptr) {
            if (curr->itemName == name) {
                if (curr == head) {
                    head = head->next;
                    if (head) head->prev = nullptr;
                } else if (curr == tail) {
                    tail = tail->prev;
                    if (tail) tail->next = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                
                delete curr;
                cout << "[SYSTEM] " << name << " was deleted!\n";
                return;
            }
            curr = curr->next;
        }

        cout << "[SYSTEM] The requested item was not found." << endl;
    }

    void displayBelt() {
        ItemNode* temp = head;
        cout << "  Belt State: NULL <-> ";
        while (temp != nullptr) {
            cout << "[" << temp->itemName << "] <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};






// ============================================================================
// ACT III: A ROUND TABLE SUMMONING (Circularly Linked List via Cursor)
// Focus: Linked List Cycle (Safe Circular Traversal)
//
// PROBLEM STATEMENT: 
// "Cathy gathers the Princess's friends to help her summon the Divisor's Council
// They all sit at a round table and pass a magic staff clockwise eaxctly 7 times.
// By maintaining a 'cursor' pointing to the tail of the list, we gain O(1) 
// access to both the front (cursor->next) and the back (cursor) of the circle."
// ============================================================================
struct FriendNode {
    string name;
    FriendNode* next = nullptr;

    FriendNode(string n) : name(n) {}
};

class FriendCircle {
public:
    // Best Practice: cursor points to the trailing node of the ring
    FriendNode* cursor = nullptr;
    int size = 0;

    // Destructor: Break the ring at the cursor to cleanly deallocate memory
    ~FriendCircle() {
        if (!cursor) return;

        FriendNode* head = cursor->next; // The true "start" of the circular sequence
        cursor->next = nullptr;          // Break the circle into a linear linked list

        FriendNode* current = head;
        while (current != nullptr) {
            FriendNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        cursor = nullptr;
    }

    // Elegant O(1) Insertion using the Cursor property - You don't traverse through the CLL to get to the point where you can add
    void addFriend(string name) {
        FriendNode* newFriend = new FriendNode(name);
        
        if (!cursor) {
            cursor = newFriend;
            cursor->next = cursor; // Node points to itself to close the initial ring
            return;
        }
        
        // Connect the new node to the front of the circle
        newFriend->next = cursor->next;
        // Make the current tail point to the new node
        cursor->next = newFriend;
        // update cursor to new friend
        cursor = newFriend;
        size++;
    }

    // SAFE TRAVERSAL (Avoiding Infinite Loops)
    void passStaff(int rounds) {
        int totalSteps = rounds*size;

        if (!cursor) {
            cout << "  The circle is empty.\n";
            return;
        }
        
        // Start passing from the front of the circle (cursor->next)
        FriendNode* curr = cursor->next;
        cout << "  Staff Movement Simulation:\n";
        
        for (int step = 1; step <= totalSteps; ++step) {
            cout << "    Step " << step << ": " << curr->name << " holds the magical staff.\n";
            curr = curr->next; // Rotates smoothly through the closed ring
        }
    }
};












// MAIN
int main() {
    // ACT I Test
    // Log Journal;
    // Journal.addEvent("The first war");
    // Journal.addEvent("The formation of Teers");
    // Journal.addEvent("Second COIR meeting");
    // Journal.addEvent("Disappearance of the Queen");
    // Journal.addEvent("Reappearance of the Princess");

    // cout << "Initially, Cathy's journal was: " << endl;
    // Journal.displayLog();

    // Journal.reverseLog();

    // cout << "But now, after the curse, her journal was reversed: " << endl;
    // Journal.displayLog();

    


    //ACT II Test
    // InventoryBelt Satchel;

    // Satchel.equipItem("Orb");
    // Satchel.equipItem("Wand");
    // Satchel.equipItem("Twine");
    // Satchel.equipItem("Hilt");
    // Satchel.equipItem("Potion");

    // cout << "Cathy's satchel currently has:" << endl;
    // Satchel.displayBelt();

    // Satchel.removeItem("Orb");

    // cout << "After removing, it is:" << endl;
    // Satchel.displayBelt();



    //ACT III Test
    // FriendCircle Circle;
    // Circle.addFriend("Cathy");
    // Circle.addFriend("Lana");
    // Circle.addFriend("Krish");
    // Circle.addFriend("Aquaris");
    // Circle.addFriend("Jusia");
    // Circle.addFriend("Kian");

    // Circle.passStaff(3);

    return 0;
}