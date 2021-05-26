#include "testManager.h"
/**   Initiate all static pointers */


testManager::testManager() {
    /** Read in data from docs/DATA/"file" into the static pointers */
    readInRaceData();
    readInWeapons();
    readInRooms();
    readInAbilities();
    // Game starts at level 1
    currentLevel = 1;
    // Initiate the memory location of the playerPtr
    playerPtr = characterCreation(1);
    // Initiate the memory location of the monsterPtr
    monsterPtr = generateMonster(1);
    // Set the screen to our default values
    print::initScreen();

// mainMenu();

}

testManager::~testManager() {
    delete weapon::allNames;
    delete roomManager::roomData;
    delete baseCharacter::allRaces;
    delete ability::allAbilities;
    delete playerPtr;
    delete monsterPtr;
    delete currentRoom;
}

void testManager::readInWeapons() {
    std::ifstream weaponNames;
    weaponNames.open(DIR_WEAPON);
    std::string line;
    // Store each line (name) in a dictionary of weaponNames
    while(getline(weaponNames, line)) {
        weapon::allNames->push_back(line);
    }

    weaponNames.close();

    weapon::allNames->shrink_to_fit();

}

void testManager::readInRooms() {
    std::ifstream toRead;
    toRead.open(DIR_ROOM);
    std::vector<std::string> tempData;
    std::string line;
    while (getline(toRead, line, ',')) {
        tempData.push_back(line);
    }
    toRead.close();
    for(int i = 0; i < 5; i++)
        roomManager::roomData->push_back(std::vector<std::string>());
    for(int i = 0; i < 11; i++) {
        int type = std::stoi(tempData[0]);
        roomManager::roomData->at(type).push_back(tempData[1]);
        tempData.erase(tempData.begin(), tempData.begin() + 2);
    }
    roomManager::roomData->shrink_to_fit();
}

void testManager::readInAbilities() {
    std::ifstream toRead;
    toRead.open(DIR_ABILITY);
    std::vector<std::string> tempData;
    std::string line;
    while (getline(toRead, line, ',')) {
        tempData.push_back(line);
    }
    toRead.close();
    for(int i = 0; i < 5; i++) {
        ability::allAbilities->push_back(std::vector<std::vector<ability::abilityData>>());
        for(int j = 0; j < 4; j++)
            ability::allAbilities->back().push_back(std::vector<ability::abilityData>());
    }
    for(int i = 0; i < 60; i++) {
        int lvlreq = std::stoi(tempData[5]) - 1;
        int stat = std::stoi(tempData[3]);
        ability::allAbilities->at(lvlreq)[stat].push_back(ability::abilityData());
        // Store the index of the ability so we can recreate it later
        ability::allAbilities->at(lvlreq)[stat].back().index = i;
        ability::allAbilities->at(lvlreq)[stat].back().aStats.resize(3);
        ability::allAbilities->at(lvlreq)[stat].back().name = tempData[1];
        ability::allAbilities->at(lvlreq)[stat].back().cooldown = std::stoi(tempData[2]);
        ability::allAbilities->at(lvlreq)[stat].back().aStats[0] = stat;
        ability::allAbilities->at(lvlreq)[stat].back().aStats[1] = std::stoi(tempData[4]);
        ability::allAbilities->at(lvlreq)[stat].back().aStats[2] = lvlreq + 1;
        ability::allAbilities->at(lvlreq)[stat].back().dSize = std::stoi(tempData[6]);
        ability::allAbilities->at(lvlreq)[stat].back().dRoll = std::stoi(tempData[7]);
        ability::allAbilities->at(lvlreq)[stat].back().description = tempData[8];
        tempData.erase(tempData.begin(), tempData.begin() + 9);
    }

    ability::allAbilities->shrink_to_fit();
}

