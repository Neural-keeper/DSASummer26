/*
Thursday June 11th, 2026 - Session 8 - OOP - We're going back.
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

/*
ROBUSTNESS
The software can handle invalid or unexpected inputs gracefully, without crashing or using the invalid input, 
where the inputs are not explicitly defined for the software. The textbook references Therac-25, where lack of robustness actively
caused death.  
Not directly or specifically an OOP concept, just a general software principle. 

To save time, I already added code modifying our Barn Account to handle exceptions using the <stdexcept> library, and try-catch.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> //this is a required library for standard exceptions (runtime_error, invalid_arguments)

using namespace std;

/*
BARN ACCOUNT (barn bank)

This is a place where a user can store their animals, and we keep track of them. 
*/

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

    string getType() const { return type; }
    int getCount() const { return count; }

    void deposit(int num) {
        if (num < 0) {
            throw invalid_argument("Deposit Amount must be positive.");
        }

        count += num;
    }

    void withdraw(int num) {
        if (num <= 0) {
            throw invalid_argument("Withdrawal Amount must be positive.");
        } //handle non-positive inputs

        if (num > count) {
            throw runtime_error("Not enough " + type + "s available");
        } //handle over withdrawals

        count -= num;
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

        throw runtime_error("Animal of type '" + type + "' not found."); //updated error case where "type" not found to throw an error
    }

    void printDeets() const {
		cout << "--- " << owner << "'s Barn Account ---" << endl;
		for (Animal* animal : inventory) {
			cout << animal->getType() << "s: " << animal->getCount() << endl;
		}
		cout << "--------------------------------------" << endl;
	}

    BarnAccount(const BarnAccount&) = delete;
    BarnAccount& operator=(const BarnAccount&) = delete;
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
    //improved barn account
    try {
        BarnAccount myBarn("Bob");

        myBarn.addAnimalType(new Horse(5));
        myBarn.addAnimalType(new Cow(8));
        myBarn.addAnimalType(new Parrot(64));

        myBarn.printDeets();

        Animal* horseRef = myBarn.findAnimal("Horse");
        horseRef->withdraw(3); 
        horseRef->deposit(12);

        myBarn.printDeets();

        Animal* cowRef = myBarn.findAnimal("Cow");
        cowRef->withdraw(9); 
        cowRef->deposit(1);

        myBarn.printDeets();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    } //updated everything to be in a try catch block
    

    // //crate code - templates intro
    // // 1. A crate holding an integer (e.g., total weight)
    // Crate<int> weightCrate(150);
    // weightCrate.inspectCrate();

    // // 2. A crate holding a string (e.g., text label)
    // Crate<string> labelCrate("Premium Horse Feed");
    // labelCrate.inspectCrate();

    // // 3. A crate holding a double
    // Crate<double> temperatureCrate(98.6);
    // temperatureCrate.inspectCrate();

    return 0; //barn account destructor deletes the horse and the cow and the parrot
}