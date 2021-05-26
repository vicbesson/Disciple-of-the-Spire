#include "gtest/gtest.h"
#include "dice.h"

TEST(testDice, constructorTest)
{
  //needs to be done still
}

TEST(testDice, overloadedConstructorTest)
{
  dice d(5);

  EXPECT_EQ(5, d.getSides());

  dice d2(0);

  EXPECT_EQ(6, d2.getSides());

  dice d3(-10);

  EXPECT_EQ(6, d3.getSides());
}

TEST(testDice, rollTest)
{
  dice d(10);

  EXPECT_TRUE(10 >= d.roll() && 1 <= d.roll());

}

TEST(testDice, roll2Test)
{
  dice d(7);
  int result = d.roll(1);
  EXPECT_TRUE(7 >= result && 1 <= result);
  result = d.roll(3);
  EXPECT_TRUE(21 >= result && 1 <= result);
}

TEST(testDice, getSidesTest)
{
  dice d(13);

  EXPECT_EQ(13, d.getSides());

  dice d2(2);

  EXPECT_EQ(2, d2.getSides());
}

