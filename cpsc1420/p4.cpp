// Devon McKee
// Project #4: SU Monopoly
// 2018-11-18
//
// Purpose: Plays SU Monopoly with the user. The user begins by entering a
//          number of players and then entering names for each player. The
//          game plays almost identically to standard Monopoly, except with
//          locations around campus instead. Players may purchase properties,
//          rent properties, etc. The game will prompt the player to restart
//          at the end of every game, and will reset all necessary variables.
//
// Input:   The user hits ENTER to go to the next turn, and enter 'y' or 'n'
//          as needed during every turn. 
//
// Output:  After the header, the game shows some necessary information,
//          loads the locations, and then asks the player for player number
//          and names for each player, and the game begins. 
//

#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

const char YES = 'y';
const int START_BAL = 1500;
const int START_SPACE = 0;
const int MAX_PLAYERS = 7; // players occupy indices 1-6 of array
const int MAX_LOCATIONS = 45;
const int DIE_MIN = 1;
const int DIE_MAX = 6;
const string FILENAME = "/home/fac/sreeder/class/cs1420/p4input.dat";
const string CHANCE = "Chance";
const string INCOME_TAX = "Income Tax";
const string FEES = "Fees";
const string CHAPEL = "Chapel of St. Ignatius";

struct Player {
  string name;
  int balance;
  int position;
};

struct Location {
  string name;
  int owner;
  int cost;
  int rent;
};

void takeTurn(Player players[], int activePlayer,
              Location locations[], int numLocations);
// function to take turn for given player

int rollDie();
// rolls a single die and returns the value

void checkLocation(Player players[], int activePlayer,
                   Location locations[], int numLocations);
// function to check player location and handle special conditions/owning/rent

bool checkBankrupt(Player players[], int numPlayers);
// checks if any players are bankrupt. if not, game continues

