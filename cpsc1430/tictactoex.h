// Devon McKee
// tictactoex.h (EC)
// Header file for tictactoe board class for TicTacToe (p2)
// 2019-02-07

#include <iostream>
#include <iomanip>

#ifndef TICTACTOE_H
#define TICTACTOE_H

class Tictactoe
{
 public:
  Tictactoe(); // constructor
  Tictactoe(int newSize);
  ~Tictactoe(); // destructor
  Tictactoe(const Tictactoe &cp); // copy constructor
  Tictactoe& operator=(const Tictactoe &cp); // overloaded assignment operator
  bool placePiece(char piece, int row, int col);
  // PRE: Takes char identifying user and ints for row/col #
  // Places piece on board, returns false if space is taken.
  // POST: Returns true if successful, false if space taken.
  bool incrementWins(char winner);
  // PRE: Takes char identifying winner
  // Increments score of winner.
  bool checkStatus();
  // POST: Checks if game is still going (board contains empty spaces),
  //       returns false if all spots are filled.
  char checkWinner();
  // POST: Checks if user has won, returns char of winner or blank char if no
  //       winner yet.
  void printBoard();
  void printScoreboard();
  void resetBoard();
  // Resets values in board to blank char
  int getSize();
 private:
  int size;
  char **board;
  int xScore;
  int oScore;
  int ties;
};

#endif // tictactoe_h
