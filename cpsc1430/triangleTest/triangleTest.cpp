// triangleTest.cpp - Tests Triangles

#include <gtest/gtest.h>
#include "triangle.h"

TEST(TriangleTest, Invalid) {
  EXPECT_EQ('n', triangleType(1, 2, 4));
  EXPECT_EQ('n', triangleType(8, 2, 6));
  EXPECT_EQ('n', triangleType(8, 20, 4));
  EXPECT_EQ('n', triangleType(0, 0, 0));
  EXPECT_EQ('n', triangleType(-1, 1, -1));
}

TEST(TriangleTest, Equilateral) {
  EXPECT_EQ('e', triangleType(1, 1, 1));
  EXPECT_EQ('e', triangleType(5, 5, 5));
}

TEST(TriangleTest, Isosceles) {
  EXPECT_EQ('i', triangleType(6, 6, 9));
  EXPECT_EQ('i', triangleType(7, 10, 7));
  EXPECT_EQ('i', triangleType(3, 4, 4));
}

TEST(TriangleTest, Scalene) {
  EXPECT_EQ('s', triangleType(8, 2, 9));
  EXPECT_EQ('s', triangleType(7, 12, 10));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
