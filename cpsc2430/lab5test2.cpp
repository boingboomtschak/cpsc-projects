// Devon McKee
// Lab #5 (MergeSort)
// 2019-06-05
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string INPUTFILE = "/home/fac/sreeder/class/cs2430/countyPop.dat";
const int NUM_ENTRIES = 3200;

struct County {
  int population;
  string place;
};

void arrMerge(County arr[], int s, int m, int e);

void mergeSort(County arr[], int s, int e);
// args: array, start, end
  
int main()
{
  ifstream infile;
  County arr[NUM_ENTRIES];
  int count = 0;
  cout << "--------------------\n";
  cout << "- Welcome to Lab 5 -\n";
  cout << "- MergeSort        -\n";
  cout << "- By Devon McKee   -\n";
  cout << "--------------------\n";
  cout << "\n";
  cout << "Opening " << INPUTFILE << "...\n";
  infile.open(INPUTFILE);
  if(infile.fail()){
    cout << "File error! Exiting program...\n";
    cout << "Press ENTER to exit...";
    cin.ignore(0);
    return 0;
  }
  cout << "Reading file...\n";
  while(infile >> arr[count].population){
    getline(infile, arr[count].place);
    count++;
  }
  infile.close();
  cout << "File reading complete!\n";
  cout << "First 10 elements of list: \n";
  for(int i=0; i<10; i++){
    cout << arr[i].population << " " << arr[i].place << "\n";
  }
  cout << "\n";
  cout << "Last 10 elements of list: \n";
  for(int i=(count-10); i<count; i++){
    cout << arr[i].population << " " << arr[i].place << "\n";
  }
  cout << "\n";
  // sort array here
  cout << "Starting to sort array...\n";
  mergeSort(arr, 0, count);
  cout << "Array sorted!\n";
  cout << "First 10 elements of sorted list: \n";
  for(int i=0; i<10; i++){
    cout << arr[i].population << " " << arr[i].place << "\n";
  }
  cout << "\n";
  cout << "Last 10 elements of sorted list: \n";
  for(int i=(count-10); i<count; i++){
    cout << arr[i].population << " " << arr[i].place << "\n";
  }
  // debug
  for(int i=0; i<count; i++){
    cout << setw(8) << arr[i].population << " ";
    if((i-1)%8 == 0 && i > 0){
      cout << "\n";
    }
  }
  // debug
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  cout << "Press ENTER to exit...";
  cin.ignore();
  return 0;
}

void arrMerge(County arr[], int s, int m, int e)
{
  County *al, *ar;
  int l, r, c;
  int als = m - s + 1;
  int ars = e - m;
  al = new County[als];
  ar = new County[ars];
  for(int i=0; i<als; i++){
    al[i] = arr[s + i];
  }
  for(int i=0; i<ars; i++){
    ar[i] = arr[m + 1 + i];
  }
  l = 0;
  r = 0;
  c = 0;
  while(l < als && r < ars){
    if(arr[l].population < arr[r].population){
      arr[c] = al[l];
      l++;
    }else{
      arr[c] = ar[r];
      r++;
    }
    c++;
  }
  while(l < als){
    arr[c] = al[l]; 
    l++;
    c++;
  }
  while(r < ars){
    arr[c] = ar[r];
    r++;
    c++;
  }
  delete[] al;
  delete[] ar;
}

void mergeSort(County arr[], int s, int e)
{
  if(s < e){
    int m = (s+e-1)/2;
    mergeSort(arr, s, m);
    mergeSort(arr, m+1, e);
    arrMerge(arr, s, m, e);
  }
}

