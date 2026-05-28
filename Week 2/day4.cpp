/*
THURSDAY - MAY 28th, Session 4 - C++ Basics (OOD and Classes)
*/

// Object Oriented Design
//
/*
POLYMORPHISM 
Many forms. In your code, you should be able to have multiple forms of the same thing (function - function overloading; 
types - templates).
It lets you use a single interface that represents various different underlying types.
*/

/*
INHERITANCE
Pass down repeated methods or common variables. We do through in inheritance between classes or structures in C++.
"is-a" relation: giraffe is a mammal, monkey is a mammal
*/

/*
ENCAPSULATION
Putting things together, into one little bundle. 
Edg: glow stick - glass rod one chemical, and then another chemical outside - these mix, create the glow effect.
We do this in C++ through classes. You can control how the outside world interacts with the materials or things inside the capsule (class).
*/

/*
ABSTRACTION
Hiding all the complicated stuff that the user doesn't need to know. We only give the user what they absolutely need to know.
In C++, we do this by using standard library structures. Don't bother too much about this right now. 
Use interfaces in your code and hide all the implementation stuff. (you should only show the user what they can do, not how it is done).
*/

//if you're interested, search up and research the SOLID principles for coding.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
BARN ACCOUNT (barn bank)

This is a place where a user can store their animals, and we keep track of them. 
*/

//INITIAL BARN ACCOUNT

// class BarnAccount {
// private: //access specifier - it dictates how the rest of the code can interact with things under it
// //private means that only things within this class can access things under this specifier
//     string owner;
//     int no_horses;
//     int no_cows;

// public: //rest of the program can access
//     //constructor
//     BarnAccount(string name, int nhorse, int ncows) : owner(name), no_horses(nhorse), no_cows(ncows) {}

//     //default constructor
//     BarnAccount() : owner("Nameless"), no_horses(0), no_cows(0) {}

//     ~BarnAccount() {} //destructor

//     //withdraw + deposit
//     //deposit
//     void depositH(int nums) {
//         if (nums > 0) {
//             no_horses += nums;
//         }
//     }

//     //withdraw
//     void withdrawH(int nums) {
//         if (nums > 0 && no_horses > nums) {
//             no_horses -= nums;
//         }
//     }

//     //same thing but for cows
//     //deposit
//     void depositC(int nums) {
//         if (nums > 0) {
//             no_cows += nums;
//         }
//     }

//     //withdraw
//     void withdrawC(int nums) {
//         if (nums > 0 && no_cows > nums) {
//             no_cows -= nums;
//         }
//     }

//     string getOwner() {
//         return owner;
//     }

//     int getHorses() {
//         return no_horses;
//     }

//     int getCows() {
//         return no_cows;
//     }

//     void printDeets() {
//         cout << "--- Barn Account ---" << endl;
//         cout << "Owner: " << owner << endl;
//         cout << "Number of Horses: " << no_horses << endl;
//         cout << "Number of Cows: " << no_cows << endl;
//         cout << "--------------------" << endl; 
//     }
// }; //don't forget the semi-colon!

/*
- public: anyone outside can see use or modify it
- protected: child (derived) classes can inherit and use it directly
- private: only functions inside this class can see or touch it
*/

//IMPROVED BARN ACCOUNT (inheritance)
// base class -> derived classses
class Animal {
protected:
    string type;
    int count = 0;

public:
    Animal(string aType, int initCount) : type(aType), count(initCount) {} //constructor

    virtual ~Animal() {} //needed for inheritance, it remembers its class history and deletes all part of it, inherited and specific

    string getType() { return type; }
    int getCount() { return count; }

    void deposit(int num) {
        if (num > 0) {
            count += num;
        }
    }

    void withdraw(int num) {
        if (num > 0 && count > num) {
            count -= num;
        } else {
            cout << "Not enough " << type << "s available.\n";
        }
    }
};

//derived classes
class Horse : public Animal {
public:
    Horse(int initHorse) : Animal("Horse", initHorse) {};
};

class Cow : public Animal {
public:
    Cow(int initCow) : Animal("Cow", initCow) {};
};

class Parrot : public Animal {
public:
    Parrot(int initPar) : Animal("Parrot", initPar) {};
};

//main barn account class
class BarnAccount {
private:
    string owner;
    vector<Animal*> inventory; //vector of raw "Animal" pointers

public:
    BarnAccount(string name) : owner(name) {}

    ~BarnAccount() {
        for (Animal* animal : inventory) {
            delete animal;
        } //for-each loop
    }

    void addAnimalType(Animal* newAnimal) {
        inventory.push_back(newAnimal);
    }

    Animal* findAnimal(string type) {
        for (Animal* animal : inventory) {
            if (animal->getType() == type) {
                return animal;
            }
        }
        cout << "Animal type '" << type << "' not found.\n"; 
        return nullptr;
    }

    void printDeets() const {
		cout << "--- " << owner << "'s Barn Account ---" << endl;
		for (Animal* animal : inventory) {
			cout << animal->getType() << "s: " << animal->getCount() << endl;
		}
		cout << "--------------------------------------" << endl;
	}
};

//templates - blueprints, they let you decide the type later
template <typename T>
class Crate {
private:
    T contents; // This could be an int, a string, a double, etc.
public:
    Crate(T item) : contents(item) {}

    T getContents() const { 
        return contents; 
    }

    void inspectCrate() const {
        cout << "This crate contains: " << contents << endl;
    }
};


int main() {
    //initial Barn Account
    // BarnAccount* barn1 = new BarnAccount("Jones", 8, 3);
    // BarnAccount* barn2 = new BarnAccount("Adam", 3, 10);
    // BarnAccount* barn3 = new BarnAccount("Edith", 20, 20);

    // barn1->printDeets();
    // barn2->printDeets();
    // barn3->printDeets();

    // barn2->depositC(3);
    // barn1->depositH(5);
    // barn3->depositC(10);
    // barn3->depositH(10);

    // barn1->printDeets();
    // barn2->printDeets();
    // barn3->printDeets();

    //delete barn1;
    //barn1 = nullptr;
    //delete barn2;
    //barn2 = nullptr;
    //delete barn3;
    //barn3 = nullptr;

    //improved barn account
    // BarnAccount myBarn("Bob");

    // myBarn.addAnimalType(new Horse(5));
    // myBarn.addAnimalType(new Cow(8));
    // myBarn.addAnimalType(new Parrot(64));

    // myBarn.printDeets();

    // Animal* horseRef = myBarn.findAnimal("Horse");
    // if (horseRef != nullptr) {
    //     horseRef->withdraw(3); 
    //     horseRef->deposit(12);
    // }

    // Animal* cowRef = myBarn.findAnimal("Cow");
    // if (cowRef != nullptr) {
    //     cowRef->withdraw(9); 
    //     cowRef->deposit(1);
    // }

    // myBarn.printDeets();

    //crate code - templates intro
    // 1. A crate holding an integer (e.g., total weight)
    Crate<int> weightCrate(150);
    weightCrate.inspectCrate();

    // 2. A crate holding a string (e.g., text label)
    Crate<string> labelCrate("Premium Horse Feed");
    labelCrate.inspectCrate();

    // 3. A crate holding a double
    Crate<double> temperatureCrate(98.6);
    temperatureCrate.inspectCrate();

    return 0; //barn account destructor deletes the horse and the cow and the parrot
}