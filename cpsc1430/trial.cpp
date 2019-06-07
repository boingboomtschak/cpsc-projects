// trial.cpp
// Debugging exercise

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void printNames(const string list[], int count);

void selectSort(string list[], int numNames);

void swapVals(string& val1, string& val2);

const int MAX = 50;

int main()
{
  ifstream inFile;
  string nameList[MAX];
  int count = 0;
  inFile.open("test.dat");

  cout << endl << endl << "This program reads in a list of names from the "
	   << "file 'test.dat' and " << endl
	   << "inserts them into an array, then sorts them." << endl << endl;

  if (inFile.fail()){
	cout << "Sorry, can't open file 'test.dat'. "
		 << "Press enter to exit program...";
	cin.get();
	return 0;
  }

  while (count < MAX && getline(inFile, nameList[count]))
	count++;

  cout << "Original List: " << endl;
  printNames(nameList, count);
  cout << "press enter to continue...";
  cin.get();

  cout << endl << endl;

  selectSort(nameList, count);

  cout << "Sorted List: " << endl;
  printNames(nameList, count);
  
  return 0;
}

void printNames(const string list[], int count)
{
  for (int i = 0; i < count; i++)
	cout << list[i] << endl;
}

void selectSort(string list[], int numNames)
{
  int index;

  for (int i = 0; i < numNames - 1; i++){
	index = i;
	for (int j = i + 1; j < numNames; j++)
	  if (list[j] < list[index])
		swapVals(list[index], list[i]);
  }
}

void swapVals(string& val1, string& val2)
{
  string temp = val1;
  val1 = val2;
  val2 = temp;
}
  
