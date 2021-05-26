/**
    @author
    @brief
*/

#include "puzzleManager.h"

puzzleManager::puzzleManager() {
    for(unsigned int i = 1; i <= numOfPuzzles; ++i)
        puzzlesLeft.push_back(i);
}

puzzleManager::~puzzleManager() {

}


// Puzzle 1: Price Beat Challenge
bool puzzleManager::puzzleOne(player* myPlayer) {
    PuzzleOne *puzzle1 = new PuzzleOne;
    puzzle1->mainGame();
    bool result = puzzle1->getResult();
    if (result == true) {
        myPlayer->setGold(10);
    } else {
        myPlayer->setGold(-10);
    }
    delete puzzle1;
    return result;
}


// Puzzle 2: Matching Card Challenge
bool puzzleManager::puzzleTwo(player* myPlayer) {
    PuzzleTwo *puzzle2 = new PuzzleTwo;
    puzzle2->mainGame();
    bool result = puzzle2->getResult();
    if (result == true) {
        // player's speed +10
        std::vector<int> stats;
        stats.push_back(0); // str
        stats.push_back(0); // dex
        stats.push_back(0); // int
        stats.push_back(10); // speed
        myPlayer->addToStats(stats);
    } else {
        // player's speed -10
        std::vector<int> stats;
        stats.push_back(0); // str
        stats.push_back(0); // dex
        stats.push_back(0); // int
        stats.push_back(-10); // speed
        myPlayer->addToStats(stats);
    }
    delete puzzle2;
    return result;
}



// Puzzle 3: Decipher the Hidden Message Challenge
bool puzzleManager::puzzleThree(player* myPlayer) {
    PuzzleThree *puzzle3 = new PuzzleThree;
    puzzle3->mainGame();
    bool result = puzzle3->getResult();
    if (result == true) {
        // playyer's intellect +10
        std::vector<int> stats;
        stats.push_back(0); // str
        stats.push_back(0); // dex
        stats.push_back(10); // int
        stats.push_back(0); // speed
        myPlayer->addToStats(stats);
    } else {
        // player's intellect -10
        std::vector<int> stats;
        stats.push_back(0); // str
        stats.push_back(0); // dex
        stats.push_back(-10); // int
        stats.push_back(0); // speed
        myPlayer->addToStats(stats);
    }
    delete puzzle3;
    return result;
}



// Puzzle 4
bool puzzleManager::puzzleFour(player* myPlayer) {
    PuzzleFour *puzzle4;
    puzzle4 = new PuzzleFour("docs/DATA/puzzle4-objects.tsv", 16, myPlayer);
    puzzle4->mainGame();
    bool result = puzzle4->getResult();
    delete puzzle4;
    return result;
}


// Puzzle 5
bool puzzleManager::puzzleFive(player* myPlayer) {
    PuzzleFour *puzzle5;
    puzzle5 = new PuzzleFour("docs/DATA/puzzle5-objects.tsv", 13, myPlayer);
    puzzle5->mainGame();
    bool result = puzzle5->getResult();
    delete puzzle5;
    return result;
}


bool puzzleManager::startPuzzle(player* myPlayer) {
    bool result;
    // choose a random puzzle index
    srand(time(NULL));
    std::random_shuffle(puzzlesLeft.begin(), puzzlesLeft.end());
    int puzzleIndex = puzzlesLeft.back();
    // redirect to the main game of the puzzles
    switch(puzzleIndex) {
    case 1:
        result = puzzleOne(myPlayer);
        break;
    case 2:
        result = puzzleTwo(myPlayer);
        break;
    case 3:
        result = puzzleThree(myPlayer);
        break;
    case 4:
        result = puzzleFour(myPlayer);
        break;
    case 5:
        result = puzzleFive(myPlayer);
        break;
    default:
        break;
    }
    // reduce puzzLesLeft
    puzzlesLeft.pop_back();

    return result;
}

std::vector<int> puzzleManager::getPuzzlesLeft() {
    return puzzlesLeft;
}

/*
std::vector<Puzzle*> puzzleManager::getPuzzles() {
    return puzzles;
}*/
