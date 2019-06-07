// Devon McKee
// p5.cpp
// Hash functions, Hash tables, and Collision resolution
// Purpose: P5 uses a hash table, custom hash function, and collision
//          resolution techniques to read and process words from "Ulysses"
//          before hashing them and placing them in a hash table to be used
//          for other purposes. 
//
// Input: User just has to hit enter to advance through menus, and then put a
//        word in to be searched for. User enters 'y' or 'n' to determine
//        whether they want to repeat the program.
//
// Output: Program outputs pertinent info to hash table, hash function
//         effectiveness, and collision resolution strategy effectiveness.
//         Program also asks user if they want to repeat, and asks user to
//         advance the program when needed.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <cmath>

using namespace std;

const int TABLE_SIZE = 49207;
const string FILENAME = "ulyss12.txt";
const char YES = 'y';

struct HNode {
  string str; // word
  int num; // # appearances of word
  HNode* next; // link to next word (in case of collision)
};

string preprocess(string str);

int hashfn(string str);

int checkOccur(HNode* table[], string str);

int main()
{
  ifstream infile;
  double loadFac, avgCollision;
  int collision, unique, words, empty;
  HNode* table[TABLE_SIZE];
  char cont = YES;
  // "temp" vars
  unsigned int strHash;
  int occur, hashIndex, sumCollision;
  string word, search;
  HNode* walk;
  HNode* delptr;
  cout << "+----------------+\n";
  cout << "| Welcome to P5  |\n"; 
  cout << "| By Devon McKee |\n";
  cout << "+----------------+\n";
  cout << "\n";
  cout << "Press ENTER to begin hashing \"Ulysses\"...";
  cin.ignore();
  for(int i=0; i<TABLE_SIZE; i++){
    table[i] = nullptr;
  }
  collision = 0;
  unique = 0;
  words = 0;
  sumCollision = 0;
  empty = 0;
  cout << "Opening file..\n";
  infile.open(FILENAME);
  if(infile.fail()){
    cout << "File error! Exiting program..\n";
    cout << "Press ENTER to exit..";
    cin.ignore();
    return 0;
  }
  cout << "Processing and hashing words in file..\n";
  while(infile >> word){
    words++;
    word = preprocess(word);
    if(word != ""){
      strHash = hashfn(word); 
      hashIndex = strHash % TABLE_SIZE;
      if(table[hashIndex] == nullptr){
        // string does not exist in table yet
        unique++;
        table[hashIndex] = new HNode;
        table[hashIndex]->str = word;
        table[hashIndex]->num = 1;
        table[hashIndex]->next = nullptr;
      }else if(table[hashIndex]->str == word){
        // string exists in table already
        table[hashIndex]->num++;
      }else{
        // collision (or existing collision hashed again)
        walk = table[hashIndex];
        while(walk->next != nullptr && walk->str != word){
          walk = walk->next;
        }
        if(walk->str == word){
          walk->num++;
        }else{
          collision++;
          unique++;
          walk->next = new HNode;
          walk->next->str = word;
          walk->next->num = 1;
          walk->next->next = nullptr;
        }
      }
    }
  }
  cout << "File processing complete.\n";
  infile.close();
  loadFac = static_cast<double>(unique) / TABLE_SIZE;
  for(int i=0; i<TABLE_SIZE; i++){
    if(table[i] == nullptr){
      empty++;
    }else{
      if(table[i]->next != nullptr){
        walk = table[i];
        while(walk != nullptr){
          sumCollision++;
          walk = walk->next;
        }
      }else{
        sumCollision++;
      }
    }
  }
  avgCollision = static_cast<double>(sumCollision) / unique;
  cout << "Hashing results: \n";
  cout << "-----------------\n";
  cout << "Words: " << words << "\n";
  cout << "Unique words: " << unique << "\n";
  cout << "# of collisions: " << collision << "\n";
  cout << "Average # of collisions per node: " << avgCollision << "\n";
  cout << "Load factor: " << loadFac << "\n";
  cout << "# of empty spaces in table: " << empty << "\n";
  cout << "-----------------\n\n";
  while(cont == YES){
    cout << "Choose a word to search for its number of occurrences.\n";
    cout << "Word: ";
    cin >> search;
    cin.ignore();
    occur = checkOccur(table, search);
    cout << "This word shows up " << occur << " times.\n";
    cout << "Would you like to search again? (y/n) ";
    cin >> cont;
    cin.ignore();
  }
  // clean up collided nodes
  for(int i=0; i<TABLE_SIZE; i++){
    if(table[i] != nullptr && table[i]->next != nullptr){
      walk = table[i]->next;
      while(walk != nullptr){
        delptr = walk;
        walk = walk->next;
        delete delptr;
      }
    }
  }
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  cout << "Press ENTER to exit...";
  cin.ignore();
  return 0;
}

string preprocess(string str)
{
  if(str.length() < 5){
    return "";
  }else{
    for(int i=0; i<static_cast<int>(str.length()); i++){
      str[i] = tolower(str[i]);
      if(!isalpha(str[i])){
        str.erase(i, 1);
        i--;
      }
    }
  } 
  return str;
}

int hashfn(string str)
{
  // Hash function based off hash function by Daniel J. Bernstein
  unsigned int numHash = 5381;
  unsigned int i = 0;
  unsigned int length = str.length();
  for(i=0; i<length; i++){
    numHash = ((numHash << 5) + numHash) + (str[i]) + (numHash << 24);
  }
  return numHash;
}

int checkOccur(HNode* table[], string str)
{
  int occur;
  str = preprocess(str);
  unsigned int numHash = hashfn(str);
  int index = numHash % TABLE_SIZE;
  if(table[index] == nullptr){
    occur = 0;
  }else if(table[index]->str == str){
    occur = table[index]->num;
  }else{
    HNode* walk = table[index];
    if(walk->next != nullptr){
      while(walk->next != nullptr || walk->str != str){
        walk = walk->next;
      }
      if(walk ->next == nullptr && walk->str != str){
        occur = 0;
      }else{
        occur = walk->num;
      }
    }else{
      occur = 0;
    }
  }
  return occur;
}
