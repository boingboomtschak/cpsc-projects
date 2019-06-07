// Devon McKee
// 2018-10-31
// Lab #8 (Referencing Functions) [lab8.cpp]

#include <iostream>
#include <string>

using namespace std;

void input(string& str1, string& str2);
// Takes two values of type "string" from the user and returns them to two
// variables in main.
// MODIFY: str1 & str2

void swapStr(string& str1, string& str2);
// Takes two pre-set variables and swaps their values by reference.
// MODIFY: str1 & str2
// OUT: shelf

void output(string str1, string str2);
// Prints two strings to the screen on the same line with a single space
// between them.
// IN: str1 & str2

int main()
{
  string firstString;
  string secondString;
  cout << "\033c"; // clears terminal
  cout << "Welcome to my lab #8!\n\n";
  input(firstString, secondString);
  output(firstString, secondString);
  swapStr(firstString, secondString);
  output(firstString, secondString);
  cout << "Thank you for using my program!\n";
  cout << "\n\n";
}

void input(string& str1, string& str2)
{
  cout << "\n";
  cout << "Please enter the first string: ";
  getline(cin, str1);
  cout << "\n";
  cout << "Please enter the second string: ";
  getline(cin, str2);
}

void swapStr(string& str1, string& str2)
{
  string shelf;
  shelf = str1;
  str1 = str2;
  str2 = shelf;
}

void output(string str1, string str2)
{
  cout << str1 << " " << str2 << "\n";
}
