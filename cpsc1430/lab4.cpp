// Devon McKee
// 2019-2-1
// lab4.cpp (Two-Dimensional Flexibility)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const char YES = 'y';
const int MIN = 3;
const int MAX = 10;
const int MAX_VAL = 100;

int main()
{
  srand(time(0));
  int **array;
  int size;
  int sum;
  char cont = YES;
  // welcome
  cout << "\033c";
  cout << " - Welcome to Lab #4 (Two-Dimensional Flexibility) -\n";
  cout << " - By Devon McKee - \n";
  cout << "\n";
  while(cont == YES){
    size = 0;
    while(size < MIN || size > MAX){
      cout << "How many rows/cols? (" << MIN << " to " << MAX << ")";
      cin >> size;
      cin.ignore();
    }
    // allocating memory
    array = new int*[size];
    for(int i=0; i<size; i++){
      array[i] = new int[size];
    }
    // populating array with numbers from 1-100
    for(int i=0; i<size; i++){
      for(int j=0; j<size; j++){
        array[i][j] = rand() % MAX_VAL + 1;
      }
    }
    // printing array
    cout << "Array: \n";
    for(int i=0; i<size; i++){
      for(int j=0; j<size; j++){
        cout << setw(4) << array[i][j];
      }
      cout << "\n";
    }
    cout << "\n";
    // sum rows
    for(int i=0; i<size; i++){
      sum = 0;
      for(int j=0; j<size; j++){
        sum += array[i][j]; 
      }
      cout << "Sum of row " << i << ": " << sum << "\n";
    }
    cout << "\n";
    // sum cols
    for(int i=0; i<size; i++){
      sum = 0;
      for(int j=0; j<size; j++){
        sum += array[j][i];
      }
      cout << "Sum of col " << i << ": " << sum << "\n";
    }
    cout << "\n";
    // sum diagonals
    sum = 0;
    for(int i=0; i<size; i++){
      sum += array[i][i];
    }
    cout << "Sum of diagonal 1: " << sum << "\n";
    sum = 0;
    for(int i=0; i<size; i++){
      sum += array[size-(i+1)][i];
    }
    cout << "Sum of diagonal 2: " << sum << "\n";
    sum = 0;
    for(int i=0; i<size; i++){
      sum += array[i][size-(i+1)];
    }
    cout << "Sum of diagonal 3: " << sum << "\n";
    sum = 0;
    for(int i=0; i<size; i++){
      sum += array[size-(i+1)][size-(i+1)];
    }
    cout << "Sum of diagonal 4: " << sum << "\n";
    cout << " \n";
    // deallocating memory
    for(int i=0; i<size; i++){
      delete[] array[i];
    }
    delete[] array;
    cout << "Would you like to run again? ";
    cin >> cont;
    cin.ignore();
  }
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  return 0;
}
