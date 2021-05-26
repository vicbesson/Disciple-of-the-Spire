#include "gameManager.h"
/**   Initiate all static pointers */
std::vector<std::string>* weapon::allNames = new std::vector<std::string>;
std::vector<std::vector<std::string>>* roomManager::roomData =
                                       new std::vector<std::vector<std::string>>;
std::vector<baseCharacter::raceData>* baseCharacter::allRaces =
    new std::vector<baseCharacter::raceData>;
std::vector<std::vector<std::vector<ability::abilityData>>>*
ability::allAbilities = new
std::vector<std::vector<std::vector<ability::abilityData>>>;

gameManager::gameManager() {
    /** Read in data from docs/DATA/"file" into the static pointers */
    readInRaceData();
    readInWeapons();
    readInRooms();
    readInAbilities();
    print::initScreen();
}

gameManager::~gameManager() {
    delete weapon::allNames;
    delete roomManager::roomData;
    delete baseCharacter::allRaces;
    delete ability::allAbilities;
    delete playerPtr;
    delete currentRoom;
}

void gameManager::readInWeapons() {
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

void gameManager::readInRooms() {
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

void gameManager::readInAbilities() {
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

void gameManager::readInRaceData() {
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

void gameManager::printRaces() {
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

/**     MAIN LOOP     */
void gameManager::startGame() {
    mainMenu();
    currentRoom = new roomManager(playerPtr);
    currentRoom->enterRoom();
}

void gameManager::mainMenu() {
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

player* gameManager::characterCreation() {
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
