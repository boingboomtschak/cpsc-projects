// Devon McKee
// p3.cpp
// Binary Search Trees and recursion
// Purpose: Tests programmer's understanding of binary search trees (BSTs)
//          as well as recursion by way of recursive (and iterative) traversal
//          of aforementioned BST.
//
// Input: User should only need to hit enter, and driver program should handle
//        testing of class.
//
// Output: Program should give verbose output as to what is happening in each
//         step.
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "tree.h"

using namespace std;

const int RAND_INT_MIN = 0;
const int RAND_INT_MAX = 50;
const int NUM_NODES = 20;

void testTree();

int main()
{
  srand(time(0));
  cout << "\033c";
  cout << "-=-=-=-=-=-=-=-\n";
  cout << " Welcome to P3 \n";
  cout << " By Devon McKee\n";
  cout << "-=-=-=-=-=-=-=-\n";
  cout << "\n\n";
  cout << "Press ENTER to test BST functions..";
  cin.ignore();
  cout << "Testing BST functions..\n";
  testTree();
  cout << "BST function testing complete!\n";
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  cout << "\n\n\n\n\n";
  return 0;
}

void testTree()
{
  int rInt;
  cout << "Testing constructor by creating tree t.. \n";
  Tree t;
  cout << "Inserting 20 random values into tree (ignoring duplicates)..\n";
  for(int i=0;i<NUM_NODES;i++){
    rInt = (rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN;
    cout << "Inserting " << rInt << "\n";
    if(!t.insertKey(rInt)){
      cout << "Insertion failed! Duplicate key!\n";
      i--;
    }
  }
  cout << "Testing traversals (preorder and inorder)..\n";
  t.preOrder();
  t.inOrder();
  cout << "Testing findKey by searching for last inserted value ("
       << rInt << ")\n";
  if(t.findKey(rInt)){
    cout << "Key found!\n";
  }else{
    cout << "Key not found in tree..\n";
  }
  cout << "Testing findMinKey()..\n";
  cout << "Minimum key is: " << t.findMinKey() << "\n";
  cout << "Testing findHeight()..\n";
  cout << "Height of tree is: " << t.findHeight() << "\n";
  cout << "Testing copy constructor on new tree u..\n";
  Tree u(t);
  cout << "Traversals of u:\n";
  u.preOrder();
  u.inOrder();
  cout << "Testing overloaded assignment operator on new tree v..\n";
  Tree v = t;
  cout << "Traversals of v:\n";
  v.preOrder();
  v.inOrder();
}
