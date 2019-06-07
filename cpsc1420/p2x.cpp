// Devon McKee
// Project #2: Guess the Numbers
// 2018-10-10
//
// Purpose: Plays a guessing game with the user. The user will guess a number
//          from 1 to 100 (range can be changed in source code). The program
//          will then tell the user if the input was too high, too low, or
//          correct. The program can be repeated as many times as needed.
//          This version of the program contains a menu that allows the
//          user to choose between playing, seeing the high scores, or
//          quitting. The high scores are randomly generated with set
//          guess ranges on each program launch. If the user beats one of
//          these high scores, they are notified and the score changes to
//          reflect that.
//
// Input:   The user will first input a number from 1-3 to either play, see
//          high scores, or quit. Assuming the user chose to play, the user
//          is then prompted for a number after being told what the range of
//          numbers is. The user will input integers within the range given,
//          but nothing is stopping the user from inputting integers outside
//          of the range other than the higher incrementation of guesses.
//
// Output:  The program displays the menu, displays the high scores if
//          prompted to, and if the user hits play, the program will start
//          the game. Once the game begins, the program informs the user
//          of the possible range of values of the answer, then prompts
//          the user for their input. The program will then tell the user
//          if the guess is too low, too high, or correct. If correct, and
//          the number of guesses is lower than a particular high score,
//          the user is notified and the score is changed.
//
// Example: ################################
//          # Project 2 - Guess The Number #
//          # By Devon McKee               #
//          ################################
//
//          1 - Play
//          2 - See High Scores
//          3 - Quit
//
//          Please select a menu option: <1/2/3>
//
// ----------------------------------------------------
//
//          ################################
//          # Project 2 - Guess The Number #
//          # By Devon McKee               #
//          ################################
//          I'm thinking of a number between {RANGEMIN} and {RANGEMAX}.
//
//          Guess 1: <input>
//          <input> was too high! Try again.
//          Guess 2: <input>
//          <input was too low! Try again.
//          Guess 3: <input>
//          You got it after {guesses} guesses!
//          You now hold the {first/second/third} highest score!
//
//          Press ENTER to return to main menu...          
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int RANGEMAX = 100;
const int RANGEMIN = 1;

int main(){
  int guesses, guess, ans, select, score1, score2, score3;
  // seeding RNG with current time
  srand(time(0));
  // initializing high scores with random values that make sense for high
  // score positions
  score1 = (rand() % 3) + 1; 
  score2 = (rand() % 3) + 4;
  score3 = (rand() % 3) + 7;
  // welcome message begins
  cout << "\033c";
  cout << "Welcome to my program!\n";
  cout << "\n";
  cout << "Press ENTER to begin...";
  cin.ignore();
  // game loop begins
  while(select != 3){
    // prints main menu, asks user for input to choose what they want to do
    cout << "\033c";
    cout << "################################\n";
    cout << "# Project 2 - Guess The Number #\n";
    cout << "# By Devon McKee               #\n";
    cout << "################################\n";
    cout << "\n";
    cout << "1 - Play\n";
    cout << "2 - See High Scores\n";
    cout << "3 - Quit\n";
    cout << "\n";
    cout << "Please select a menu option: ";
    cin >> select;
    cin.ignore();
    switch(select){
      case 1:
        guesses = 1;
        // creates random number in range for answer
        ans = (rand() % (RANGEMAX - RANGEMIN + 1)) + RANGEMIN;
        cout << "\033c";
        cout << "################################\n";
        cout << "# Project 2 - Guess The Number #\n";
        cout << "# By Devon McKee               #\n";
        cout << "################################\n";
        cout << "I'm thinking of a number between " << RANGEMIN << " and "
             << RANGEMAX << ".\n\n";
        // asks the user for guesses until 
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
            // checking if user got high score
            if(guesses <= score1){
              cout << "You now hold the highest score! Congratulations!\n";
              score1 = guesses;
            }else if(guesses <= score2){
              cout << "You now hold the second highest score!\n";
              score2 = guesses;
            }else if(guesses <= score3){
              cout << "You now hold the third highest score!\n";
              score3 = guesses;
            }
            cout << "\n";
            cout << "Press ENTER to return to main menu...";
            cin.ignore();
          }
        }
        break;
      case 2:
        // menu of high scores begins
        cout << "\033c";
        cout << "################################\n";
        cout << "# Project 2 - Guess The Number #\n";
        cout << "# By Devon McKee               #\n";
        cout << "################################\n";
        cout << "\n";
        cout << "       HIGH SCORES       \n";
        cout << "\n";
        cout << "  #1 Score: " << score1 << " guesses\n";
        cout << "  #2 Score: " << score2 << " guesses\n";
        cout << "  #3 Score: " << score3 << " guesses\n";
        cout << "\n";
        cout << "Press ENTER to return to main menu...";
        cin.ignore();
        break;
      case 3:
        // user chooses to quit the program
        cout << "\033c";
        cout << "################################\n";
        cout << "# Project 2 - Guess The Number #\n";
        cout << "# By Devon McKee               #\n";
        cout << "################################\n";
        cout << "\n";
        cout << "Goodbye!\n";
        cout << "Thanks for playing!\n";
        cout << "\n";
        cout << "Press ENTER to exit the program...";
        cin.ignore();
        break;
    }  
  }
  return 0;
}
