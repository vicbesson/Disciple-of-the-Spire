#include "gtest/gtest.h"
#include "baseCharacter.h"

//only needed when compiling this test seperately from testAbilities.cpp
/*
#include "gameManager.h"
gameManager* myManager = new gameManager;
*/

TEST(testBaseCharacter, constructorTest)
{
  baseCharacter b;

  //testing for inventory? maxHP and currentHP and isDead weird values?
  EXPECT_EQ("", b.getName());
  EXPECT_EQ("", b.getRace());
  EXPECT_EQ(0, b.getLevel());
  EXPECT_EQ(nullptr, b.getWeapon());
  EXPECT_EQ(0, b.getGold());
  //EXPECT_TRUE(b.isDead());
  //EXPECT_EQ(0, b.getCurrentHealth());
  //EXPECT_EQ(0, b.getMaxHealth());

  EXPECT_EQ(0, b.getStatBonuses()[0]);
  EXPECT_EQ(0, b.getStatBonuses()[1]);
  EXPECT_EQ(0, b.getStatBonuses()[2]);
  EXPECT_EQ(0, b.getStatBonuses()[3]);

  EXPECT_EQ(0, b.getStats()[0]);
  EXPECT_EQ(0, b.getStats()[1]);
  EXPECT_EQ(0, b.getStats()[2]);
  EXPECT_EQ(0, b.getStats()[3]);

}

TEST(testBaseCharacter, getNameTest)
{
  baseCharacter b;

  EXPECT_EQ("", b.getName());
}

TEST(testBaseCharacter, RaceTest)
{
  baseCharacter b;

  EXPECT_EQ("", b.getRace());
}

TEST(testBaseCharacter, getCurrentHealthTest)
{
  baseCharacter b;

  //random values? sometimes zero
}

TEST(testBaseCharacter, getMaxHealthTest)
{
  baseCharacter b;

  //random values? sometimes zero
}

TEST(testBaseCharacter, getLevelTest)
{
  baseCharacter b;

  EXPECT_EQ(0, b.getLevel());
}

TEST(testBaseCharacter, getStatBonusesTest)
{
  baseCharacter b;

  EXPECT_EQ(0, b.getStatBonuses()[0]);
  EXPECT_EQ(0, b.getStatBonuses()[1]);
  EXPECT_EQ(0, b.getStatBonuses()[2]);
  EXPECT_EQ(0, b.getStatBonuses()[3]);
}

TEST(testBaseCharacter, getDamagePowerTest)
{
  baseCharacter b;

  //random values? can this be tested?
}

TEST(testBaseCharacter, getGoldTest)
{
  baseCharacter b;

  EXPECT_EQ(0, b.getGold());
}

TEST(testBaseCharacter, getWeaponTest)
{
  baseCharacter b;

  EXPECT_EQ(nullptr, b.getWeapon());
}

TEST(testBaseCharacter, setWeaponTest)
{
  baseCharacter b;
  weapon* w;
  weapon* wtest;

  w = new weapon(1);
  EXPECT_EQ(nullptr, b.getWeapon());
  b.setWeapon(w);
  wtest = b.getWeapon();
  EXPECT_EQ(w->getName(), wtest->getName());
}

TEST(testBaseCharacter, getStatsTest)
{
  baseCharacter b;

  EXPECT_EQ(0, b.getStats()[0]);
  EXPECT_EQ(0, b.getStats()[1]);
  EXPECT_EQ(0, b.getStats()[2]);
  EXPECT_EQ(0, b.getStats()[3]);
}

TEST(testBaseCharacter, getInventoryTest)
{
  baseCharacter b;
  //better testing method?
  inventory* inv = b.getInventory();
  EXPECT_TRUE(inv->isEmpty());

}

TEST(testBaseCharacter, getActiveAbilitiesTest)
{

}

TEST(testBaseCharacter, setActiveAbilitiesTest)
{

}

TEST(testBaseCharacter, setGoldTest)
{
  baseCharacter b;

  EXPECT_EQ(0, b.getGold());
  b.setGold(50);
  EXPECT_EQ(50, b.getGold());
  b.setGold(75);
  EXPECT_EQ(125, b.getGold());
}

TEST(testBaseCharacter, isDeadTest)
{
  //random values for max and current HP affecting this?
}

TEST(testBaseCharacter, takeDamageTest)
{
  //random values for max and current HP affecting this?
}

TEST(testBaseCharacter, dealDamageTest)
{
  //come back to this, range of values based on dice
  baseCharacter b;
  weapon* w;

  w = new weapon(1);
  b.setWeapon(w);

  std::cout << b.dealDamage();
}

TEST(testBaseCharacter, useAbilityTest)
{

}

TEST(testBaseCharacter, spawnWeaponTest)
{

}

