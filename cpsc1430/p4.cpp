// Devon McKee
// p4.cpp
// Testing of integer Stack & Queue classes for Stack and Queue (p4)

#include <iostream>
#include "stack.h"
#include "queue.h"

using namespace std;

void testStack();
// tests Stack methods

void testQueue();
// tests Queue methods

int main()
{
  cout << "\033c";
  cout << "-=-=-=-=-=-=-=-=-=-=-=-\n";
  cout << "  Stack and Queue (p4)\n";
  cout << "    By Devon McKee\n";
  cout << "-=-=-=-=-=-=-=-=-=-=-=-\n";
  cout << "\n";
  cout <<"Press ENTER to test Stack functions..";
  cin.ignore();
  cout << "Testing Stack functions...\n";
  testStack();
  cout << "Stack testing complete.\n";
  cout << "\n";
  cout << "Press ENTER to test Queue functions..";
  cin.ignore();
  testQueue();
  cout << "Queue testing complete.\n";
  cout << "Press ENTER to exit the program..";
  cin.ignore();
  cout << "Have a nice day!\n";
  return 0;
}

void testStack()
{
  int val;
  cout << "Testing default constructor on Stack s1\n";
  Stack s1;
  cout << "Testing constructor with size 3 on Stack s2\n";
  Stack s2(3);
  cout << "Testing Stack::push(val)\n";
  val = 8;
  for(int i=0; i<4; i++){
    cout << "Pushing " << val << " to s1\n";
    s1.push(val);
    val++;
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
    val++;
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
    cout <<  s1.pop();
  }catch(Stack::EmptyStack){
    cout << "Exception EmptyStack: Cannot pop from empty Stack\n";
  }
}

void testQueue()
{
  int val;
  cout << "Testing constructor on Queues q1 and q3\n";
  Queue q1, q3;
  cout << "Enqueuing 5 items to Queue q1 with Queue:enqueue(val)\n";
  val = 4;
  for(int i=0; i<5; i++){
    cout << "Enqueuing " << val << " in q1\n";
    q1.enqueue(val);
    val++;
  }
  cout << "Testing copy constructor\n";
  cout << "Creating q2 as a copy of q1\n";
  Queue q2(q1);
  cout << "Emptying q1 with Queue::dequeue() and Queue::isEmpty()\n";
  while(!q1.isEmpty()){
    cout << "Dequeuing " << q1.dequeue() << " from q1\n";
  }
  cout << "Testing overloaded assignment operator (OAO)\n";
  cout << "Copying q2 into q3 using OAO\n";
  q3 = q2;
  cout << "Emptying q2 with previous method\n";
  while(!q2.isEmpty()){
    cout << "Dequeuing " << q2.dequeue() << " from q2\n";
  }
  cout << "Emptying q3 with previous method\n";
  while(!q3.isEmpty()){
    cout << "Dequeuing " << q3.dequeue() << " from q3\n";
  }
  cout << "Attempting to catch the EmptyQueue exception from q3\n";
  try{
    q3.dequeue();
  }catch(Queue::EmptyQueue){
    cout << "Exception EmptyQueue: Cannot dequeue from empty Queue\n";
  }
}
