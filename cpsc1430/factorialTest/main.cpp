// Driver for factorial function

#include <iostream>
using namespace std;

#include "factorial.h"

int main()
{
  int n;
  cout << "Enter a number: ";
  cin >> n;

  cout << "The value of " << n << "! is " << factorial(n) << endl;

  return 0;
}
