// Devon McKee
// stack.h
// Header file for Stack class (handles ints)
// 2019-02-28

// #includes here

#ifndef STACK_H
#define STACK_H

class Stack
{
 public:
  class EmptyStack{};
  Stack(); // constructor
  Stack(int num); // constructor with parameter
  Stack(const Stack &cp); // copy constructor
  Stack& operator=(const Stack &cp); //overloaded assignment operator
  ~Stack(); // destructor
  void push(int val);
  // pushes val to stack
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

#endif // stack_h
