/**
    @author
    @brief
*/

#include "PuzzleFour.h"
#include <vector>
#include <string>
#include <map>
#include <utility>
// filename //number of empty jars
PuzzleFour::PuzzleFour(std::string filename, int numOfEmptyJars, player* p) {
    emptyJars = numOfEmptyJars;
    //std::cout << "Number of empty jars: " << numOfEmptyJars;
    // initialize all the needed objects to be put into the jar
    storeInitialObjects(filename);

    // initialize player attributes
    playerPuz.totalHealth = 0;
    playerPuz.totalDex = 0;
    playerPuz.totalIntel = 0;
    playerPuz.totalSpeed = 0;
    playerPuz.totalGold = 0;
    playerPuz.totalImm = 0;
    playerPuz.key = false;

    myPlayer = p;
}



PuzzleFour::~PuzzleFour() {}



// displays the title and the mechanics of the puzzle
void PuzzleFour::displayStartingMessage() {
    std::cout << PUZZLE_TITLE << std::endl << std::endl;
    std::cout << "You found yourself stuck in this room. "
              << "The door you\njust came in gets locked, "
              << "and the door on the other side\nof the "
              << "room is also locked. The only way to unlock "
              << "the other door\nis to find its key in one of the "
              << objects.size() << " jars in the room.\n"
              << "It's not going to be easy though. "
              << "Monsters and catastrophe lurk in\n"
              << "some of the jars, but huge rewards awaits.\n\n";
}



// displays the goal of the puzzle
void PuzzleFour::displayGoal() {
    std::cout << "\nGoal: Find the key that unlocks the exit door."
              << std::endl;
}


// consequence of the player depends on the rewards collected
void PuzzleFour::displayConsequence() {}


// print each object's attributes
void PuzzleFour::printObjects() {
    for ( Object o : objects ) {
        std::cout << "state: " << o.state << std::endl;
        std::cout << "name: " << o.name << std::endl;
        std::cout << "health: " << o.impactOnHealth << std::endl;
        std::cout << "dexterity: " << o.impactOnDexterity << std::endl;
        std::cout << "intelligence: " << o.impactOnIntelligence << std::endl;
        std::cout << "speed: " << o.impactOnSpeed << std::endl;
        std::cout << "gold: " << o.impactOnGold << std::endl;
        std::cout << "description: " << o.description << std::endl;
        std::cout << std::endl;
    }
}


// get result
bool PuzzleFour::getResult() {
    return result;
}


// create objects (to be put in the jars)
// and store them in objects vector
void PuzzleFour::storeInitialObjects(std::string filename) {
    std::string tempString;
    std::ifstream infile;


    // open a file
    infile.open(filename.c_str());

    // delimeter of each field
    char delimiter = ';';

    if (!infile) {
        std::cerr << "\nUnable to open file\n";
        exit(1);
    }

    // scan each record from the file.
    // Each record represents an object
    while ( std::getline(infile, tempString, '\n') ) {
        std::istringstream iss(tempString);
        std::string token;
        Object obj;

        int i = 0;
        while (std::getline(iss, token, delimiter)) {
            switch (i) {
            case 0:
                obj.state = std::stoi(token);
                break;
            case 1:
                obj.name = token;
                break;
            case 2:
                obj.impactOnHealth = std::stoi(token);
                break;
            case 3:
                obj.impactOnDexterity = std::stoi(token);
                break;
            case 4:
                obj.impactOnIntelligence = std::stoi(token);
                break;
            case 5:
                obj.impactOnSpeed = std::stoi(token);
                break;
            case 6:
                obj.impactOnGold = std::stoi(token);
                break;
            case 7:
                obj.description = token;
                break;
            default:
                break;
            }

            ++i;
        }
        objects.push_back(obj);
    }
    infile.close();

    // create empty objects to fill the rest of the jars
    fillJars();
}



