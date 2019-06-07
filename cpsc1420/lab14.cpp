// Devon McKee
// Lab #14 (Dimensional Madness)
// 2018-12-03

#include <iostream>
#include <iomanip>

using namespace std;

const int ROWS = 6;
const int COLS = 6;
const int COL_WIDTH = 4;
const int MIN_VALUE = -99;
const int MAX_VALUE = 999;
const char YES = 'y';

void printTable(const int array[][COLS], int arrayRows, int arrayCols);
// prints array to screen as a table

int calcTotal(const int array[][COLS], int arrayRows, int arrayCols);
// calculates total of all values in 2d array and returns total as int

int main()
{
  int dimArray[ROWS][COLS] = {0};
  int userRow;
  int userCol;
  int userVal;
  char cont = YES;
  int total;
  cout << "\033c";
  cout << "-- Welcome to Lab #14 (Dimensional Madness!!) --\n";
  cout << " - By Devon McKee - \n";
  cout << "\n";
  printTable(dimArray, ROWS, COLS);
  while(cont == YES){
    userVal = 1000;
    cout << "Please supply a row #: ";
    cin >> userRow;
    cin.ignore();
    cout << "Please supply a col #: ";
    cin >> userCol;
    cin.ignore();
    while(userVal < MIN_VALUE || userVal > MAX_VALUE){
      cout << "Please supply a value from " << MIN_VALUE
           << " to " << MAX_VALUE << ": ";
      cin >> userVal;
      cin.ignore();
    }
    dimArray[userRow][userCol] = userVal;
    printTable(dimArray, ROWS, COLS);
    cout << "Would you like to enter a new value? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  total = calcTotal(dimArray, ROWS, COLS);
  cout << "The total of all the values in the array is " << total <<"\n";
  cout << "\n";
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit...\n";
  cin.ignore();
  return 0;
}

void printTable(const int array[][COLS], int arrayRows, int arrayCols)
{
  cout << "   ";
  for(int c = 0;c < arrayCols;c++){
    cout << setw(3) << c;
  }
  cout << "\n";
  for(int r = 0;r < arrayRows;r++){
    cout << setw(3) << r;
    for(int c = 0;c < arrayCols;c++){
      cout << setw(3) << array[r][c];
    }
    cout << "\n";
  }
}

int calcTotal(const int array[][COLS], int arrayRows, int arrayCols)
{
  int total = 0;
  for(int r = 0;r < arrayRows;r++){
    for(int c = 0;c < arrayCols;c++){
      total += array[r][c];
    }
  }
  return total;
}
