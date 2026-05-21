/*
TUESDAY - MAY 19th, Session 1 - C++ Basics
*/

#include <iostream> //<stdio.h\n'>
#include <string>
#include <vector> //necessary for using vectors
#include <cstdlib> //EXIT_SUCCESS

using namespace std; 

void helloWorld() {
    cout << "Hello World!" << endl; 
}

void sumof2() {
    int x, y;

    cout << "Enter two numbers: ";
    cin >> x >> y;

    int sum = x + y;
    cout << "Their sum is: " << sum << endl;
}

void strings() {
    string A = "Hello";
    string B = "World!";
    string combined = A + B;
    string output = A + ' ' + B;

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "A + B: " << combined << endl;
    cout << "HelloWorld Output: " << output << endl;

    cout << "1st letter of word/string A: " << A[0] << endl;
}

void vectors() {
    //dynamic arrays
    //section on vectors later
}

vector<int> addToVector(vector<int> nums, int addedElem) {
    nums.push_back(addedElem);
    return nums;
}

void printVector(vector<int> nums) {
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << ' ';
    }
}

void arrExamp() {
    int intArr[] = {10, 15, 20, 30, 45, 50};
    string SArr[] = {"Hello", "World", "!", "I", "You", "fun", "have", "will", "not", "am", " "};

    cout << intArr[0] << endl;
    cout << intArr[3] << endl;

    cout << *intArr << endl;
    cout << *(intArr + 3) << endl;

    cout << SArr[0] << ' ' << SArr[1] << SArr[2] << endl;
    cout << SArr[0] << SArr[0][0] << endl;
}

void forScore(int& score, int time) {
    for (int i = 0; i < time; i++) {
        score++;
    }

    cout << "Internal score: " << score << endl;
}

void forTypes() {
    int hours[] = {2, 4, 1, 3, 5};
    int total = 0;

    for (int i = 0; i < 5; i++) {
        total += hours[i];
    }
    cout << total << endl;

    total = 0;

    for (int* ptr = hours; ptr < (hours + 5); ptr++) {
        total+= *ptr;
    }
    cout << total << endl;

    total = 0;

    for (int h : hours) total += h; //for-each loop
    //---
    cout << total << endl;
}

void whileScore(int& score, int time) {
    int i = 0;
    while (i < time) {
        score++;
        i++;
    }
}

void whileBattle(int& playerHP, int& oppHP) {
    int turn = 1;

    while(playerHP > 0 && oppHP > 0) {
        cout << "Turn--" << turn << "--\n";

        //using rand() cstdlib
        int playerDMG = rand() % 10 + 1;

        oppHP -= playerDMG;
        cout << "Player deals---" << playerDMG << endl;
        cout << "Player HP: " << playerHP << endl;
        cout << "Opponent HP: " << oppHP << endl;

        if (oppHP <= 0) {
            break;
        }

        int oppDMG = rand() % 10 + 1;
        playerHP -= oppDMG;
        cout << "Opponent deals---" << oppDMG << endl;
        cout << "Player HP: " << playerHP << endl;
        cout << "Opponent HP: " << oppHP << endl;

        turn++;
    }

    cout << "Battle ended at " << turn << " turns" << endl;

    if(playerHP > 0) {
        cout << "Player wins!" << endl;
    } else {
        cout << "Opponent wins. :(" << endl;
    }
}

void gameMenu() {
	int choice;
	string inventory[] = {"Cheese", "String", "Thunderbolt", "Feather"};
	int balance = 9;
	
	do { 
		cout << "Welcome to MOIRA - Menu/Inventory" << endl;
		cout << "1. Check inventory \n";
		cout << "2. Check balance \n";
		cout << "3. Exit \n";
		
		cout << "Enter your choise [1-3]: ";
		cin >> choice;
		
		switch (choice) {
			case 1:
				for (string item : inventory) {
					cout << item << endl;
				}
				break;
			case 2:
				cout << "Your balance is " << balance << " gold. \n";
				break;
			case 3:
				cout << "Exiting...\n";
				break;
			default:
				cout << "Invalid! Try again. \n";
		}
	} while (choice != 3); 
} // a while loop might not even run once, but a do while loop will run at minimum once


int main() {
    // helloWorld();
    // sumof2();
    // strings();

    // arrExamp();

    // int score = 0;
    // whileScore(score, 56);

    // cout << score << endl;

    // int Player = 100;
    // int Opp = 100;

    // whileBattle(Player, Opp);
    // gameMenu(); 
    //example for do-while loop^


    return EXIT_SUCCESS;
}