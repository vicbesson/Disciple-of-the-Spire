#include "gtest/gtest.h"
#include "ability.h"


TEST(testAbility, constructorTest)
{
  ability a;

  EXPECT_EQ("", a.getName());
  EXPECT_EQ("", a.getDescription());
  EXPECT_EQ(0, a.getCooldown());
  EXPECT_EQ(0, a.getCurrentCooldown());
  EXPECT_EQ(0, a.getCost());
  EXPECT_EQ(0, a.getSellValue());
}

//will sometimes fail currently
TEST(testAbility, overloadedConstructor1Test)
{

  ability a(1);

  //change these to read from data instead: (also getDescription and getIndex and getCooldown and getStats)
  EXPECT_TRUE("Slash" == a.getName() || "Stomp" == a.getName() || "Fury" == a.getName()
            || "Lunge" == a.getName() || "Charge" == a.getName() || "Tornado" == a.getName()
            || "Combustion" == a.getName() || "Frosted Tip" == a.getName() || "Falling Bolt" == a.getName()
            || "Gust Charm" == a.getName() || "Shade Splitter" == a.getName() || "Adrenaline Rush" == a.getName());
  EXPECT_TRUE(0 == a.getStatRequirements()[0] || 1 == a.getStatRequirements()[0]
              || 2 == a.getStatRequirements()[0] || 3 == a.getStatRequirements()[0]);
  EXPECT_TRUE(2 == a.getStatRequirements()[1] || 4 == a.getStatRequirements()[1] || 6 == a.getStatRequirements()[1]);
  EXPECT_TRUE(4 == a.getDiceSize() || 6 == a.getDiceSize() || 8 == a.getDiceSize());
  EXPECT_EQ(2, a.getCooldown());

  EXPECT_EQ(1, a.getDiceRolls());
  EXPECT_EQ(50 * a.getDiceRolls(), a.getCost());  //********double check formatting
  EXPECT_EQ(0, a.getCurrentCooldown());
  EXPECT_EQ(a.getCost()/2, a.getSellValue());  //********double check formatting
  EXPECT_EQ(1, a.getStatRequirements()[2]);


  ability a2(2);

  //change these to read from data instead: (also getDescription and getIndex and getCooldown and getStats)
  EXPECT_TRUE("Strike" == a2.getName() || "Spin Bash" == a2.getName() || "Storming Rage" == a2.getName()
            || "Chained Dance" == a2.getName() || "Champion's Charge" == a2.getName() || "Leaping Slash" == a2.getName()
            || "Blood Shot" == a2.getName() || "Blazing Roar" == a2.getName() || "Plasma Roar" == a2.getName()
            || "Puncture" == a2.getName() || "Quickstep" == a2.getName() || "Rapid Fire" == a2.getName());
  EXPECT_TRUE(0 == a2.getStatRequirements()[0] || 1 == a2.getStatRequirements()[0]
              || 2 == a2.getStatRequirements()[0] || 3 == a2.getStatRequirements()[0]);
  EXPECT_TRUE(4 == a2.getStatRequirements()[1] || 6 == a2.getStatRequirements()[1] || 8 == a2.getStatRequirements()[1]);
  EXPECT_TRUE(8 == a2.getDiceSize() || 10 == a2.getDiceSize() || 12 == a2.getDiceSize());
  EXPECT_EQ(2, a2.getCooldown());

  EXPECT_EQ(1, a2.getDiceRolls());
  EXPECT_EQ(50 * a2.getDiceRolls(), a2.getCost()); //********double check formatting
  EXPECT_EQ(0, a2.getCurrentCooldown());
  EXPECT_EQ(a2.getCost()/2, a2.getSellValue()); //********double check formatting


  ability a3(8);

  //change these to read from data instead: (also getDescription and getIndex and getCooldown and getStats)
  EXPECT_TRUE("Slash" == a3.getName() || "Stomp" == a3.getName() || "Fury" == a3.getName()
            || "Lunge" == a3.getName() || "Charge" == a3.getName() || "Tornado" == a3.getName()
            || "Combustion" == a3.getName() || "Frosted Tip" == a3.getName() || "Falling Bolt" == a3.getName()
            || "Gust Charm" == a3.getName() || "Shade Splitter" == a3.getName() || "Adrenaline Rush" == a3.getName());
  EXPECT_TRUE(0 == a3.getStatRequirements()[0] || 1 == a3.getStatRequirements()[0]
              || 2 == a3.getStatRequirements()[0] || 3 == a3.getStatRequirements()[0]);
  EXPECT_TRUE(2 == a3.getStatRequirements()[1] || 4 == a3.getStatRequirements()[1] || 6 == a3.getStatRequirements()[1]);
  EXPECT_TRUE(4 == a3.getDiceSize() || 6 == a3.getDiceSize() || 8 == a3.getDiceSize());
  EXPECT_EQ(2, a3.getCooldown());

  EXPECT_EQ(1, a3.getDiceRolls());
  EXPECT_EQ(50 * a3.getDiceRolls(), a3.getCost());  //********double check formatting
  EXPECT_EQ(0, a3.getCurrentCooldown());
  EXPECT_EQ(a3.getCost()/2, a3.getSellValue());  //********double check formatting
  EXPECT_EQ(1, a.getStatRequirements()[2]);

  ability a4(-10);

  //change these to read from data instead: (also getDescription and getIndex and getCooldown and getStats)
  EXPECT_TRUE("Slash" == a4.getName() || "Stomp" == a4.getName() || "Fury" == a4.getName()
            || "Lunge" == a4.getName() || "Charge" == a4.getName() || "Tornado" == a4.getName()
            || "Combustion" == a4.getName() || "Frosted Tip" == a4.getName() || "Falling Bolt" == a4.getName()
            || "Gust Charm" == a4.getName() || "Shade Splitter" == a4.getName() || "Adrenaline Rush" == a4.getName());
  EXPECT_TRUE(0 == a4.getStatRequirements()[0] || 1 == a4.getStatRequirements()[0]
              || 2 == a4.getStatRequirements()[0] || 3 == a4.getStatRequirements()[0]);
  EXPECT_TRUE(2 == a4.getStatRequirements()[1] || 4 == a4.getStatRequirements()[1] || 6 == a4.getStatRequirements()[1]);
  EXPECT_TRUE(4 == a4.getDiceSize() || 6 == a4.getDiceSize() || 8 == a4.getDiceSize());
  EXPECT_EQ(2, a4.getCooldown());

  EXPECT_EQ(1, a4.getDiceRolls());
  EXPECT_EQ(50 * a4.getDiceRolls(), a4.getCost());  //********double check formatting
  EXPECT_EQ(0, a4.getCurrentCooldown());
  EXPECT_EQ(a4.getCost()/2, a4.getSellValue());  //********double check formatting
  EXPECT_EQ(1, a4.getStatRequirements()[2]);
}

