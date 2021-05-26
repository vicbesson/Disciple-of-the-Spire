/**
    @author
    @brief
*/

#ifndef PUZZLEFOUR_H
#define PUZZLEFOUR_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <random>
//#include <chrono>
//#include <thread>
#include "player.h"
#include "Puzzle.h"
#include "PuzzleUtils.h"

class PuzzleFour : public Puzzle {
    void displayStartingMessage();
    void displayGoal();
    void displayConsequence();

    /**
     *  @brief  create objects (to be put in the jars)
     */
    void storeInitialObjects(std::string filename);

    /**
     *  @brief  display unshuffled objects and their attributes
     */
    void printObjects();

    /**
     *  @brief  create empty jars or objects
     */
    void fillJars();

    /**
     *  @brief  determine number of empty jars
     *  @return number of empty jars
     */
    int numOfEmptyJars();

    /**
     *  @brief  determine number of jars with monsters in it
     *  @return number of jars with monster
     */
    int numOfMonsterJars();

    /**
     *  @brief  determine number of jars with rewards in it
     *  @return number of jars with rewards
     */
    int numOfRewardJars();

    /**
     *  @brief  randomly shuffle the elements (or objects)
     *          in the objects vector
     */
    void shuffleObjects();

    /**
     *  @brief      create a collection of jars that has the objects in it.
     *              Placement of the objects in the jar is based on
     *              whether or not shuffleObjects is called.
     *              By default, objects are placed into the jars based on their
     *              order in the text file. To make sure objects are randomly ordered
     *              call shuffleObjects() before createObjBoard()
     */
    void createObjBoard();


    /**
     *  @brief  display jars
     */
    void displayObjBoard();

    /**
     *  @brief  format string description that wraps,
     *          each character is displayed with delays
     *  @param  stringInput     string to display
     */
    void formatDescription(std::string stringInput);

    /**
     *  @brief  pick a jar
     *  @param  jarMum     id number of the jar picked
     */
    void pickAJar(int jarNum);


    /**
     *  @brief  display player stats or rewards collected
     */
    void displayPlayerStats();

    /**
     *  @brief  check if the player inputs a valid choice of jar
     *  @param  jarNum      number or id of jar picked
     *  @return -2  jarNum is not a digit
     *          -1  if jarNum or id is out of range
     *           0  if jar associated with the jarNum does not exist
     *          -3  if there is a runtime or compile error of any type
     *          if jarNum is valid, it returns the actual key of the
     *          jar associated with the jarNum.
     */
    int checkValidity(std::string jarNum);

    /**
     *  @brief  destroy or remove jars from possible choices
     *  @param  key     key or jarNum of the jar which contains
     *                  an explosive or trigger object like
     *                  dynamite, thunder, etc.
     *          jarCount    number of jars to renove or destroy
     *  @return true if it destroys the jar that contains tke key,
     *          otherwise false
     */
    bool destroyJars(int triggerKey, int jarCount);

    /**
     *  @brief  determine if the location of the key
     *          is in an even or odd-numbered jar
     *  @return 0   if it's even
     *          1   if it's odd
     */
    int clue();


    /**
     *  @brief  generate random id or jarNum that
     *          is still available (in the objBoard)
     *  @param  triggerKey  jarNum or id of the jar where the
     *                      object that calls this function is located
     *  @return return a random jarNum or id of the jar that is
     *          still available to be picked
     */
    int randomObjKey(int triggerKey);
    struct Object {
        int state;          // 0 empty, -1 danger, 1 reward
        std::string name;
        int impactOnHealth;
        int impactOnDexterity;
        int impactOnIntelligence;
        int impactOnSpeed;
        int impactOnGold;
        std::string description;
    };
    struct PuzzlePlayer {
        int totalHealth;
        int totalDex;
        int totalIntel;
        int totalSpeed;
        int totalGold;
        int totalImm;
        bool key;
    };
    PuzzlePlayer playerPuz;   // only to display the rewards collected so far
    player* myPlayer;
    std::string PUZZLE_TITLE = "The Pandora's Jar Challenge";
    std::string ROOM_CHARACTER = "The Voice";
    std::vector<Object> objects;
    std::map<int, Object> objBoard;
    std::map<int, Object> objChosen;
    int emptyJars;
    bool result = false;

public:
    PuzzleFour(std::string filename, int numOfEmptyJars, player* myPlayer);
    virtual ~PuzzleFour();
    void mainGame();
    bool getResult();
};

#endif // PUZZLEFOUR_H
