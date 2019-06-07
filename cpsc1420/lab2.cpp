// Devon McKee
// Lab #2 (Input and Output)
// 2018-10-03

#include <iostream>
#include <string>

using namespace std;

int main(){
  string name;
  int age;
  cout << "############################\n";
  cout << "# Lab 2 (Input and Output) #\n";
  cout << "############################\n\n";
  cout << "What is your name?: ";
  getline(cin, name);
  cout << "\nHow old are you?: ";
  cin >> age;
  cout << "\nYour name is " << name << "\n";
  cout << "and you are " << age << " years old.\n";
}
