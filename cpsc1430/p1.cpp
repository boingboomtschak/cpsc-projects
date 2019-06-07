// Devon McKee
// p1.cpp
// Chutes & Ladders Redux
// 2019-1-17
// Purpose: Plays Chutes & Ladders with the user. Players roll die (1-6)
//          to move forward on a board made up of 100 spaces (not including
//          the beginning space) Players start at space 0 and move with each
//          turn until they either reach 100 or hit a chute/ladder, at which
//          point they are sent forward or back a certain number of spaces.
//          Chutes and ladders are static and not randomized.
//
// Input:   Only required input from user is amount of players, names of
//          players, and for the user to hit ENTER to go through turns/menus.
//
// Output:  Program welcomes user, asks for amount/names of players, then
//          starts the game, outputting information about each turn to the
//          players.

#include <iostream>
#include "board.h"
#include "player.h"

using namespace std;

const int PLAYER_MAX = 7;
const char YES = 'y';

int main(){
  Player players[PLAYER_MAX + 1]; // players occupy 1-6 of array
  Board board;
  int numPlayers;
  int activePlayer;
  string tempName;
  int tempSpace;
  int chuteLadders;
  int winner;
  char cont = YES;
  // welcome message
  cout << "\033c";
  cout << "╔═════════════════════════════════════╗\n";
  cout << "║ Welcome to Chutes and Ladders Redux ║\n";
  cout << "╚═════════════════════════════════════╝\n";
  cout << "\n";
  // game/player setup
  while(numPlayers > 6 || numPlayers < 2){
    cout << "How many players are there? (2-6) ";
    cin >> numPlayers;
    cin.ignore();
  }
  for(int i=1; i<=numPlayers; i++){
    cout << "Player " << i << "'s name? ";
    cin >> tempName;
    cin.ignore();
    players[i].setName(tempName);
  }
  cout << "Press ENTER to begin the game..\n";
  cin.ignore();
  // game loop begins
  while(cont == YES){
    activePlayer = 1;
    winner = 0;
    for(int i=1; i<=numPlayers; i++){
      players[i].reset();
    }
    while(winner < 1){
      tempSpace = players[activePlayer].getSpace();
      chuteLadders = board.takeTurn(players[activePlayer].getName(),
                     tempSpace);  
      players[activePlayer].setSpace(tempSpace);
      if(chuteLadders == 1)
        players[activePlayer].incrementLadders();
      else if(chuteLadders == -1)
        players[activePlayer].incrementChutes();
      activePlayer++;
      if(activePlayer > numPlayers)
        activePlayer = 1;
      for(int i=1; i<=numPlayers; i++){
         if(board.ifWinner(players[i].getSpace())){
          winner = i;
        }
      }
    }
    cout << "Game over! The winner is " << players[winner].getName() << "!\n";
    players[winner].reportChutesLadders();
    cout << "Would you like to play again? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  // goodbye message
  cout << "\033c";
  cout << "╔══════════════════════════════════════════════╗\n";
  cout << "║ Thanks for playing Chutes and Ladders Redux! ║\n";
  cout << "║              Have a nice day!                ║\n";
  cout << "╚══════════════════════════════════════════════╝\n";
  return 0;
}
