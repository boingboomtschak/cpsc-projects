// Devon McKee
// Lab #12 ()
// 2018-11-26

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int ARRAY_SIZE = 40;
const int VAL_MAX = 20;

void arrSwap(int array[], int index1, int index2);
// swaps two items in given array at given indices

int findMin(int array[], int index1, int index2);
// finds minimum value in given array and returns index of it

void selectionSort(int array[], int arrCount);
// sorts array using the selection sort algorithm

void printArr(int array[], int arrCount);
// prints formatted array to console

int main()
{
  int toSort[ARRAY_SIZE];
  int toSortCount = 0;
  int numValues = ARRAY_SIZE + 1;
  // seeding rand();
  srand(time(0));
  cout << "\033c";
  cout << " -- Welcome to Lab #12 (Sort it!) -- \n";
  cout << " -- By Devon McKee -- \n";
  while(numValues > ARRAY_SIZE){
    cout << "\n";
    cout << "How many values would you like to sort? (1 to " << ARRAY_SIZE
         << ") ";
    cin >> numValues;
    cin.ignore();
  }
  cout << "Populating list with " << numValues << " values... \n";
  // populating list with values from 1 to VAL_MAX
  for(int i=0;i<numValues;i++){
    toSort[i] = (rand() % VAL_MAX) + 1;
    toSortCount++;
  }
  printArr(toSort, toSortCount);
  // beginning sort
  selectionSort(toSort, toSortCount);
  cout << "Array sorted!\n";
  printArr(toSort, toSortCount);
  cout << "Thanks for using my program, goodbye!\n";
  return 0;
}

void arrSwap(int array[], int index1, int index2)
{
  int shelf;
  shelf = array[index1];
  array[index1] = array[index2];
  array[index2] = shelf;
}

int findMin(int array[], int index1, int index2)
{
  int minIndex = index1;
  for(int i=index1+1;i<index2;i++){
    if(array[i] < array[minIndex]){
      minIndex = i;
    }
  }
  return minIndex;
}

void selectionSort(int array[], int arrCount)
{
  int sortMin;
  int sortMax = arrCount;
  int minimum;
  for(int i=0;i<arrCount;i++){
    sortMin = i;
    minimum = findMin(array, i, sortMax);
    arrSwap(array, sortMin, minimum);
  }
}

void printArr(int array[], int arrCount)
{
  cout << " - Array - \n";
  cout << "Index | Value\n";
  for(int i=0;i<arrCount;i++){
    cout << setw(5) << i << " | " << setw(5) << array[i] << "\n";
  }
}
