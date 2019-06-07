// Devon McKee
// Project #3: Chutes and Ladders
// 2018-11-3
//
// Purpose: Plays the game "Chutes and Ladders" with the user. The user will
//          enter their name and then the game will begin. Both the player
//          and the CPU player will start at 0 on the board, going up to 100
//          as they spin a virtual spinner from 1-6. The number from the
//          spinner is the number of spaces that they will move forward.
//          If either player hits a chute, they will go up a certain number
//          of spaces depending on which chute it is. If either player hits
//          a ladder, they will go down a certain number of spaces depending
//          on which ladder it is.
//
// Input:   The user will press ENTER every time to increment their turn as
//          well as the turn for the CPU. No input is required from the user
//          other than ENTER and their name at the beginning.
//
// Output:  The program will output the players position, what number the
//          spinner returned, whether they hit a chute/ladder, as well as
//          the necessary welcome and goodbye messages.
//
// Example:
//

#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

const char YES = 'y';
const string CPU_NAME = "Johnny 5";
const int START_SPACE = 0;
const int END_SPACE = 100;
const int SPIN_MIN = 1;
const int SPIN_MAX = 6;

void welcome(string name);
// Welcomes the user to the program
// IN: name

int spin();
// Spins the spinner for the user and returns the value (from 1-6) spun.
// OUT: value

int checkLocation(int position);
// Checks if the given position has a chute or a ladder and returns the
// value of the chute or ladder.
// IN: position

int takeTurn(string name, int position);
// Takes a turn for a specific user when given their name and position on
// the board and returns their new position.
// IN: position & name
// OUT: newPosition


void goodbye(string name);
// Says goodbye to the user as the program is closing
// IN: name

int main()
{
  char ans = YES;
  string playerName;
  int playerPosition;
  int cpuPosition;
  char activePlayer = 'p';
  srand(time(0));
  // seeding rand()
  cout << "\033c";
  cout << "Your name? ";
  cin >> playerName;
  cin.ignore();
  welcome(playerName);
  while(ans == YES){
    playerPosition = START_SPACE;
    cpuPosition = START_SPACE;
    while(playerPosition != END_SPACE && cpuPosition != END_SPACE){
      if(activePlayer == 'p'){
        playerPosition = takeTurn(playerName, playerPosition);
        activePlayer = 'c';
      }else{
        cpuPosition = takeTurn(CPU_NAME, cpuPosition);
        activePlayer = 'p';
      }
    }
    cout << "\033c";
    cout << "Would you like to play another game of "
         << "Chutes and Ladders? <y/n>";
    cin >> ans;
    cin.ignore();
  }
  goodbye(playerName);
  return 0;
}

void welcome(string name)
{
  cout << "\033c";
  cout << "##################################\n";
  cout << "# Welcome to Chutes and Ladders, #\n";
  cout << "# " << name << setw(30-name.length()) << " " << " #\n";
  cout << "##################################\n";
  cout << "Your opponent today is " << CPU_NAME << ". \n";
  cout << "\n";
}

int spin()
{
  int value = (rand() % (SPIN_MAX - SPIN_MIN + 1)) + SPIN_MIN;
  return value;
}

int checkLocation(int position)
{
  if(position == 1){
    return 37;
  }else if(position == 4){
    return 10;
  }else if(position == 9){
    return 12;
  }else if(position == 23){
    return 21;
  }else if(position == 28){
    return 56;
  }else if(position == 36){
    return 8;
  }else if(position == 51){
    return 15;
  }else if(position == 71){
    return 19;
  }else if(position == 80){
    return 20;
  }else if(position == 98){
    return -20;
  }else if(position == 95){
    return -20;
  }else if(position == 93){
    return -20;
  }else if(position == 87){
    return -63;
  }else if(position == 64){
    return -4;
  }else if(position == 62){
    return -43;
  }else if(position == 56){
    return -3;
  }else if(position == 49){
    return -38;
  }else if(position == 48){
    return -22;
  }else if(position == 16){
    return -10;
  }else{
    return 0;
  }
}

int takeTurn(string name, int position)
{
  int turnSpin = spin();
  int positionChange = 0;
  int newPosition = 0;
  cout << "It is now " << name << "'s turn.\n";
  if((position + turnSpin) < 100){
    cout << "They are at space " << position << ".\n";
    cout << "They spun a " << turnSpin << " and now move forward!\n";
    position += turnSpin;
    if(checkLocation(position)>0){
      positionChange = checkLocation(position);
      cout << "They hit a ladder!\n";
      cout << "They get to move " << positionChange << " spaces forward!\n";
      newPosition = position + positionChange;
      cout << "Their new position is at space " << newPosition << ".\n";
      cout << "This turn is over, press ENTER to continue.. \n";
      cout << "\n";
      cin.ignore();
      return newPosition;
    }else if(checkLocation(position)<0){
      positionChange = checkLocation(position);
      cout << "They hit a chute!\n";
      cout << "They have to move " << positionChange * -1
           << " spaces backwards...\n";
      newPosition = position + positionChange;
      cout << "Their new position is at space " << newPosition << ".\n";
      cout << "This turn is over, press ENTER to continue.. \n";
      cout << "\n";
      cin.ignore();
      return newPosition;
    }else{
      cout << "No chutes or ladders here!\n";
      cout << "Their new position is at space " << position << ".\n";
      cout << "This turn is over, press ENTER to continue.. \n";
      cout << "\n";
      cin.ignore();
      return position;
    }
  }else if((position + turnSpin) == 100){
    position += turnSpin;
    cout << "They are at space " << position << ".\n";
    cout << "They spun a " << turnSpin << ".\n";
    cout << "They hit space 100 and won the game!\n";
    cout << "Congratulations, " << name << "!\n";
    cout << "Press ENTER to continue.. \n";
    cin.ignore();
    return position;
  }else{
    cout << "They are at space " << position << ".\n";
    cout << "They spun a " << turnSpin << ".\n";
    cout << "However, their turn was skipped because this spin would bring\n"
         << "them past space 100.\n";
    cout << "This turn is over, press ENTER to continue.. \n";
    cout << "\n";
    cin.ignore();
    return position;
  }
}

void goodbye(string name){
  cout << "\033c";
  cout << "##########################################\n";
  cout << "# Thanks for playing Chutes and Ladders! #\n";
  cout << "#            Have a nice day!            #\n";
  cout << "##########################################\n";
}
