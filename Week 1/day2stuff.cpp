/*
THURSDAY - MAY 21st, Session 2 - C++ Basics
*/
#include <iostream> //input output, <stdio.h>
#include <vector>
#include <string>

//macro definitiions
#define PI 3.1415

using namespace std; //std::cout -> cout; string, std::string

//function declarations
void sumof2();
void strings();
// void bubbleSortStrings(vector<string>& arr); //didn't dicuss
void daytonum();
int SumEven(int arr[], int n); //sum values of integer array if they are even, and then if a negative number is encountered, stop adding
void gameMenu(); 


//main
int main() {
    // sumof2();
    // strings();
    // daytonum();

    // int randomArray[20] = {14, 82, 45, 91, 3, 67, 29, 54, 8, 73, -37, 19, 62, 88, 5, 41, 96, 23, 70, 12};
    // int sum = SumEven(randomArray, 20);

    // cout << "The required sum is: " << sum << endl;

    cout << "Opening menu...\n";
    gameMenu();
    cout << "Thanks for playing!" << endl;

    return 0;
}

//function definitions
void sumof2() {
    int x, y;

    cout << "Enter two numbers: ";
    cin >> x >> y;

    int sum = x + y;
    cout << "Their sum is: " << sum << endl;
}

void strings() {
    string A = "Zebra";
    string B = "Elephant";
    string combined = A + B;
    string output = A + ' ' + B;

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "A + B: " << combined << endl;
    cout << "HelloWorld Output: " << output << endl;

    cout << "1st letter of word/string A: " << A[0] << endl;

    if (A > B) {
        cout << B << " comes alphabetically before " << A << endl;
    } else {
        cout << A << " comes alphabetically before " << B << endl;
    }
}

// void bubbleSortStrings(vector<string>& arr) {
//     int n = arr.size();
//     for (int i = 0; i < n - 1; ++i) {
//         for (int j = 0; j < n - i - 1; ++j) {
//             if (arr[j + 1] < arr[j]) {
//                 swap(arr[j], arr[j + 1]);
//             }
//          }
//      }
// } // note: you likely will not need to know bubble sort, but I just want to show you how you can directly use '<' for string sorting

void daytonum() {
    enum Day {sun, mon, tue, wed, thu, fri, sat}; 

    Day today = thu;

    switch (today) {
        case sun:
            cout << "1\t";
            break;
        case mon:
            cout << "2\t";
            break;
        case tue:
            cout << "3\t";\
            break;
        case wed:
            cout << "4\t";
            cout << "Hi there! \n";
            break;
        case thu:
            cout << "5\t";
            cout << "What's up? \n";
            break;
        case fri:
            cout << "6\t";
            break;
        case sat: 
            cout << "7\t";
            break;
        default: 
            cout << "Boo" << endl;
            break; 
    }
}

int SumEven(int arr[], int n) {
    int sumnums = 0;
    for (int i = 0; i < n; i++) {
        //add to sum if even -> skip if odd
        //if the number arr[i] < 0, break loop
        if (arr[i] < 0) {
            break;
        } else if (arr[i] % 2 == 1) {
            continue;
        } else {
            sumnums += arr[i];
        }

        //line reached after continue invoked
    }
    //line reached after break invoked
    return sumnums;
}

void gameMenu() {
    int choice;
    string inventory[] = {"Cheese", "String", "Mushrooms", "Thunderbolt", "Feather", "Twine"};
    int balance = 9;

    do {
        cout << "Welcome to MOIRA - Menu/Inventory" << endl;
        cout << "1. Check inventory" << endl;
        cout << "2. Check balance" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice [1-3]: ";
        cin >> choice;

        switch (choice) {
            case 1:
                for(string item : inventory) {
                    cout << item << '\t';
                }
                cout << '\n';
                break;
            case 2:
                cout << "Your balance is " << balance << " gold. \n";
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "How dare you defy the rules which govern the menu? Try again. \n";
                break;
        }
    } while (choice != 3);

    cout << "Exited successfully" << endl;
}