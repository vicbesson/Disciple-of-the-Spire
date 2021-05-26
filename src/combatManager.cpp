#include "combatManager.h"

combatManager::combatManager(player* p, monster* m) {
    // Create an array of pointers to the parent class of the
    // monster and player so we can flip-flop between them easily
    fightOrder = new baseCharacter* [2];
    // If the player's speed is >= the monsters speed, the player goes first
    if (p->getStats()[3] >= m->getStats()[3])
        playersTurn = true;
    else
        playersTurn = false;
    // Monster
    fightOrder[0] = m;
    // Player
    fightOrder[1] = p;
}

combatManager::~combatManager() {
    delete[] fightOrder;
}

bool combatManager::startFight() {
    // Debugging
    bool forceQuit = true;
    // Stores how much damage was done so it can be printed
    int tempDamage = 0;
    // Start of combat text formatting
    if (playersTurn) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout
                << "\nCOMBAT HAS BEGUN!!!\n" << fightOrder[playersTurn]->getName() +
                "'s faster than the " + fightOrder[!playersTurn]->getName()
                << "\nType (atk) to attack with weapon or (abl) to use an ability\n"
                << "What would you like to do adventurer: ";
    } else {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout
                << "\nCOMBAT HAS BEGUN!!!\n"
                << "A " + fightOrder[playersTurn]->getName()
                << " has gotten the first attack against you!\n";
    }

    // forceQuit is for debugging, takes you to looting the monster
    while (!checkCombatDone() && forceQuit) {
        // dummy variables to consume user input
        std::string command;
        std::vector<int> input;

        if (playersTurn) {
            //Reduce the CD on all the players abilities
            for(auto ab : fightOrder[1]->getActiveAbilities())
                ab->reduceCooldown();

            if (turnCount > 0) {
                // Print out the players basic hero stats each turn
                // (should probably change)
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout
                        << "Type (atk) to attack with weapon or (abl) to use an ability\n"
                        << "What would you like to do adventurer: ";
            }
            print::setCursor(true);

            while(command.empty() || command[0] == '\n')
                std::getline(std::cin, command);

            input = formatCommand(command);
            print::setCursor(false);
        } else {
            // Reduce the CD on the monsters abilities
            for(auto ab : fightOrder[0]->getActiveAbilities())
                ab->reduceCooldown();
            // Index of active ability
            int index = 0;
            // If an active ability is off cooldown, store the location
            // and push back the input
            for(auto ab : fightOrder[0]->getActiveAbilities()) {
                // std::cout << ab->getCurrentCooldown() << std::endl;
                if(ab->getCurrentCooldown() == 0) {
                    input.push_back(2);
                    input.push_back(index);
                    break;
                } else index++;
            }
            // Currently if it's the monsters turn, just auto attack
            input.push_back(1);
        }

        switch (input[0]) {
        // dealDamage with equipped weapon
        // attack, atk
        case 1:
            tempDamage = fightOrder[playersTurn]->dealDamage();
            if(tempDamage < 0)
                tempDamage = 0;
            fightOrder[!playersTurn]->takeDamage(tempDamage);

            // Display who did how much damage to who after each attack
            std::cout
                    << fightOrder[playersTurn]->getName() << " dealt " << tempDamage
                    << " to " << fightOrder[!playersTurn]->getName()
                    << "   HP: " << fightOrder[!playersTurn]->getCurrentHealth()
                    << " / " << fightOrder[!playersTurn]->getMaxHealth()
                    << std::endl;
            break;
        // ability, abl
        case 2:
            if(playersTurn) {
                if(fightOrder[1]->getActiveAbilities().empty()) {
                    print::textColour(print::C_RED);
                    print::str("Currently " + fightOrder[1]->getName() +
                               " has no active abilities");
                    print::textColour(print::C_DEFAULT);
                    break;
                }
                input.push_back(0);
                for(auto ab : fightOrder[1]->getActiveAbilities())
                    std::cout
                            << std::setw(4) << ++input[1]
                            << std::setw(10 + ab->getName().length() / 2) << ab->getName()
                            << std::setw(15 + ab->getName().length())
                            << "CD Remaining: " << ab->getCurrentCooldown()
                            << std::setw(3)
                            << ab->getDiceRolls() << " * D" << ab->getDiceSize()
                            << std::endl;
                std::cout << "\nChoose the index of the ability would you like to use: ";

                print::setCursor(true);
                // Reusing the input vector instead of declaring new index
                print::setCursor(true);
                command.clear();
                while(command[0] == '\n' || command.empty())
                    getline(std::cin, command);
                print::setCursor(false);
                if(print::is_number(command)) {
                    input[1] = std::stoi(command);
                    input[1]--;

                    if(static_cast<unsigned int> (input[1])
                            < fightOrder[playersTurn]->getActiveAbilities().size()
                            && input[1] >= 0
                            && fightOrder[playersTurn]->
                            getActiveAbilities()[input[1]]->getCurrentCooldown() == 0) {
                        tempDamage = fightOrder[playersTurn]->useAbility(input[1]);
                    } else if (static_cast<unsigned int>(input[1])
                               >= fightOrder[1]->getActiveAbilities().size()
                               || input[1] < 0) {
                        print::textColour(print::C_RED);
                        print::str("Invalid Ability Index");
                        print::textColour(print::C_DEFAULT);
                        // So typing in an invalid command does not waste the players turn
                        playersTurn = !playersTurn;
                        //  Skip printing damage
                        break;
                    }
                }


                else {
                    print::textColour(print::C_RED);
                    print::str("Invalid Active Ability Index");
                    std::cout << std::endl;
                    print::str("Abilities can only be used if their CD Remaining = 0");
                    print::textColour(print::C_DEFAULT);
                    // So typing in an invalid command does not waste the players turn
                    playersTurn = !playersTurn;
                    //  Skip printing damage
                    break;
                }
            }
            // Monster using an ability
            else {
                tempDamage = fightOrder[playersTurn]->useAbility(input[1]);
            }

            fightOrder[!playersTurn]->takeDamage(tempDamage);
            std::cout
                    << fightOrder[playersTurn]->getName()
                    << " used "
                    << fightOrder[playersTurn]->getActiveAbilities()[input[1]]->getName()
                    << " dealing " << tempDamage
                    << " damage to " << fightOrder[!playersTurn]->getName()
                    << "   HP: " << fightOrder[!playersTurn]->getCurrentHealth()
                    << " / " << fightOrder[!playersTurn]->getMaxHealth()
                    << std::endl;

            break;
        // pp, pplayer
        case 12:
            // Print the basic character information for the player
            std::cout << *fightOrder[1] << std::endl;
            // Reusing the input vector instead of declaring new index
            input[0] = 0;
            for(auto ab : fightOrder[1]->getActiveAbilities())
                std::cout
                        << std::setw(4) << ++input[0]
                        << std::setw(10 + ab->getName().length() / 2) << *ab;
            // So printing won't cost you the turn
            playersTurn = !playersTurn;
            break;
        // pm, pmonster
        case 13:
            // Print the basic character information for the monster
            std::cout << *fightOrder[0] << std::endl;
            // So printing the monster won't take up the users turn
            playersTurn = !playersTurn;
            break;

        // exit
        case 0:
            forceQuit = false;
            break;

        // help
        case -1:
            std::cout << "\n"
                      << "atk:  Attack the monster with your weapon.\n"
                      << "abl:  Choose an ability to perform on the monster.\n"
                      << std::endl;
            // Stops the player from loosing their turn if
            // they enter a wrong command
            playersTurn = !playersTurn;
            break;

        default:
            print::textColour(print::C_RED);
            print::str("Invalid command. Type 'Help' for all available commands");
            print::textColour(print::C_DEFAULT);
            break;
        }
        // Flip-Flop turns
        playersTurn = !playersTurn;
        turnCount++;
    }
    // Set the turn back to who the winner of the fight was
    playersTurn = !playersTurn;
    // Set the turn count back to the winning/losing turn
    turnCount--;
    return endFight();
}

