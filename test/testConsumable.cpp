#include "gtest/gtest.h"
#include "consumable.h"
/*
TEST(testConsumable, constructorTest)
{
  //need to do this still
}
*/
TEST(testConsumable, overloadedConstructorTest)
{
  consumable c(5);

  EXPECT_EQ(5, c.getID());
  EXPECT_EQ("Book of Strength", c.getName());
  EXPECT_EQ(0, c.statsToAdd()[0]);
  EXPECT_EQ(2, c.statsToAdd()[1]);
  EXPECT_TRUE(c.getIsPerminant());
  EXPECT_EQ(300, c.getCost());
  EXPECT_EQ(100, c.getSellValue());

  consumable c2(300);

  EXPECT_EQ(0, c2.getID());
  EXPECT_EQ("Bandage", c2.getName());
  EXPECT_EQ(4, c2.statsToAdd()[0]);
  EXPECT_EQ(10, c2.statsToAdd()[1]);
  EXPECT_FALSE(c2.getIsPerminant());
  EXPECT_EQ(10, c2.getCost());
  EXPECT_EQ(5, c2.getSellValue());

  consumable c3(-10);

  EXPECT_EQ(0, c3.getID());
  EXPECT_EQ("Bandage", c3.getName());
  EXPECT_EQ(4, c3.statsToAdd()[0]);
  EXPECT_EQ(10, c3.statsToAdd()[1]);
  EXPECT_FALSE(c3.getIsPerminant());
  EXPECT_EQ(10, c3.getCost());
  EXPECT_EQ(5, c3.getSellValue());
}

TEST(testConsumable, getNameTest)
{
  consumable c(2);

  EXPECT_EQ("Healing Potion", c.getName());

  consumable c2(8);

  EXPECT_EQ("Book of Speed", c2.getName());
}

TEST(testConsumable, getIDTest)
{
  consumable c(5);

  EXPECT_EQ(5, c.getID());

  consumable c2(1);

  EXPECT_EQ(1, c2.getID());
}

TEST(testConsumable, statsToAddTest)
{
  consumable c(1);

  EXPECT_EQ(4, c.statsToAdd()[0]);
  EXPECT_EQ(20, c.statsToAdd()[1]);

  consumable c2(8);

  EXPECT_EQ(3, c2.statsToAdd()[0]);
  EXPECT_EQ(2, c2.statsToAdd()[1]);

}

TEST(testConsumable, getIsPerminantTest)
{
  consumable c(2);

  EXPECT_FALSE(c.getIsPerminant());

  consumable c2(6);

  EXPECT_TRUE(c2.getIsPerminant());
}

TEST(testConsumable, getCostTest)
{
  consumable c(2);

  EXPECT_EQ(50, c.getCost());

  consumable c2(7);

  EXPECT_EQ(300, c2.getCost());
}

TEST(testConsumable, getSellValueTest)
{
  consumable c(1);

  EXPECT_EQ(10, c.getSellValue());

  consumable c2(4);

  EXPECT_EQ(100, c2.getSellValue());
}

