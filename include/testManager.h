/**
    @author Tyler Justinen-Teite
    @author Victor Besson
    @brief

*/

#ifndef TESTMANAGER_H
#define TESTMANAGER_H

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

class testManager {
public:
    /**
      @brief
    */
    testManager();
    virtual ~testManager();
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
    monster* monsterPtr;
    roomManager* currentRoom;

    int currentLevel;

    // Helper functions for main loop
    std::string formatRoomType(int type);
    bool checkRoomIndex(int t, int i);
    // Format the users input string to an int to switch on in the mian loop
    std::vector<int> formatCommand(std::string command);
    /**
      @brief Create a character based on user input. Base function
             is used during main menu
    */
    player* characterCreation();
    /**
      @brief Overloaded character creation which allows you to
              create a hero based on a race index (see races.csv)
      @param[in] int index of csv to create
    */
    player* characterCreation(int index);


    void mainMenu();

    void saveGame();
    void loadGame();

    void enterRoom();
    // We'll have to start each room description with an index so we know what
    // type of monster to spawn
    void beginCombat(int l, int index);

    void chooseNextRoom();
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
    /**
      @brief Debugging: Print the remaining dictionary of weapon prefixes
    */
    void printWeapons();
    /**
      @brief Print all of the consumables from docs/DATA/consumableDATA.csv
    */
    void printConsumables();
    /**
      @brief generate a random monster at a given level
      @param [in] int level
    */
    void printAbility();
    /**
      @brief generate a random monster at a given level
      @param [in] int level
    */
    monster* generateMonster(int l);
    /**
      @brief generate a monster with a given race at a given level
      @param[in] int level
      @param[in] int race index
    */
    monster* generateMonster(int l, int index);
    /**
      @brief generate a monster with a given race at a given level, with a given name
      @param[in] int level
      @param[in] int race index
      @param[in] std::string name
    */
    monster* generateMonster(int l, int index, std::string tName);

    // Default sleep time is rand % 50

};
#endif // TESTMANAGER_H
