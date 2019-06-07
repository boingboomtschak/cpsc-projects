// Devon McKee
// board.h
// Header file for board class for Chutes & Ladders Redux (p1)
// 2019-1-17

#include <iostream>
#include <cstdlib>
#include <ctime>
#ifndef BOARD_H
#define BOARD_H

class Board
{
 public:
  Board();
  bool ifWinner(int space);
  // pre: method needs player's location on the board
  // post: method returns bool if player has won or not
  int takeTurn(std::string name, int& space);
  // pre: method needs name of player and their location on the board
  // post: method returns final space of player, as well as cout feedback
  int spin();
  // post: method returns result of spinner from 1 to 6
 private:
  int board[101]; // 101 so that indices match spaces on board
};

#endif // board_h
