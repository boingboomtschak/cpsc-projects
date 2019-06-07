// Devon McKee
// Lab #6 (No Duplicates!)
// 2019-02-15

#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
  int data;
  Node* next;
};

const string FILENAME = "/home/fac/sreeder/class/cs1430/lab6.dat";

void insertInOrder(Node*& h, int d);
// inserts d into h in numerical order
// post: h may be changed

void printList(Node* h);
// prints all data on h to the screen

void delList(Node*& h);
// post: each node of h deleted

void delDuplicate(Node*& h);
// deletes all duplicates in h

int main()
{
  Node* head = nullptr;
  ifstream infile;
  int num;
  cout << "Welcome to Lab #6 (No Duplicates)\n";
  cout << "           By Devon McKee        \n";
  cout << "\n";
  infile.open(FILENAME);
  if(infile.fail()){
    cout << "File problem.. exiting program.. press ENTER..";
    cin.ignore();
    return 0;
  }
  while(infile >> num){
    insertInOrder(head, num);
  }
  infile.close();
  delDuplicate(head);
  printList(head);
  delList(head);
  cout << "\n";
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  return 0;
}

void insertInOrder(Node*& h, int d)
{
  Node* temp = new Node;
  temp->data = d;
  Node* walk;
  if(h == nullptr){
    h = temp;
  }else if(h->data >= temp->data){
    temp->next = h;
    h = temp;
  }else{
    walk = h;
    while(walk->next != nullptr && walk->next->data < d){
      walk = walk->next;
    }
    temp->next = walk->next;
    walk->next = temp;
  }
}

void printList(Node* h)
{
  Node* walk = h;
  while(walk != nullptr){
    cout << walk->data << "\n";
    walk = walk->next;
  }
}

void delList(Node*& h)
{
  Node* walk;
  while(h != nullptr){
    walk = h;
    h = h->next;
    delete walk;
  }
}

void delDuplicate(Node*& h)
{
  Node* walk = h;
  Node* delptr;
  while(walk != nullptr){
    while(walk-> next != nullptr && walk->data == walk->next->data){
      delptr = walk->next;
      walk->next = walk->next->next;
      delete delptr;
    }
    walk = walk->next;
  }
}
