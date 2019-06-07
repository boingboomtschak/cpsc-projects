// Devon McKee
// p1.cpp
// Stack class, odd integers only
// Purpose:
//
// Input:
//
// Output:
//

#include <iostream>
#include "stack.h"

using namespace std;

void testStack();
// tests Stack methods

int main()
{
  cout << "\033c";
  cout << "----------------\n";
  cout << "   P1 - Stack   \n";
  cout << " (Odd Integers) \n";
  cout << "----------------\n";
  cout << "\n";
  cout << "Press ENTER to test Stack functions..";
  cin.ignore();
  cout << "Testing Stack functions...\n";
  testStack();
  cout << "Stack testing complete.\n";
  cout << "Press ENTER to exit the program..";
  cin.ignore();
  cout << "Have a nice day!\n";
  cout << "\n\n\n";
  return 0;
}

void testStack()
{
  int val;
  cout << "Testing default constructor on Stack s1\n";
  Stack s1;
  cout << "Testing constructor with size 3 on Stack s2\n";
  Stack s2(3);
  cout << "Testing Stack::push(val) with odd ints\n";
  val = 3;
  for(int i=0; i<4; i++){
    cout << "Pushing " << val << " to s1\n";
    s1.push(val);
    val = val + 2;
  }
  cout << "Attempting to catch the EvenInteger exception from s1\n";
  try{
    s1.push(2);
  }catch(Stack::EvenInteger){
    cout << "Exception EvenInteger: Stack cannot accept even integers\n";
  }
  cout << "Testing copy constructor\n";
  cout << "Creating s3 as a copy of s1\n";
  Stack s3(s1);
  cout << "Testing Stack::pop() and Stack::isEmpty()\n";
  while(!s1.isEmpty()){
    cout << "Popping " << s1.pop() << " from s1\n";
  }
  cout << "Stack s1 is now empty\n";
  while(!s3.isEmpty()){
    cout << "Popping " << s3.pop() << " from s3\n";
  }
  cout << "Stack s3 is now empty\n";
  cout << "Testing Stack::resize() on s2 (size 3)\n";
  for(int i=0; i<20; i++){
    cout << "Pushing " << val << " to s2\n";
    s2.push(val);
    val = val + 2;
  }
  cout << "Testing overloaded assignment operator (OAO)\n";
  cout << "Copying s2 into s1 with OAO\n";
  s1 = s2;
  cout << "Emptying s2 with Stack::pop() and Stack::isEmpty()\n";
  while(!s2.isEmpty()){
    cout << "Popping " << s2.pop() << " from s2\n";
  }
  cout << "Emptying s1 with same method\n";
  while(!s1.isEmpty()){
    cout << "Popping " << s1.pop() << " from s1\n";
  }
  cout << "Attempting to catch the EmptyStack exception from s1\n";
  try{
    cout << s1.pop();
  }catch(Stack::EmptyStack){
    cout << "Exception EmptyStack: Cannot pop from empty Stack\n";
  }
}