void testManager::readInRaceData() {
    // ifstream to read in the csv file
    std::ifstream toRead;
    // Open the file
    toRead.open(DIR_RACE);
    // temp variables
    std::vector<std::string> tempData;
    std::string line;

    while(getline(toRead, line, ',')) {
        tempData.push_back(line);
    }
    toRead.close();

//  std::cout << ""
    for(unsigned int i = 0; i < 10; i ++) {
        // Initialize a new index in the vector
        baseCharacter::allRaces->push_back(baseCharacter::raceData());
        // Init the stats vector to have a size of 4
        baseCharacter::allRaces->at(i).mStats.resize(4);
        // Load all of the race data into the allRaces vector
        baseCharacter::allRaces->at(i).index = std::stoi(tempData.at(0));
        baseCharacter::allRaces->at(i).race = tempData.at(1);
        baseCharacter::allRaces->at(i).maxHP = std::stoi(tempData.at(2));
        baseCharacter::allRaces->at(i).mStats[0] = std::stoi(tempData.at(3));
        baseCharacter::allRaces->at(i).mStats[1] = std::stoi(tempData.at(4));
        baseCharacter::allRaces->at(i).mStats[2] = std::stoi(tempData.at(5));
        baseCharacter::allRaces->at(i).mStats[3] = std::stoi(tempData.at(6));
        baseCharacter::allRaces->at(i).description = tempData.at(7);

        // Once all the data for a race has been loaded, clear that section
        // of the tempData vector
        tempData.erase(tempData.begin(), tempData.begin() + 8);
    }
    baseCharacter::allRaces->shrink_to_fit();
}

void testManager::printRaces() {
    std::cout
            << "| Index |     Race     |  Health  |  Str  |  Dex  |  Int  | Speed |\n"
            << std::setfill('-') << std::setw(70) << ' '
            << std::endl << std::setfill(' ');

    for(auto i : (*baseCharacter::allRaces)) {
        // Spacers for formating race data
        int wName = 18 - i.race.length();
        int wHP = 9;
        int wStr = 8;
        int wDex = 8;
        int wInt = 8;
//    int wSpd = 9; // Spacer between speed int and description

        // Set the colour after we add it to the output buffer
        std::cout << std::setw(5) << i.index << std::internal
                  << std::setw(7 +  i.race.length()) << i.race
                  << std::setw(wName) << i.maxHP;
        print::textColour(print::C_DEFAULT);
        // Strength
        std::cout << std::setw(wHP) << i.mStats[0];
        print::textColour(print::C_RED);
        // Dexterity
        std::cout << std::setw(wStr) << i.mStats[1];
        print::textColour(print::C_GREEN);
        // intellect
        std::cout << std::setw(wDex) << i.mStats[2];
        print::textColour(print::C_BLUE);
        // Speed
        std::cout << std::setw(wInt) << i.mStats[3];
        print::textColour(print::C_BROWN);
        // endl (render to screen)
        std::cout << std::endl;
    }
    // Set the text colour back to default
    print::textColour(print::C_DEFAULT);
}
void testManager::printConsumables() {
    for (int i = 0; i <= consumable::lastIndex; i++) {
        consumable* toPrint = new consumable(i);
        std::cout << *toPrint;
        delete toPrint;
    }
}

void testManager::printAbility() {
    for(int i = 0; i < 3; i++) {
        for(int lev = 1; lev < 6; lev++) {
            for(int stat = 0; stat < 4; stat++) {
                ability toPrint(lev, stat, i);
                std::cout << toPrint << std::endl;
            }
        }
    }
}

