// Fraction.cpp - implementation of fractions functions

#include <iostream>
using namespace std;

#include "Fraction.h"

// Constructor - sets the fraction to 0 / 1
Fraction::Fraction()
{
  numer = 0;
  denom = 1;
}

// Constructor - sets the numerator and denominator
Fraction::Fraction(int n, int d)
{
  numer = n;
  denom = d;
}

// getNumer - returns the numerator
int Fraction::getNumer() const
{
  return numer;
}

// getDenom - returns the denominator
int Fraction::getDenom() const
{
  return denom;
}

// isSame - returns the true if the fractions have the same numerator and
// denominator
bool Fraction::isSame(const Fraction f) const
{
  return ((numer == f.numer) && (denom == f.denom));
}

// display - displays the fraction on the screen
void Fraction::display() const
{
  cout << numer << "/" << denom << endl;
}

// reduceFraction - reduce fraction to lowest terms 
void Fraction::reduce()
{
  if (numer == 0) {
    denom = 1;
    return;
  }

  for (int i = numer; i > 1; i--) {
    if ((denom % i == 0) && (numer % i == 0)) {
      denom = denom / i;
      numer = numer / i;
    }
  }
}
