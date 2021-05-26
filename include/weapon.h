/**
    @author Tyler Justinen-Teite
    @author Victor Besson
    @brief

*/

#ifndef WEAPON_H
#define WEAPON_H

#define DIR_WEAPON "docs/DATA/weaponNames.txt"

// Inherited Class
#include "item.h"
// User Defined
#include "dice.h"
// I/O
#include <iostream>
#include <fstream>
// Containters
#include <vector>
#include <string>
// Temp for random weapon generation
#include <time.h>
#include <random>
#include <memory>
#include <algorithm>
class weapon : public item {
    /**
      weapon should be a constant reference, but when it's a constant
      it gets angry that we're accessing non constant members. So just
      don't change any variables of the weapon in the print function...
    */
    friend std::ostream& operator << (std::ostream& out, weapon& toRender);
    friend std::ostream& operator >> (std::ostream& out, weapon& readIn);

public:
    weapon();
    /**
      @brief Generate a random weapon at a given level
    */
    weapon(int l);
    /**
      @brief Generate a weapon that matches the given stats
      @param[in] std::vector<int> [0] statType : [1] statAmount : [2] level
    */
    weapon(std::vector<int> sReq);
    /**
      @brief Create a weapon with all specified stats
      @param[in] std::string name of the weapon
      @param[in] intSize of the dice
      @param[in] int How many dice rolls
      @param[in] std::vector<int> [0] statType : [1] statAmount : [2] level
    */
    weapon(std::string name, int dSize, int dRolls, std::vector<int> sReq);
    /**
      @brief ~dtor
    */
    virtual ~weapon();
    /**
        @brief Return the name of this weapon
        @param[out] std::string name
    */
    std::string getName();
    /**
        @brief Return the number of rolls with weapon has
        @param[out] int diceRolls
    */
    int getDiceRolls();
    /**
        @brief Return the size of this weapons dice
        @param[out] int diceSize
    */
    int getDiceSize();
    /**
        @brief Return the stat type, amount, and level required for this weapon
        @param[out] std::vector<int> [0] statType : [1] statAmount : [2] level
    */
    std::vector<int> getStatRequirements();

    /**
      @brief Spawn a random weapon based, stats and damage increased
    */
    void generateWeapon(int level);
    /**
      @brief Iterate through all of the dice rolls and return the total value
             of all the rolls
      @param[out] int sum of dice rolls
    */
    int dealDamage();
    static std::vector<std::string>* allNames;
private:
    int diceRolls;
    int diceSize;

    // stat type, stat amount, level
    std::vector<int> statRequirements;

    std::vector<dice>* weaponDice;

    /**
        @brief Based on the stat is required to use this weapon, give it a type
        @param[out] std::string Type of weapon (i.e. Sword, Rapier, Wand)
        @param[in] int How many sides the dice has
        @param[in] int stat required to use this weapon
    */
    std::string formatOutput(int type, std::string value);
    std::string addType(int dSize, int sType);
};

#endif // WEAPON_H



