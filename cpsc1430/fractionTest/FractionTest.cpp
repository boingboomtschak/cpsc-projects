// FractionTest.cpp - Tests Fraction class

#include <gtest/gtest.h>
#include "Fraction.h"

TEST(FractionTest, DefaultConstructor) {
  Fraction a;
  EXPECT_EQ(0, a.getNumer());
  EXPECT_EQ(1, a.getDenom());
}

TEST(FractionTest, Constructor) {
  Fraction a(3, 8);
  EXPECT_EQ(3, a.getNumer());
  EXPECT_EQ(8, a.getDenom());

  Fraction b(14, 6);
  EXPECT_EQ(14, b.getNumer());
  EXPECT_EQ(6, b.getDenom());
}

TEST(FractionTest, GetNumer) {
  Fraction a(2, 10);
  EXPECT_EQ(2, a.getNumer());

  Fraction b(7, 4);
  EXPECT_EQ(7, b.getNumer());
}

TEST(FractionTest, GetDenom) {
  Fraction a(5, 15);
  EXPECT_EQ(15, a.getDenom());

  Fraction b(13, 6);
  EXPECT_EQ(6, b.getDenom());
}

TEST(FractionTest, isSame) {
  Fraction a(1, 2);

  Fraction b(1, 2);
  EXPECT_EQ(true, a.isSame(b)); 
  EXPECT_EQ(true, b.isSame(a)); 

  Fraction c(3, 8);
  EXPECT_EQ(false, a.isSame(c)); 
  EXPECT_EQ(false, c.isSame(a)); 

  Fraction d(2, 4);
  EXPECT_EQ(false, a.isSame(d)); 
  EXPECT_EQ(false, d.isSame(a)); 
}

TEST(FractionTest, reduce) {
  Fraction a(1, 2);
  a.reduce();
  EXPECT_EQ(1, a.getNumer());
  EXPECT_EQ(2, a.getDenom());
  
  Fraction b(4, 8);
  b.reduce();
  EXPECT_EQ(1, b.getNumer());
  EXPECT_EQ(2, b.getDenom());

  Fraction c(8, 4);
  c.reduce();
  EXPECT_EQ(2, c.getNumer());
  EXPECT_EQ(1, c.getDenom());

  Fraction d(14, 35);
  d.reduce();
  EXPECT_EQ(2, d.getNumer());
  EXPECT_EQ(5, d.getDenom());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
