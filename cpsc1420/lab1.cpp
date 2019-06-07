// Devon McKee
// Lab #1
// 2018-09-25
//
// Purpose: Programs prints given name of user, their favorite color, and their place of birth.
// Pertinent information is stored as a string variable and then printed to console.
// 
// Input: N/A
//
// Process: Stores given values in variables and then prints variables and formatting on individual line.
//
// Output: Prints given name, favorite color, and place of birth to console. 
//
// Examples: lab1.cpp - Devon M
//           Name: Devon McKee
//           Favorite Color: Red
//           Place of Birth: Daly City

#include <iostream>
#include <string>
using namespace std;

int main() {
    string name = "Devon McKee";
    string color = "Red";
    string birthplace = "Daly City, CA";
    cout << "lab1.cpp - Devon M" << endl;
    cout << "Name: " << name << endl;
    cout << "Favorite Color: " << color << endl;
    cout << "Place of Birth: " << birthplace << endl;
}