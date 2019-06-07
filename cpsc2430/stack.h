// Devon McKee
// stack.h
// Header file for Stack class (odd ints only)
// 2019-04-08

#ifndef STACK_H
#define STACK_H

class Stack
{
 public:
  class EmptyStack{};
  class EvenInteger{};
  Stack(); // constructor
  Stack(int num); // constructor with parameter for size
  Stack(const Stack &cp); // copy constructor
  Stack& operator=(const Stack &cp); // overloaded assignment operator
  ~Stack(); // destructor 
  void push(int val);
  // pushes val to stack (throws EvenInteger if given even integer)
  int pop();
  // pops value on top of stack
  bool isEmpty();
  // returns true if stack is empty
 private:
  int* stack;
  int top;
  int size;
  void resize();
};

#endif 
