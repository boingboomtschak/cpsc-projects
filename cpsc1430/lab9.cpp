// Devon McKee
// 2019-03-15
// Lab #9 (Sort it out & Find it)

#include <iostream>
#include <fstream>

using namespace std;

const string FILEN = "/home/fac/sreeder/class/cs1430/lab9.dat";
const char YES = 'y';

void arrSwap(string arr[], int i1, int i2);

int findMin(string arr[], int min, int max);

void sort(string arr[], int count);

void printList(string arr[], int count);

int search(string arr[], int count, string target);

int main()
{
  ifstream infile;
  string read;
  string arr[50];
  string searchTerm;
  int count = 0;
  int searchIndex = -1;
  char cont = YES;
  cout << "Welcome to Lab #9!\n";
  cout << "(Sort it out & Find it)\n";
  cout << "By Devon McKee\n";
  cout << "\n";
  cout << "Reading file..\n";
  infile.open(FILEN.c_str());
  if(infile.fail()){
    cout << "File error, exiting program..\n";
    cout << "Press ENTER to exit..";
    cin.ignore();
    return 0;
  }
  while (infile >> read && count < 50){
    arr[count] = read;
    count++;
  }
  cout << "File reading completed!\n";
  cout << "\n";
  printList(arr, count);
  cout << "Sorting beginning..\n";
  sort(arr, count);
  cout << "Sorting completed!\n";
  printList(arr, count);
  while(cont == YES){
    cout << "Search: ";
    cin >> searchTerm;
    cin.ignore();
    searchIndex = search(arr, count, searchTerm);
    if(searchIndex != -1){
      cout << "Searched term found at index " << searchIndex << "!\n";
    }else{
      cout << "Searched term not found!\n";
    }
    cout << "Would you like to continue searching? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  cout << "\n";
  cout << "Thank you for using my program!\n";
  cout << "Have a nice day!\n";
  return 0;
}

void arrSwap(string arr[], int i1, int i2)
{
  string shelf;
  shelf = arr[i1];
  arr[i1] = arr[i2];
  arr[i2] = shelf;
}

int findMin(string arr[], int min, int max)
{
  int minIndex = min;
  for(int i=min+1; i<max; i++){
    if(arr[i] < arr[minIndex]){
      minIndex = i;
    }
  }
  return minIndex;
}

void sort(string arr[], int count)
{
  int min;
  for(int i=0; i<count; i++){
    min = findMin(arr, i, count);
    arrSwap(arr, i, min);
  }
}

void printList(string arr[], int count)
{
  cout << "List:\n";
  for(int i=0; i<count; i++){
    cout << arr[i] << "\n";
  }
}

int search(string arr[], int count, string target)
{
  int retIndex = -1;
  for(int i=0; i<count; i++){
    if(arr[i] == target && arr[retIndex] != target){
      retIndex = i;
    }
  }
  return retIndex;
}
