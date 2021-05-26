/**
    @author
    @brief
*/

#include "PuzzleUtils.h"
#include <string>

PuzzleUtils::PuzzleUtils() {}

PuzzleUtils::~PuzzleUtils() {}


int PuzzleUtils::randomizer(int randomizerLimit) {
    //srand(time(NULL));
    if (randomizerLimit > 0) {
        int seed;
        do {
            seed = (rand() % randomizerLimit) + 1;
        } while (seed <= 0);
        return seed;
    } else {
        return 0;
    }
}


int PuzzleUtils::getIntWidth(int num) {
    int counter = 0;
    while (num > 0) {
        num = num / 10;
        counter++;
    }
    return counter;
}


bool PuzzleUtils::isChoiceWithinBounds(int target,
                                       int lowestNum,
                                       int highestNum) {
    if (target < lowestNum || target > highestNum) {
        return false;
    } else {
        return true;
    }
}


bool PuzzleUtils::isChoiceInt(std::string choice) {
    for (int unsigned i = 0; i < choice.length(); ++i) {
        if (!isdigit(choice[i])) {
            return false;
        }
    }
    return true;
}




void PuzzleUtils::delayCharOutput(std::string stringInput) {
    for (char c : stringInput) {
        for (int i = 0; i <= 19999999 ; i++) { }
        std::cout << c;
    }
}


























