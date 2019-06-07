// Fraction.h - definition of Fraction class

class Fraction
{
  public:

    // Constructor - sets the fraction to 0 / 1
    Fraction();

    // Constructor - sets the numerator and denominator
    Fraction(int n, int d);

    // getNumer - returns the numerator
    int getNumer() const;

    // getDenom - returns the denominator
    int getDenom() const;

    // isSame - returns the true if the fractions have the same numerator and
    // denominator
    bool isSame(const Fraction f) const;

    // display - displays the fraction on the screen
    void display() const;

    // reduce - reduce fraction to lowest terms 
    void reduce();

  private:
    int numer;		// numerator
    int denom;		// denominator
};

