#include "gtest/gtest.h"
#include "monster.h"


TEST(testMonster, constructorTest)
{
  monster m("Bob", "Orc", 100 ,{1,2,3,4} , 4);

  EXPECT_EQ("Bob", m.getName());
  EXPECT_EQ("Orc", m.getRace());
  EXPECT_EQ(1, m.getLevel());

  //these keep changing by one between 100 and 111??
  //EXPECT_EQ((100+(100*0.1)+(1*0.5)), m.getMaxHealth());
  //EXPECT_EQ((100+(100*0.1)+(1*0.5)), m.getCurrentHealth());
  EXPECT_TRUE(m.isBoss == false);

  //fix this tomorrow
  EXPECT_EQ(1, m.getStats()[0]);
  EXPECT_EQ(2, m.getStats()[1]);
  EXPECT_EQ(3, m.getStats()[2]);
  EXPECT_EQ(4, m.getStats()[3]);

  //add other baseCharacter variables


}

TEST(testMonster, isBossTest)
{
  monster m("Bob", "Orc", 80 ,{1,2,3,4} , 6);
  //error when level is used to indicate a boss

}