/**     MAIN LOOP     */
void testManager::startGame() {
    combatManager* thisFight = nullptr;
    consumable* myConsumable = nullptr;
    shopManager* myShop = nullptr;
    std::vector<consumable*> myConVec;
    chest* myChest = nullptr;


    bool play = true;
    // User input converted into integers
    // input[0] command to switch on in the main loop
    std::vector<int> input;
    std::string command;


    while (play) {
        print::setCursor(true);
        command.clear();
        std::cout << ">>> ";
        while(command[0] == '\n' || command.empty())
            getline(std::cin, command);
        input = formatCommand(command);
        print::setCursor(false);
        switch (input[0]) {
        /**     print commands       */
        // pPlayer, pp
        case 10:
            printRaces();
            break;
        // pPlayer, pp
        case 12:
            std::cout << (*playerPtr);
            break;
        // pPlayerWeapon, ppw
        case 120:
            std::cout << (*playerPtr->getWeapon()) << std::endl;
            break;
        //viewinventory, vi
        case 121:
            playerPtr->inventoryManagement();
            std::cout << std::endl;
            break;
        //swapabilities, sab
        case 122:
            //playerPtr->swapAbilities();
            break;
        // swapweapon, sw
        case 123:
            //playerPtr->swapWeapon();
            break;
        // useconsumable, ucon
        case 124:
            playerPtr->getInventory()->viewInventory();
            std::cout << "Which consumable would you like to use? ";
            std::cin >> input[1];
            playerPtr->useConsumable(input[1] - 1);
            break;

        // pMonster, pm
        case 13:
            std::cout << (*monsterPtr);
            break;
        //pMonsterWeapon, pmw
        case 130:
            std::cout << (*monsterPtr->getWeapon()) << std::endl;
            break;
        // pMonsterGold, pmg
        case 131:
            std::cout << monsterPtr->getGold() << std::endl;
            break;

        // pConsumables, pcon
        case 14:
            printConsumables();
            break;
        // pabilities, pa
        case 16:
            printAbility();
            break;
        //viewchest, vch
        case 17:
            myChest->getInventory()->viewInventory();
            break;
        //OpenChest, och
        case 171:
            std::cout << "Found " << myChest->getGold() << " gold.\n";
            playerPtr->setGold(myChest->lootGold());
            for(weapon* w : myChest->getInventory()->removeAllWeapons()) {
                std::cout << "Picked up\n" << *w << std::endl;
                playerPtr->getInventory()->addWeapon(w);
            }
            for(std::vector<consumable*> cStack : myChest->getInventory()->removeAllConsumables()) {
                std::cout << "Looted\n" << *cStack.front() << " x" << cStack.size() << std::endl;
                playerPtr->getInventory()->addConsumables(cStack);
            }
            break;
        /**        make commands (spawn an object)      */
        // makeWeapon,  mw
        case 20:
            // Replace the players equipped weapon at the given level
            if (input.size() == 2)
                playerPtr->spawnWeapon(input[1]);
            // Replace the players equipped weapon with one of the global level
            else
                playerPtr->spawnWeapon(currentLevel);
            std::cout << (*playerPtr->getWeapon());
            break;
        // makePlayer, mp
        case 21:
            if (playerPtr != nullptr)
                delete playerPtr;
            // Spawn a player with the given race index
            if(input.size() == 2) {
                if(input[1] < 0 || input[1] > 9)
                    input [1] = 0;
                playerPtr = characterCreation(input[1]);
            }
            // Spawn a player at a given race index and levelUp x times
            else if (input.size() == 3) {
                if(input[1] < 0 || input[1] > 9)
                    input [1] = 0;
                playerPtr = characterCreation(input[1]);
                for (int i = 0; i < input[2]; i++)
                    playerPtr->levelUp();
            }
            // If no race is given, go through the default character creation
            else {
                playerPtr = characterCreation();
            }

            std::cout << (*playerPtr);
            break;

        /**         makeMonster, mm     */
        case 22:
            if(monsterPtr != nullptr)
                delete monsterPtr;
            // input0 = level, input1 = raceIndex
            if(input.size() == 3)
                monsterPtr = generateMonster(input[1], input[2]);
            else if(input.size() == 2)
                monsterPtr = generateMonster(input[1]);
            else {
                std::cout << "Current Level: " << currentLevel << std::endl;
                monsterPtr = generateMonster(currentLevel);
            }

            std::cout << *monsterPtr;
            break;
        // makeCombat, mc
        case 23:
            // Generate a monster at a given level then begin combat
            if (input.size() == 2) {
                monsterPtr = generateMonster(input[1]);
                thisFight = new combatManager(playerPtr, monsterPtr);
                thisFight->startFight();
            }
            // Generate a monster at a given level, and race then begin combat
            else if (input.size() == 3) {
                monsterPtr = generateMonster(input[1], input[2]);
                thisFight = new combatManager(playerPtr, monsterPtr);
                thisFight->startFight();
            }
            // Start combat with a random monster based on the global level
            else {
                monsterPtr = generateMonster(currentLevel);
                thisFight = new combatManager(playerPtr, monsterPtr);
                thisFight->startFight();
            }

            delete thisFight;
            break;
        // makeConsumable, mcon
        case 24:
            myConsumable = new consumable(input[1]);
            std::cout << *myConsumable << std::endl;
            delete myConsumable;
            break;

        case 25:
            myShop = new shopManager(currentLevel, playerPtr);
            myShop->startTransaction();
            break;
        case 27:
            delete myChest;
            myChest = new chest(25);
            myChest->getInventory()->viewInventory();
            break;
        /**             debugging commands            */
        // Clear the terminal window of all text
        case 90:
            // WINDOWS
            //system("cls");
            // Linux
            system("clear");
            break;
        // addExperience, xp
        case 91:
            playerPtr->addExperience(input[1]);
            //std::cout << (*playerPtr);
            break;
        // levelUp, lvl
        case 210:
            playerPtr->levelUp();
            break;
        // Make an ability and add it to the players inventory
        case 211:
            if(input.size() == 3)
                playerPtr->getInventory()->addAbility(
                    new ability(input[1], input[2]));
            else if (input.size() == 2)
                playerPtr->getInventory()->addAbility(new ability(input[1]));
            else
                playerPtr->getInventory()->addAbility(new ability(currentLevel));

            playerPtr->getInventory()->viewInventory();
            break;
        // Make a consumable and add it to the players inventory
        case 212:
            myConVec.clear();
            myConVec.push_back(new consumable(input[1]));
            playerPtr->getInventory()->addConsumables(myConVec);
            playerPtr->getInventory()->viewInventory();
            break;
        // mpw, Make a weapon and add it to the players inventory
        case 213:
            if(input.size() == 4) {
                input.erase(input.begin());
                playerPtr->getInventory()->addWeapon(new weapon(input));
            } else if(input.size() == 2)
                playerPtr->getInventory()->addWeapon(new weapon (input[1]));

            else
                playerPtr->getInventory()->addWeapon(new weapon(currentLevel));

            playerPtr->getInventory()->viewInventory();
            break;
        //  atk : deal damage with the players equipped weapon
        case 92:
            std::cout << playerPtr->dealDamage() << std::endl;
            break;
        //mainmenu, mmenu
        case 93:
            mainMenu();
            break;
        case 94:
            currentLevel = input[1];
            break;
        case 96:
            currentRoom = new roomManager(playerPtr);
            currentRoom->enterRoom();
            break;
        case 99:
            mainMenu();
            currentRoom = new roomManager(playerPtr);
            currentRoom->enterRoom();
        // exit, e
        case 0:
            std::cout << "bye" << std::endl;
            play = false;
            break;

        default:
            std::cout << "invalid command" << std::endl;
            break;
        }
    }
    delete myChest;
    delete thisFight;
    delete myConsumable;
    delete myShop;
    delete currentRoom;
    for(consumable* c : myConVec) {
        delete c;
    }
    myConVec.clear();
}

