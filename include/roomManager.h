/**
    @author Victor Besson

    @brief

*/

#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H
//User Defined
#include "chest.h"
#include "player.h"
#include "monster.h"
#include "combatManager.h"
#include "shopManager.h"
#include "puzzleManager.h"
// Containers
#include <string>
#include <vector>
// I/O
#include <fstream>
#include <sstream>
// Math
#include <algorithm>

class roomManager {
public:
    /**
      @brief
      @param[out]
    */
    roomManager(player* p);
    virtual ~roomManager();
    /**
      @brief
      @param[out]
    */
    std::string getDescription();
    /**
      @brief
      @param[out]
    */
    int getLevel();
    /**
      @brief
      @param[out]
    */
    int getRoomType();
    /**
      @brief
      @param[out]
    */
    void enterRoom();
    static std::vector<std::vector<std::string>>* roomData;
private:
    int puzzleRoomCounter = 0;
    int roomType;
    std::vector<int> nextRooms;
    std::vector<chest*> chests;
    player* myPlayer;
    monster* myMonster;
    combatManager* myCombat;
    shopManager* myShop;
    puzzleManager* myPuzzle;
    int roomLevel;
    std::string description;
    void changeRoom(int nextRoom);
    void inventoryManagement();
    void createRoom(int type);
    void createChestRoom();
    void createMonsterRoom();
    void createShopRoom();
    void createPuzzleRoom();
    void finishSpire();
    void deathSequence();
    int roomDescription;
    std::string inputInfo;
    bool introRead;
    std::vector<int> formatCommand(std::string command);
    monster* generateMonster();
};

#endif // ROOMMANAGER_H
