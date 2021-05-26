#include "roomManager.h"
#include "monster.h"
#include <iostream>

roomManager::roomManager(player* p) {
    myPlayer = p;
    srand (time(NULL));
    for(int i = 0; i < 3; i++) {
        int tempRoomType = rand() % 2 + 1;
        nextRooms.push_back(tempRoomType);
    }
    roomLevel = 0;
    roomType = 2;
    introRead = false;
    roomDescription = rand() % roomManager::roomData->at(roomType).size();
    myPuzzle = new puzzleManager();
}

roomManager::~roomManager() {
    delete myPlayer;
    if(!chests.empty()) {
        for(chest* i : chests) {
            delete i;
        }
        chests.clear();
    }
    delete myMonster;
    delete myCombat;
    delete myShop;
    delete myPuzzle;
}

void roomManager::enterRoom() {
    roomLevel++;
    bool play = true;
    bool done = false;
    // Temp variables used for comsuming input stream
    // Convert to string stream for dynamic input / overloading
    std::string command;
    // User input converted into integers
    // input[0] command to switch on in the main loop
    std::vector<int> input;
    switch (roomType) {
    case 0: //boss
        myMonster = generateMonster();
        myCombat = new combatManager(myPlayer, myMonster);
        createMonsterRoom();
        break;
    case 1:
        createChestRoom();
        break;
    case 2: //monster
        myMonster = generateMonster();
        myCombat = new combatManager(myPlayer, myMonster);
        createMonsterRoom();
        break;
    case 3:
        myShop = new shopManager(roomLevel, myPlayer);
        createShopRoom();
        break;
    case 4:
        createPuzzleRoom();
        break;
    }
    while (play) {
        print::clearScreen();
        if(!introRead)
            print::str(description);
        else
            std::cout << description;
        std::cout << std::endl;
        std::cout << inputInfo << std::endl;
        std::cout << "What would you like to do adventurer: ";
        introRead = true;
        print::setCursor(true);
        command.clear();
        while(command[0] == '\n' || command.empty())
            getline(std::cin, command);
        input = formatCommand(command);
        print::setCursor(false);
        switch (input[0]) {
        case 0:
            play = false;
            break;
        case 121:
            myPlayer->inventoryManagement();
            break;
        case 151:
            myShop->startTransaction();
            play = false;
            break;
        case 171:
            if(static_cast<unsigned int>(input[1] - 1) < chests.size()) {
                std::cout << "Would you like to open chest number " << input[1] << "? (y/n)" << std::endl;
                print::setCursor(true);
                command.clear();
                while(command[0] == '\n' || command.empty())
                    getline(std::cin, command);
                print::setCursor(false);
                std::string c = print::toLower(command);
                if(c == "y" || c == "yes") {
                    print::str("Found " + std::to_string(chests[input[1] - 1]->getGold()) + " gold.\n");
                    myPlayer->setGold(chests[input[1] - 1]->lootGold());
                    for(weapon* w : chests[input[1] - 1]->getInventory()->removeAllWeapons()) {
                        print::str("Picked up " + w->getName());
                        std::cout << std::endl;
                        myPlayer->getInventory()->addWeapon(w);
                    }
                    for(std::vector<consumable*> cStack : chests[input[1] - 1]->getInventory()->removeAllConsumables()) {
                        print::str("Looted " + cStack.front()->getName() + " x" + std::to_string(cStack.size()));
                        std::cout << std::endl;
                        myPlayer->getInventory()->addConsumables(cStack);
                    }
                    delete chests[input[1]-1];
                    chests.erase(chests.begin()+ input[1] - 1);
                    print::textColour(print::C_RED);
                    print::str("The chest has been consumed by the spire!!!");
                    std::cout << std::endl;
                    print::textColour(print::C_DEFAULT);
                    if(!chests.empty())
                        createRoom(roomType);
                    else
                        play = false;
                } else if(c == "n" || c == "no")
                    break;
                else {
                    print::textColour(print::C_RED);
                    print::str("That is a yes or no question adventurer! Try again");
                    print::textColour(print::C_DEFAULT);
                    std::cout << std::endl;
                }
            } else {
                print::textColour(print::C_RED);
                print::str("That chest does not exist!");
                std::cout << std::endl;
                print::textColour(print::C_DEFAULT);
            }
            break;
        case 23:
            if(myCombat->startFight()) {
                play = false;
                if(roomLevel == 25) {
                    finishSpire();
                    done = true;
                }
            } else {
                deathSequence();
                play = false;
                done =true;
            }
            break;
        case 24:
            if(myPuzzle->startPuzzle(myPlayer)) {
                play = false;
            } else {
                deathSequence();
                play = false;
                done =true;
            }
            break;
        default:
            print::textColour(print::C_RED);
            print::str("invalid command");
            std::cout << std::endl;
            print::textColour(print::C_DEFAULT);
            break;
        }
        createRoom(roomType);
    }
    play = true;
    if(!done) {
        while(play) {
            print::clearScreen();
            std::cout << "Choose the room you would like to enter or type(i) to view inventory" << std::endl;
            for(int i = 0 ; i < nextRooms.size(); i++) {
                std::cout << std::to_string(i + 1) + ". ";
                switch(nextRooms[i]) {
                case 0:
                    if(roomLevel + 1 == 25)
                        std::cout << "final boss" << std::endl;
                    else
                        std::cout << "boss" << std::endl;
                    break;
                case 1:
                    std::cout << "chest" << std::endl;
                    break;
                case 2:
                    std::cout << "monster" << std::endl;
                    break;
                case 3:
                    std::cout << "shop" << std::endl;
                    break;
                case 4:
                    std::cout << "mystery" << std::endl;
                    break;
                }
            }
            std::cout << "What would you like to do adventurer: ";
            print::setCursor(true);
            command.clear();
            while(command[0] == '\n' || command.empty())
                getline(std::cin, command);
            print::setCursor(false);
            if(print::toLower(command) == "i" || print::toLower(command) == "inventory") {
                myPlayer->inventoryManagement();
            } else {
                if(print::is_number(command)) {
                    int index = std::stoi(command) - 1;
                    if(index < nextRooms.size()) {
                        if(nextRooms.size() == 2 && index == 1) {
                            myShop = new shopManager(roomLevel, myPlayer);
                            myShop->startTransaction();
                        } else {
                            changeRoom(index);
                            play = false;
                        }
                    } else {
                        print::textColour(print::C_RED);
                        print::str("What are you doing adventurer that's not a option?! Try again!");
                        print::textColour(print::C_DEFAULT);
                        std::cout << std::endl;
                    }
                } else {
                    print::textColour(print::C_RED);
                    print::str("What are you doing adventurer that's not a valid answer?! Try again!");
                    print::textColour(print::C_DEFAULT);
                    std::cout << std::endl;
                }
            }
        }
    }


}

