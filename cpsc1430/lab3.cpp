// Devon McKee
// lab3.cpp (Pointer Play)

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
  srand(time(0)); // Seeding rand()
  int num;
  int* numptr;
  int arrSize;
  cout << "Welcome to lab #3 (Pointer Play)\n";
  cout << "By Devon McKee\n";
  cout << "\n";
  // Step #1
  cout << "Please enter a number..";
  cin >> num;
  cin.ignore();
  // Step #2
  numptr = &num;
  // Step #3
  cout << "Regular Value: " << num  << "\n";
  cout << "Regular Address: " << &num  << "\n";
  cout << "Pointer Value: " << *numptr  << "\n";
  cout << "Pointer Address: " << numptr  << "\n";
  cout << "\n";
  // Step #4
  numptr = new int;
  // Step #5
  *numptr = 17;
  // Step #6
  cout << "Regular Value: " << num << "\n";
  cout << "Regular Address: " << &num << "\n";
  cout << "Pointer Value: " << *numptr << "\n";
  cout << "Pointer Address: " << numptr << "\n";
  // Step #7
  delete numptr;
  // Step #8
  cout << "Please enter a (small) number.. ";
  cin >> arrSize;
  cin.ignore();
  numptr = new int[arrSize];
  // Step #9
  for(int i=0; i<arrSize; i++){
    numptr[i] = rand() % 10; 
  }
  // Step #10
  cout << "Pointer Array: \n";
  for(int i=0; i<arrSize; i++){
    cout << numptr[i] << ", ";
  }
  cout << "\n";
  // Step #11
  delete[] numptr;
  //
  cout << "\n";
  cout << "Thanks for using my program!\n";
  cout << "Press ENTER to exit..";
  cin.ignore();
  return 0;
}
