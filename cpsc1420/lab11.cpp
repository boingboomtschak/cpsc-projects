// Devon McKee
// Lab #11 (Find it!)
// 2018-11-19

using namespace std;

#include <iostream>
#include <fstream>
#include <cstring>

const string FILENAME = "/home/fac/sreeder/class/cs1420/lab11input.dat";
const int SIZE = 75;
const char YES = 'y';

int search(string arr[], int arrCount, string target);
// searches for the given string from the given array and returns the index
// of the string if found, otherwise returns -1

int main()
{
  ifstream infile;
  string strArray[SIZE];
  int strCount = 0;
  char cont = YES;
  string searchTerm;
  int resultIndex;
  // welcome user
  cout << "\033c";
  cout << "## Welcome to Devon McKee's ##\n";
  cout << "## Lab #11 (Find it!)       ##\n";
  cout << "\n";
  infile.open(FILENAME.c_str());
  // checking for file validity
  if(infile.fail()){
    cout << "File error, exiting program..\n";
    cin.ignore();
    return 0;
  }
  // file reading begins
  while(strCount < SIZE && infile >> strArray[strCount]){
    strCount++;
  }
  // closing file after string reading
  infile.close();
  // user input begins
  while(cont == YES){
    cout << "Which word would you like to search for? ";
    getline(cin, searchTerm);
    resultIndex = search(strArray, strCount, searchTerm);
    if(resultIndex  == -1){
      cout << "The term does not exist in the array!\n";
    }else{
      cout << "The term exists in the array and is at index " << resultIndex
           << ".\n";
    }
    cout << "Would you like to search again? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  cout << "\033c";
  cout << "Thanks for using my program, goodbye!\n";
  cout << "Press ENTER to continue..\n";
  cin.ignore();
  return 0;
}

int search(string arr[], int arrCount, string target)
{
  int index = 0;
  while(index < arrCount && arr[index] != target){
    index++;
  }
  if(index == arrCount){
    return -1;
  }else{
    return index;
  }
}
