/**
    @author Tyler Justinen-Teite

    @brief

*/

#ifndef MONSTER_H
#define MONSTER_H
// Inherited Class
#include "baseCharacter.h"


class monster : public baseCharacter {
    friend std::ostream& operator << (std::ostream& out, monster& toRender);
public:
    monster(std::string tName, std::string tRace, int tMaxHP, std::vector<int> tmMStats, int l);
    virtual ~monster();
    /**
      @brief Boss = level % 5 == 0
    */
    bool isBoss;
private:



    /**
        @brief level up the monster (if applicable)
               give the monster an ability
               create a weapon for the monster
               update stat bonuses
               give the monster gold
    */
    void initMonster();
};

#endif // MONSTER_H
