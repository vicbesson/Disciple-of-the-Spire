/**
    @author
    @brief
*/

#include "PuzzleTwo.h"
#include <list>
#include <string>

PuzzleTwo::PuzzleTwo() {
    // initialize cards ids
    for (unsigned int i = 0; i < figure.size(); ++i) {
        cardIDs.push_back(i + 1);
    }
    createDeck();
    shuffleDeck();
}

PuzzleTwo::~PuzzleTwo() {}


// displays the title and the mechanics of the puzzle
void PuzzleTwo::displayStartingMessage() {
    std::cout << PUZZLE_TITLE << std::endl << std::endl;
    std::cout << ROOM_CHARACTER << " "
              << "wants to deceive you!\n"
              << "There are 25 cards on the table. " << ROOM_CHARACTER << "\n"
              << "holds a card in his hand. Your task is to pick a card \n"
              << "from the deck of cards that will match the card he\'s \n"
              << "holding. You have " << attemptLeft <<  " chances to pick "
              << "the right card. \n"
              << "For every incorrect card you pick, the deck gets shuffled."
              << "\n\n";
    std::cout << "There are special cards in the deck:\n"
              << "   \'The Great Sword\' card gives you 2 additional attempts."
              << "\n"
              << "   \'The Evil Ring\' card will reduce your attempts by 2."
              << "\n"
              << "   \'The Headless Man\' card means game is over.\n";
    std::cout << std::endl;
}


// displays the goal of the puzzle
void PuzzleTwo::displayGoal() {
    std::cout << "\nGoal: Pick the card that matches the card \n"
              << ROOM_CHARACTER << " is holding." << std::endl;
}


// displays the consequence of the puzzle
void PuzzleTwo::displayConsequence() {
    std::cout << "Win this game and your speed increases by 10." << std::endl;
    std::cout << "Lose, your speed decreases by 10." << std::endl;
}


// get result
bool PuzzleTwo::getResult() {
    return result;
}


// display all the cards with the content facing down
void PuzzleTwo::layCards() {
    std::list<int> deckTemp;
    for (Card c : deck) {
        deckTemp.push_back(c.id);
    }

    std::cout << "\n\n\tCards:\n\n";

    int i = 1, numOfCards = figure.size();
    int w = PuzzleUtils::getIntWidth(numOfCards);

    std::cout << "\t";
    while (i <= numOfCards) {
        if ( deckTemp.front() == i ) {
            std::cout << i << "\t";
            deckTemp.pop_front();
        } else {
            std::cout << std::setfill('-') << std::setw(w) << "\t";
        }


        if ( i%5 == 0 ) {
            std::cout << std::endl << "\t";
        }

        i++;
    }
    std::cout << "\n\n";
}


// create unshuffled cards in the deck
void PuzzleTwo::createDeck() {
    for (unsigned int i = 0; i < figure.size(); i++) {
        Card c;
        c.id = 0;
        c.figure = figure[i];
        deck.push_back(c);
    }

    /*
    for(Card c : deck)
        std::cout << c.id << "..." << c.figure << std::endl;
    */
}


// shuffle the deck and reassign card ids
void PuzzleTwo::shuffleDeck() {
    srand(time(NULL));
    unsigned int i = 0;
    do {
        std::random_shuffle(deck.begin(), deck.end());
        i++;
    } while (i < (figure.size() / 2 ));

    //reassign ids based on shuffled cards
    i = 0;
    while (i < cardIDs.size()) {
        deck[i].id = cardIDs[i];
        i++;
    }

    /*
    for(Card c : deck)
        std::cout << c.id << "..." << c.figure << std::endl;
    */
}


// pick a card that will serve as a reference
// card for the player to match
void PuzzleTwo::getReferenceCard() {
    bool loop = true;
    do {
        int randomID = PuzzleUtils::randomizer(cardIDs.size());
        for (Card c : deck) {
            if (c.id == randomID) {
                if (c.figure == "The Evil Ring" ||
                        c.figure == "The Great Sword" ||
                        c.figure == "The Headless Man") {
                    loop = true;
                    continue;
                } else {
                    loop = false;
                    referenceCard = c;
                    break;
                }
            }
        }
    } while (loop);
}


// check to see if the card chosen exists
bool PuzzleTwo::doesCardExist(int id) {
    for (Card c : deck) {
        if (c.id == id) {
            return true;
        }
    }
    return false;
}


// pick a card from the deck
void PuzzleTwo::pickCard(int id) {
    // retrieve card
    for (unsigned int i = 0; i < deck.size(); i++) {
        if (deck[i].id == id) {
            for (unsigned int j = 0; j < cardIDs.size(); ++j) {
                if (cardIDs[j] == id) {
                    pickedCard = deck[i];
                    deck.erase(deck.begin()+i);
                    cardIDs.erase(cardIDs.begin()+j);
                }
            }
        }
    }
}


