/**
    @author Tyler Justinen-Teite

    @brief

*/

#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H

#include "print.h"
#include "monster.h"
#include "player.h"
// Containers
#include <string>
#include <vector>
// I/O
#include <iostream>
#include <iomanip>
#include <sstream>

class combatManager {
public:
    combatManager(player* p, monster* m);
    virtual ~combatManager();

    bool startFight();


private:
    // [0] = monster : [1] = player
    baseCharacter** fightOrder;
    // Because player is always in fightOrder[1], when it is the players turn,
    // we get the 1st (true) index
    bool playersTurn;

    int turnCount = 0;

    bool endFight();


    bool checkCombatDone();
    /**
        @brief Helper function to parse the users input into ints
        @param[out] [0] switch, [1] type, [2] subType
     */
    std::vector<int> formatCommand(std::string command);



};

#endif // COMBATMANAGER_H
