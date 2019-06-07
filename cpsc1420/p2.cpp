// Devon McKee
// Project #2: Guess the Numbers
// 2018-10-13
//
// Purpose: Plays a guessing game with the user. The user will guess a number
//          from 1 to 100 (range can be changed in source code). The program
//          will then tell the user if the input was too high, too low, or
//          correct. The program can be repeated as many times as needed.
//
// Input: The user will input integers within the range given, but nothing is
//        stopping the user from inputting integers outside of the range other
//        than the higher incrementation of guesses.
//
// Output: The program tells the user what the range of numbers is, then
//         prompts the user for input. Once the user enters a number, the
//         program then tells the user whether the guess is too high, too
//         low, or correct (as stated in the purpose). The game continues
//         until the user guesses correctly, where it tells the user that
//         they won and asks if they want to play again.
//
// Example: #################################
//          # Project #2 - Guess The Number #
//          # By Devon McKee                #
//          #################################
//
//          I'm thinking of a number between {RANGEMIN} and {RANGEMAX}.
//
//          Guess 1: <User inputs int>
//          <int> is too high! Try again.
//          Guess 2: <User inputs int>
//          You got it after {guesses} guesses!
//
//          Would you like to play again? <y/n>
// 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int RANGEMAX = 100;
const int RANGEMIN = 1;
const char YES = 'y';

int main(){
  int ans, guesses;
  int guess = 0;
  char again = YES;
  // seeding rand() with current time
  srand(time(0));
  // welcome message begins
  cout << "\033c";
  cout << "\n\n\n";
  cout << "Welcome to my program\n";
  cout << "\n\n\n";
  cout << "Press ENTER to begin...";
  cin.ignore();
  // game loop begins
  while(again == YES){
    guesses = 1;
    // creates random # for answer
    ans = (rand() % (RANGEMAX - RANGEMIN + 1)) + RANGEMIN;
    // game begins
    cout << "\033c";
    cout << "################################\n";
    cout << "# Project 2 - Guess The Number #\n";
    cout << "# By Devon McKee               #\n";
    cout << "################################\n";
    cout << "\n";
    cout << "I'm thinking of a number between " << RANGEMAX << " and "
         << RANGEMIN << ".\n\n";
    // runs until user's guess matches correct answer
    while(guess != ans){
      cout << "Guess " << guesses << ": ";
      cin >> guess;
      cin.ignore();
      if(guess > ans){
        cout << guess << " is too high! Try again.\n";
        guesses++;
      }else if(guess < ans){
        cout << guess << " is too low! Try again.\n";
        guesses++;
      }else{
        cout << "You got it after " << guesses << " guesses!\n";
        cout << "\n";
        // asks the user if they want to continue
        cout << "Would you like to play again? (y/n) ";
        cin >> again;
        cin.ignore();
      }
    }
  }
  // goodbye message
  cout << "\033c";
  cout << "\n\n\n";
  cout << "Goodbye!\n";
  cout << "Thanks for playing my game!\n";
  cout << "\n\n\n";
  cout << "Press ENTER to exit the program...";
  cin.ignore();
}
