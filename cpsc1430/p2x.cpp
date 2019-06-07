// Devon McKee
// p2x.cpp
// TicTacToe (EC)
// 2019-02-07
// Purpose: Plays TicTacToe with the user. User alternates between playing for
//          "X" or "O" player, and enters a row and column number to place
//          each piece on that space. Game continues until all pieces in a
//          column, row, or diagonal match or until the board is filled, ending
//          in a tie. Score for both X and O players is kept, and is printed
//          at end of each round. Ties are also kept in scoreboard.
//
// Input:   Required input from user is row and column number (corresponding
//          with grid numbers) of space, as well as confirmation of to repeat
//          the game.
//
// Output:  Program welcomes user, gives information on how to use program,
//          and game begins. Game rounds continue until user answers prompt
//          to leave game, and program says goodbye and exits.
//

#include <iostream>
#include "tictactoex.h"

using namespace std;

const char YES = 'y';
const char XCHAR = 'X';
const char OCHAR = 'O';
const char BLANKCHAR = ' ';
const int SIZEMIN = 3;
const int SIZEMAX = 15;

int main()
{
  char active;
  char cont = YES;
  char winner;
  bool status;
  bool placed;
  int size = 0;
  int row;
  int col;
  cout << "\033c";
  cout << "╔═════════════════════════════════════════════════╗\n";
  cout << "║ Ｗｅｌｃｏｍｅ ｔｏ ＴｉｃＴａｃＴｏｅ （ｐ２） ║\n";
  cout << "║                  By Devon McKee                 ║\n";
  cout << "╚═════════════════════════════════════════════════╝\n";
  cout << "                                                   \n";
  cout << "This program will allow you to play TicTacToe from \n";
  cout << "the (relative) comfort of your own terminal. After \n";
  cout << "this screen, the game will begin and you can play  \n";
  cout << "by entering the row and column number of the space \n";
  cout << "you want to place your piece in. When the game     \n";
  cout << "detects there is a winner, the game will end and   \n";
  cout << "the scoreboard will be displayed.                  \n";
  cout << "Press ENTER to continue.. ";
  cin.ignore();
  while(size < SIZEMIN || size > SIZEMAX){
    cout << "How big would you like the board to be? (3-15) ";
    cin >> size;
    cin.ignore();
  }
  Tictactoe game(size);
  while(cont == YES){
    active = XCHAR;
    status = true;
    winner = BLANKCHAR;
    while(status == true && winner == BLANKCHAR){
      cout << "\033c";
      placed = false;
      game.printBoard();
      cout << "It is " << active << "'s turn.\n";
      while(placed == false){  
        row = -1;
        col = -1;
        while(row < 0 || row >= size){
          cout << "What row would you like to place your piece in? ";
          cin >> row;
        }
        while(col < 0 || col >= size){ 
          cout << "What column would you like to place your piece in? ";
          cin >> col;
        }
        placed = game.placePiece(active, row, col);
      }
      cout << "\n";
      if(active == XCHAR){
        active = OCHAR;
      }else if(active == OCHAR){
        active = XCHAR;
      }
      status = game.checkStatus();
      winner = game.checkWinner();
    }
    if(winner == BLANKCHAR){
      cout << "Game over! The game was a tie.\n";
    }else{
      cout << "Game over! The winner was " << winner << ".\n";
    }
    game.incrementWins(winner);
    game.printScoreboard();
    game.resetBoard();
    cout << "Would you like to play again? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  cout << "\033c";
  cout << "╔═══════════════════════════════╗\n";
  cout << "║ Thanks for playing TicTacToe! ║\n";
  cout << "║        Have a nice day!       ║\n";
  cout << "╚═══════════════════════════════╝\n";
  return 0;
}