void roomManager::finishSpire() {
    print::clearScreen();
    print::str("You win!!!!!!!!!!!!!!!!!");
}

void roomManager::deathSequence() {
    print::clearScreen();
    print::deathScreen();
    print::str("You have been defeated!!!!");
}

void roomManager::changeRoom(int nextRoom) {
    if(!chests.empty()) {
        for(chest* i : chests) {
            delete i;
        }
        chests.clear();
    }
    roomType = nextRooms[nextRoom];
    nextRooms.clear();
    if((roomLevel + 2) % 5 == 0) {
        nextRooms.push_back(0);
        nextRooms.push_back(3);
    } else {
        int isPuzzle = rand() % 100 + 1;
        int numRooms = 3;
        if(isPuzzle < 21 && !myPuzzle->getPuzzlesLeft().empty()) {
            nextRooms.push_back(4);
            numRooms--;
        }
        for(int i = 0; i < numRooms; i++) {
            int tempRoomType = rand() % 2 + 1;
            nextRooms.push_back(tempRoomType);
        }
    }
    roomDescription = rand() % roomManager::roomData->at(roomType).size();
    introRead = false;
    enterRoom();
}

void roomManager::createChestRoom() {
    if(chests.empty()) {
        srand (time(NULL));
        int chestAmount = rand() % 3 + 1;
        for(int i = 0; i < chestAmount; i++) {
            chests.push_back(new chest(roomLevel));
        }
    }
    int index = 1;
    description = roomManager::roomData->at(roomType)[roomDescription] + "\n";
    inputInfo = "(Floor " + std::to_string(roomLevel) + ") " + "Type the index of the chest you would like to open or type(i) to view inventory\n";
    if(!chests.empty()) {
        for(chest* i : chests) {
            inputInfo += std::to_string(index) + ". Chest\n";
            index++;
        }
    }
}