// create empty objects or jars
void PuzzleFour::fillJars() {
    int startingIndex = objects.size();
    int totalJars = objects.size() + emptyJars;

    for (int i = startingIndex; i < totalJars; ++i) {
        Object obj;
        obj.state = 0;
        obj.name = "Empty";
        obj.impactOnHealth = 0;
        obj.impactOnDexterity = 0;
        obj.impactOnIntelligence = 0;
        obj.impactOnSpeed = 0;
        obj.impactOnGold = 0;
        obj.description = "Jar is empty.";
        objects.push_back(obj);
    }
}



// return number of empty jars
int PuzzleFour::numOfEmptyJars() {
    int total = 0;
    for (Object obj : objects) {
        if (obj.state == 0)
            ++total;
    }
    return total;
}



// return number of jars with monsters or catastrophe in it
int PuzzleFour::numOfMonsterJars() {
    int total = 0;
    for (Object obj : objects) {
        if (obj.state == -1)
            ++total;
    }
    return total;
}



// return number of jars with rewards in it
int PuzzleFour::numOfRewardJars() {
    int total = 0;
    for (Object obj : objects) {
        if (obj.state == 1)
            ++total;
    }
    return total;
}



// randomly shuffle the elements (or objects) in the objects vector
void PuzzleFour::shuffleObjects() {
    int i = 0;
    while (i < (PuzzleUtils::randomizer(10) + 1)) {
        srand(time(NULL));
        std::random_shuffle(objects.begin(), objects.end());
        ++i;
    }
}


/*
    create a collection of jars that has the objects in it.
    Placement of the objects in the jar is based on
    whether or not shuffleObjects is called.
    By default, objects are placed into the jars based on their
    order in the text file. To make sure objects are randomly ordered
    call shuffleObjects() before createObjBoard()
*/
void PuzzleFour::createObjBoard() {
    std::pair<int, Object> x;

    for (unsigned int i = 1; i <= objects.size(); ++i) {
        x = std::make_pair(i, objects[i-1]);
        objBoard.insert(x);
    }
}



// display jars
void PuzzleFour::displayObjBoard() {
    std::map<int, Object>::iterator oPtr = objBoard.begin();
    unsigned int i = 1;
    std::cout << "\n\n\tJars left: " << objBoard.size();
    std::cout << "\n\t";
    std::cout << std::setfill('.') << std::setw(14 * 4) << "\n\t\t";
    unsigned int w = PuzzleUtils::getIntWidth(objBoard.size());

    while (i <= objects.size()) {
        if (i == oPtr->first) {
            std::cout << oPtr->first
                      << std::setfill(' ')
                      << std::setw(w)
                      << "\t";
            ++oPtr;
        } else {
            std::cout << std::setfill('-')
                      << std::setw(w)
                      << "\t";
        }


        if ( i%5 == 0 ) {
            std::cout << std::endl << "\t\t";
        }
        ++i;
    }
    std::cout << "\n";
}



// format string description that wraps the text.
// Each character is displayed with delays
void PuzzleFour::formatDescription(std::string stringInput) {
    int freq = 0;
    for (char c : stringInput) {
        for (int i = 0; i <= 19999999 ; i++) { }
        std::cout << c;

        if ( c == ' ' ) {
            ++freq;
            if ( freq == 10 ) {
                std::cout << "\n";
                freq = 0;
            }
        }
    }
}



// display player stats
void PuzzleFour::displayPlayerStats() {
    std::cout << "\n\n\n";
    std::cout << "\n  Total Rewards Collected:"
              << "\n  Health:       " << playerPuz.totalHealth
              << "\t  Dexterity:    " << playerPuz.totalDex
              << "\t  Intelligence: " << playerPuz.totalIntel
              << "\n  Speed:        " << playerPuz.totalSpeed
              << "\t  Gold:         " << playerPuz.totalGold
              << "\t  Immunity:     " << playerPuz.totalImm;
}




