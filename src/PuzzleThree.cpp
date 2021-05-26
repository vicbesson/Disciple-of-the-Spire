/**
    @author
    @brief
*/

#include "PuzzleThree.h"
#include <vector>
#include <string>
#include <list>
#include <utility>
#include <map>

// create or initialize character board
// generate random phrase
PuzzleThree::PuzzleThree() {
    createCharBoard();
    phrase = generatePhrase();
}



PuzzleThree::~PuzzleThree() {}



// displays the title and the mechanics of the puzzle
void PuzzleThree::displayStartingMessage() {
    std::cout << PUZZLE_TITLE << "\n\n";
    std::cout << "Time is running out!\n"
              << "Help " << ROOM_CHARACTER << " and yourself "
              << "escape by solving a word puzzle.\n"
              << "Enter the character you think is in the word "
              << "until you complete\n"
              << "the word. For every incorrect character, "
              << "part of the string of the bomb\n"
              << "is burnt.\n\n";
}



// displays the goal of the puzzle
void PuzzleThree::displayGoal() {
    std::cout << "\nGoal: Save " << ROOM_CHARACTER
              << " and yourself by completing the word puzzle.\n";
}



// displays the consequence of the puzzle
void PuzzleThree::displayConsequence() {
    std::cout << "Win this game and your "
              << "intelligence increases by 10.\n";
    std::cout << "Lose, your it decreases by 10.\n";
}



// get result
bool PuzzleThree::getResult() {
    return result;
}


// initialize character board.
// read all data in the character vector and initialize ids
void PuzzleThree::createCharBoard() {
    std::pair<int, char> x;

    for (unsigned int i = 1; i <= characters.size(); ++i) {
        // <id><element>
        x = std::make_pair(i, characters[i - 1]);
        charBoard.insert(x);
    }

    /*
    std::map<int, char>::iterator ptr;;

    for(ptr = charBoard.begin(); ptr != charBoard.end(); ++ptr)
        std::cout << ptr->first << " => " << ptr->second << "\n";
    */
}



// display character board in proper format
void PuzzleThree::displayCharBoard() {
    std::map<int, char>::iterator ptr = charBoard.begin();
    unsigned int i = 1;
    std::cout << "\n\n\t";
    std::cout << std::setfill('*')
              << std::setw(15 * 4)
              << "\n\t\t";

    while (i <= characters.size()) {
        if (i == ptr->first) {
            std::cout << char(toupper(ptr->second))
                      << "  ";
            ++ptr;
        } else {
            std::cout << "   ";
        }


        if ( i%15 == 0 ) {
            std::cout << std::endl << "\t\t";
        }

        ++i;
    }
    std::cout << "\n\t";
    std::cout << std::setfill('*') << std::setw(15 * 4) << "\n";
}



// check if the character is in the character board
bool PuzzleThree::isCharAvailable(char c) {
    //std::map<int, char>::iterator ptr = charBoard.begin();
    for (std::pair<int, char> d : charBoard) {
        if (c == d.second) {
            return true;
        }
    }
    return false;
}



// collect all the index or position of the characters of the phrase
// that matches the target character or character to be examined
void PuzzleThree::getPhraseIndex(char c,
                                 std::list<int>* matchingIndex) {
    // get all the indexes of the matching chars
    for (unsigned int i = 0; i < phrase.length(); ++i) {
        if ( c == tolower(phrase[i]) ) {
            matchingIndex->push_back(i);
        }
        //std::cout << phrase[i] << std::endl;
    }
}



// display bomb
void PuzzleThree::displayBomb() {
    //int i = 0;
    //while(i<attemptLeft)
    //    std::cout <<
    std::cout << "\n\t" << std::setfill(' ') << "*" <<
              std::setfill('_') <<
              std::setw(attemptLeft * 6) <<
              "Bomb" << std::endl;
}



// reveal the characters of the word to guess based
// on the collected index from the generated phrase
void PuzzleThree::revealChars(char c,
                              std::string *wordPlay,
                              std::list<int> *matchingIndex) {
    while ( !matchingIndex->empty() ) {
        int d = matchingIndex->front();
        wordPlay->at(d) = c;
        matchingIndex->pop_front();
    }
}



// display the the word to guess (blank word)
void PuzzleThree::displayWordToGuess(std::string wordPlay) {
    std::cout << "\n\t";
    for (char c : wordPlay) {
        if (c == '_') {
            std::cout << c << "_ ";
        } else if (c == ' ') {
            std::cout << "\n\n\t";
        } else {
            std::cout << c << " ";
        }
    }
    std::cout << std::endl;
}



// check if the generated phrase and the
// word being guessed are the same
bool PuzzleThree::areWordsSame(std::string *wordPlay,
                               std::string *phrase) {
    if ( (*wordPlay).compare(*phrase) == 0 ) {
        return true;
    } else {
        return false;
    }
}



