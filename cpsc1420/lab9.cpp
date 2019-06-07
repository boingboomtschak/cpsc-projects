// Devon McKee
// 2018-11-6
// Lab #9 (Array Distribution)

using namespace std;

#include <iostream>
#include <fstream>

const string FILENAME = "/home/fac/sreeder/class/cs1420/lab9input.dat";
const int SIZE = 30;

int main()
{
  ifstream infile;
  int evenNum[SIZE] = {0};
  int evenCount = 0;
  int oddNum[SIZE] = {0};
  int oddCount = 0;
  int negNum[SIZE] = {0};
  int negCount = 0;
  int shelf = 0;
  // welcome user
  cout << "\033c";
  cout << "Welcome to Lab #9 (Array Distribution)\n";
  cout << " --- By Devon McKee ---\n";
  cout << "\n";
  infile.open(FILENAME.c_str());
  // checking for valid file
  if(infile.fail()){
    cout << "File error, exiting program..\n";
    cin.ignore();
    return 0;
  }
  // file reading begins
  while(negCount < SIZE && oddCount < SIZE && evenCount < SIZE
        && infile >> shelf){
    if(shelf < 0){
      negNum[negCount] = shelf;
      negCount++;
    }else if(shelf % 2 == 0){
      evenNum[evenCount] = shelf;
      evenCount++;
    }else{
      oddNum[oddCount] = shelf;
      oddCount++;
    }
  }
  // close file after reading is complete
  infile.close();
  // print arrays
  cout << "-- Even Numbers --\n";
  for(int i=0;i<evenCount;i++){
    cout << evenNum[i] << "\n";
  }
  cout << "\n";
  cout << "-- Odd Numbers --\n";
  for(int i=0;i<oddCount;i++){
    cout << oddNum[i] << "\n";
  }
  cout << "\n";
  cout << "-- Negative Numbers --\n";
  for(int i=0;i<negCount;i++){
    cout << negNum[i] << "\n";
  }
  cout << "\n";
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit... \n";
  cin.ignore();
  return 0;
}
