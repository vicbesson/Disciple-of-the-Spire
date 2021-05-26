/**
    @author Tyler Justinen-Teite
    @author Victor Besson
    @brief This class is designed to for controlling how text is rendered to the
           screen. By default, it will print text at soft-white colour, and
           output a character at a time, so that it looks like the text is being
           typed into the terminal.
           The default time between each character is rand() % 75 milliseconds.
*/

#ifndef PRINT_H
#define PRINT_H

#define DIR_COMMANDS "docs/DATA/commands.csv"
#define DEFAULT_MOD 50
// Linux
#define SYS_CLEAR "clear"
// Windows
//#define SYS_CLEAR "cls";

// "printf '\e[38;2;200;200;200m'"

// Containters
#include <vector>
#include <string>
#include <cstring>
/// Not a container but used for converting text to c_strings
#include <algorithm>
// I/O
#include <iostream>
#include <ostream>
#include <sstream>
// For sleep
#include <chrono>
#include <random>
#include <thread>

/**
  @brief This is a very rough class atm, it's jank to be honest...
          BUT you can print strings like they're being typed by a "person"
          Change the colour of the text or the 'typing' speed

          To access a colour for any of the functions, call print::C_'colour'
          i.e. print::str_colour(string toPrint, print::C_WHITE);
*/

class print {
public:
    // I guess?
    /**
      @brief access with print::C_
    */
    static int C_WHITE [3];
    static int C_BLACK [3];
    static int C_RED [3];
    static int C_GREEN [3];
    static int C_GREEN_D [3];
    static int C_BLUE [3];
    static int C_PURPLE [3];
    static int C_BROWN [3];
    static int C_PINK [3];
    static int C_DEFAULT [3];

    /**
      @brief Print out the string every few milliseconds, so it looks
             like the text is being typed to the screen. Does not endl
    */
    static void str(const std::string& toPrint);

    /**
      @brief Print out the string one char at a time every x milliseconds
    */
    static void str_time(const std::string& toPrint, const int& maxMillis);
    /**
      @brief Print the std::vector<std::string>> to the screen, one char
             at a time, and wait a small amount of time between each char
    */
    static void vec(const std::vector<std::string>& toPrint);
    /**
      @brief Print the std::vector<std::string>> to the screen, one char
             at a time, and wait a small amount of time between each char,
             and increase the speed as it's printed.
    */
    static void vec_faster(const std::vector<std::string>& toPrint);
    /**
      @brief Print the std::vector<std::string>> to the screen, one char
             at a time, and wait a small amount of time between each char,
             and increase the speed as it's printed.
    */
    static void vec_time(const std::vector<std::string>& toPrint,
                         const int& maxMillis);
    /**
      @brief  Set the text colour
      @param[in] int[3] print::C_'colour'
    */
    static void textColour(const int colour[3]);
    /**
      @brief  Sets the cursor to a box (true) or an underscore
      @param[in] bool Box?
    */
    static void setCursor(const bool& box);
    /**
      @brief  Screen dimensions: 31h x 80h
              Background colour: Black
              Text Colour: Light Grey
              Cursor : Underscore
    */
    static void initScreen();
    /**
      @brief
      @param[in]
    */
    static bool is_number(const std::string& s);
    /**
      @brief Fade the screen to red, hold for 3 seconds, then fade back to black
    */
    static void deathScreen();
    /**  gameManager* myManager = new gameManager;

    myManager->startGame();

      @brief Call the system command to clear the terminal
    */
    static void clearScreen();
    /**
      @brief Convert string to lower
    */
    static std::string toLower(std::string input);
};


#endif // PRINT_H
