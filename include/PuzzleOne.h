/**
    @author
    @brief
*/

#ifndef PUZZLEONE_H
#define PUZZLEONE_H
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include "Puzzle.h"
#include "PuzzleUtils.h"


class PuzzleOne : public Puzzle {
public:
    PuzzleOne();
    virtual ~PuzzleOne();

    void displayStartingMessage();
    void displayConsequence();
    void displayGoal();
    void mainGame();
    bool getResult();

protected:
    /**
     *  @brief  create chests with random amount
     *          of gold in each
     */
    void createChests();

    /**
     *  @brief  display properly-formatted chests
     */
    void printChests();

    /**
     *  @brief  show the amount of gold in all chests
     *          in proper format
     */
    void openAllChests();

    /**
     *  @brief  determine if chest exists or not
     *  @param  id    id of the chest the player wants to pick
     *  @return true if it exists, false otherwise
     */
    bool doesChestExist(int id);

    /**
     *  @brief  player picks a chest
     *  @param  id      id of the chest the player wants to pick
     *          player  player who picks the chest.
     *                  true if human, false if computer
     */
    void pickChest(int id, bool player);

    /**
     *  @brief  computer picks random chest
     */
    void compPickChest();


    /**
     *  @brief  determine winner,
     *          display congratulatory message
     */
    void getWinner();


private:
    struct Chest {
        int id;
        int numOfGold;
    };
    std::string PUZZLE_TITLE = "Price Beat Challenge";
    std::string ROOM_CHARACTER = "Malachi the Dwarf";
    int maxNumOfGold = 10000;
    int numOfChests = 70;
    int humanPlayerScore = 0;
    int compPlayerScore = 0;
    int maximumPoints = 10;
    std::vector<Chest>chests;
    Chest humanPick;
    Chest compPick;
    bool result = false;
};

#endif // PUZZLEONE_H
