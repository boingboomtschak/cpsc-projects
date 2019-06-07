// Devon McKee
// lab5.cpp

#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
  int data;
  Node* next;
};

const string FILENAME = "/home/fac/sreeder/class/cs1430/lab5.dat";

void insertInOrder(Node*& h, int d);
// inserts d into h in numerical order
// post: h may be changed

void printList(Node* h);
// prints all data on h to the screen in a column

void delList(Node*& h);
// post: each node of h deleted

int main()
{
  Node* head = nullptr;
  ifstream inFile;
  int num;
  cout << "Welcome to Lab #5 (Linking it up)\n";
  cout << "        By Devon McKee\n";
  cout << "\n";
  inFile.open(FILENAME);
  if (inFile.fail()){
	cout << "File problem...exiting program...press ENTER...";
	cin.get();
  }

  while (inFile >> num)
	insertInOrder(head, num);

  inFile.close();

  cout << endl;
  printList(head);

  cout << endl << endl;
  
  delList(head);
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  return 0;
}

void insertInOrder(Node*& h, int d)
{
  // complete this function
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
    while(walk->next != nullptr && walk->next->data <= d){
      walk = walk->next; 
    }
    temp->next = walk->next;
    walk->next = temp;
  }
}

void printList(Node* h)
{
  // complete this function
  Node* walk = h;
  while(walk != nullptr){
    cout << walk->data << "\n";
    walk = walk->next;
  }
}

void delList(Node*& h)
{
  // complete this function
  Node* walk;
  while(h != nullptr){
    walk = h;
    h = h->next;
    delete walk;
  }
}
