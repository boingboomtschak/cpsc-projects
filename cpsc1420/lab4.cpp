// Devon McKee
// Lab #4 (Repeating Decisions)
// 2018-10-10

#include <iostream>
#include <cstdlib>

using namespace std;

void calculateMultiple(){
  int num1, num2;
  cout << "###############################\n";
  cout << "# Lab 4 (Repeating Decisions) #\n";
  cout << "###############################\n";
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

int main() {
  bool again = true;
  string run;
  // First time run
  cout << "Would you like to calculate multiples? ";
  getline(cin, run);
  system("clear");
  if(run == "yes"){
    calculateMultiple();
    while(again){
      string ans;
      cout << "Would you like to calculate again? ";
      getline(cin, ans);
      if(ans == "yes"){
        system("clear");
        calculateMultiple();
      } else {
        cout << "Have a nice day!\n\n";
        again = false;
      }
    }
  } else {
    cout << "Have a nice day!\n\n";
    return 0;
  }
}
