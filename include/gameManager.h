/**
    @author Tyler Justinen-Teite
    @author Victor Besson
    @brief

*/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

/// UPDATE
#define DIR_COMMANDS "docs/DATA/commands.csv"
#define DIR_RACE "docs/DATA/raceData.csv"
#define DIR_ROOM "docs/DATA/roomData.csv"
#define DIR_WEAPON "docs/DATA/weaponNames.txt"
#define DIR_ABILITY "docs/DATA/abilitiesData.csv"
#define DIR_DOTS_LOGO "docs/DATA/DOTS-ASCII.txt"
#define DIR_MM_BUTTONS "docs/DATA/mainMenuButtons.txt"
#define DIR_INTRO "docs/DATA/introStory.txt"
#define DIR_STAIRS_SPIRAL "docs/DATA/stairs_spiral.txt"
// User defined
#include "player.h"
#include "monster.h"
#include "chest.h"
#include "combatManager.h"
#include "roomManager.h"
#include "item.h"
#include "print.h"
#include "shopManager.h"
// Containers
#include <vector>
#include <string>
#include <cstring>
// I/O
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

// trying to find what libraries i need to slowly print text
#include <chrono>
#include <thread>
#include <time.h>

class gameManager {
public:
    /**
      @brief
    */
    gameManager();
    virtual ~gameManager();
    /**
        @brief  Main loop of the game
    */
    void startGame();
    /**
        @brief Debugging: Print all weapon names read in the the weaponNames dictionary
    */


private:
    // Easiest to store all of the race data in a vector<raceData>
    struct raceData {
        int index;
        std::string race;
        int maxHP;
        std::vector<int> mStats;
        std::string description;
    };
    player* playerPtr;
    roomManager* currentRoom;
    /**
      @brief Create a character based on user input. Base function
             is used during main menu
    */
    player* characterCreation();
    void mainMenu();
    void loadGame();
    /**
      @brief Read in and store all the races from docs/DATA/races.csv
    */
    void readInRaceData();
    /**
      @brief Print all the races in the docs/DATA/races.csv file
    */
    void printRaces();
    /**
      @brief Debugging: Read in all of the weapon names from docs/DATA/weaponNames
    */
    void readInWeapons();
    /**
      @brief Read in all of the room names from docs/DATA/roomNames
    */
    void readInRooms();
    /**
      @brief Read in all of the ability names from docs/DATA/abilitiesNames
    */
    void readInAbilities();
};
#endif // GAMEMANAGER_H