std::string testManager::formatRoomType(int type) {
    std::string temp;

    if (type == 0)
        temp = "boss";
    else if (type == 1)
        temp = "chest";
    else if (type == 2)
        temp = "monster";
    else if (type == 3)
        temp = "shop";
    else if (type == 4)
        temp = "default";

    return temp;
}

bool testManager::checkRoomIndex(int t, int i) {
    bool validIndex;

    if (t < 4 && t >= 0)
        validIndex = true;
    else {
        std::cout << "invalid room type\n";
        validIndex = false;
    }

    if (i < 3 && i >= 0)
        validIndex = true;
    else {
        std::cout << "invalid room type index\n";
        validIndex = false;
    }
    return validIndex;
}

std::vector<int> testManager::formatCommand(std::string command) {

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

    /** Print functions are prefixed with 1 */
    if (tempCommand[0] == "prace" || tempCommand[0] == "pr")
        temp.push_back(10);

    else if (tempCommand[0] == "pplayer" || tempCommand[0] == "pp")
        temp.push_back(12);
    // Print the players weapon
    else if (tempCommand[0] == "pplayerweapon" || tempCommand[0] == "ppw")
        temp.push_back(120);
    //print view inventory
    else if (tempCommand[0] == "viewinventory" || tempCommand[0] == "vi")
        temp.push_back(121);
    // View the swap abilities menu
    else if (tempCommand[0] == "swapabilities" || tempCommand[0] == "sab")
        temp.push_back(122);
    // Swap weapon
    else if (tempCommand[0] == "swapweapon" || tempCommand[0] == "sw")
        temp.push_back(123);
    // Use a consumable
    else if (tempCommand[0] == "useconsumable" || tempCommand[0] == "ucon")
        temp.push_back(124);

    // Print the monsters detailed stats
    else if (tempCommand[0] == "pmonster" || tempCommand[0] == "pm")
        temp.push_back(13);
    // Print the monsters weapon
    else if (tempCommand[0] == "pmonsterweapon" || tempCommand[0] == "pmw")
        temp.push_back(130);
    // Print the monsters gold
    else if (tempCommand[0] == "pmonstergold" || tempCommand[0] == "pmg")
        temp.push_back(131);
    // Print all the consumables in the csv
    else if (tempCommand[0] == "pconsumables" || tempCommand[0] == "pcon")
        temp.push_back(14);
    // Prints all the abilities in the csv
    else if (tempCommand[0] == "pabilities" || tempCommand[0] == "pa")
        temp.push_back(16);
    //Print all items in chest inventory
    else if(tempCommand[0] == "viewChest" || tempCommand[0] == "vch")
        temp.push_back(17);
    else if(tempCommand[0] == "OpenChest" || tempCommand[0] == "och")
        temp.push_back(171);

    /** Create object prefixed with 2 */
    else if (tempCommand[0] == "makweapon" || tempCommand[0] == "mw")
        temp.push_back(20);
    // Make a player with a chosen race
    else if (tempCommand[0] == "makeplayer" || tempCommand[0] == "mp")
        temp.push_back(21);
    // Increase the players level by 1
    else if (tempCommand[0] == "levelup" || tempCommand[0] == "lvl")
        temp.push_back(210);
    // Make an ability and add it to the players inventory
    else if (tempCommand[0] == "pmakeability" || tempCommand[0] == "mpab")
        temp.push_back(211);
    // Make a consumable and add it to the players inventory
    else if (tempCommand[0] == "mpcon")
        temp.push_back(212);
    // Make a weapon and add it to the players inventory
    else if (tempCommand[0] == "mpw")
        temp.push_back(213);

    else if (tempCommand[0] == "makemonster" || tempCommand[0] == "mm")
        temp.push_back(22);
    // Start combat
    else if (tempCommand[0] == "makecombat" || tempCommand[0] == "mc")
        temp.push_back(23);
    // Make a consumable, also needs an index.
    else if (tempCommand[0] == "makeconsumable" || tempCommand[0] == "mcon")
        temp.push_back(24);
    // make a shop
    else if (tempCommand[0] == "makeshop" || tempCommand[0] == "ms")
        temp.push_back(25);
    else if (tempCommand[0] == "makechest" || tempCommand[0] == "mch")
        temp.push_back(27);
    /** debugging gets a prefix of 9 */
    else if (tempCommand[0] == "clear")
        temp.push_back(90);
    // add x to the players current experience
    else if (tempCommand[0] == "addexperience" || tempCommand[0] == "xp")
        temp.push_back(91);
    // print the damage done from a normal weapon attack by the player
    else if (tempCommand[0] == "atk")
        temp.push_back(92);

    else if(tempCommand[0] == "mainmenu" || tempCommand[0] == "mmenu")
        temp.push_back(93);
    else if(tempCommand[0] == "enterroom" || tempCommand[0] == "er")
        temp.push_back(96);
    else if(tempCommand[0] == "setlevel" || tempCommand[0] == "sl")
        temp.push_back(95);
    else if(tempCommand[0] == "game" || tempCommand[0] == "eg")
        temp.push_back(99);
    // GTFO
    else if (tempCommand[0] == "exit" || tempCommand[0] == "quit"
             || tempCommand[0] == "e")
        temp.push_back(0);

    // If no valid command was entered
    else {
        temp.push_back(-1);
        return temp;
    }
    // Remove the command  string
    tempCommand.erase(tempCommand.begin());
    // Pushback all the numbers remaining in the command
    if (!tempCommand.empty()) {
        for (auto i : tempCommand) {
            if(print::is_number(i)) {
                temp.push_back(std::stoi(i));
            }
        }
    }

    if(temp.empty())
        temp.push_back(-1);

    temp.shrink_to_fit();

    return temp;
}


