// Devon McKee  
// Project #1: Word Game
// 2018-10-1
//
// Purpose: Plays a "mad libs" style game with the user.
// 
// Input: The program will ask the user for 7 different inputs, including
// name, place, age, college, profession, animal, and pet name.
//
// Output: The program will take all those inputs and output a "mad libs"
// style paragraph at the end.
// 

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string properString(string inputString) {
  char c = inputString[0];
  if(isupper(c)) {
	return inputString;
  } else {
	inputString[0] = toupper(c);
	return inputString;
  }
}

int main() {
  // Declares necessary variables
  string name, place, college, profession, animal, petName;
  int age;
  // Prints program introduction
  cout << "#########################\n";
  cout << "# Project 1 (Word Game) #\n";
  cout << "# By Devon McKee        #\n";
  cout << "#########################\n\n";
  // Ask user for input;
  cout << "A name?: ";
  getline(cin, name);
  name = properString(name);
  cout << "\nA place?: ";
  getline(cin, place);
  cout << "\nAn age?: ";
  cin >> age;
  cin.ignore();
  cout << "\nA college?: ";
  getline(cin, college);
  cout << "\nA profession?: ";
  getline(cin, profession);
  cout << "\nAn animal?: ";
  getline(cin, animal);
  cout << "\nA pet name?: ";
  getline(cin, petName);
  name = properString(name);
  // Input ends, program starts to print paragraph
  cout << "\n\nHere is your paragraph: \n";
  cout << "There once was a person named " << name << " who lived in \n";
  cout << place << ". At the age of " << age << ", " << name << "\n";
  cout << "went to college at " << college << ". " << name << "\n";
  cout << "graduated and went to work as a " << profession << ". \n";
  if(tolower(animal[0]) == 'a') {
  	cout << "Then, " << name << " adopted an " << animal << " named \n";
  } else { 
  	cout << "Then, " << name << " adopted a " << animal << " named \n";
  }
  cout << petName << ". They both lived happily ever after!\n\n";
  cout << "The End.\n";
  return 0;
}