// determine the maximum number of characters a string figure
// can have. This is form formatting purposes
int PuzzleTwo::maxCharNum() {
    unsigned int maxNum = 0;
    for (unsigned int i = 0; i < figure.size(); ++i) {
        if ( maxNum < figure[i].length() ) {
            maxNum = figure[i].length();
        }
    }

    return maxNum;
}


// show the contents or figure on the card
void PuzzleTwo::showCards() {
    std::list<Card> cardList;
    for (Card c : deck) {
        cardList.push_back(c);
    }


    std::cout << "\n\tCards flipped:\n\n";

    int i = 1, numOfCards = figure.size();
    //int w = PuzzleUtils::getIntWidth(numOfCards);

    std::cout << std::setfill(' ') << std::setw(maxCharNum()+5);
    while (i <= numOfCards) {
        if ( cardList.front().id == i ) {
            //int figLength = cardList.front().figure.length();
            std::cout << cardList.front().figure
                      << std::setfill(' ')
                      << std::setw(maxCharNum()+5);
            cardList.pop_front();
        } else {
            std::cout << "*"
                      << std::setfill(' ')
                      << std::setw(maxCharNum()+5);
        }


        if ( i%5 == 0 ) {
            std::cout << std::endl
                      << std::setfill(' ')
                      << std::setw(maxCharNum()+5);
        }

        i++;
    }
    std::cout << "\n\n";
}


// get the number of attempt left
int PuzzleTwo::getAttemptLeft() {
    if (attemptLeft >= 0) {
        return attemptLeft;
    } else {
        return 0;
    }
}

// game proper
void PuzzleTwo::mainGame() {
    std::string choiceStr;
    int choiceInt;
    bool loop = true, isWinner = false;
    this->displayStartingMessage();
    this->displayConsequence();
    this->displayGoal();
    layCards();
    showCards();
    getReferenceCard();
    //std::cout << maxCharNum() << std::endl;

    //std::cout << deck[10].id <<std::endl;
    //std::cout << deck[10].figure << std::endl;

    do {
        std::cout << ROOM_CHARACTER << " is holding a \'" << referenceCard.figure <<
                  "\' card.\n"
                  << "Find " << referenceCard.figure << "\n";
        std::cout << "\nEnter card number of your choice: ";
        std::cin >> choiceStr;

        // if choice is not a digit
        if ( !PuzzleUtils::isChoiceInt(choiceStr) ) {
            std::cout << "Invalid choice!\n\n";
            continue;
        } else {
            // check if input is too big
            try {
                choiceInt = std::stoi(choiceStr);
            } catch ( const std::exception &e ) {
                std::cerr << "Invalid choice!\n\n";
                continue;
            }

            // check of card exists
            if ( doesCardExist(choiceInt) ) {
                pickCard(choiceInt);

                std::cout << "You've picked " << pickedCard.id << ": "
                          << pickedCard.figure << std::endl;


                if (pickedCard.figure == "The Great Sword") {
                    // if card picked is The Great Sword
                    attemptLeft += 2;
                    std::cout << "\nYou've got two additional attempts"
                              << "\nAttempt Left: " << getAttemptLeft();
                } else if (pickedCard.figure == "The Evil Ring") {
                    // if card picked is The Evil Ring
                    attemptLeft -= 2;
                    std::cout << "\nYou're number of attempts is reduced by 2"
                              << "\nAttempt Left: " << getAttemptLeft();
                } else if (pickedCard.figure == "The Headless Man") {
                    // if card picked is The Headless Man
                    std::cout << "\nGame Over\n";
                    loop = false;
                } else if (referenceCard.figure == pickedCard.figure) {
                    // if the picked card matches the referenced card
                    std::cout << "\nYou win! ";
                    isWinner = true;
                    loop = false;
                    result = true;
                } else {
                    shuffleDeck();
                    attemptLeft--;
                    std::cout << "\nDoes not match!\n"
                              << "\nDeck shuffling";
                    PuzzleUtils::delayCharOutput("...");
                    std::cout << "\nAttempt Left: "
                              << getAttemptLeft() << std::endl;
                }
                layCards();
                //showCards();


                //std::cout << pickedCard.id << std::endl;

                /*
                for(Card c : deck)
                    std::cout << c.id << "..." << c.figure << std::endl;

                for(int c : cardIDs)
                    std::cout << c << std::endl;
                */

            } else {
                std::cout << "Card does not exist\n\n";
            }
        }



        /*
        std::cout << std::boolalpha
                  << doesCardExist(choiceInt)
                  << std::endl;
          */
    } while (attemptLeft > 0 && loop);


    showCards();
    if (!isWinner) {
        std::cout << "You lost\n";
    }
    std::cout << std::endl;
}
