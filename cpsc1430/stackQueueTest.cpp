// Susan Reeder
// stackQueueTest.cpp
// testing of integer stack & queue packages

#include <iostream>
#include "stack.h"
#include "queue.h"

using namespace std;

void testStack();
// tests all stack package methods

void testQueue();
// tests all queue package methods

int main()
{
  cout << endl << endl;
  cout << "testing Stack operations...." << endl;
  testStack();
  cout << endl;
  cout << "Press enter to continue with Queue test....";
  cin.get();
  cout << "testing Queue operations...." << endl;
  testQueue();
  cout << "Tests done" << endl;
  cout << endl << endl;
  return 0;
}

void testStack()
{
  int val;
  // constructor
  Stack s1;
  // constructor with size
  Stack s2(3);

  // push
  cout << "pushing 4 values onto stack of size 50" << endl;
  val = 10;
  for (int i = 0; i < 4; i++){
	cout << "Now pushing " << val << endl;
	s1.push(val);
	val++;
  }
  // copy constructor
  cout << "making a copy of stack into new instance" << endl;
  Stack s3(s1);
  // pop & isEmpty
  cout << "now popping all values from original stack" << endl;
  while (!s1.isEmpty())
	cout << s1.pop() << ' ';

  cout << endl;

  cout << "now popping all values from copied stack" << endl;
  while (!s3.isEmpty())
	cout << s3.pop() << ' ';
  
  cout << endl;

  // resize
  cout << "pushing 5 values onto stack (s2) of size 3" << endl;
  val = 15;
  for (int i = 0; i < 5; i++){
	cout << "Now pushing " << val << endl;
	s2.push(val);
	val++;
  }

  // assignment operator
  cout << "copying s2 into s1" << endl;
  s1 = s2;
  cout << "now popping all of s2" << endl;
  while (!s2.isEmpty())
	cout << s2.pop() << ' ';
  cout << endl;
  
  cout << "now popping all of s1" << endl;
  while (!s1.isEmpty())
	cout << s1.pop() << ' ';
  cout << endl;
  
  cout << "trying to catch the EmptyStack exception" << endl;
  try{
	cout << s1.pop();
  }
  catch (Stack::EmptyStack){
	cout << "ERROR: Cannot pop from empty stack"  << endl;
  }
  cout << endl;
}

void testQueue()
{
  int val;
  // constructor
  Queue q1, q3;
  // enqueue
  cout << "Adding 5 items to queue...." << endl;
  val = 5;
  for (int i = 0; i < 5; i++){
	cout << "Enqueuing " << val << endl; 
	q1.enqueue(val);
	val++;
  }
  // copy constructor
  cout << "Making a copy of q1 into new instance" << endl;
  Queue q2(q1);
  cout << "now emptying q1" << endl;
  // dequeue & isEmpty
  while (!q1.isEmpty())
	cout << q1.dequeue() << ' ';
  cout << endl;
  
  // assignment operator
  cout << "copying q2 into q3 using overloaded assignment operator" << endl;
  q3 = q2;
  cout << "now removing all values from q2" << endl;
  while (!q2.isEmpty())
	cout << q2.dequeue() << ' ';
  cout << endl;
  cout << "now removing all values from q3" << endl;
  while (!q3.isEmpty())
  	cout << q3.dequeue() << ' ';
  cout << endl;
  cout << "trying to catch the EmptyQueue exception" << endl;

  try{
    cout << q3.dequeue();
  }
  catch (Queue::EmptyQueue){
    cout << "ERROR: Cannot remove from empty queue" << endl;
  }
}
  