// generate random phrase from a text file
std::string PuzzleThree::generatePhrase() {
    std::vector <std::string> readPhrases;
    std::string p, finalString;
    std::ifstream infile;
    unsigned int randIndex, numOfPhrases = 0;
    infile.open("docs/DATA/phrases.txt");
    if (!infile) {
        std::cerr << "\nUnable to open file\n";
        exit(1);
    }

    while ( std::getline(infile, p) ) {
        readPhrases.push_back(p);
        ++numOfPhrases;
        //std::cout << p << std::endl;
    }

    infile.close();

    //std::cout << readPhrases.size();

    srand(time(NULL));
    std::random_shuffle(readPhrases.begin(), readPhrases.end());

    srand(time(NULL));
    randIndex = PuzzleUtils::randomizer(readPhrases.size());
    //std::cout << "Random string: " << readPhrases[0] << std::endl;
    //std::cout << "Random string based on randindex: " << readPhrases[randIndex];

    //convert it to lowercase
    for (char c : readPhrases[randIndex]) {
        finalString += tolower(c);
    }

    return finalString;
}





// check if character input is valid
int PuzzleThree::checkInput(std::string stringInput) {
    char charInput;
    std::map<int, char>::iterator ptr;

    // check if string has space as its first character
    // make the first character of the string as the char input
    if (stringInput.length() > 0 && stringInput[0] != ' ') {
        charInput = tolower(stringInput[0]);
    } else {
        return -1;
    }


    // invalid if charInput is already in charsChosen
    for (ptr = charsChosen.begin(); ptr != charsChosen.end(); ++ptr) {
        if (charInput == ptr->second) {
            return -2;
        }
    }

    // valid if charInput is still in charBoard
    for (ptr = charBoard.begin(); ptr != charBoard.end(); ++ptr) {
        if (charInput == ptr->second) {
            return static_cast<int>(ptr->first);
        }
    }
    // invalid if charInput is not in the charBoard
    return -3;
}



// collect all characters chosen
void PuzzleThree::collectChosenChars(char charInput) {
    /**/
    std::pair<int, char> x;
    std::map<int, char>::iterator ptr = charBoard.begin();
    while (ptr != charBoard.end()) {
        //std::cout << ptr->second << std::endl;
        if (charInput == ptr->second) {
            x = std::make_pair(ptr->first, ptr->second);
            charsChosen.insert(x);
            charBoard.erase(ptr->first);
            return;
        }
        ++ptr;
    }
}



// game proper
void PuzzleThree::mainGame() {
    std::string toGuess;
    std::list<int> indexes;
    //std::map<int, char> charsChosen;

    std::string stringInput;
    char charInput;

    // make a blank string that has the same number of chars as the phrase
    // convert characters of the phrase into blank lines and space
    for (char c : phrase) {
        if (c != ' ') {
            toGuess += '_';
        } else {
            toGuess += ' ';
        }
    }


    /// ----- game proper ------
    this->displayStartingMessage();
    this->displayConsequence();
    this->displayGoal();

    // display character board and bomb
    displayCharBoard();
    displayBomb();

    //std::cout << "\n" << phrase << "\n";

    displayWordToGuess(toGuess);
    do {
        std::cout << "\n\nEnter character: ";
        std::getline(std::cin, stringInput);

        //check validity of stringInput
        if ( checkInput(stringInput) == -1 ) {
            std::cerr << "\nSpace character is invalid\n";
            continue;
        } else if ( checkInput(stringInput) == -2 ) {
            std::cerr << "\nCharacter already chosen!\n";
            continue;
        } else if ( checkInput(stringInput) == -3 ) {
            std::cerr << "\nCharacter invalid!\n";
            continue;
        } else {
            // get the first character of the string
            charInput = stringInput[0];
            charInput = tolower(charInput);

            // get indexes of characters in the phrase that matches charInput
            getPhraseIndex(charInput, &indexes);

            // reveal the characters indexed in word to guess
            if (indexes.size() > 0) {
                revealChars(charInput, &toGuess, &indexes);
            } else {
                --attemptLeft;
            }


            // store chosen character and delete it from the charBoard
            collectChosenChars(charInput);
        }


        displayCharBoard();
        displayWordToGuess(toGuess);

        /*for(std::map<int,char>::iterator ptr = charsChosen.begin(); ptr!=charsChosen.end(); ++ptr)
            std::cout << ptr->second << "\t";
        */
        //std::cout << toGuess << std::endl;
        displayBomb();
    } while (  !(areWordsSame(&toGuess, &phrase)) && attemptLeft != 0 );

    // display result
    if (attemptLeft > 0) {
        std::cout << "\nYou and "
                  << ROOM_CHARACTER << " are safe."
                  << std::endl;
        result = true;
    } else {
        std::cout << "\nGame Over!"
                  << std::endl;
        std::cout << "The phrase is: "
                  << phrase << "." << std::endl;
    }
}
