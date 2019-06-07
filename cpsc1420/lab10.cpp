// Devon McKee
// 2018-11-07
// Lab #10 (Functional Arrays)

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const string FILENAME = "/home/fac/sreeder/class/cs1420/lab10input.dat";
const int SIZE = 50;
const int NUM_DIGITS = 3;
const int INDEX_COL = 2;
const int FLOAT_COL = 7;

float sum(float arr[], int arrCount);
// sums all items in given array and returns sum as a floating-point value.

void printFloat(float arr[], int arrCount);
// prints items from given float array in ordered list with indices

int main()
{
  ifstream infile;
  float num[SIZE] = {0.0};
  int numCount = 0;
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(NUM_DIGITS);
  // welcome user
  cout << "\033c";
  cout << " - Welcome to Lab #10 (Functional Arrays) - \n";
  cout << " --- By Devon McKee ---\n";
  cout << "\n";
  // opening file and checking for validity
  infile.open(FILENAME.c_str());
  if(infile.fail()){
    cout << "File error, exiting program..\n";
    cin.ignore();
    return 0;
  }
  // file reading begins
  while(numCount < SIZE && infile >> num[numCount]){
    numCount++;
  }
  // file closed after reading
  infile.close();
  // printing array
  printFloat(num, numCount);
  // printing sum
  cout << "Sum of all given numbers: " << sum(num, numCount) << "\n";
  // sending off user with msg
  cout << "\n";
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit... \n";
  cin.ignore();
  return 0;
}

float sum(float arr[], int arrCount)
{
  float sum = 0.0;
  for(int i=0;i<arrCount;i++){
    sum += arr[i];
  }
  return sum;
}

void printFloat(float arr[], int arrCount)
{
  cout << " - Float Values w/ Indices -\n";
  for(int i=0;i<arrCount;i++){
    cout << setw(INDEX_COL) << i << " - " << setw(FLOAT_COL) << arr[i] << "\n";
  }
  cout << " ---------------------------\n";
  cout << "\n";
}
