/**
    @author Tyler Justinen-Teite
    @author Victor Besson
    @brief Parent class of Player and Monster.
           Stores the basic functionality for a Player Character
           (or Non-Player Character (monsters)).

    @param cInventory = new inventory()
    @param weapon* equippedWeapon = nullptr
    @param mainStats.resize(4, 0)
    @param statBonuses.resize(4, 0)

*/


#ifndef BASECHARACTER_H
#define BASECHARACTER_H

// User Defined
#include "ability.h"
#include "inventory.h"
// Containers
#include <string>
#include <vector>
// I/O
#include <iostream>
#include <iomanip>

// Forward declarations
class ability;
class inventory;

class baseCharacter {
    friend std::ostream& operator << (std::ostream& out, baseCharacter& toRender);
public:
    baseCharacter();
    virtual ~baseCharacter();
    struct raceData {
        int index;
        std::string race;
        int maxHP;
        std::vector<int> mStats;
        std::string description;
    };
    /**
      @brief  return the name of the character
      @param[out] std::string name
    */
    std::string getName();
    /**
      @brief return the race of the character
      @param[out] std::string race
    */
    std::string getRace();
    /**
      @brief  return the remaining health that the character has
      @param[out] int currentHP
    */
    const int&  getCurrentHealth();
    /**
      @brief  return the maximum health points that the character has
      @param[out] int maxHP
    */
    const int&  getMaxHealth();
    /**
      @brief Return the current level of the character
      @param[out] int Characters level
    */
    const int&  getLevel();
    /**
      @brief
      @param[out] std::vector<int> [0] Str : [1] Dex : [2] Int
    */
    std::vector<int> getStatBonuses();
    /**
      @brief Damage power = stat bonus[equippedWeapon->getStats()[1]]
      @param[out] int Damage Power
    */
    const int& getDamagePower();
    /**
      @brief Return the players current amount of gold.
      @param[out] int Current Gold
    */
    const int& getGold();
    /**
      @brief Return the pointer to the players equipped weapon.
      @param[out] weapon* Equipped weapon.
    */
    weapon* getWeapon();
    /**
      @brief When the player is first made, equip the player with a weapon
             of their highest stat
       @param[in] weapon* new equipped weapon
    */
    void setWeapon(weapon* toSet);
    /**
        @brief Return the players current stats.
        @param[out] std::vector<int> [0] str : [1] dex : [2] int : [3] speed
      */
    std::vector<int> getStats();
    /**
      @brief
      @param[out]
    */
    inventory* getInventory();
    /**
      @brief
      @param[out]
    */
    std::vector<ability*> getActiveAbilities();
    void setActiveAbilities(std::vector<ability*> toSet);
    /**
      @brief Increase the current gold of the character by the given amount.
      @param[in] int Gold to add
    */
    void setGold(int g);
    /**
      @brief Check if the character is still alive.
      @param[out] bool Is the character dead
    */
    bool isDead();
    /**
      @brief Subtract the damage from the current health.
      @param[in] int Damage taken
    */
    void takeDamage(int damage);
    /**
      @brief Attack with the equipped weapon.
      @param[out] int Weapon damage + Damage Power
    */
    int dealDamage();
    /**
      @brief
      @param[in]
      @param[out]
    */
    int useAbility(unsigned int index);
    /**
      @brief
      @param[in]
    */
    void spawnWeapon(int level);
    /**
      @brief
    */
    static std::vector<baseCharacter::raceData>* allRaces;

protected:

    std::string race;
    std::string name;

    int currentHealth;
    int maxHealth;

    int level;
    // 0 = strength : 1 = dex : 2 = int : 3 = speed
    std::vector<int> mainStats;
    // How much of a benafit do your stats give you
    std::vector<int> statBonuses;

    int gold;
    inventory* cInventory;

    // Add the players stat bonus to the weapon that they are using
    // depending on what stat the weapon requires
    int damagePower;
    weapon* equippedWeapon;

    std::vector<ability*> activeAbilities;
    /**
      @brief for every 2 points in a stat, gain either +1 or -1.
             Bonus becomes positive above 10
             (i.e. 6 dexterity = -2 bonus, and 14 dexterity = +2 bonus)
    */
    void checkStatBonuses();
    /**
      @brief Check if the equipped weapon gain a bonus to damage
             based on the type of weapon it is and the players stats
             so use this weapon
    */
    void updateDamagePower();
};

#endif // BASECHARACTER_H
