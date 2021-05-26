/**
    @author
    @brief
*/

#ifndef PUZZLEMANAGER_H
#define PUZZLEMANAGER_H
#include "player.h"
#include "Puzzle.h"
#include "Puzzle.h"
#include "PuzzleOne.h"
#include "PuzzleTwo.h"
#include "PuzzleThree.h"
#include "PuzzleFour.h"
#include <vector>
#include <ctime>
#include <random>

class puzzleManager {
public:
    puzzleManager();
    virtual ~puzzleManager();
    bool startPuzzle(player* myPlayer);
    //std::vector<Puzzle*> getPuzzles();
    std::vector<int> getPuzzlesLeft();
private:
    //std::vector<Puzzle*> puzzles;
    bool puzzleOne(player* myPlayer);
    bool puzzleTwo(player* myPlayer);
    bool puzzleThree(player* myPlayer);
    bool puzzleFour(player* myPlayer);
    bool puzzleFive(player* myPlayer);
    std::vector<int> puzzlesLeft;
    const int numOfPuzzles = 5;

};

#endif // PUZZLEMANAGER_H
