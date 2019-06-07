// triangle.cpp - Determines the type of triangle based on the three sides.

// Returns the triangle type based on the length of the three sides:
// 'e' : Equilateral triangle
// 'i' : Isosceles triangle
// 's' : Scalene triangle
// 'n' : Not a triangle
char triangleType(int side1, int side2, int side3)
{
  // Check for invalid triangle
  if (side1 + side2 <= side3 || side2 + side3 <= side1
      || side1 + side3 <= side2) {
    return 'n';
  }

  // Check for equilateral triangle
  if ((side1 == side2) && (side2 == side3)) {
    return 'e';
  }

  // Check for isosceles triangle
  if ((side1 == side2) || (side2 == side3) || (side1 == side3)) {
    return 'i';
  }

  // At this point, the triangle must be scalene
  return 's';
}

