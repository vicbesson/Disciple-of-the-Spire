/**
    @author Victor Besson
    @brief

*/

#ifndef INVENTORY_H
#define INVENTORY_H
// User Defined
#include "consumable.h"
#include "weapon.h"
#include "ability.h"
// Containers
#include <vector>
// I/O
#include <iostream>

class inventory {
public:
    inventory();
    virtual ~inventory();
    /**
      @brief
      @param[in] unsigned int
      @param[in] unsigned int
      @param[out]
    */
    bool deleteConsumables(unsigned int index, unsigned int amount);
    /**
      @brief
      @param[in]
      @param[out]
    */
    bool deleteWeapon(unsigned int index);
    /**
      @brief
      @param[in]
    */
    void addConsumables(std::vector<consumable*> conStack);
    /**
      @brief
      @param[in]
    */
    void addAbility(ability* abilityToAdd);
    /**
      @brief
      @param[in]
    */
    ability* removeAbility(unsigned int index);
    /**
      @brief
      @param[in]
      @param[in]
      @param[out]
    */
    std::vector<consumable*> removeConsumables(unsigned int index,
            unsigned int amount);
    /**
      @brief
      @param[out]
    */
    std::vector<std::vector<consumable*>> removeAllConsumables();
    /**
      @brief
      @param[in]
      @param[out]
    */
    weapon* removeWeapon(unsigned int index);
    /**
      @brief
      @param[in]
    */
    void addWeapon(weapon* wpnToAdd);
    /**
      @brief
      @param[out]
    */
    //int getInventorySize();
    /**
      @brief
    */
    void viewInventory();
    /**
      @brief
      @param[in]
    */
    //void increaseInventorySize(int amount);
    /**
      @brief
      @param[out]
    */
    std::vector<weapon*> removeAllWeapons();
    /**
      @brief
      @param[in]
      @param[out]
    */
    //bool checkForRoom(unsigned int amountToAdd);
    /**
      @brief
      @param[out]
    */
    std::vector<ability*> getAbilities();
    /**
      @brief
      @param[out]
    */
    std::vector<weapon*> getWeapons();
    /**
      @brief
      @param[out]
    */
    std::vector<std::vector<consumable*>> getConsumables();

    bool isEmpty();


private:
    std::vector<std::vector<consumable*>> consumableStacks;
    std::vector<weapon*> weapons;
    std::vector<ability*> abilities;
    std::string formatIndex(std::string index);
    //int inventorySize;
};

#endif // INVENTORY_H