void roomManager::createMonsterRoom() {
    description = roomManager::roomData->at(roomType)[roomDescription] + "\n";
    inputInfo = "(Floor " + std::to_string(roomLevel) + ") " + "Type(start) to start combat or type(i) to view your inventory";
}

void roomManager::createShopRoom() {
    description = roomManager::roomData->at(roomType)[roomDescription] + "\n";
    inputInfo = "(Floor " + std::to_string(roomLevel) + ") " + "Type(shop) to enter shop or type(i) to view your inventory";
}

void roomManager::createPuzzleRoom() {
    description = roomManager::roomData->at(roomType)[roomDescription] + "\n";
    inputInfo = "(Floor " + std::to_string(roomLevel) + ") " + "Type(begin) to start mystery event or type(i) to view your inventory";
}

void roomManager::createRoom(int type) {
    switch(type) {
    case 0:
        createMonsterRoom();
        break;
    case 1:
        createChestRoom();
        break;
    case 2:
        createMonsterRoom();
        break;
    case 3:
        createShopRoom();
        break;
    case 4:
        createPuzzleRoom();
        break;
    }
}

monster* roomManager::generateMonster() {
    int spawnLevel = roomLevel / 5;
    if(spawnLevel < 1)
        spawnLevel = 1;
    else if(spawnLevel > 5)
        spawnLevel = 5;
    int index = rand() % baseCharacter::allRaces->size();
    monster* temp = new monster( baseCharacter::allRaces->at(index).race,
                                 baseCharacter::allRaces->at(index).race,
                                 baseCharacter::allRaces->at(index).maxHP,
                                 baseCharacter::allRaces->at(index).mStats,
                                 roomLevel);
    temp->spawnWeapon(spawnLevel);
    return temp;
}

std::vector<int> roomManager::formatCommand(std::string command) {
    std::vector<int> temp;
    std::vector<std::string> tempCommand;
    std::string parsed;
    std::stringstream parser(command);
    while (getline(parser, parsed, ' ')) {
        tempCommand.push_back(parsed);
    }
    for (unsigned int i = 0; i < tempCommand.size(); i++) {
        for (unsigned int c = 0; c < tempCommand[i].size(); c++) {
            tempCommand[i][c] = tolower(tempCommand[i][c]);
        }
    }
    // GTFO
    if (tempCommand[0] == "exit" || tempCommand[0] == "quit"
            || tempCommand[0] == "e")
        temp.push_back(0);
    else if(tempCommand[0] == "i" || tempCommand[0] == "inventory")
        temp.push_back(121);
    else if(roomType == 3 && (tempCommand[0] == "shop" || tempCommand[0] == "enter"))
        temp.push_back(151);
    //Open chest using index
    else if(roomType == 1 && (tempCommand[0] == "1" || tempCommand[0] == "2" || tempCommand[0] == "3") && tempCommand.size() == 1) {
        temp.push_back(171);
        temp.push_back(std::stoi(tempCommand[0]));
    } else if((roomType == 0 || roomType == 2) && (tempCommand[0] == "start" || tempCommand[0] == "combat" || tempCommand[0] == "fight"))
        temp.push_back(23);
    else if(roomType == 4 && (tempCommand[0] == "begin" || tempCommand[0] == "start"))
        temp.push_back(24);
    // If no valid command was entered
    else {
        temp.push_back(-1);
        return temp;
    }
    // Remove the command  string
    tempCommand.erase(tempCommand.begin());
    // Pushback all the numbers remaining in the command
    if (!tempCommand.empty()) {
        for (std::string i : tempCommand) {
            if(print::is_number(i))
                temp.push_back(std::stoi(i));
        }
    }
    temp.shrink_to_fit();
    return temp;
}

std::string roomManager::getDescription() {
    return description;
}

int roomManager::getLevel() {
    return roomLevel;
}

int roomManager::getRoomType() {
    return roomType;
}