void testManager::mainMenu() {
    // Make the main menu taller to account for the buttons
    system("resize -s 41 80");

    std::ifstream toRead;
    std::string line;
    std::vector<std::string> logo;
    // Read in the Logo and store each line in the logo std::vector<std::string>
    toRead.open(DIR_DOTS_LOGO);
    while(getline(toRead, line)) {
        logo.push_back(line);
    }
    toRead.close();

    logo.shrink_to_fit();

    // Read in the intro story that plays after the logo comes up
    std::vector<std::string> introText;
    toRead.open(DIR_INTRO);
    while(!toRead.eof()) {
        getline(toRead, line);
        introText.push_back(line);
    }

    toRead.close();
    introText.shrink_to_fit();

    // Fade to white
    // printf '\e[48;2;r;g;bm'  0 -255
    for(int i = 0; i < 255; i += 2) {
        std::string bgColour = "printf '\e[48;2;";
        bgColour.append(std::to_string(i) + ";");
        bgColour.append(std::to_string(i) + ";");
        bgColour.append(std::to_string(i) + "m';");

        char sysCommand[bgColour.length()];

        strcpy(sysCommand, bgColour.c_str());

        system(sysCommand);

        for(int f = 0; f < 41; f++)
            std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::microseconds(2000));
    }
    // Pause for dramatic effect
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // Fade to black
    for (int i = 255; i > 3; i -= 3) {
        system("clear");

        std::string bgColour = "printf '\e[48;2;";
        bgColour.append(std::to_string(i) + ";");
        bgColour.append(std::to_string(i) + ";");
        bgColour.append(std::to_string(i) + "m';");

        char sysCommand[bgColour.length()];

        strcpy(sysCommand, bgColour.c_str());

        system(sysCommand);

        for(int i = 0; i < 30; i++)
            std::cout<<std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(5000));
    }


    /** Bring the logo up on the screen */
    for(unsigned int i = 1; i < logo.size(); i ++) {
        system("clear");

        for(unsigned int e = logo.size(); e > i; e--) {
            std::cout << std::endl;
        }
        for(unsigned int row = 0; row < i; row++) {
            if (row == 0) {
                print::textColour(print::C_WHITE);
            }

            else if(row == 11) {
                print::textColour(print::C_BROWN);
            }

            else  if(row == 21) {
                print::textColour(print::C_RED);
            }

            std::cout << logo[row] << "\n";
        }
        std::this_thread::sleep_for(std::chrono::microseconds(160000));
    }
    // Reset the colour of the text
    print::textColour(print::C_DEFAULT);
    std::cout << std::endl << std::endl;


    /** Actual main menu part */

    std::vector<std::string> menuButtons;
    int input;
    // Read in the buttons for the main menu
    toRead.open(DIR_MM_BUTTONS);
    while(!toRead.eof()) {
        getline(toRead, line);
        menuButtons.push_back(line);
    }
    toRead.close();
    menuButtons.shrink_to_fit();

    // Reprint the logo on the screen with the buttons beneath
    for(unsigned int row = 0; row < logo.size(); row ++) {
        // Disciple
        if (row == 0) {
            print::textColour(print::C_WHITE);
        }
        // Of The
        else if(row == 11) {
            print::textColour(print::C_BROWN);
        }
        // Spire
        else  if(row == 21) {
            print::textColour(print::C_RED);
        }
        std::cout << logo[row] << "\n";
    }
    // Set text colour back to light grey
    print::textColour(print::C_DEFAULT);
    print::vec_time(menuButtons, 1);

    // Get the users first input
    std::cout << ">>> ";
    std::cin >> input;
    switch(input) {
    case 1:
        std::cout << "Continuing is currently under development" << std::endl;
        break;

    case 2:
        std::cout << "You you like to watch the intro story?\n"
                  "1. Yes    2. No\n"
                  ">>> ";
        std::cin >> input;
        switch(input) {
        case 1:
            /** Print all the intro text from the introText.txt */
            system("clear");
            print::vec(introText);

            // Once the intro story is done, scroll the text off the screen
            for(int i = 0; i < 41; i++) {
                std::cout << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(130));
            }
        // No break so that we can go right into character creation
        case 2:
            // Set the terminal back to "standard" size
            system("resize -s 31 80");
            playerPtr = characterCreation();
            break;

        case 3:
            /** MAKE HELP MENU FUNCTION*/
            std::cout << "Help menu is still under development" << std::endl;
            break;

        case 4:
            // Essentially Alt+F4's right out of here
            system("exit");
            break;

        default:
            std::cout << "Invalid command" << std::endl;
            break;
        }
    }
}

