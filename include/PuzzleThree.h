/**
    @author
    @brief
*/

#ifndef PUZZLETHREE_H
#define PUZZLETHREE_H
#include "Puzzle.h"
#include "PuzzleUtils.h"
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <utility>
#include <vector>
#include <iomanip>
#include <cctype>
#include <list>
#include <fstream>
#include <ctime>
#include <algorithm>

class PuzzleThree : public Puzzle {
public:
    PuzzleThree();
    virtual ~PuzzleThree();
    void displayStartingMessage();
    void displayGoal();
    void displayConsequence();
    void mainGame();
    bool getResult();

    /**
     *  @brief  create a board of characters
     */
    void createCharBoard();

    /**
     *  @brief  display the available characters on the board
     */
    void displayCharBoard();

    /**
     *  @brief  determine if the character is on the board
     *  @param  c   character to check if it exists on the board
     *  @return true if it exists, otherwise false
     */
    bool isCharAvailable(char c);

    /**
     *  @brief  collect all the indexes or position
     *          of the characaters in the phrase that matches
     *          target character
     *  @param  c   target character to search for in the phrase
     *          macthingIndex   collecetion of indexes of the
     *                          characters in the phrase that
     *                          match the target character
     */
    void getPhraseIndex(char c,
                        std::list<int>* matchingIndex);

    /**
     *  @brief  reveal the character in the blank word (phrase to guess)
     *  @param  c   target character to reveal in the wordPlay
     *          wordPlay    the phrase the player is trying to
     *                      fill in (blank phrase)
     *          matchingIndex   collection of indexes or position of
     *                          characters to reveal
     */
    void revealChars(char c,
                     std::string *wordPlay,
                     std::list<int> *matchingIndex);

    /**
     *  @brief  display bomb that represents the number of attempt left
     */
    void displayBomb();


    /**
     *  @brief  check if the generated phrase to guess matches
     *          the phrase the player has guessed so far
     *  @param  wordPlay    the phrase the player is trying to fill in
     *                      (blank phrase)
     *          phrase      random phrase to guess
     *  @return true if they are the same, false otherwise
     */
    bool areWordsSame(std::string *wordPlay,
                      std::string *phrase);

    /**
     *  @brief  display the blank phrase the player has to fill in
     *  @param  wordPlay   the phrase the player is trying to
     *                      fill in (blank phrase)
     */
    void displayWordToGuess(std::string wordPlay);

    /**
     *  @brief  generate a random phrase from a list of
     *          phrases in the text file
     *  @return random phrase
     */
    std::string generatePhrase();

    /**
     *  @brief  checks validity of user input
     *  @param  stringInput     string input of the
     *  @return -1      if player inputs only a space
     *                  or just presses enter
     *          -2      if player chooses a character
     *                  that is already chosen
     *          -3      if player chooses any invalid character
     *           if the player chose a valid character,
     *           it will return the key of that character
     */
    int checkInput(std::string stringInput);

    /**
     *  @brief  collect all the characters chosen
     *  @param  chosen character
     */
    void collectChosenChars(char charInput);

private:
    std::string PUZZLE_TITLE = "Decipher the Hidden Message Challenge";
    std::string ROOM_CHARACTER = "Vish\'ka";
    std::string phrase;
    int attemptLeft = 10;
    bool result = false;
    std::vector<char> characters = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', '-', '0', '1', '2',
        '3', '4', '5', '6', '7', '8', '9'
    };
    std::map<int, char> charBoard;
    std::map<int, char> charsChosen;
};

#endif // PUZZLETHREE_H
