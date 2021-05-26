#include "gtest/gtest.h"
#include "item.h"

TEST(testItem, constructorTest)
{
  item i;

  EXPECT_EQ("", i.getName());
  //no values for cost or sell value?
}

TEST(testItem, getNameTest)
{
  item i;

  EXPECT_EQ("", i.getName());
}

TEST(testItem, getCostTest)
{
  //no values for cost?
}

TEST(testItem, getSellValueTest)
{
  //no values for sell value?
}
