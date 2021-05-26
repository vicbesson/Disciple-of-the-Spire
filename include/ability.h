/**
    @author Victor Besson

    @brief

*/

#ifndef ABILITY_H
#define ABILITY_H
// User Defined
#include "dice.h"
#include "item.h"
// Containers
#include <string>
#include <vector>
// I/O
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
// Time
#include <random>


class ability : public item {
    friend std::ostream& operator << (std::ostream& out, ability& toRender);
public:
    /**
      @brief
    */
    ability();
    /**
      @brief
    */
    ability(int level);
    /**
      @brief
    */
    ability(int level, int sType);
    /// this needs to be changed to take in the line of a csv
    /// so we can make an ability from a save file
    ability(int level, int sType, int abil);
    /**
      @brief
    */
    virtual ~ability();
    struct abilityData {
        int index;
        std::string name;
        std::vector<int> aStats;
        int cooldown;
        int dSize;
        int dRoll;
        std::string description;
    };
    /**
      @brief
      @param[out]
    */
    std::string getDescription();
    /**
      @brief
      @param[out]
    */
    int getDiceRolls();
    /**
      @brief
      @param[out]
    */
    int getDiceSize();
    /**
      @brief
      @param[out]
    */
    int getCurrentCooldown();
    /**
      @brief
      @param[out]
    */
    int getCooldown();
    /**
      @brief
      @param[out] std::vector<int> [0] statType : [1] statAmount : [2] level
    */
    std::vector<int> getStatRequirements();
    /**
      @brief
      @param[out]
    */
    void reduceCooldown();
    /**
      @brief
      @param[out]
    */
    int dealDamage();
    /**
      @brief
      @param[out]
    */
    static std::vector<std::vector<std::vector<abilityData>>>* allAbilities;
    /**
      @brief
      @param[out]
    */
    int getCost();
    /**
      @brief
      @param[out]
    */
    int getSellValue();
    /**
      @brief
      @param[out]
    */
    int getIndex();

private:
    int index;
    std::string description;
    int cooldown;
    int currentCooldown;
    bool onCooldown;
    int diceRolls;
    int diceSize;
    int cost;
    int sellValue;
    //[0] = stattype [1] = amount [2] = level req
    std::vector<int> statRequirements;
    std::vector<dice>* abilityDice;
    std::string formatOutput(unsigned int type, std::string value);
};

#endif // ABILITY_H