int main()
{
  // declaring vars
  ifstream infile;
  int numPlayers;
  Player players[MAX_PLAYERS];
  int activePlayer;
  Location locations[MAX_LOCATIONS];
  int locationsCount = 0;
  int winner;
  char cont = YES;
  // seeding rand()
  srand(time(0));
  cout << "\033c";
  cout << "############################\n";
  cout << "# Project #4 - SU Monopoly #\n";
  cout << "# By Devon McKee           #\n";
  cout << "############################\n";
  cout << "\n";
  cout << "Welcome to SU Monopoly!\n";
  cout << "You must have 2-6 players to play.\n";
  cout << "In order to load locations correctly, the file at\n";
  cout << "/home/fac/sreeder/class/cs1420/p4input.datw\n";
  cout << "must be available.\n";
  cout << "Attempting to load location file...\n";
  infile.open(FILENAME.c_str());
  if(infile.fail()){
    cout << "File error, exiting program..\n";
    cin.ignore();
    return 0;
  }
  while(locationsCount < MAX_LOCATIONS &&
        getline(infile, locations[locationsCount].name)){
    infile >> locations[locationsCount].owner;
    infile.ignore();
    infile >> locations[locationsCount].cost;
    infile.ignore();
    infile >> locations[locationsCount].rent;
    infile.ignore();
    locationsCount++;
  }
  cout << "Locations successfully read.\n";
  cout << "\n";
  while(cont == YES){
    winner = 1;
    numPlayers = 0;
    activePlayer = 1;
    while(numPlayers < 2 || numPlayers > MAX_PLAYERS-1){
      cout << "How many players are there? (2 to " << MAX_PLAYERS-1 << ")  ";
      cin >> numPlayers;
      cin.ignore();
    }
    for(int i=1; i<=numPlayers; i++){
      cout << "What is player " << i << "'s name? ";
      cin >> players[i].name;
      cin.ignore();
      players[i].balance = START_BAL;
      players[i].position = START_SPACE;
    }
    cout << "\n";
    cout << "*** Game Begins! ***\n";
    while(!checkBankrupt(players, numPlayers)){
      takeTurn(players, activePlayer, locations, locationsCount);
      activePlayer++;
      if(activePlayer > numPlayers){
        activePlayer = 1;
      }
    }
    cout << "A player is bankrupt and the game ends!\n";
    for(int i=2; i<numPlayers;i++){ 
      if(players[winner].balance < players[i].balance){
        winner = i;
      }
    }
    cout << "The winner was " << players[winner].name << "!\n";
    cout << "They won with $" << players[winner].balance << " in the bank.\n";
    cout << "Would you like to play again? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  cout << "Thank you for playing SU Monopoly!\n";
  cout << "Program exiting, press ENTER to continue.. \n";
  cin.ignore();
  return 0;
}

void takeTurn(Player players[], int activePlayer,
              Location locations[], int numLocations)
{
  int rollOne = rollDie();
  int rollTwo = rollDie();
  string name = players[activePlayer].name;
  int position = players[activePlayer].position;
  int newPosition = position + rollOne + rollTwo;
  cout << "It is " << name << "'s turn.\n";
  cout << "They have $" << players[activePlayer].balance << " in the bank.\n";
  cout << name << " is on space " << position << ".\n";
  cout << name << " rolls a " << rollOne << " and a " << rollTwo
       << " for a total of " << rollOne + rollTwo << "\n";
  if(newPosition >= numLocations){
    newPosition = newPosition - numLocations;
    cout << name << " passed GO and collected $200!\n";
    players[activePlayer].balance += 200;
  }
  cout << name << " moves forward and is now on space "
       << newPosition << ".\n";
  players[activePlayer].position = newPosition;
  checkLocation(players, activePlayer, locations, numLocations);
  cout << "This turn is now over.. \n";
  cout << "Press ENTER to continue..\n";
  cin.ignore();
  cout << "\n";
}

int rollDie()
{
  int value = (rand() % (DIE_MAX - DIE_MIN +1)) + DIE_MIN;
  return value;
}

void checkLocation(Player players[], int activePlayer,
                   Location locations[], int numLocations)
{
  int position = players[activePlayer].position;
  cout << "The player is at " << locations[position].name << ".\n";
  if(locations[position].owner == -1){
    cout << "This location cannot be owned.\n";
    if(locations[position].name == INCOME_TAX ||
       locations[position].name == FEES){
      cout << "The player has " << locations[position].rent
           << " deducted from their balance.\n";
      players[activePlayer].balance -= locations[position].rent;
      cout << "Their new balance is $" << players[activePlayer].balance
           << ".\n";
    } else if(locations[position].name == CHANCE){
      int chance = rollDie();
      if(chance < 4){
        cout << "The player rolled a " << chance
             << " and had $50 added to their balance!\n";
        players[activePlayer].balance += 50;
      } else {
        cout << "The player rolled a " << chance
             << " and was sent to the Chapel!\n";
        for(int i=0; i<numLocations; i++){
          if(locations[i].name == CHAPEL){
            players[activePlayer].position = i; 
          }
        }
      }
    }
  }else if(locations[position].owner == 0){
    char ans;
    cout << "This space is unowned and can be bought by the player.\n";
    cout << "This space costs $" << locations[position].cost << "\n";
    cout << "The rent for this space is $" << locations[position].rent << "\n";
    cout << "Would the player like to purchase this space? ";
    cin >> ans;
    if(ans == YES){
      cout << "The player chose to buy the space!\n";
      players[activePlayer].balance -= locations[position].cost;
      locations[position].owner = activePlayer;
      cout << "The player's new balance is "
           << players[activePlayer].balance << "\n";
    }else{
      cout << "The location was not bought.. \n";
    }
  }else if(locations[position].owner != activePlayer){
    Player owner = players[locations[position].owner];
    cout << "This space is owned by " << owner.name << "\n";
    cout << "The rent for this space is $" << locations[position].rent << "\n";
    cout << "The player has the rent deducted from their balance\n";
    players[activePlayer].balance -= locations[position].rent;
    players[locations[position].owner].balance += locations[position].rent;
    cout << owner.name << " gains $" << locations[position].rent << "\n";
    cout << "Their new balance is " << players[activePlayer].balance << "\n";
  }else{
    cout << "This space is owned by the player!\n";
  }
}

bool checkBankrupt(Player players[], int numPlayers)
{
  bool bankrupt = false;
  for(int i=1; i<=numPlayers; i++){
    if(players[i].balance <= 0){
      bankrupt = true;
    }
  }
  return bankrupt;
}
