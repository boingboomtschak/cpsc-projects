// Devon McKee  
// Project #1: Word Game
// 2018-10-1
//
// Purpose: Plays a "mad libs" style game with the user.
// 
// Input: The program will ask the user for 7 different inputs, including
// name, place, age, college, profession, animal, and pet name. The program
// also asks the user if they want to play again at the end, and handles
// incorrect responses.
// 
// Output:  The program will take all the given inputs and output a "mad libs"
// style paragraph at the end.
// 
// Examples: <Intro to program>
//           A name? <User Entry>
//           A place? <User Entry>
//           An age? <User Entry>
//           #etc.#
//           There once was a person named <name> who lived in
//           <place>. At the age of <age>, <name>
//           went to college at <college>. <name>
//           graduated and went to work as a <profession>.
//           Then, <name> adopted an <animal> named
//           <petName>. They both lived happily ever after!
//
//           The End.
//
//           Would you like to play again? <yes/no>

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

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

void wordGame() {
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
}

int main(){
  bool again = true;
  string play;
  // First time run
  cout << "Would you like to play Word Game? ";
  getline(cin, play);
  system("clear");
  if(play == "yes"){
    wordGame();
    while(again) {
      string ans;
      cout << "Would you like to play again? ";
      getline(cin, ans);
      if(ans == "yes"){
        system("clear");
        wordGame();
      }else if(ans == "no"){
        cout << "Thanks for playing!\n\n\n";
        again = false;
      }else{
        cout << "You didn't answer 'yes' or 'no'!\n";
      }
    }
  } else {
    cout << "Have a nice day!\n\n";
    return 0;
  }
  return 0;
}