TEST(testAbility, overloadedConstructor2Test)
{
  ability a(1, 0);

  //change these to read from data instead: (also getDescription and getIndex and getCooldown and getStats)
  EXPECT_TRUE("Slash" == a.getName() || "Stomp" == a.getName() || "Fury" == a.getName()
            || "Lunge" == a.getName() || "Charge" == a.getName() || "Tornado" == a.getName()
            || "Combustion" == a.getName() || "Frosted Tip" == a.getName() || "Falling Bolt" == a.getName()
            || "Gust Charm" == a.getName() || "Shade Splitter" == a.getName() || "Adrenaline Rush" == a.getName());
  EXPECT_TRUE(4 == a.getDiceSize() || 6 == a.getDiceSize() || 8 == a.getDiceSize());

  EXPECT_EQ(0, a.getStatRequirements()[0]); //checks type of ability
  EXPECT_EQ(1, a.getStatRequirements()[2]); //checks level of ability
  EXPECT_EQ(50 * a.getDiceRolls(), a.getCost());  //********double check formatting
  EXPECT_EQ(0, a.getCurrentCooldown());
  EXPECT_EQ(a.getCost()/2, a.getSellValue());  //********double check formatting
  EXPECT_EQ(2, a.getCooldown());

  ability a2(2, 3);

  //change these to read from data instead: (also getDescription and getIndex and getCooldown and getStats)
  EXPECT_TRUE("Puncture" == a2.getName() || "Quickstep" == a2.getName() || "Rapid Fire" == a2.getName());
  EXPECT_TRUE(8 == a2.getDiceSize() || 10 == a2.getDiceSize() || 12 == a2.getDiceSize());

  EXPECT_EQ(3, a2.getStatRequirements()[0]); //checks type of ability
  EXPECT_EQ(2, a2.getStatRequirements()[2]); //checks level of ability
  EXPECT_EQ(50 * a2.getDiceRolls(), a2.getCost());  //********double check formatting
  EXPECT_EQ(0, a2.getCurrentCooldown());
  EXPECT_EQ(a2.getCost()/2, a2.getSellValue());  //********double check formatting
  EXPECT_EQ(2, a2.getCooldown());

/*
//needs to be changed for correct value checks
  ability a3(0, 0);

  //change these to read from data instead: (also getDescription and getIndex and getCooldown and getStats)
  EXPECT_TRUE("Slash" == a3.getName() || "Stomp" == a3.getName() || "Fury" == a3.getName()
            || "Lunge" == a3.getName() || "Charge" == a3.getName() || "Tornado" == a3.getName()
            || "Combustion" == a3.getName() || "Frosted Tip" == a3.getName() || "Falling Bolt" == a3.getName()
            || "Gust Charm" == a3.getName() || "Shade Splitter" == a3.getName() || "Adrenaline Rush" == a3.getName());
  EXPECT_TRUE(4 == a3.getDiceSize() || 6 == a3.getDiceSize() || 8 == a3.getDiceSize());

  EXPECT_EQ(1, a.getStatRequirements()[2]); //checks level of ability
  EXPECT_EQ(50 * a.getDiceRolls(), a.getCost());  //double check formatting
  EXPECT_EQ(0, a.getCurrentCooldown());
  EXPECT_EQ(a.getCost()/2, a.getSellValue());  //double check formatting
  EXPECT_EQ(2, a.getCooldown());
*/
}