bool combatManager::endFight() {
    if (playersTurn) {
        //  *** Arbitrary amount of experience for the player to gain when
        // they killed the monster ***
        // Gain 1/3 of the players max experience, and 20% of the
        // monsters HP as experience
        int monsterXP =  (*dynamic_cast<player*>
                          (fightOrder[1])).getExperience()[1] / 3
                         + (fightOrder[0]->getMaxHealth() * 0.2);

        dynamic_cast<player*> (fightOrder[1])->addExperience(monsterXP);
        // First line draws a bar of '*' to seperate the combat phase
        //  from the end of combat
        std::cout
                << "\n" << std::setfill('*') << std::setw(50) << "\n\n"
                << std::setfill(' ')
                << "Congratulations " + fightOrder[playersTurn]->getName()
                << "! You were victorious over the "
                << fightOrder[!playersTurn]->getRace() << ".\n"
                << "Defeating the monster has granted you " << monsterXP
                << " experience.\n"
                << "Here's how " << fightOrder[1]->getName()
                << " is looking after that fight.\n"
                <<  (*fightOrder[1])
                << std::endl;




        bool monsterLooted = false;
        while (!monsterLooted) {
            int input;
            std::cout << "Would you like to 'Loot' the monster? (y/n)" << std::endl;
            std::cout << "What would you like to do adventurer: ";
            print::setCursor(true);
            std::string command;
            while(command.empty() || command[0] == '\n')
                getline(std::cin, command);
            print::setCursor(false);

            input = formatCommand(command)[0];

            switch (input) {
            // loot, yes
            case 20:
                // Loot the monsters weapon
                fightOrder[1]->getInventory()->addWeapon
                (fightOrder[0]->getWeapon());
                // Take the gold
                fightOrder[1]->setGold(fightOrder[0]->getGold());

                if(dynamic_cast<monster*>(fightOrder[0])->isBoss)
                    // If the monster was a boss, get an ability
                    fightOrder[1]->getInventory()
                    ->addAbility(dynamic_cast<monster*>(fightOrder[0])
                                 ->getInventory()->removeAbility(0));


                print::str( "Victory granted  " + fightOrder[1]->getName()
                            + " " + std::to_string(monsterXP) + " experience.\n"
                            + "Found " + std::to_string(fightOrder[0]->getGold()) + " gold.\n"
                            +"Picked up\n" + fightOrder[0]->getWeapon()->getName());
                std::cout << std::endl;
                if(dynamic_cast<monster*>(fightOrder[0])->isBoss)
                    print::str( "\n"
                                + fightOrder[1]->getInventory()->getAbilities().back()->getName());

                std::cout << std::endl;
                monsterLooted = true;
                break;

            case 0:
                print::str(
                    "\nOnce you leave the monster encounter,\n"
                    "this monsters loot will be gone forever.\n"
                    "Taken as sacrifice to the spire.\n"
                    "Are you sure that you don't want to see what the "
                    "monster has on its body? (y/n)\n"
                );
                std::cout << ">> ";
                print::setCursor(true);
                command.clear();
                while(command[0] == '\n' || command.empty())
                    getline(std::cin, command);
                print::setCursor(false);
                command = print::toLower(command);
                if (command == "y" || command == "yes") {
                    std::cout << "Exiting Combat\n" << std::endl;
                    return true;
                } else if(command == "n" || command == "no")
                    break;
                break;
            default:
                std::cout << "Invalid Command\nCommands: Yes/No" << std::endl;
                break;
            }
        }
    }
    // We should create a gameOver state. And call it here
    else {
        return false;
    }

    return true;
}

