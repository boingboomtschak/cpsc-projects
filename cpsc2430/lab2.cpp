// Devon McKee
// lab2.cpp
// 2019-04-17
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
  int data;
  Node* next;
};

const int RAND_INT_MIN = -100;
const int RAND_INT_MAX = 100;

int recurLastNeg(Node* head);
// returns last negative number in unordered linked list, recursively

void insertUnorder(Node*& head, int data);
// inserts integer "data" in unordered linked list, at head

void printList(Node* head);
// prints linked list to screen with set-width columns

void deleteList(Node*& head);
// deletes linked list at end of program

int main()
{
  Node* head = nullptr;
  int nodes, randInt, lastNeg;
  srand(time(0));
  cout << "-------------------\n";
  cout << " Welcome to Lab #2 \n";
  cout << "   By Devon McKee  \n";
  cout << "-------------------\n";
  cout << "\n";
  cout << "How many nodes would you like in the linked list? ";
  cin >> nodes;
  cin.ignore();
  for(int i=0; i<nodes; i++){
    randInt = (rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN;
    insertUnorder(head, randInt);
  }
  cout << "Linked list complete.\n";
  printList(head);
  cout << "Finding last negative..\n";
  lastNeg = recurLastNeg(head);
  cout << "Last negative value found is " << lastNeg << ".\n";
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  deleteList(head);
  cout << "Exiting program..\n\n\n\n";
  return 0;
}

int recurLastNeg(Node* head)
{
  int last;
  if(head->next == nullptr){
    return head->data;
  }else{
    last = recurLastNeg(head->next);
    if(last < 0){
      return last;
    }else{
      return head->data;
    }
  }
}

void insertUnorder(Node*& head, int data)
{
  Node* temp = new Node;
  temp->data = data;
  if(head == nullptr){
    temp->next = nullptr;
    head = temp;
  }else{
    temp->next = head;
    head = temp;
  }
}

void printList(Node* head)
{
  Node* walk = head;
  int itemNum = 0;
  cout << "Index | Value\n";
  while(walk != nullptr){
    cout << setw(5) << itemNum << " | " << setw(5) << walk->data << "\n";
    itemNum++;
    walk = walk->next;
  }
}

void deleteList(Node*& head)
{
  Node* delptr;
  while(head != nullptr){
    delptr = head;
    head = head->next;
    delete delptr;
  }
}