TEST(testAbility, getNameTest)
{
  ability a(5, 2);
  //change this to read from data instead:
  EXPECT_TRUE("Sand Edge" == a.getName() || "Aurora Flash" == a.getName() || "Blood Barrage" == a.getName());

  ability a2(3, 3);

  //change this to read from data instead:
  EXPECT_TRUE("Counter" == a2.getName() || "Tackle" == a2.getName() || "Wolf Leap" == a2.getName());
}

TEST(testAbility, getDescriptionTest)
{
  //needs data to be read in for this?
}


TEST(testAbility, getDiceRollsTest)
{
  ability a(1);

  EXPECT_EQ(1, a.getDiceRolls());

  ability a2(3, 1);

  EXPECT_EQ(2, a2.getDiceRolls());
}

TEST(testAbility, getDiceSizeTest)
{
  //needs data to be read in for this?
}

//will sometimes fail currently
TEST(testAbility, getCurrentCooldownTest)
{
  ability a(3);

  EXPECT_EQ(0, a.getCurrentCooldown());

  ability a2(3, 0);

  EXPECT_EQ(0, a2.getCurrentCooldown());
}

//will sometimes fail currently
TEST(testAbility, getCooldownTest)
{
    ability a(5, 2);

    EXPECT_EQ(2, a.getCooldown());

    ability a2(4, 1);

    EXPECT_EQ(2, a2.getCooldown());
}

TEST(testAbility, getStatRequirementsTest)
{
  //needs date to be read in for this?

  ability a(2, 2);

  EXPECT_TRUE(4 == a.getStatRequirements()[1] || 6 == a.getStatRequirements()[1] || 8 == a.getStatRequirements()[1]);
  EXPECT_EQ(2, a.getStatRequirements()[0]);
  EXPECT_EQ(2, a.getStatRequirements()[2]);

  ability a2(5, 3);

  EXPECT_TRUE(16 == a2.getStatRequirements()[1] || 18 == a2.getStatRequirements()[1] || 20 == a2.getStatRequirements()[1]);
  EXPECT_EQ(3, a2.getStatRequirements()[0]);
  EXPECT_EQ(5, a2.getStatRequirements()[2]);
}


TEST(testAbility, reduceCooldownTest)
{
  //need data to be read in for this for certain cooldowns > 2:
  ability a(1,1);

  EXPECT_EQ(0, a.getCurrentCooldown());
  a.dealDamage();
  EXPECT_EQ(2, a.getCurrentCooldown());
  a.reduceCooldown();
  EXPECT_EQ(1, a.getCurrentCooldown());

  ability a2(2,1);

  EXPECT_EQ(0, a2.getCurrentCooldown());
  a2.dealDamage();
  EXPECT_EQ(3, a2.getCurrentCooldown());
  a2.reduceCooldown();
  EXPECT_EQ(2, a2.getCurrentCooldown());

}

TEST(testAbility, dealDamageTest)
{
  //need data to be read in for this for certain cooldowns > 2:
  ability a(1, 0);

  EXPECT_EQ(0, a.getCurrentCooldown());
  a.dealDamage();
  EXPECT_EQ(2, a.getCurrentCooldown());

  ability a2(5,0);

  EXPECT_EQ(0, a2.getCurrentCooldown());
  a2.dealDamage();
  EXPECT_EQ(4, a2.getCurrentCooldown());
}

TEST(testAbility, getCostTest)
{
  ability a(3);

  EXPECT_EQ(50 * a.getDiceRolls(), a.getCost()); //*******double check formatting

  ability a2(0, 1);

  EXPECT_EQ(50 * a2.getDiceRolls(), a2.getCost()); //*******double check formatting
}


TEST(testAbility, getSellValueTest)
{
  ability a(2);

  EXPECT_EQ(a.getCost()/2, a.getSellValue());  //********double check formatting

  ability a2(2, 3);

  EXPECT_EQ(a2.getCost()/2, a2.getSellValue());  //********double check formatting
}

TEST(testAbility, getIndexTest)
{
  //need to read in data?
}
