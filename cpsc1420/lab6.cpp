// Devon McKee
// 2018-10-17
// Lab #6 (Again and Again)

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int NUM_MIN = 0;

int main(){
  int num = 0;
  int sum = 0;
  string again = "y";
  while(again == "y"){
    num = 0;
    sum = 0;
    cout << "\033c";
    cout << "###########################\n";
    cout << "# Lab 6 - Again and Again #\n";
    cout << "# By Devon McKee          #\n";
    cout << "###########################\n";
    cout << "\n";
    cout << "Please enter a number above " << NUM_MIN << ": ";
    while(num <= NUM_MIN){
      cin >> num;
      cin.ignore();
    }
    for(int i=1;i<=num;i++){
      sum = sum+i;
    }
    cout << "The sum of all numbers leading up to (and including) your \n"
         << "number is " << sum << "\n";
    cout << "\n";
    cout << "Would you like to run again? <y/n> ";
    cin >> again;
    cin.ignore();
  }
  cout << "\n";
  cout << "Thanks for using my program!\n";
  cout << "\n";
}
