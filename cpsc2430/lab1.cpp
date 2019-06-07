// Devon McKee
// lab1.cpp
// 2019-04-03

#include <iostream>
#include <iomanip>

using namespace std;

const int NUM_INTS = 13;
const int INT_MIN = 10;
const int INT_MAX = 100;
const char YES = 'y';

int returnMax(int arr[], int count);
// PRE: Takes array of integers of size count
// POST: returns maximum integer value in array

int main()
{
  int count;
  int arr[NUM_INTS];
  int num;
  int arrMax;
  char cont = YES;
  cout << "\033c";
  cout << "Welcome to Lab #1!\n";
  cout << " By Devon McKee\n";
  cout << "------------------\n";
  cout << "Please enter 13 even numbers between " << INT_MIN << " and "
       << INT_MAX << ".\n";
  while(cont == YES){
    count = 0;
    while(count < NUM_INTS){
      cout << "Enter number " << count << ": ";
      cin >> num;
      cin.ignore();
      if(num < INT_MIN || num > INT_MAX || (num % 2) == 1){
        cout << "Number must be between " << INT_MIN << " and "
             << INT_MAX << ".\n";
        cout << "Number must also be even.\n";
      }else{
        arr[count] = num;
        count++;
      }
    }
    cout << "-------------\n";
    cout << "Index | Value\n";
    for(int i=0; i<count; i++){
      cout << setw(5) << i << " | " << setw(5) << arr[i] << "\n";
    }
    arrMax = returnMax(arr, count);
    cout << "The maximum value of your array is " << arrMax << ".\n";
    cout << "Would you like to run it again? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  cout << "\033c";
  return 0;
}

int returnMax(int arr[], int count)
{
  int max = arr[0];
  for(int i=1; i<count; i++){
    if(arr[i] > max){
      max = arr[i];
    }
  }
  return max;
}
