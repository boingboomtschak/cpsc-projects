// Devon McKee
// p6.cpp
// Uniform interfaces, STL, and iterators
// Purpose: Demonstrates usage of STL, iterators, algorithms, and uniform
//          interfaces.
//
// Input: Only input needed from user is to hit enter. Program will go through
//        necessary steps and then close when complete.
//
// Output: Program prints out beginning array, highlighting values to be
//         removed at each step with [ ]. Program reports when no more numbers
//         can be removed, and ends program.
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

const int RAND_INT_MIN = 0;
const int RAND_INT_MAX = 999;
const int NUM_INTS = 1000;
const int LINE_ELEMENTS = 15;
const int ELEMENT_SPACE = 3;

bool isPrime(int n);
// returns true if given int is prime, false otherwise

bool isMultipleFive(int n);
// returns true if int is multiple of 5
// (unary predicate for erase-remove idiom)

bool isEven(int n);
// returns true if n is even

bool primeMixedParity(vector<int> v);
// returns true if there are still prime numbers between numbers of mixed
// parity in the vector

bool primeMixedParity(vector<int> v, vector<int>::iterator it);
// returns true if number pointed to by iterator is prime and between
// numbers of mixed parity

int main()
{
  srand(time(0));
  vector<int> v;
  int pos;
  cout << "\033c";
  cout << "//*//*//*//*//*//*//\n";
  cout << "// Welcome to P6  //\n";
  cout << "// (STL)          //\n";
  cout << "// By Devon McKee //\n";
  cout << "//*//*//*//*//*//*//\n";
  cout << "\n";
  cout << "Press ENTER to continue...";
  cin.ignore();
  cout << "\033c";
  cout << "Printing vector with random int elements: \n";
  cout << "(Highlighting elements to be removed next pass)\n";
  for(int i = 0; i < NUM_INTS; i++){
    v.push_back((rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN);
    if(isMultipleFive(v.at(i))){
      cout << "[" << setw(ELEMENT_SPACE) << v.at(i) << "]";
    }else{
      cout << " " << setw(ELEMENT_SPACE) << v.at(i) << " ";
    }
    if(((i+1) % LINE_ELEMENTS) == 0 && i > 0){
      cout << "\n";
    }
  }
  cout << "\n";
  cout << "Press ENTER to continue...";
  cin.ignore();
  cout << "\033c";
  cout << "Removing multiples of five...\n";
  v.erase(remove_if(v.begin(), v.end(), isMultipleFive), v.end());
  cout << "Printing vector: \n";
  cout << "(Highlighting numbers to be removed next)\n";
  for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
    if(primeMixedParity(v, it)){
      cout << "[" << setw(ELEMENT_SPACE) << *it << "]";
    }else{
      cout << " " << setw(ELEMENT_SPACE) << *it << " ";
    }
    pos = distance(v.begin(), it);
    if(((pos+1) % LINE_ELEMENTS) == 0 && pos > 0){
      cout << "\n";
    }
  }
  cout << "\n";
  cout << "Next, repeatedly removing prime numbers of mixed parity\n";
  cout << "Press ENTER to continue...";
  cin.ignore();
  while(primeMixedParity(v)){
    cout << "\033c";
    cout << "Removing prime numbers between numbers of mixed parity...\n";
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
      if(primeMixedParity(v, it)){
        v.erase(it);
      }
    }
    cout << "Printing vector without selected numbers: \n";
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
      if(primeMixedParity(v, it)){
        cout << "[" << setw(ELEMENT_SPACE) << *it << "]";
      }else{
        cout << " " << setw(ELEMENT_SPACE) << *it << " ";
      }
      pos = distance(v.begin(), it);
      if(((pos+1) % LINE_ELEMENTS) == 0 && pos > 0){
        cout << "\n";
      }
    }
    cout << "\n";
    if(!primeMixedParity(v)){
      cout << "No more prime numbers between numbers of mixed parity!\n";
    }
    cout << "Press ENTER to continue...";
    cin.ignore();
  }
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  return 0;
}

bool isPrime(int n)
{
  if(n == 0 || n == 1){
    return false;  
  }else{
    for(int i=2; i<n; i++){
      if(n % i == 0){
        return false;
      }
    }
  }
  return true;
}

bool isMultipleFive(int n)
{
  if((n % 5) == 0){
    return true;
  }else{
    return false;
  }
}

bool isEven(int n)
{
  if(n % 2 == 0){
    return true;
  }else{
    return false;
  }
}

bool primeMixedParity(vector<int> v)
{
  bool ret = false;
  for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
    if(primeMixedParity(v, it)){
      ret = true;
    }
  }
  return ret;
}

bool primeMixedParity(vector<int> v, vector<int>::iterator it)
{
  if(it != v.begin() || it != v.end()){
    if(isPrime(*it)){
      if((isEven(*(prev(it, 1))) && !isEven(*(next(it, 1)))) ||
         (!isEven(*(prev(it, 1))) && isEven(*(next(it, 1))))){
        return true;
      }else{
        return false;
      }
    }else{
      return false;
    }
  }else{
    return false;
  }
}
