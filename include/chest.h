/**
    @author Victor Besson

    @brief

*/

#ifndef CHEST_H
#define CHEST_H
// User Defined
#include "inventory.h"

class chest {
public:
    /**
      @brief
      @param[in]
    */
    chest(int level);
    virtual ~chest();
    /**
      @brief
      @param[out]
    */
    int lootGold();
    /**
      @brief
      @param[out]
    */
    inventory* getInventory();
    int getGold();
private:
    int gold;
    inventory* cinventory;
};

#endif // CHEST_H
