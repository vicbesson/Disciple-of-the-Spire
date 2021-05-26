/**
    @author
    @brief
*/

#ifndef PUZZLETWO_H
#define PUZZLETWO_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <list>
#include <iomanip>
#include <iterator>
#include <ctime>
#include "Puzzle.h"
#include "PuzzleUtils.h"


class PuzzleTwo : public Puzzle {
public:
    PuzzleTwo();
    virtual ~PuzzleTwo();

    void displayStartingMessage();
    void displayGoal();
    void displayConsequence();
    void mainGame();
    bool getResult();

    /**
     *  @brief  display all the cards in the deck
     *          with the content facing down
     */
    void layCards();

    /**
     *  @brief  create or initialize a deck of card
     *          with each card having 0 id
     */
    void createDeck();

    /**
     *  @brief  shuffle the cards in the deck
     *          and reassign card ids
     */
    void shuffleDeck();

    /**
     *  @brief  pick a random card from the deck
     *          that will serve as a reference card
     *          that the player will attempt to match
     */
    void getReferenceCard();

    /**
     *  @brief  check to see if the card exists based on the id
     *  @param  id    id of the card to search
     *  @return true if the card exists, false otherwise
     */
    bool doesCardExist(int id);

    /**
     *  @brief  pick a card from the deck based on the id
     *  @param  id    id of the card to pick
     */
    void pickCard(int id);

    /**
     *  @brief  determine the maximum number of character
     *          a string figure can have. This is for
     *          formatting purposes
     *  @return  returns the maximum number of character
     *           of a vector of string
     */
    int maxCharNum();

    /**
     *  @brief  show the contents or figure of the
     *          cards left in the deck
     */
    void showCards();

    /**
     *  @brief  get the number of attempt left
     *  @return attempt left
     */
    int getAttemptLeft();

private:
    struct Card {
        int id;
        std::string figure;
    };
    std::string PUZZLE_TITLE = "Matching Card Challenge";
    std::string ROOM_CHARACTER = "Cohen the Magician";
    int attemptLeft = 12;
    Card referenceCard;
    Card pickedCard;
    bool result = false;
    std::vector<Card> deck;
    std::vector<int> cardIDs;
    std::vector<std::string> figure = {
        "Basilisk",
        "Mermaid",
        "Kraken",
        "Werewolf",
        "Fairy",
        "Rafflesia",
        "Sceptre",
        "Crown",
        "The Evil Ring",
        "Archer",
        "Scroll",
        "Pendant",
        "Three-Eyed Raven",
        "Winged Dragon",
        "Ametyst",
        "Sundial",
        "Golden Compass",
        "The Great Sword",
        "Dagger",
        "Atlas",
        "Cornucopia",
        "The Headless Man",
        "Imp",
        "Ghoul",
        "Ogre"
    };
};

#endif // PUZZLETWO_H
