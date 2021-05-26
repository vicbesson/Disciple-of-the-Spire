/**
    @author Tyler Justinen-Teite

    @brief

*/

#ifndef DICE_H
#define DICE_H
// Time
#include <random>
#include <time.h>

class dice {
public:
    /**
        @brief Default constructor. Sides = 6
    */
    dice();
    /**
        @brief Overloaded constructor for a dice with not 6 sides
        @param[in] int Number of sides for this dice
    */
    dice(int nSides);

    virtual ~dice();
    /**
      @brief Roll the dice a single time
      @param[out] int roll = rand(1, sides)
    */
    int roll();
    /**
    @brief Roll the dice n time(s).
    @param[in] int how many times the die is being rolled.
    @param[out] int roll = rand(1, sides).
    */
    int roll(int nRolls);
    /**
      @brief Return the number of sides that this dice has
      @param[out] int numberOfSides
    */
    const int& getSides();

private:
    int sides;

};

#endif // DICE_H