/// return 0    no key
/// return 1    key
// destroy jars
bool PuzzleFour::destroyJars(int triggerKey, int jarCount) {
    std::vector<int> index;
    for ( std::pair<int, Object> o  : objBoard ) {
        if ( o.first != triggerKey ) {
            index.push_back(o.first);
        }
    }


    srand(time(NULL));
    std::random_shuffle(index.begin(), index.end());

    int i = 0, damage = jarCount;
    while ( i < damage ) {
        if ( objBoard.size() > 0 ) {
            int randKey = index.back();
            std::map<int, Object>::iterator ptr = objBoard.find(randKey);
            Object obj = ptr->second;
            if ( obj.name == "key" ) {
                std::cout << std::endl;
                formatDescription(obj.description);
                PuzzleUtils::delayCharOutput("\n");
                objBoard.erase(randKey);
                return true;
            } else {
                objBoard.erase(randKey);
            }
            index.pop_back();
        }
        ++i;
    }

    return false;
}



// determine if the id of the jar/object that has the
// key in it is odd or even
int PuzzleFour::clue() {
    std::map<int, Object>::iterator ptr;
    Object obj;
    int keyID = -999;
    for (ptr = objBoard.begin(); ptr != objBoard.end(); ++ptr) {
        obj = ptr->second;
        if (obj.name == "key") {
            keyID = ptr->first;
        }
    }

    /// determine if the key is in oo or even numbered jar
    /// even
    if ( (keyID % 2) == 0 )
        return 0;
    else
        return 1;
}



// get random key of one of the remaining jars in the board
int PuzzleFour::randomObjKey(int triggerKey) {
    if (objBoard.size() > 0) {
        std::vector<int> index;
        std::map<int, Object>::iterator ptr;
        for ( ptr = objBoard.begin(); ptr != objBoard.end(); ++ptr ) {
            if ( ptr->first != triggerKey ) {
                index.push_back(ptr->first);
            }
        }

        srand(time(NULL));
        std::random_shuffle(index.begin(), index.end());

        //std::cout << "Hello World: " << index.front() << std::endl;

        /*
        for( int i : index )
          std::cout << i << ", ";
        */
        return index.front();
    }
    return 0;
}



// pick a jar
void PuzzleFour::pickAJar(int jarNum) {
    std::map<int, Object>::iterator oPtr;
    oPtr = objBoard.find(jarNum);

    int objKey = oPtr->first;
    Object objValue = oPtr->second;

    // insert chosen jar to objChosen
    objChosen.insert(std::pair<int, Object>(objKey, objValue));

    // display description
    std::cout << "Breaking jar #" << objKey;
    PuzzleUtils::delayCharOutput(" ...");
    std::cout << std::endl;
    formatDescription(objValue.description);
    PuzzleUtils::delayCharOutput("\n");


    // determine consequences


    if (objValue.name == "imm") {
        // immunity protects the player
        playerPuz.totalImm++;
    } else if (objValue.name == "dyn") {
        // dynamite destroys six jars
        playerPuz.key = destroyJars(objKey, 5);
    } else if (objValue.name == "thunder") {
        // thunder destroys four jars
        playerPuz.key = destroyJars(objKey, 3);
    } else if (objValue.name == "landmine") {
        // landmine destroys at most half of the jars in the board
        playerPuz.key = destroyJars(objKey, objBoard.size()/2);
    } else if (objValue.name == "goldMult") {
        // doubles the number of gold
        /*if (playerPuz.totalGold > 0) {
          playerPuz.totalGold *= 2;
          myPlayer->setGold(myPlayer->getGold());
        }*/
    } else if (objValue.name == "healthMult") {
        // doubles the number of health
        /*if (playerPuz.totalHealth > 0) {
          playerPuz.totalHealth *= 2;
        }*/
    } else if (objValue.name == "possessed") {
        // player randomly opens a jar
        int randIndex = randomObjKey(objKey);
        if (randIndex > 0)
            pickAJar(randIndex);
    } else if (objValue.name == "clue") {
        // determines if key is in an odd or even jar
        if (clue() == 0)
            formatDescription("The key is in an even-numbered jar");
        else
            formatDescription("The key is in an odd-numbered jar");
    } else if (objValue.name == "key") {
        // key
        playerPuz.key = true;
    } else {
        // testing purposes
    }

    // collect all attibute values of the object in the jar
    if ( (playerPuz.totalImm > 0) && (objValue.state == -1) ) {
        PuzzleUtils::delayCharOutput("The immunity necklace protects you!\n"
                                     "You've been spared.");
        PuzzleUtils::delayCharOutput("\nAny damage or harm inflicted by "
                                     "the monster or\ncatastrophe you "
                                     "just opened did not affect you.");
        --playerPuz.totalImm;
    } else {
        // cumulative
        playerPuz.totalHealth += objValue.impactOnHealth;
        playerPuz.totalDex += objValue.impactOnDexterity;
        playerPuz.totalIntel += objValue.impactOnIntelligence;
        playerPuz.totalSpeed += objValue.impactOnSpeed;
        playerPuz.totalGold += objValue.impactOnGold;
        // real-time stats
        std::vector<int> stats;
        stats.push_back(0); //str
        stats.push_back(objValue.impactOnDexterity); // dex
        stats.push_back(objValue.impactOnIntelligence); // int
        stats.push_back(objValue.impactOnSpeed); // speed
        myPlayer->addToStats(stats);
        myPlayer->setGold(objValue.impactOnGold); // gold
        // flips the value of health and make it as param og takeDamage()
        myPlayer->takeDamage(-1 * objValue.impactOnHealth);
    }
    // remove chosen jar from objBoard
    objBoard.erase(objKey);
}