void testManager::saveGame() {
    playerPtr->save();
}

void testManager::loadGame() {

}

void testManager::enterRoom() {

}

void testManager::beginCombat(int l, int index) {
    std::string tName = "Cheeky McGee";
    monsterPtr = generateMonster(l, index, tName);
}

void testManager::chooseNextRoom() {

}

monster* testManager::generateMonster(int l) {
    int index = rand() % baseCharacter::allRaces->size();
    monster* temp = new monster("Twisted",
                                baseCharacter::allRaces->at(index).race,
                                baseCharacter::allRaces->at(index).maxHP,
                                baseCharacter::allRaces->at(index).mStats,
                                l);

    return temp;
}

monster* testManager::generateMonster(int l, int index) {
    monster* temp = new monster("Temp Monster",
                                baseCharacter::allRaces->at(index).race,
                                baseCharacter::allRaces->at(index).maxHP,
                                baseCharacter::allRaces->at(index).mStats,
                                l);

    return temp;
}

monster* testManager::generateMonster(int l, int index, std::string tName) {
    monster* temp = new monster(tName,
                                baseCharacter::allRaces->at(index).race,
                                baseCharacter::allRaces->at(index).maxHP,
                                baseCharacter::allRaces->at(index).mStats,
                                l );

    return temp;
}

