#include "gtest/gtest.h"
#include "chest.h"

TEST(testChest, constructorTest)
{
  chest c(5);

  //testing for inventory?
  EXPECT_TRUE(c.getGold() >= 1 && c.getGold() <= 100);

}

TEST(testChest, lootGoldTest)
{
  chest c(2);

  EXPECT_TRUE(c.getGold() >= 1 && c.getGold() <= 100);
  c.lootGold();
  EXPECT_TRUE(c.getGold() == 0);
}

TEST(testChest, getInventoryTest)
{
  chest c(4);

  //better testing method?
  inventory* inv = c.getInventory();
  inv->removeAllWeapons();
  inv->removeAllConsumables();
  EXPECT_TRUE(inv->isEmpty());

}

TEST(testChest, getGoldTest)
{
  chest c(10);
  EXPECT_TRUE(35 >= c.getGold() && 0 <= c.getGold());
}
