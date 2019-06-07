// Devon McKee
// tictactoex.cpp (EC)
// Implementation of Tictactoe as described in tictactoex.h

#include "tictactoex.h"

using namespace std;

Tictactoe::Tictactoe() // constructor
{
  size = 3;
  xScore = 0;
  oScore = 0;
  ties = 0;
  board = new char*[size];
  for(int i=0; i<size; i++){
    board[i] = new char[size];
  }
  for(int i=0; i<size; i++){
    for(int j=0;j<size; j++){
      board[i][j] = ' ';
    }
  }
}

Tictactoe::Tictactoe(int newSize)
{
  size = newSize;
  xScore = 0;
  oScore = 0;
  ties = 0;
  board = new char*[size];
  for(int i=0; i<size; i++){
    board[i] = new char[size];
  }
  for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
      board[i][j] = ' ';
    }
  }
}

Tictactoe::~Tictactoe() // destructor
{
  for(int i=0; i<size; i++){
    delete[] board[i];
  }
  delete[] board;
}

Tictactoe::Tictactoe(const Tictactoe &cp) // copy constructor
{
  board = cp.board;
  xScore = cp.xScore;
  oScore = cp.oScore;
  ties = cp.ties;
}

Tictactoe& Tictactoe::operator=(const Tictactoe &cp) // OAO
{
  board = cp.board;
  xScore = cp.xScore;
  oScore = cp.oScore;
  ties = cp.ties;
  return *this;
}

bool Tictactoe::placePiece(char piece, int row, int col)
{
  if(board[row][col] == ' '){
    board[row][col] = piece;
    return true;
  }else{
    cout << "Space taken! Try again.. \n";
    return false;
  }
}

bool Tictactoe::incrementWins(char winner)
{
  if(winner == 'X'){
    xScore++;
  }else if(winner == 'O'){
    oScore++;
  }else{
    ties++;
  }
  return true;
}

bool Tictactoe::checkStatus()
{
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(board[i][j] == ' '){
        return true;
      }
    }
  }
  return false;
}

char Tictactoe::checkWinner()
{
  char temp;
  int count;
  // checking rows
  for(int i=0; i<size; i++){
    temp = board[i][0];
    count = 1;
    for(int j=1; j<size; j++){
      if(board[i][j] == temp){
        count++;
      }
    }
    if(count == size){
      return temp;
    }
  }
  //checking cols
  for(int i=0; i<size; i++){
    temp = board[0][i];
    count = 1;
    for(int j=1; j<size; j++){
      if(board[j][i] == temp){
        count++;
      }
    }
    if(count == size){
      return temp;
    }
  }
  // checking diagonals
  temp = board[0][0];
  count = 1;
  for(int i=1; i<size; i++){
    if(board[i][i] == temp){
      count++;
    }
  }
  if(count == size){
    return temp;
  }
  temp = board[size-1][0];
  count = 1;
  for(int i=1; i<size; i++){
    if(board[size-(i+1)][i] == temp){
      count++;
    }
  }
  if(count == size){
    return temp;
  }
  return ' ';
}

void Tictactoe::printBoard()
{
  // abandon all hope, ye who attempt to comprehend this code
  cout << "  ";
  for(int i=0; i<size; i++){
    cout << setw(4) << i;
  }
  cout << "\n";
  cout << "   ╔";
  for(int i=0; i<size-1; i++){
    cout << "═══╦";
  }
  cout << "═══╗\n";
  for(int i=0; i<size; i++){
    cout << setw(2) << i << " ";
    for(int j=0; j<size; j++){
      cout << "║ " << board[i][j] << " ";
    }
    cout << "║\n";
    if(i < size-1){
      cout << "   ╠";
      for(int k=0; k<size-1; k++){
        cout << "═══╬";
      }
      cout << "═══╣\n";
    }
  }
  cout << "   ╚";
  for(int i=0; i<size-1; i++){
    cout << "═══╩";
  }
  cout << "═══╝\n";
}

void Tictactoe::printScoreboard()
{
  cout << "╔═══╦═══╦══════╗\n";
  cout << "║ X ║ O ║ Ties ║ \n";
  cout << "╠═══╬═══╬══════╣\n";
  cout << "║" << setw(3) << xScore << "║"
       << setw(3) << oScore << "║"
       << setw(6) << ties << "║\n";
  cout << "╚═══╩═══╩══════╝\n";
}

void Tictactoe::resetBoard()
{
  for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
      board[i][j] = ' ';
    }
  }
}

int Tictactoe::getSize()
{
  return size;
}
