// Devon McKee
// Lab #5 (Pretty Fors)
// 2018-10-15

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int NUM_MIN = 1;
const int NUM_MAX = 10;

int main() {
  int num;
  bool cont = true;
  string ans;
  while(cont == true){
    cout << "\033c";
    cout << "#######################\n";
    cout << "# Lab 5 (Pretty Fors) #\n";
    cout << "# By Devon McKee      #\n";
    cout << "#######################\n";
    cout << "\n";
    cout << "Please enter a number from " << NUM_MIN << " to " << NUM_MAX
         << ": ";
    cin >> num;
    cin.ignore();
    if(num >= NUM_MIN && num <= NUM_MAX){
      // #1
      cout << "1. " << num << " copies of " << num  << " on one line.\n";
      for(int i=0;i<num;i++){
        cout << num;
      }
      cout << "\n\n";
      // #2
      cout << "2. " << num << " lines with a single 1 on each line.\n";
      for(int i=0;i<num;i++){
        cout << num << "\n";
      }
      cout << "\n";
      // #3
      cout << "3. Multiplication table to " << num << ".\n";
      cout << "  ";
      for(int i=1;i<=num;i++){
        cout << setw(4) << i;
      }
      cout << "\n";
      for(int i=1;i<=num;i++){
        cout << setw(2) << i;
        for(int j=1;j<=num;j++){
          cout << setw(4) << i * j;
        }
        cout << "\n";
      }
      cout << "\n";
      // #4
      cout << "4. " << num << " lines with 1 ones on the first line,\n"
           << "2 twos on the second, etc. to " << num <<".\n";
      for(int i=0;i<=num;i++){
        for(int j=0;j<i;j++){
          cout << i << " ";
        }
        cout << "\n";
      }
      cout << "\n";
      // #5
      cout << "5. The outline of a half-diamond, with " << num << " at the\n"
           << "widest point.\n";
      for(int i=1;i<=num;i++){
        for(int j=1;j<i;j++){
          cout << " ";
        }
        cout << i << "\n";
      }
      for(int i=num-1;i>=1;i--){
        for(int j=1;j<i;j++){
          cout << " ";
        }
        cout << i << "\n";
      }
      cout << "\n";
      // again?
      cout << "Would you like to run again? <y/n> ";
      getline(cin, ans);
      if(ans != "y"){
        cout << "Thanks for using my program!\n";
        cout << "\n";
        cont = false;
      }
    }else{
      cout << "The number you entered does not fit the required range!\n";
      cout << "Press ENTER to continue...";
      cin.ignore();
    }
  }
}
