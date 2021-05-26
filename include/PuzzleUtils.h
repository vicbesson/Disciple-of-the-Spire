/**
    @author
    @brief
*/

#ifndef PUZZLEUTILS_H
#define PUZZLEUTILS_H
#include <string>
#include <iostream>
#include <random>

class PuzzleUtils {
public:
    PuzzleUtils();
    virtual ~PuzzleUtils();

    /**
     *  @brief generate a random integer
     *  @param randomizerLimit    the highest value that the
     *                            randomizer can return
     *  @return random integer up to and including randomizerLimit
     */
    static int randomizer(int randomizerLimit);

    /**
     *  @brief determine width of an integer
     *  @param num    an integer
     *  @return the number of digit an integer has (e.g. 10 has 2 integer)
     */
    static int getIntWidth(int num);

    /**
     *  @brief determine if an integer is within the allowed range
     *  @param target       the integer to examine
     *         lowestNum    the lowest integer in the range
     *         highestNum   the highest integer in the range
     *  @return true if target is within range, otherwise return false
     */
    static bool isChoiceWithinBounds(int target,
                                     int lowestNum,
                                     int highestNum);

    /**
     *  @brief determine if user input is an integer
     *  @param choice   user input to examine
     *  @return true if the string contains only digits,
     *          otherwise return false
     */
    static bool isChoiceInt(std::string choice);

    /**
     *  @brief print each character of the string with delay
     *  @param stringInput    string to display
     *         timeDelay      time delay if each character in milliseconds
     *  @return true if the string contains only digits,
     *          otherwise return false
     */
    static void delayCharOutput(std::string stringInput);

private:
};

#endif // PUZZLEUTILS_H
