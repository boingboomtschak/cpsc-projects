// Devon McKee
// stack.cpp
// Implementation of odd int Stack as described in stack.h

#include "stack.h"

using namespace std;

Stack::Stack()
{
  size = 3;
  stack = new int[size];
  top = 0;
}

Stack::Stack(int num)
{
  size = num;
  stack = new int[size];
  top = 0;
}

Stack::Stack(const Stack &cp)
{
  top = cp.top;
  size = cp.size;
  stack = new int[size];
  for(int i=0; i<top; i++){
    stack[i] = cp.stack[i];
  }
}

Stack& Stack::operator=(const Stack &cp)
{
  if(this != &cp){
    top = cp.top;
    size = cp.size;
    stack = new int[size];
    for(int i=0; i<top; i++){
      stack[i] = cp.stack[i];
    }
  }
  return *this;
}

Stack::~Stack()
{
  delete[] stack;
}

void Stack::push(int val)
{
  if((val % 2) == 0){
    throw EvenInteger();
  }else{
    if(top == size){
      resize();
    }
    stack[top] = val;
    top++;
  }
}

int Stack::pop()
{
  if(top == 0){
    throw EmptyStack();
  }else{
    top--;
    return stack[top];
  }
}

bool Stack::isEmpty()
{
  return (top == 0);
}

void Stack::resize()
{
  int newSize = size * 1.5;
  int* newStack = new int[newSize];
  for(int i=0; i<top; i++){
    newStack[i] = stack[i];
  }
  delete[] stack;
  size = newSize;
  stack = newStack;
}
