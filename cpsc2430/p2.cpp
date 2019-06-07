// Devon McKee
// p2.cpp
// Linked lists, dynamic memory, and pointers
// Purpose: Tests programmers understanding of linked lists, dynamic memory
//          and pointers. Program should create an ordered linked list to
//          store integer values, create functions to print the values on said
//          list, insert an element into that list, and delete a specific
//          element from the list. After that, the driver for the program
//          should follow steps 3)a-f as described in the p2 assignment file
//          in order to test the aforementioned functions. 
//
// Input: All that is needed from the user is to hit enter and the program
//        should perform all the functions necessary.
//
// Output: Program should give verbose output as to what is happening in each
//         step.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

struct Node
{
  int data;
  Node* next;
};

const string OUTPUT_A = "OutputA.txt";
const string OUTPUT_B = "OutputB.txt";
const int LIST_ITEMS = 60;
const int RAND_INT_MIN = 1;
const int RAND_INT_MAX = 100;

void printList(Node* h, ostream& outs);
// Prints list to output stream given

void insertInOrder(Node*& h, int value);
// Inserts given integer into list in order

void deleteItem(Node*& h, int target);
// Searches linked list for node with target integer, and then removes it
// cleanly

void delList(Node*& h);
// deletes dynamic memory for list at end of program

int main()
{
  ofstream outfile;
  Node* head = nullptr;
  Node* walk;
  int randInt;
  int smallest;
  int largest;
  int middle;
  // seeding rand()
  srand(time(0));
  cout << "\033c";
  cout << "------------------------\n";
  cout << "    P2 - Linked List    \n";
  cout << "     By Devon McKee     \n";  
  cout << "------------------------\n";
  cout << "\n";
  cout << "Press ENTER to begin the program..";
  cin.ignore();
  cout << "Constructing linked list...\n";
  for(int i=1; i<LIST_ITEMS; i++){
    randInt = (rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN;
    insertInOrder(head, randInt);
  }
  cout << "Linked list constructed as 'list'\n";
  cout << "Opening " << OUTPUT_A << " for program output..\n";
  outfile.open(OUTPUT_A.c_str());
  if(outfile.fail()){
    cout << "File problem, exiting program..\n";
    cout << "Press ENTER to exit..";
    cin.ignore();
    return 0;
  }
  cout << "Printing list to " << OUTPUT_A << "...\n";
  printList(head, outfile);
  cout << "List outputted to " << OUTPUT_A << ".\n";
  outfile.close();
  smallest = head->data;
  walk = head;
  while(walk != nullptr){
    largest = walk->data;
    walk = walk->next;
  }
  walk = head;
  for(int i=0;i<LIST_ITEMS/2; i++){
    walk = walk->next;
  }
  middle = walk->data;
  cout << "Deleting smallest element of linked list..\n";
  deleteItem(head, smallest);
  cout << "Deleting largest element of linked list..\n";
  deleteItem(head, largest);
  cout << "Deleting middle value of linked list..\n";
  deleteItem(head, middle);
  cout << "Opening " << OUTPUT_B << " for program output..\n";
  outfile.open(OUTPUT_B.c_str());
  if(outfile.fail()){
    cout << "File problem, exiting program..\n";
    cout << "Press ENTER to exit..";
    cin.ignore();
    return 0;
  }
  cout << "Printing list to " << OUTPUT_B << "...\n";
  printList(head, outfile);
  cout << "List outputted to " << OUTPUT_B << ".\n";
  outfile.close();
  cout << "Tasks complete!\n";
  delList(head);
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  
  cout << "\n\n\n";
  return 0;
}

void printList(Node* h, ostream& outs)
{
  Node* walk = h;
  int itemNum = 0;
  outs << "Index | Value\n";
  while(walk != nullptr){
    outs << setw(5) << itemNum << " | " << setw(5) << walk->data << "\n";
    itemNum++;
    walk = walk->next;
  }
}

void insertInOrder(Node*& h, int value)
{
  Node* temp = new Node;
  temp->data = value;
  temp->next = nullptr;
  Node* walk;
  if(h == nullptr){
    h = temp;
  }else if(h->data >= temp->data){
    temp->next = h;
    h = temp;
  }else{
    walk = h;
    while(walk->next != nullptr && walk->next->data < value){
      walk = walk->next;
    }
    temp->next = walk->next;
    walk->next = temp;
  }
}

void deleteItem(Node*& h, int target)
{
  Node* walk;
  Node* delptr;
  walk = h;
  if(h->data == target){
    // item to delete is at head
    delptr = h;
    h = h->next;
    delete delptr;
  }else{
    while(walk->next != nullptr && walk->next->data != target){
      walk = walk->next;
    }
    if(walk->next != nullptr){
      // item found, otherwise function just ends
      delptr = walk->next;
      walk->next = walk->next->next;
      delete delptr;
    }
  }
}

void delList(Node*& h)
{
  Node* delptr;
  while(h != nullptr){
    delptr = h;
    h = h->next;
    delete delptr;
  }
}
