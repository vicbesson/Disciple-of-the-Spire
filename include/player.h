/**
    @author Tyler Justinen-Teite
    @author Victor Besson
    @brief The user will play as an instance of this class.
           The Player class is the hero (adventurer) that the user uses to
           interact with DOTS, and the users source of progression.


*/

#ifndef PLAYER_H
#define PLAYER_H

#define DIR_PLAYERSAVE "docs/DATA/save"

// Inherited Class
#include "baseCharacter.h"
// User Defined
#include "print.h"
// Math
#include <algorithm>


class player : public baseCharacter {
public:

    /**
      @brief Default constructor. Not used in this program
    */
    player();
    /**
        @brief  Overloaded constructor, used to create a new hero
        @param[in] std::string Name
        @param[in] std::string Race
        @param[in] int Maximum amount of Health points
        @param[in] std::vector<int> [0] str : [1] dex : [2] int : [3] speed
    */
    player(std::string tName, std::string tRace, int tMaxHP,
           std::vector<int> tStat);

    virtual ~player();

    /**
        @brief Overloaded class operator to add & format player information,
               then add it to the output stream
    */
    friend std::ostream& operator << (std::ostream& out, player& toRender);
    /**
     @brief Manage player inventory
    */
    void inventoryManagement();
    /**
      @brief Move abilities between the players active and stored abilities
    */
    void swapAbilities(unsigned int index);
    /**
      @brief Swap the players equipped weapon with one in their inventory
    */
    void swapWeapon(unsigned int index);
    /**
      @brief Adds the given amount of experience to the current experience,
             then checks if the player has enough experience to level up,
             and call levelup()
      @param[in] int how much experience is to be added
    */
    void addExperience(int toAdd);
    /**
      @brief  Set currentExperience to current - maxExperience, allow the user
              to select which stats they would like to add, and check if the
              added stats will give the player an increase to their stat bonuses
              , finally, increase the players HP.
      @param Level 1: 100
      @param Level 2: 175
      @param Level 3: 250
      @param Level 4: 325
      @param Level 5: 401
      @param Level 6: 477
    */
    void levelUp();
    /**
      @brief Add to the players main stats
      @param[in] std::vector<int> [0] str : [1] dex : [2] int : [3] speed
    */
    void addToStats(std::vector<int> toAdd);
    /**
      @brief If "apply" == true add the status effect to the players current stats
             If "apply" == false subtract the status effect from the players stats
      @param[in] bool apply
      @param[in] std::vector<int> [0] str : [1] dex : [2] int : [3] speed
    */
    void applyStatusEffect(std::vector<int> toApply, bool apply);
    /**
        @brief
        @param[in]
    */
    void useConsumable(unsigned int index);
    /**
        @brief return the players currentExperience and the experience they need
        to level up
        @param[out] std::vector<int> [0] currentExperience : [1]  maxExperience
    */
    std::vector<int> getExperience();

    void save();


private:
    int currentExperience;
    int maxExperience;

    std::vector<int> statusEffect;

    bool checkAbilityReq(unsigned int inventoryIndex);
    bool checkWeaponReq(unsigned int inventoryIndex);

};

#endif // PLAYER_H
