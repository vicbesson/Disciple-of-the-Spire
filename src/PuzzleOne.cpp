#include "PuzzleOne.h"
#include <vector>
#include <list>
#include <string>
#include <algorithm>

PuzzleOne::PuzzleOne() {
    createChests();
}


PuzzleOne::~PuzzleOne() {}


// displays the title and the mechanics of the puzzle
void PuzzleOne::displayStartingMessage() {
    std::cout << PUZZLE_TITLE << "\n\n"
              << ROOM_CHARACTER << " "
              << "challenges you in a one-on-one match.\n"
              << "For every round, both of you will pick a chest "
              << "that contains gold bars.\n"
              << "Whoever gets the most gold gets a point.\n"
              << "The player who earns " << maximumPoints
              << " points first wins the game.\n";
    std::cout << std::endl;
}


// displays the goal of the puzzle
void PuzzleOne::displayGoal() {
    std::cout << "\nGoal: Beat " << ROOM_CHARACTER << std::endl;
}


// displays the consequence of the puzzle
void PuzzleOne::displayConsequence() {
    std::cout << "Win, you get 10 golds." << std::endl;
    std::cout << "Lose, you lose 10 golds." << std::endl;
}


// create chests
void PuzzleOne::createChests() {
    srand(time(NULL));
    for (int i = 0; i < numOfChests; i++) {
        Chest c;
        c.id = i+1;
        c.numOfGold = PuzzleUtils::randomizer(maxNumOfGold);
        chests.push_back(c);
    }
}



// get result
bool PuzzleOne::getResult() {
    return result;
}


// print properly-formatted chests
void PuzzleOne::printChests() {
    std::list<int> chestNum;
    for (Chest c : chests) {
        chestNum.push_back(c.id);
    }


    std::cout << "\n\tChests:\n";

    int i = 1;
    int w = PuzzleUtils::getIntWidth(numOfChests);

    std::cout << "\t";
    while (i <= numOfChests) {
        if ( chestNum.front() == i ) {
            std::cout << i << "\t";
            chestNum.pop_front();
        } else {
            std::cout << std::setfill('-') << std::setw(w) << "\t";
        }


        if ( i%5 == 0 ) {
            std::cout << std::endl << "\t";
        }

        i++;
    }
}


// reveal the amount of gold content in
// all chests in proper format
void PuzzleOne::openAllChests() {
    std::list<Chest> chestList;
    for (Chest c : chests) {
        chestList.push_back(c);
    }

    std::cout << "\n\tChests opened:\n";

    int i = 1;
    int w = PuzzleUtils::getIntWidth(maxNumOfGold);

    std::cout << "\t";
    while (i <= numOfChests) {
        if ( chestList.front().id == i ) {
            std::cout << chestList.front().numOfGold << "\t";
            chestList.pop_front();
        } else {
            std::cout << std::setw(w) << " " << "\t";
        }

        if ( i%5 == 0 ) {
            std::cout << std::endl << "\t";
        }
        i++;
    }
    //std::cout << "\n" << chests[1].numOfGold
    //<< "\t" << chests[chests.size()-2].numOfGold;
}

// determine if the chest does exist
bool PuzzleOne::doesChestExist(int id) {
    for (int unsigned i = 0; i < chests.size(); ++i) {
        if (chests[i].id == id) {
            return true;
        }
    }
    std::cout << "Chest number does not exist!\n";
    return false;
}


// pick chest and stores pick
void PuzzleOne::pickChest(int id, bool player) {
    for (int unsigned i = 0; i < chests.size(); ++i) {
        if (chests[i].id == id) {
            if (player) {
                humanPick = chests[i];
            } else {
                compPick = chests[i];
            }
            chests.erase(chests.begin()+i);
            return;
        }
    }
}

// computer picks chest
void PuzzleOne::compPickChest() {
    srand(time(NULL));
    std::vector<Chest>temp;
    for (Chest c : chests) {
        temp.push_back(c);
    }
    int i = 0;
    do {
        std::random_shuffle(temp.begin(), temp.end());
        i++;
    } while ( i < (numOfChests) / 2 );


    int chestID = temp.back().id;
    pickChest(chestID, false);
    std::cout << std::endl;
    std::cout << ROOM_CHARACTER <<"\'s pick: "
              << compPick.id << std::endl;
}


// determine winner, display congratulatory message
void PuzzleOne::getWinner() {
    if (humanPlayerScore == maximumPoints && compPlayerScore != maximumPoints) {
        std::cout << "\nYou win" << std::endl;
        result = true;
    } else if (humanPlayerScore != maximumPoints
               && compPlayerScore == maximumPoints) {
        std::cout << "\n" << ROOM_CHARACTER << " wins! You lose." << std::endl;
    } else {
        std::cout << "Draw" << std::endl;
    }
}

// game proper
void PuzzleOne::mainGame() {
    std::string choiceStr;
    int choiceInt;
    int highestScore = -1;
    int humanTurn = 0;
    int compTurn = 0;
    bool human = true;

    this->displayStartingMessage();
    this->displayConsequence();
    this->displayGoal();
    std::cout << "\n\n";
    printChests();
    //openAllChests();

    // checks validity of the input
    /*
    if(isChoiceInt(choiceStr) == false){
        loop = true;
    } else {
        choiceInt = std::stoi(choiceStr);
        loop = !isChoiceWithinBounds(choiceInt);
    }
    */
    do {
        // human vs comp take turn
        if (human) {
            do {
                std::cout << "\nEnter chest number of your choice: ";
                std::cin >> choiceStr;
                // checks if choice is a digit or not
                if ( !PuzzleUtils::isChoiceInt(choiceStr) ) {
                    std::cout << "Invalid choice!\n";
                }
            } while (PuzzleUtils::isChoiceInt(choiceStr) == false);

            // check if choice is a large number
            try {
                choiceInt = std::stoi(choiceStr);
            } catch ( const std::exception &e ) {
                std::cerr << "Invalid choice!" << std::endl;
                continue;
            }


            // check if choice exists
            if ( doesChestExist(choiceInt) == true ) {
                pickChest(choiceInt, true);
                humanTurn++;
                human = false;
                std::cout << "Chest #" << humanPick.id
                          << " contains " << humanPick.numOfGold
                          << " gold bars." << std::endl;
            } else {
                continue;
            }
        } else {
            compPickChest();
            compTurn++;
            human = true;
            std::cout << "Chest #" << compPick.id
                      << " contains " << compPick.numOfGold
                      << " gold bars." << std::endl;
        }

        // if every one has an equal turn, compare numOfGold
        if (humanTurn == compTurn) {
            // scoring
            if (humanPick.numOfGold > compPick.numOfGold) {
                humanPlayerScore++;
            } else if (humanPick.numOfGold < compPick.numOfGold) {
                compPlayerScore++;
            } else {
                break;
            }


            std::cout << "\nScore: " << std::endl;
            std::cout << "You" << std::setfill('.')
                      << std::setw(30 - 3) << humanPlayerScore
                      << std::endl;
            std::cout << ROOM_CHARACTER << std::setfill('.')
                      << std::setw(30 - ROOM_CHARACTER.length())
                      << compPlayerScore << std::endl;
            printChests();
        }

        highestScore = std::max(humanPlayerScore, compPlayerScore);
    } while ( highestScore < maximumPoints );

    getWinner();
    //openAllChests();
}










