// Devon McKee
// p4.cpp
// Heaps (Priority Queues) and dynamic memory
// Purpose: Tests programmer's understanding of heaps (implemented in a similar
//          way as priority queues) and performing functions on those heaps
//          including insert, removeMinValue, and flush.
//
// Input: User should only need to hit enter, and driver program should handle
//        testing of class.
//
// Output: Program should give verbose output as to what is happening in each
//         step.
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "heap.h"

using namespace std;

const int RAND_INT_MIN = 0;
const int RAND_INT_MAX = 30;
const int NUM_INTS = 15;

void testHeap();

int main()
{
  srand(time(0));
  cout << "\033c";
  cout << "╔════════════════╗\n";
  cout << "║ Welcome to p4  ║\n";
  cout << "║ By Devon McKee ║\n";
  cout << "╚════════════════╝\n";
  cout << "\n\n";
  cout << "Press ENTER to test Heap functions..";
  cin.ignore();
  cout << "Testing Heap functions..\n";
  testHeap();
  cout << "Heap function testing complete!\n";
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  cout << "\n\n\n\n\n";
  return 0;
}

void testHeap()
{
  int rArr[NUM_INTS];
  int num;
  cout << "Populating testing array..\n";
  cout << "Testing array: ";
  for(int i=0; i<NUM_INTS; i++){
    rArr[i] = (rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN;
    cout << rArr[i] << " ";
  }
  cout << "\n";
  cout << "Testing constructor by creating heap h.. \n";
  Heap h;
  cout << "Inserting items from testing array to h..\n";
  for(int i=0; i<NUM_INTS; i++){
    cout << "Inserting " << rArr[i] << "...\n";
    h.insert(rArr[i]);
  }
  cout << "Testing copy constructor on new heap j..\n";
  Heap j(h);
  cout << "Testing removeMin() and empty() to remove and print j..\n";
  cout << "j: ";
  while(!j.empty()){
    num = j.removeMin();
    cout << num << " ";
  }
  cout << "\n";
  cout << "Testing overloaded assignment operator on new heap k..\n";
  Heap k = h;
  cout << "Emptying and printing k..\n";
  cout << "k: ";
  while(!k.empty()){
    num = k.removeMin();
    cout << num << " ";
  }
  cout << "\n";
  cout << "Testing flush(int) on h with first int in testing array..\n";
  cout << "Flushing " << rArr[0] << "\n";
  h.flush(rArr[0]);
  cout << "Emptying and printing h..\n";
  cout << "h: ";
  while(!h.empty()){
    num = h.removeMin();
    cout << num << " ";
  }
  cout << "\n";
  cout << "Attempting to catch the EmptyHeap exception..\n";
  try {
    h.removeMin();
  } catch (Heap::EmptyHeap) {
    cout << "Exception caught!\n";
  }
  cout << "\n";
}
