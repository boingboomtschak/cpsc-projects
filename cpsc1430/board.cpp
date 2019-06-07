// Devon McKee
// board.cpp
// Implementation of Board as described in board.h
// 2019-1-17

#include "board.h"

using namespace std;

Board::Board()
{
  srand(time(0)); // seeding rand()
  for(int i=0; i<=100; i++){
    board[i] = 0;
  }
  board[1] = 37;
  board[4] = 10;
  board[9] = 12;
  board[23] = 21;
  board[28] = 56;
  board[36] = 8;
  board[51] = 15;
  board[71] = 19;
  board[80] = 20;
  board[95] = -20;
  board[93] = -20;
  board[87] = -63;
  board[64] = -4;
  board[62] = -43;
  board[56] = -3;
  board[49] = -38;
  board[48] = -22;
  board[16] = -10;
}

bool Board::ifWinner(int space)
{
  if(space == 100){
    return true;
  }else{
    return false;
  }
}

int Board::takeTurn(string name, int& space)
{
  int newSpace = space;
  int spin = Board::spin();
  int ret = 0;
  cout << "It is " << name << "'s turn.\n";
  cout << "They are on space " << space << ".\n";
  cout << "They rolled a " << spin << "!\n";
  if(newSpace + spin <= 100)
    newSpace += spin;
  cout << "They are now on space " << newSpace << ".\n";
  if(board[newSpace] > 0){
    cout << name << " landed on a ladder and moved forward "
         << board[newSpace] << " spaces.\n";
    cout << "They are now on space " << newSpace + board[newSpace] << ".\n";
    ret = 1;
  }else if(board[newSpace] < 0){
    cout << name << " landed on a chute and moved back "
         << board[newSpace] * -1 << " spaces.\n";
    cout << "They are now on space " << newSpace + board[newSpace] << ".\n";
    ret = -1;
  }
  newSpace += board[newSpace];
  cout << name << "'s turn is now over. Press ENTER to continue..\n";
  cout << "\n";
  cin.ignore();
  space = newSpace;
  return ret;
}

int Board::spin()
{
  return (rand() % (6 - 1 + 1)) + 1;
}
