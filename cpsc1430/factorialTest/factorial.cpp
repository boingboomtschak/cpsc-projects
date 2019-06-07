// factorial.cpp - Computes n!

// Returns the n!.  For example 4! = 4 x 3 x 2 x 1 = 24
int factorial(int n)
{
  if (n <= 1) return 1;

  int product = 1;

  for (int i = 2; i <= n; i++) {
    product = product * i;
  }

  return product;
}
