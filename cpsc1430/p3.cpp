// Devon McKee
// p3.cpp
// Secret Messages
// 2019-02-11
// Purpose: Program welcomes user, takes an objective path to a file as input,
//          then places the char/int pairs in the file in a linked list in
//          order from lowest to highest int. Then, the program prints the
//          resulting message by iterating through the linked list and
//          printing the character. The program then deallocates the memory
//          for the linked list, asks the user if they want to repeat, and
//          then ends.
//
// Input:   User must input an objective path to a file containing char/int
//          pairs on each line, separated by a space. Any unexpected input
//          and the program may not work correctly, if at all. User also
//          reports if they want to try again with a different file.
//
// Output:  Program welcomes user, outputs combined characters from list,
//          then repeats (when prompted to), then says goodbye to user.
//

#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
  int num;
  char letter;
  Node* next;
};

// const here
const char YES = 'y';

// funcs here
void insertInOrder(Node*& h, int num, char letter);
// inserts num/letter into h in numerical order by num
// post: h changed

void printList(Node* h);
// prints letters of h together as one line on screen

void delList(Node*& h);
// deletes h and all subsequent nodes

Node*& indexEnd(Node*& h);
// iterates to end of linked list and returns pointer to end

void combineList(Node* h1, Node* h2, Node*& hout);
// combines h1 and h2 into hout, alternating whenever a space is reached.

int main()
{
  string filename;
  ifstream infile;
  Node* head = nullptr;
  char letter;
  char cont = YES;
  int num;
  cout << "\033c";
  cout << "\n";
  cout << "╔▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓╗\n";
  cout << "▓ « Welcome to Secret Messages (p3)» ▓\n";
  cout << "▓         « By Devon McKee »         ▓\n";
  cout << "╚▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓╝\n";
  cout << "\n";
  while(cont == YES){
    cout << "Please enter an objective path to a file: ";
    cin >> filename;
    cin.ignore();
    infile.open(filename);
    if(infile.fail()){
      cout << "File error! Exiting program..\n";
      cout << "Press ENTER to continue..";
      cin.ignore();
    }
    // file processing here
    cout << "\n";
    cout << "Unraveling file...\n";
    while(infile.get(letter)){
      infile >> num;
      infile.ignore();
      insertInOrder(head, num, letter);
    }
    infile.close();
    cout << "Message unraveled!\n\n";
    printList(head);
    cout << "\n";
    delList(head);
    cout << "Would you like to try again? (y/n) ";
    cin >> cont;
    cin.ignore();
  }  
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit..";          
  cin.ignore();
  return 0;
}

void insertInOrder(Node*& h, int num, char letter)
{
  Node* temp = new Node;
  temp->num = num;
  temp->letter = letter;
  Node* walk;
  if(h == nullptr || h->num >= temp->num){
    temp->next = h;
    h = temp;
  }else{
    walk = h;
    while(walk->next != nullptr && walk->next->num <= temp->num){
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
    cout << walk->letter;
    walk = walk->next;
  }
  cout << "\n";
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

Node*& indexEnd(Node*& h)
{
  Node* walk = h;
  while(walk != nullptr){
    walk = walk->next;
  }
  return walk;
}

void combineList(Node* h1, Node* h2, Node*& hout) 
{
  Node* walk1 = h1;
  Node* walk2 = h2;
  Node* end;
  Node* temp;
  while(walk1 != nullptr || walk2 != nullptr){ // iterate over h1 and h2
    while(walk1->letter != ' '){ // iterate over h1 until word is over
      temp = new Node;
      temp = walk;
      end = indexEnd(hout);
      end->next = temp;
      walk1 = walk1->next;
    }
    // walk1 = walk1->next; // may have to iterate forward past space
    while(walk2->letter != ' '){ // iterate over h2 until word is over
      temp = new Node;
      temp = walk;
      walk2 = walk2->next;
    }
    // walk2 = walk2->next; // may have to iterate forward past space
  }
}
