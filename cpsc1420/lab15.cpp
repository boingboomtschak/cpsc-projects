// Devon McKee
// Lab #15 (Binary Search)
// 2018-12-05

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

const string FILENAME = "/home/fac/sreeder/class/cs1420/lab13input.dat";
const int ARRAY_SIZE = 150;

struct Person {
  string name;
  int age;
  int coffee;
};

void printRecord(Person record);
// prints given record to screen

Person findOldest(Person records[], int recordsCount);
// finds oldest record in list of records and returns record

Person findLeastCoffee(Person records[], int recordsCount);
// finds person with least coffee and returns record

void swapPerson(Person& person1, Person& person2);
// swaps values (by reference)

void sortByName(Person records[], int recordsCount);
// sorts given list of records by name

int searchName(string name, Person records[], int recordsCount);
// searches for a person by name and returns their index

int main()
{
  ifstream infile;
  Person people[ARRAY_SIZE];
  int peopleCount = 0;
  string nameShelf;
  int ageShelf;
  int coffeeShelf;
  string targetName;
  int searchIndex;
  // Welcome user
  cout << "\033c";
  cout << "Welcome to Lab #13 (Coffee Counts)\n";
  cout << " --- By Devon McKee --- \n";
  cout << "\n";
  // opening/reading file/checking file validity
  infile.open(FILENAME.c_str());
  if(infile.fail()){
    cout << "File error, exiting program..\n";
    cin.ignore();
    return 0;
  }
  while(peopleCount < ARRAY_SIZE && infile >> nameShelf >> ageShelf
        >> coffeeShelf){
    people[peopleCount].name = nameShelf;
    people[peopleCount].age = ageShelf;
    people[peopleCount].coffee = coffeeShelf;
    peopleCount++;
  }
  // closes file once program is done with it
  infile.close();
  cout << "Task 1:\n";
  printRecord(findOldest(people, peopleCount));
  cout << "\n";
  cout << "Task 2:\n";
  printRecord(findLeastCoffee(people, peopleCount));
  cout << "\n";
  cout << "Task 3:\n";
  for(int i=0; i<peopleCount; i++){
    printRecord(people[i]);
    cout << "\n";
  }
  cout << "\n";
  cout << "Task 4:\n";
  sortByName(people, peopleCount);
  cout << "Sorted people by name.\n";
  cout << "\n";
  cout << "Task 5:\n";
  for(int i=0; i<peopleCount; i++){
    printRecord(people[i]);
    cout << "\n";
  }
  cout << "Task 6:\n";
  cout << "Enter a name to search for: ";
  cin >> targetName;
  cin.ignore();
  searchIndex = searchName(targetName, people, peopleCount);
  if(searchIndex == -1){
    cout << "Person with name " << targetName << " was not found!\n";
  }else{
    cout << "Person with name " << targetName << " was found at index "
         << searchIndex << "!\n";
    cout << "Printing their record.. \n";
    printRecord(people[searchIndex]);
  }
  cout << "\n";
  cout << "Thanks for using my program! Goodbye!\n";
  cout << "Press ENTER to exit... \n";
  cin.ignore();
  return 0;
}

void printRecord(Person record)
{
  cout << "Name: " << record.name << "\n";
  cout << "Age: " << record.age << "\n";
  cout << "Coffee: " << record.coffee << "\n";
}

Person findOldest(Person records[], int recordsCount)
{
  int oldest = 0;
  for(int i=0; i<recordsCount; i++){
    if(records[i].age > records[oldest].age){
      oldest = i;
    }
  }
  return records[oldest];
}

Person findLeastCoffee(Person records[], int recordsCount)
{
  int leastCoffee = 0;
  for(int i=0; i<recordsCount; i++){
    if(records[i].coffee < records[leastCoffee].coffee){
      leastCoffee = i;
    }
  }
  return records[leastCoffee];
}

void swapPerson(Person& person1, Person& person2)
{
  Person shelf = person1;
  person1 = person2;
  person2 = shelf;
}

int findMinName(Person records[], int index1, int index2)
{
  int minIndex = index1;
  for(int i=index1+1;i<index2;i++){
    if(records[i].name < records[minIndex].name){
      minIndex = i;
    }
  }
  return minIndex;
}

void sortByName(Person records[], int recordsCount)
{
  int sortMin;
  int sortMax = recordsCount;
  int minimum;
  for(int i=0; i<recordsCount;i++){
    sortMin = i;
    minimum = findMinName(records, sortMin, sortMax);
    swapPerson(records[sortMin], records[minimum]);
  }
}

int searchName(string name, Person records[], int recordsCount)
{
  int index = -1; // returns -1 if name not found
  int searchMin = 0;
  int searchMax = recordsCount;
  int middle = searchMax - (searchMax - searchMin)/2;
  while(index == -1 && searchMin != searchMax){
    if(records[middle].name == name){
      index = middle;
    } else if(records[middle].name < name) {
      searchMin = middle;
      middle = searchMax - (searchMax - searchMin) / 2;
    } else if(middle == searchMax){
      index = searchMin;
    }else { 
      searchMax = middle;
      middle = searchMax - (searchMax - searchMin) / 2;
    }
  }
  return index;
}
