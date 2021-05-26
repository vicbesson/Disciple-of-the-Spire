/**
  @author Tyler Justinen-Teite

*/

#include "gameManager.h"
#include "testManager.h"
int main() {
    std::string command;
    while(true) {
        print::clearScreen();
        std::cout << "Type(start) to start game or type(test) to begin testing\n"
                  << "What would you like to do: ";
        std::cin >> command;
        command = print::toLower(command);
        if(command == "start") {
            gameManager* myGame = new gameManager();
            myGame->startGame();
            delete myGame;
            break;
        } else if(command == "test") {
            testManager* myTest = new testManager();
            myTest->startGame();
            delete myTest;
            break;
        } else {
            print::str("invalid command");
            std::cout << std::endl;
        }
    }

    return 0;
}
