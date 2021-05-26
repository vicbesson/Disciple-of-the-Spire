/**

    @brief main.cpp for testing all of the public methods in Disciple of the Spire
*/



#include "gtest/gtest.h"
#include "gameManager.h"



int main(int argc, char **argv) {

    gameManager myManager;
    
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

    /** baseCharacter */

       /// constructor

       /// getName

       /// getRace

       /// current HP

       /// max HP

       /// level

       /// get statBonuses

       /// damage power

       /// setGold

       /// getGold

       /// stats

       /// is dead

       /// Take damage

       /** baseCharacter : weapon */

           /// spawnWeapon

           /// deal damage

       /** baseCharacter : inventory */

           ///

       /** baseCharacter : abilities */

           /// use ability


       /** baseCharacter : abilities */

           ///


       /** baseCharacter : Player */

           /// Constructor

           /// swapAbilities (need to write a new function for it : random is fine)

           /// addToStats

           /// Apply Status Effect

           /// useConsumable

           /// get Experience

       /** baseCharacter : Monster */

           /// constructor

   /** Dice */

       /// constructor

       /// Overloaded Constructor

       /// roll

       ///  get sides

   /** Item */



       /** Item : Consumable */

           /// constructor

           /// overloaded constructor [id]

           /// get id

           /// is perminant

           /// getName

           /// getCost

           /// getSellValue

       /** Item : Weapon */

           /// Constructor

           /// overloadedConstructor(int level)

           /// overloadedConstructor(vector<int> statRequirements)

           /// overloadedConstructor(std::string name, int dSize, int dRolls, std::vector<int> sReq)

           /// getName

           /// getDiceRolls

           /// getDiceSize

           /// getStatReq

           /// generateWeapon(int level)

           /// dealDamage

   /** Ability */

       /// constructor

       /// overloadedConstructor(int)

       /// overloadedConstructor(int, int)

       /// get name

       /// get description

       /// get dice rolls

       /// get dice size

       /// get current cooldown

       /// get cooldown

       /// get stat requirements

       /// reduceCooldown + get current cooldown -> should never go bellow 0

       /// deal damage






//    return 0;
//}

