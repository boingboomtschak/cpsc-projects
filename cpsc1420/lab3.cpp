// Devon McKee
// Lab #3 (Making Decisions)
// 2018-10-08

#include <iostream>

using namespace std;

int main(){
  int num1, num2;
  cout << "############################\n";
  cout << "# Lab 3 (Making Decisions) #\n";
  cout << "############################\n";
  cout << "\n";
  cout << "First Number?: ";
  cin >> num1;
  cin.ignore();
  cout << "\n";
  cout << "Second Number?: ";
  cin >> num2;
  cin.ignore();
  cout << "\n";
  if((num1 % num2) == 0){
    cout << num1 << " is a multiple of " << num2 <<  "!\n";
    cout << "The other factor of " << num1 << " is " << (num1/num2) << ".\n";
    cout << "\n";
    cout << "Thank you for running my program!\n\n";
  }else{
    cout << num1 << " is not a multiple of " << num2 <<  "!\n";
    cout << "\n";
    cout << "Thank you for running my program!\n\n";
  }
}