// check if the chosen jar num is valid or not
int PuzzleFour::checkValidity(std::string jarNum) {
    // check is jarNum contains a non digit
    if (!PuzzleUtils::isChoiceInt(jarNum)) {
        return -2;
    } else {
        int key;
        try {
            key = std::stoi(jarNum);
        } catch ( const std::exception &e ) {
            return -3;
        }

        // check if key is within bounds
        if (!PuzzleUtils::isChoiceWithinBounds(key, 1, objects.size())) {
            return -1;
        } else {
            // check key if is in the objBoard
            if ( objBoard.count(key) > 0 )
                return key;
            else
                return 0;
        }
    }
}


// game proper
void PuzzleFour::mainGame() {
    this->displayStartingMessage();
    this->displayConsequence();
    this->displayGoal();
    //printObjects();
    //displayObjBoard();
    std::srand(time(NULL));
    shuffleObjects();
    createObjBoard();
    //displayPlayerStats();

    //print for debugging
    /*
        std::map<int, Object>::iterator o;
        for(o = objBoard.begin(); o != objBoard.end(); ++o )
        {
            std::cout << o->first << std::endl;
            std::cout << (o->second).name << std::endl;
        }
    */


    do {
        /// game proper
        displayPlayerStats();
        displayObjBoard();

        int jarNum;
        bool invalid = true;
        do {
            std::string choice;
            std::cout << "Jar to break: ";
            std::cin >> choice;

            switch ( checkValidity(choice) ) {
            case -2:
                std::cout << "Invalid input!\n";
                break;
            case -1:
                std::cout << "Jar does not exist.\n";
                break;
            case 0:
                std::cout << "Jar already broken.\n";
                break;
            case -3:
                std::cerr << "Invalid input!\n";
                break;
            default:
                jarNum = std::stoi(choice);
                invalid = false;
                break;
            }
        } while ( invalid );
        pickAJar(jarNum);
        //displayPlayerStats();
    } while ( playerPuz.key == false );

    if(playerPuz.key == true) {
        result = true;
    }
    displayObjBoard();
    /*
    std::cout << "Total num of jars: " << objects.size() << std::endl;
    std::cout << "Num of empty jars: " << numOfEmptyJars() << std::endl;
    std::cout << "Num of monster jars: " << numOfMonsterJars() << std::endl;
    std::cout << "Num of reward jars: " << numOfRewardJars() << std::endl;
    */
}































