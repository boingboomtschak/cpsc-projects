// Devon McKee
// Lab #13 (Coffee Counts)
// 2018-11-28

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
  
int main()
{
  ifstream infile;
  Person people[ARRAY_SIZE];
  int peopleCount = 0;
  string nameShelf;
  int ageShelf;
  int coffeeShelf;
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