// Default characterCreation(), has cout and cin
player* testManager::characterCreation() {
    player* temp;
    std::string command;
    system("clear;");

    print::str("Anyways adventurer, where do you come from? "
               "I can't quite place it.\n\n");
    // Show the user the races to choose from
    printRaces();
    // Set the cursor to box
    int tempRaceIndex = 0;
    while(true) {
        std::cout << "Race Index: ";
        // Select the race for your hero
        print::setCursor(true);
        command.clear();
        while(command[0] == '\n' || command.empty())
            getline(std::cin, command);
        print::setCursor(false);
        if(print::is_number(command)) {
            tempRaceIndex = std::stoi(command);
            if(tempRaceIndex >= 0 && tempRaceIndex <= 9) {
                break;
            } else {
                print::textColour(print::C_RED);
                print::str("What are you doing adventurer that's not a valid index?! Try again!");
                print::textColour(print::C_DEFAULT);
                std::cout << std::endl;
            }
        } else {
            print::textColour(print::C_RED);
            print::str("What are you doing adventurer that's not an index?! Try again!");
            print::textColour(print::C_DEFAULT);
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    // set the cursor to underscore
    // "Story"
    print::str("One " + baseCharacter::allRaces->at(tempRaceIndex).race +
               " coming right up!!!");


    std::this_thread::sleep_for(std::chrono::seconds(1));

    system("clear");

    print::str("*scurrying (and panting) can be heard as the hero approaches*\n");

    std::ifstream toRead;
    std::string line;
    std::vector<std::string> stairs;
    // Dramatic effect
    toRead.open(DIR_STAIRS_SPIRAL);
    while (getline(toRead, line))
        stairs.push_back(line);
    toRead.close();

    std::cout << "\n\n\n";
    /** Print the stairs txt file, and increase the speed
                                                    as the "animation" plays */
    print::vec_faster(stairs);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("clear");


    print::str("Finally! Your hero has arrived!\n"
               "What shall we call this one then?");

    print::setCursor(true);
    std::cout << std::endl;

    std::cout << "Name: ";
    // Enter the name for your hero
    std::cin >> command;
    print::setCursor(false);
    std::cout << std::endl;
    // Print the character that the user has made
    print::str("Cool a " + baseCharacter::allRaces->at(tempRaceIndex).race +
               " named " + command +
               " \nNo ones ever done that combo before I'm sure");

    print::str_time("...", 600);

    print::str("Anyways!\nONWARD TO STAT SELECTION!");

    std::cout << std::endl;

    // Set the temp player to what the user has selected, and genereate their hero
    temp = new player(command,
                      baseCharacter::allRaces->at(tempRaceIndex).race,
                      baseCharacter::allRaces->at(tempRaceIndex).maxHP,
                      baseCharacter::allRaces->at(tempRaceIndex).mStats);
    // The player needs to have a weapon before leveling up so that the damage
    // Power check doesn't seg fault
    temp->spawnWeapon(1);
    // Add 6 points of the users choice to the heros main stats
    temp->levelUp();
    // Give the player between 10 and 40 gold to start
    temp->setGold(rand() % 41 + 10);

    system("clear");

    // Make the player a weapon with their highest stat
    delete temp->getWeapon();

    int tMainStat = 0;
    int tMainStatIndex;
    // Check if str, dex, or int is highest for this heros race
    for (unsigned int i = 0; i < temp->getStatBonuses().size(); i++) {
        if (temp->getStats()[i] > tMainStat) {
            tMainStat = temp->getStats()[i];
            tMainStatIndex = i;
        }
        if (i == 2 && temp->getStats()[i] > tMainStat
                && temp->getStats()[0] < temp->getStats()[i]) {
            tMainStat = temp->getStats()[i];
            tMainStatIndex = i;
        }
    }
    // [0] statReq : [1] statAmount : [2] levelReq
    std::vector<int> sReq;
    sReq.push_back(tMainStatIndex);
    sReq.push_back(temp->getStats()[tMainStatIndex]);
    sReq.push_back(temp->getLevel());

    // Equip the hero with a weapon that uses their highest stat
    temp->setWeapon(new weapon(sReq));
    // Add an ability to the heros active abilities at level 1,
    // and the heros highest stat
    std::vector<ability*> tempAbil;
    std::vector<consumable*> tempCon;
    for(int i = 0; i < 5; i++)
        tempCon.push_back(new consumable(0));
    temp->getInventory()->addConsumables(tempCon);
    tempAbil.push_back(new ability(1, tMainStatIndex));
    temp->setActiveAbilities(tempAbil);

    return temp;
}
// Overloaded characterCreation(), generates a player at given race index
player* testManager::characterCreation(int index) {
    player* temp = new player("Temp_Hero",
                              baseCharacter::allRaces->at(index).race,
                              baseCharacter::allRaces->at(index).maxHP,
                              baseCharacter::allRaces->at(index).mStats);


    int tMainStat = 0;
    int tMainStatIndex;
    // Check if str, dex, or int is highest for that race
    for (unsigned int i = 0; i < temp->getStatBonuses().size(); i++) {
        if (temp->getStats()[i] > tMainStat) {
            tMainStat = temp->getStats()[i];
            tMainStatIndex = i;
        }
        if (i == 2 && temp->getStats()[i] > tMainStat
                && temp->getStats()[0] < temp->getStats()[i]) {
            tMainStat = temp->getStats()[i];
            tMainStatIndex = i;
        }
    }
    std::vector<int> sReq;
    sReq.push_back(tMainStatIndex);
    sReq.push_back(temp->getStats()[tMainStatIndex]);
    sReq.push_back(temp->getLevel());
    // Equip weapon made just for our player
    temp->setWeapon(new weapon(sReq));

    std::vector<ability*> tempAbil;
    tempAbil.push_back(new ability(1, tMainStatIndex));
    temp->setActiveAbilities(tempAbil);

    return temp;
}
