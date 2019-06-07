// Devon McKee
// lab4.cpp (Heaps)
// 2019-05-08

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int ARR_SIZE = 30;
const int NUM_ELEMENTS = 15;
const int RAND_INT_MIN = 0;
const int RAND_INT_MAX = 20;

void insertHeap(int arr[], int& size, int num);

int removeMin(int arr[], int& size);

void printHeap(int arr[], int size);

int main()
{
  int arr[ARR_SIZE] = {0};
  int size = 0;
  int rInt;
  srand(time(0));
  cout << "\033c";
  cout << "Welcome to Lab #4\n";
  cout << "By Devon McKee\n";
  cout << "\n\n";
  for(int i=0; i<NUM_ELEMENTS; i++){
    rInt = (rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN;
    insertHeap(arr, size, rInt);
  }
  cout << "Printing heap..\n";
  printHeap(arr, size);
  cout << "Removing all items from heap and printing..\n";
  cout << "Removing: \n";
  for(int i=0; i<NUM_ELEMENTS/5; i++){
    for(int i=0; i<5; i++){
      cout << setw(3) << removeMin(arr, size);
    }
    cout << "\n";
  }
  printHeap(arr, size);
  cout << "Repeating insert, print, delete, and print..\n";
  for(int i=0; i<NUM_ELEMENTS; i++){
    rInt = (rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN;
    insertHeap(arr, size, rInt);
  }
  cout << "Printing heap..\n";
  printHeap(arr, size);
  cout << "Removing all items from heap and printing..\n";
  cout << "Removing: \n";
  for(int i=0; i<NUM_ELEMENTS/5; i++){
    for(int i=0; i<5; i++){
      cout << setw(3) << removeMin(arr, size);
    }
    cout << "\n";
  }
  printHeap(arr, size);
  cout << "Heap testing complete!\n";
  cout << "Press ENTER to exit the program..";
  cin.ignore();
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  return 0;
}

void insertHeap(int arr[], int& size, int num)
{
  size++;
  int hole = size;
  while(hole > 1 && num < arr[hole/2]){
    arr[hole] = arr[hole/2];
    hole = hole/2;
  }
  arr[hole] = num;
}

int removeMin(int arr[], int& size)
{
  int hole = 1;
  int temp;
  int rm = arr[hole];
  arr[hole] = arr[size];
  size--;
  temp = arr[hole];
  while((hole*2 <= size && temp > arr[hole*2])
        || (hole*2+1 <= size && temp > arr[hole*2+1])){
    if(hole*2+1 <= size && arr[hole*2+1] < arr[hole*2]){
      arr[hole] = arr[hole*2+1];
      hole = hole*2+1;
    }else{
      arr[hole] = arr[hole*2];
      hole = hole*2;
    }
  }
  arr[hole] = temp;
  return rm;
}

void printHeap(int arr[], int size)
{
  if(size > 0){
    cout << "Heap: \n";
    for(int i=1;i<size; i++){
      cout << setw(3) << arr[i];
      if(i%5 == 0){
        cout << "\n";
      }
    }
    cout << "\n";
  }else{
    cout << "Heap empty!\n";
  }
}
