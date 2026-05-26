/*
TUESDAY - MAY 26th, Session 3 - C++ Basics
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Player {
    string name;
    int HP = 500; //default for new player as 500
    bool isActive = true; //by default, active
    int score = 0; //default score 0
    int level = 0;
};

// struct Node {
//     int value = 0;
//     Node* next = nullptr;
// }; //will talk about soon, when talking about linked lists

void displayPlayer(Player P) {
    cout << "Name: " << P.name << endl;
    cout << "HP: " << P.HP << endl;
    cout << "Score: " << P.score << endl;
    cout << "Level: " << P.level << endl;
}

struct NPC {
    string name;
    int health = 50;
};

struct Villager : public NPC {
    string profession;
    string village;
};

struct God : public NPC {
    string power;
};

typedef Player* PlayerPtr;
// typedef vector<vector<vector<string>>> d3vs;

void refreshPointers();
void dynamicMemoryLeak();
PlayerPtr dynamicPlayer(string name, int health, int score, int lvl);
void resizeArray(int*& arr, int currSize, int newSize);
void addToVector(vector<int>& arr, int newnum);
void printVec(vector<int>& arr);
void clearVec(vector<int>& arr);


int main() {
    // Player p1;
    // p1.name = "John Smith";
    // p1.HP = 600;
    // p1.score = 1000; //overall score 
    // p1.level = 1;

    // Player p2;
    // p2.name = "Eve Smith";
    // p2.score = 800;
    
    // Player p3 = p1;
    // p3.name = "John2"; //new name for p3

    // // cout << "Player 1 Name: " << p1.name << endl;
    // // cout << "PLayer 2 Name: " << p2.name << endl;
    // // cout << "Player 3 Name: " << p3.name << endl;

    // displayPlayer(p1);

    /*___*/

    // NPC npc1;
    // npc1.name = "Batholomew";
    // npc1.health = 100;

    // Villager vill1;
    // vill1.name = "Matthew";
    // vill1.profession = "Jester";
    // vill1.village = "Thoriander";

    // God Apolli;
    // Apolli.name = "Apolli";
    // Apolli.power = "Star Creation";

    // cout << Apolli.power << " " << vill1.health;

    // refreshPointers();

    //the case of the dangling pointer
    /*
    This is when the pointer points to an address, but the value at that address has been deleted
    */

    // int* ptr = new int(42); //new integer, value 42, address is 0xb6899ff894
    // delete ptr; //this frees the memory and something else can take its place
    // // ptr = 0xb6899ff894

    // cout << "Your lucky number is: " << *ptr << endl; //absolute garbage number

    // ptr = nullptr; //make sure to do this

    // cout << "Your lucky number is: " << *ptr << endl;

    // int* arr = new int[100];
    // delete arr; 

    // PlayerPtr p = new Player;
    // p->name = "James Jones";

    // displayPlayer(*p);

    // delete p;
    // p = nullptr;

    PlayerPtr P1 = dynamicPlayer("Kim", 900, 8, 0);
    PlayerPtr P2 = dynamicPlayer("Kate", 600, 1000, 1);

    displayPlayer(*P1);
    displayPlayer(*P2);

    delete P1;
    P1 = nullptr;
    delete P2;
    P2 = nullptr;

    return 0;
}

void refreshPointers() {
    int a = 5;
    int* p = &a;

    cout << *p << " : value at the address stored in p\n";
    cout << p << " : address held in p\n";
    cout << a << " : value of a\n";
    cout << &a << " : the address of a\n";

    const int* ptr = &a; //pointer at points to a value that cannot be changed by this pointer
    int* const ptrr = &a;

    //* - dereference - to get the value stored at an address
    //& - get the address (or get the reference)
}

void dynamicMemoryLeak() {
    int* newarr = new int[1000];
    //newarr is local, gone after the function ends
} //creates a memory leak

//delete[] newarr

// delete ptr; //allocated a single thing (new)
// delete[] ptr; //alocated an array of objects with new[]

PlayerPtr dynamicPlayer(string name, int health, int score, int lvl) {
    PlayerPtr p = new Player;
    p->name = name;
    p->HP = health;
    p->score = score;
    p->level = lvl;
    return p;
}

void resizeArray(int*& arr, int currentSize, int newSize) { 
	int* temp = new int[newSize]{0}; //new, bigger array, initialied to 0
	
	//copy old array values in,
	for (int i = 0; i < currentSize; i++) { 
		temp[i] = arr[i]; 
	} 
	delete[] arr; //delete the old array, free up space
	arr = temp; //change pointer to the head of the new resized array
} // resize arrays without vectors

void addToVector(vector<int>& arr, int newnum) {
	arr.push_back(newnum); //adds to the end of the vector
}

void printVec(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << endl;
	}
} //vec.size() returns the size/length of vec

void clearVec(vector<int>& arr) {
	if (arr.empty()) {
		return;
	}
	arr.pop_back(); //doesn't return the last value, removes it
	clearVec(arr);
} //.empty() returns bool dependent on whether or not the vector is empty
//best way is to vec.clear()

//need to cover - classes - OOD