bool combatManager::checkCombatDone() {
    if (fightOrder[0]->isDead() || fightOrder[1]->isDead()) {
        return true;
    }

    else
        return false;
}

std::vector<int> combatManager::formatCommand(std::string command) {
    // Return a vector of ints as formatted commands
    std::vector<int> temp;
    // Push back each new command to a new vector index
    std::vector<std::string> tempCommand;
    std::string parsed;
    std::stringstream parser(command);

    // Parse the line of commands input by the player
    while (getline(parser, parsed, ' ')) {
        tempCommand.push_back(parsed);
    }
    // Format the commands to be all lower case
    for (unsigned int i = 0; i < tempCommand.size(); i++) {
        for (unsigned int c = 0; c < tempCommand[i].size(); c++) {
            tempCommand[i][c] = tolower(tempCommand[i][c]);
        }
    }

    // Perform a basic attack with the equipped weapon
    if (tempCommand[0] == "attack" || tempCommand[0] == "atk")
        temp.push_back(1);
    // Choose an ability to perform
    else if (tempCommand[0] == "ability" || tempCommand[0] == "abl")
        temp.push_back(2);
    // Only used during the endFight phase
    else if (tempCommand[0] == "loot" || tempCommand[0] == "lt"
             || tempCommand[0] == "yes" || tempCommand[0] == "y")
        temp.push_back(20);
    else if (tempCommand[0] == "n" || tempCommand[0] == "no")
        temp.push_back(0);
    /**** Debugging Commands ****/
    // Print the player
//    else if (tempCommand[0] == "pplayer" || tempCommand[0] == "pp")
//        temp.push_back(12);
//    // Print the monster
//    else if (tempCommand[0] == "pmonster" || tempCommand[0] == "pm")
//        temp.push_back(13);
//
//    // Debugging: Exit the combat loop and go straight to the looting phase
//    else if (tempCommand[0] == "exit" || tempCommand[0] == "e" ||
//             tempCommand[0] == "no"   || tempCommand[0] == "n")
//        temp.push_back(0);

    // If no valid command was entered, display the available commands
    else
        temp.push_back(-1);


    //// Get rid of the command string once it's been formatted
    tempCommand.erase(tempCommand.begin());
    // Push back all the type numbers that the user entered in their command
    if (!tempCommand.empty())
        for (auto i : tempCommand)
            if(isdigit(temp[0]))
                temp.push_back(std::stoi(i));

    return temp;
}
