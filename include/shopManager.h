/**
    @author Tyler Justinen-Teite

    @brief

*/

#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H
// User Defined
#include "inventory.h"
#include "print.h"
#include "item.h"
#include "ability.h"
#include "player.h"

// I/O
#include <iostream>
#include <iomanip>

class shopManager {
public:
    /**
      @brief
      @param[in]
    */
    shopManager(const int& roomCount, player* customer);
    virtual ~shopManager();
    void startTransaction();
private:
    int gold;

    int lastWeapon;
    int lastConsumable;
    bool hasAbility;
    // Prevents the user from entering in an index that'll seg fault
    int lastIndex;

    player* customer;
    inventory* sinventory;
    int formatCommand(std::string command);
    /**
      @brief Players gold >= cost
    */
    bool playerAfford(const int& cost);
    /**
      @brief Shops gold <= cost
    */
    bool shopAfford(const int& cost);
    /**
      @brief Prints a random message if the player cannot afford the item
    */
    void tooExpensive(const int& cost);
    /**
      @brief Prints a random 'continue shopping' message
    */
    void somethingElse();
    /**
      @brief
    */
    bool checkIndex(const int& index);
    /**
      @brief Display the amount of gold the shop and player has
    */
    void displayGold();
    /**
      @brief When the player makes a purchase, thank them for their patronage
    */
    void confirmPurchase();

    void shopCantAfford();
};

#endif // SHOPMANAGER_H
