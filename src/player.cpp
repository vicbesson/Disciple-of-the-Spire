#include "player.h"


player::player() {
    name = "temp";
    race = "n/a";

    maxHealth = 0;
    currentHealth = maxHealth;

    currentExperience = 0;
    maxExperience = 100;

    statusEffect.resize(3, 0);
    checkStatBonuses();
}
// Essentially the default constructor for the player
player::player(std::string tName, std::string tRace, int tMaxHP,
               std::vector<int> tStat) {
    name = tName;
    race = tRace;

    maxHealth = tMaxHP;
    currentHealth = maxHealth;

    mainStats = tStat;

    checkStatBonuses();

    currentExperience = 0;
    maxExperience = 100;

    statusEffect.resize(3, 0);

}

player::~player() {
    //dtor
}

// Print
std::ostream& operator << (std::ostream& out, player& toRender) {
    // Figure out the widths for each section of the player output stream
    int nameSpacer = 17 - toRender.getName().length();
    int raceSpacer = 12 - toRender.getRace().length();
    int levelSpacer = 3 - std::to_string(toRender.getLevel()).length();
    int currentXpSpacer = std::to_string(toRender.getExperience()[0]).length();
    int maxXpScacer = 5 + std::to_string(toRender.getExperience()[1]).length();
    int hpSpacer = 4 - std::to_string(toRender.getCurrentHealth()).length();
    int goldSpacer = 10 - std::to_string(toRender.getGold()).length();
    std::string strBonus;
    std::string dexBonus;
    std::string intBonus;
    // Formatting variables for the damage bonus the player recieves
    // from using their current weapon based on their stats
    int dmgBonus = abs(toRender.getDamagePower());
    std::string dmgBonusSign;
    // Change the operation after the weapon damage to +/- based on their stats
    if (toRender.getDamagePower() >= 0)
        dmgBonusSign = " + ";
    else
        dmgBonusSign = " - ";

    if (toRender.getStatBonuses()[0] >= 0)
        strBonus = " + ";
    else
        strBonus = " - ";

    if (toRender.getStatBonuses()[1] >= 0)
        dexBonus = " + ";
    else
        dexBonus = " - ";

    if (toRender.getStatBonuses()[2] >= 0)
        intBonus = " + ";
    else
        intBonus = " - ";

    out << "\n" <<
        toRender.getName() << std::setw(nameSpacer) << toRender.getRace()
        << std::setw(raceSpacer)
        << "HP: " << std::setw(hpSpacer)
        << toRender.getCurrentHealth() << " / " << toRender.getMaxHealth()
        << std::setw(9)
        << "Level: " << toRender.getLevel() << std::setw(levelSpacer)
        << "(" << toRender.getExperience()[0] << std::setw(currentXpSpacer)
        << " / " << toRender.getExperience()[1] << ")" << std::setw(maxXpScacer)
        << std::setw(goldSpacer) << "Gold: " << toRender.getGold() << "g"

        << "\n" << std::setfill('.')
        /** Stats */
        << "1. " << "Str" << std::setw(5) << toRender.getStats()[0] << strBonus
        << abs(toRender.getStatBonuses()[0]) << "\n"
        << "2. " <<"Dex" << std::setw(5) << toRender.getStats()[1] << dexBonus
        << abs(toRender.getStatBonuses()[1]) << "\n"
        << "3. " <<"Int" << std::setw(5) << toRender.getStats()[2] << intBonus
        << abs(toRender.getStatBonuses()[2]) << "\n"
        << "Spd" << std::setw(5) << toRender.getStats()[3]
        // reset the fill back to empty space
        << std::setfill(' ') << "\n"


        /** Weapon */
        << "\nEquipped Weapon: "
        << toRender.getWeapon()->getName() << std::setw(3)
        << "(" << toRender.getWeapon()->getDiceRolls() << " * D"
        << toRender.getWeapon()->getDiceSize() << ")"
        << dmgBonusSign << dmgBonus << "\n\n";


    if(!toRender.getActiveAbilities().empty()) {

        int index = 0;
        out << "Active Abilities\n"
            << "| Index |        Name         |   CD   |  Stat Req | "
            << "Lvl Req | Damage | Price |\n"
            << std::setw(80) << std::setfill('-') << ' ' << std::setfill(' ')
            << std::endl;
        for(auto i : toRender.getActiveAbilities())
            out
                    << "|" << std::setw(4) << ++index <<std::setw(4)
                    << *i << std::endl;
    }
    out << std::endl;
    return out;
}

void player::inventoryManagement() {
    std::string command;
    int index = 0;
    bool done = false;
    if((cInventory->getAbilities().size() + cInventory->getConsumables().size() + cInventory->getWeapons().size()) > 0) {
        while(!done) {
            std::cout << name << "'s Inventory" << std::endl;
            cInventory->viewInventory();
            std::cout << "Choose the index of the item you want to manage, or \n"
                      << "type(m) to see player menu or type(e) to exit\n"
                      << "Choose index: ";
            print::setCursor(true);
            command.clear();
            while(command[0] == '\n' || command.empty())
                getline(std::cin, command);
            print::setCursor(false);
            if(print::toLower(command) == "e" || print::toLower(command) == "exit") {
                done = true;
            } else if(print::toLower(command) == "m" || print::toLower(command) == "menu") {
                print::clearScreen();
                std::cout << *this << std::endl;
            } else {
                if(print::is_number(command)) {
                    index = std::stoi(command) - 1;
                    if(index < cInventory->getWeapons().size()
                            + cInventory->getConsumables().size()
                            + cInventory->getAbilities().size()) {
                        while(!done) {
                            int counter = 0;
                            if(index < cInventory->getWeapons().size()) {
                                std::cout << "Would you like to swap " << cInventory->getWeapons()[index]->getName()
                                          << " with " << equippedWeapon->getName() << "? (y/n):" << std::endl;
                                while(!done) {
                                    print::setCursor(true);
                                    command.clear();
                                    while(command[0] == '\n' || command.empty())
                                        getline(std::cin, command);
                                    print::setCursor(false);
                                    std::string c = print::toLower(command);
                                    if(c == "yes" || c == "y") {
                                        swapWeapon(index);
                                        break;
                                    } else if(c == "no" || c == "n")
                                        break;
                                    else {
                                        print::textColour(print::C_RED);
                                        std::cout << "That is a yes or no question adventurer! Try again" << std::endl;
                                        print::textColour(print::C_DEFAULT);
                                    }
                                }
                                break;
                            } else if(index < cInventory->getWeapons().size()
                                      + cInventory->getConsumables().size()) {
                                index -= cInventory->getWeapons().size();
                                std::cout << "Would you like to consume " << cInventory->getConsumables()[index].front()->getName()
                                          << "? (y/n)" << std::endl;
                                while(!done) {
                                    print::setCursor(true);
                                    command.clear();
                                    while(command[0] == '\n' || command.empty())
                                        getline(std::cin, command);
                                    print::setCursor(false);
                                    std::string c = print::toLower(command);
                                    if(c == "yes" || c == "y") {
                                        useConsumable(index);
                                        break;
                                    } else if(c == "no" || c == "n")
                                        break;
                                    else {
                                        print::textColour(print::C_RED);
                                        std::cout << "That is a yes or no question adventurer! Try again" << std::endl;
                                        print::textColour(print::C_DEFAULT);
                                    }
                                }
                                break;
                            } else {
                                index -= cInventory->getWeapons().size() + cInventory->getConsumables().size();
                                std::cout << "Would you like to swap " << cInventory->getAbilities()[index]->getName()
                                          << " with one of your current abilities? (y/n)" << std::endl;
                                while(!done) {
                                    print::setCursor(true);
                                    command.clear();
                                    while(command[0] == '\n' || command.empty())
                                        getline(std::cin, command);
                                    print::setCursor(false);
                                    std::string c = print::toLower(command);
                                    if(c == "yes" || c == "y") {
                                        swapAbilities(index);
                                        break;
                                    } else if(c == "no" || c == "n")
                                        break;
                                    else {
                                        print::textColour(print::C_RED);
                                        std::cout << "That is a yes or no question adventurer! Try again" << std::endl;
                                        print::textColour(print::C_DEFAULT);
                                    }
                                }
                                break;
                            }
                        }
                    } else {
                        print::textColour(print::C_RED);
                        print::str("What are you doing adventurer that's not a valid index?! Try again!");
                        print::textColour(print::C_DEFAULT);
                        std::cout << std::endl;
                    }
                } else {
                    print::textColour(print::C_RED);
                    print::str("What are you doing adventurer that's not an index?! Try again!");
                    print::textColour(print::C_DEFAULT);
                    std::cout << std::endl;

                }
                print::clearScreen();
            }
        }
    } else {
        print::textColour(print::C_RED);
        print::str(name + "'s inventory is currently empty");
        print::textColour(print::C_DEFAULT);
        std::cout << std::endl;
    }
}

void player::swapAbilities(unsigned int index) {
    bool done = false;
    std::string command;
    int aindex = 0;
    if(!(activeAbilities.size() < 2)) {
        while(!done) {
            std::cout
                    << "Active Abilities\n"
                    << "| Index |        Name         |   CD   |  Stat Req | "
                    << "Lvl Req | Damage | Price |\n"
                    << std::setw(80) << std::setfill('-') << ' ' << std::setfill(' ')
                    << std::endl;
            for(auto ab : activeAbilities)
                std::cout <<
                          "|" << std::setw(4) << ++aindex << std::setw(4)
                          << *ab << std::endl;
            std::cout
                    <<"Which ability would you like to swap "
                    << cInventory->getAbilities()[index]->getName()
                    << " with?"
                    << std::endl;
            std::cout << "Choose index: ";
            print::setCursor(true);
            command.clear();
            while(command[0] == '\n' || command.empty())
                getline(std::cin, command);
            print::setCursor(false);
            if(print::is_number(command)) {
                int mindex = std::stoi(command) - 1;
                if(mindex < activeAbilities.size()) {
                    std::cout << "Would you like to swap " << activeAbilities[mindex]->getName()
                              << " with " << cInventory->getAbilities()[index]->getName() << "? (y/n)" << std::endl;
                    while(!done) {
                        print::setCursor(true);
                        command.clear();
                        while(command[0] == '\n' || command.empty())
                            getline(std::cin, command);
                        print::setCursor(false);
                        std::string c = print::toLower(command);
                        if(c == "yes" || c == "y") {
                            ability* a = cInventory->removeAbility(index);
                            ability* ea = activeAbilities[mindex];
                            activeAbilities.erase(activeAbilities.begin()+mindex);
                            activeAbilities.push_back(a);
                            cInventory->addAbility(ea);
                            print::str("You have swapped ");
                            print::textColour(print::C_GREEN);
                            print::str(ea->getName());
                            print::textColour(print::C_DEFAULT);
                            print::str(" with ");
                            print::textColour(print::C_PINK);
                            print::str(a->getName());
                            print::textColour(print::C_DEFAULT);
                            std::cout << std::endl;
                            done = true;
                            break;
                        } else if(c == "no" || c == "n")
                            break;
                        else {
                            print::textColour(print::C_RED);
                            std::cout << "That is a yes or no question adventurer! Try again" << std::endl;
                            print::textColour(print::C_DEFAULT);
                        }
                    }
                } else {
                    print::textColour(print::C_RED);
                    print::str("What are you doing adventurer that's not a valid index?! Try again!");
                    print::textColour(print::C_DEFAULT);
                    std::cout << std::endl;
                }
            } else {
                print::textColour(print::C_RED);
                print::str("What are you doing adventurer that's not an index?! Try again!");
                print::textColour(print::C_DEFAULT);
                std::cout << std::endl;
            }
        }
    } else {
        if(activeAbilities.empty())
            std::cout << "Currently you have no active abilities." << std::endl;
        else
            std::cout << "Seems you have room to add this ability." << std::endl;
        std::cout << "Would you like to add " << cInventory->getAbilities()[index]->getName()
                  << " to your active abilities? (y/n)" << std::endl;
        while(!done) {
            print::setCursor(true);
            command.clear();
            while(command[0] == '\n' || command.empty())
                getline(std::cin, command);
            print::setCursor(false);
            std::string c = print::toLower(command);
            if(c == "yes" || c == "y") {
                ability* a = cInventory->removeAbility(index);
                activeAbilities.push_back(a);
                print::str("You have added " + a->getName() + " to your active abilities!");
                std::cout << std::endl;
                break;
            } else if(c == "no" || c == "n")
                break;
            else {
                print::textColour(print::C_RED);
                print::str("That is a yes or no question adventurer! Try again");
                std::cout << std::endl;
                print::textColour(print::C_DEFAULT);
            }
        }
    }
}

void player::swapWeapon(unsigned int index) {
    if(checkWeaponReq(index)) {
        weapon* e = equippedWeapon;
        weapon* w = cInventory->removeWeapon(index);
        equippedWeapon = w;
        cInventory->addWeapon(e);
        print::str("You have swapped ");
        print::textColour(print::C_GREEN);
        print::str(e->getName());
        print::textColour(print::C_DEFAULT);
        print::str(" with ");
        print::textColour(print::C_PINK);
        print::str(w->getName());
        print::textColour(print::C_DEFAULT);
        std::cout << std::endl;
    } else if(index < cInventory->getWeapons().size()) {
        print::textColour(print::C_RED);
        print::str("You do not meet the requirements for this weapon");
        std::cout
                << std::endl;
        print::textColour(print::C_DEFAULT);
    } else {
        print::textColour(print::C_RED);
        print::str("Invalid weapon selection");
        std::cout << std::endl;
        print::textColour(print::C_DEFAULT);
    }
}


void player::addExperience(int toAdd) {
    currentExperience += toAdd;
    if (currentExperience >= maxExperience)
        levelUp();
}

void player::levelUp() {
    // temp variables used to for input
    int statIn;
    int statAmountIn;
    std::string command;
    // Stats the user has chosen to upgrade
    std::vector<int> tempStats(4);
    // how many stat points the player can add to their hero
    int availablePoints;
    // When you create your character you get more points
    if (level == 0) {
        availablePoints = 6;
        // Debugging
        currentExperience = 0;
    } else {
        // So we can level up the player without giving them negative experience
        currentExperience -= maxExperience;
        // Don't increase the max experience required for level 1 as it is set
        // by default in the constructor
        maxExperience *= 1.2;
        availablePoints = 2;
    }
    // stored amount of available points in case the user does not want
    //  to commit their changes
    int backupAvailPoints = availablePoints;
    // ding!
    level += 1;

    // Print out the current player before they level up for reference
    std::cout << (*this);

    std::cout
            << "First choose the index of the stat you want to increase\n"
            << "then type the amount of points to add to that stat\n"
            << "For every 2 points after 10 in any stat, you will gain a +1 bonus"
            << "\ni.e. 1 will choose strength and then type 1 to add one point "
            << "to strength.\n\n"
            << "Available points: " << availablePoints << std::endl;

    print::setCursor(true);
    // While the player still has points to spend on additional stat upgrades
    while (availablePoints > 0) {
        bool done = false;
        std::string In;
        std::string AmountIn;
        while(!done) {
            std::cout.flush() << "Choose stat: ";
            std::cin >> In;
            if(print::is_number(In) && (In == "1" || In == "2" || In == "3")) {
                statIn = std::stoi(In) - 1;
                while(!done) {
                    std::cout << "Choose amount: ";
                    std::cin >> AmountIn;
                    std::cout << std::endl;
                    if(print::is_number(AmountIn)) {
                        if(std::stoi(AmountIn) > 0) {
                            statAmountIn = std::stoi(AmountIn);
                            done = true;
                        } else {
                            std::cout << "Invalid stat amount" << std::endl;
                        }
                    } else {
                        std::cout << "Invalid stat amount" << std::endl;
                    }
                }
            } else
                std::cout << "\nInvalid stat type" << std::endl;
        }
        // Check that the amount of stats input does not exceed the amount of available points
        if (statIn < 3 && availablePoints - statAmountIn >= 0) {
            // Add the stats input by the player to the tempStats vector
            tempStats[statIn] += statAmountIn;
            // reduce the available points by the amount of points the player just spent
            availablePoints -= statAmountIn;
            // Print what the user just did so they know whats up
            switch (statIn) {
            case 0:
                std::cout
                        << statAmountIn << " point(s) added to Strength. "
                        << availablePoints << " points remaining."
                        << std::endl;
                break;

            case 1:
                std::cout
                        << statAmountIn << " point(s) added to Dexterity. "
                        << availablePoints << " points remaining."
                        << std::endl;
                break;

            case 2:
                std::cout
                        << statAmountIn << " point(s) added to Intellect. "
                        << availablePoints << " points remaining."
                        << std::endl;
                break;
            }
        }
        // Tell the user if they entered an invalid command / stat amount
        else {
            std::cout << "Invalid stat type or amount" << std::endl;
        }
        // If all the available points are spent, show the user what they
        // have selected so far
        if (availablePoints == 0) {
            while(true) {
                std::cout << "Would you like to commit? (y/n)\n"
                          << "Strength  + " << tempStats[0] << "\n"
                          << "Dexterity + " << tempStats[1] << "\n"
                          << "Intellect + " << tempStats[2] << "\n"
                          << std::endl;
                std::cout << "What would you like to do adventurer: ";
                print::setCursor(true);
                command.clear();
                while(command[0] == '\n' || command.empty())
                    getline(std::cin, command);
                print::setCursor(false);
                std::string c = print::toLower(command);
                // add the chosen stats from the player to the main stats vector
                // break for the while loop
                if (c == "yes" || c == "y") {
                    addToStats(tempStats);
                    // Positive reinforcement is a key value of the Spire...
                    std::cout << "Good Choice Adventurer!" << std::endl;
                    break;
                }

                // reset the available points and tempStats vector which
                // essentially restarts the loop
                else if(c == "no" || c == "n") {
                    availablePoints = backupAvailPoints;
                    tempStats.clear();
                    tempStats.resize(4);
                    std::cout << (*this);
                    std::cout
                            << "First choose the index of the stat you want to increase\n"
                            << "then type the amount of points to add to that stat\n"
                            << "For every 2 points after 10 in any stat, you will gain a +1 bonus"
                            << "\ni.e. 1 will choose strength and then type 1 to add one point "
                            << "to strength.\n\n"
                            << "Available points: " << availablePoints << std::endl;
                    break;
                } else {
                    print::textColour(print::C_RED);
                    print::str("That is a yes or no question adventurer! Try again");
                    print::textColour(print::C_DEFAULT);
                    std::cout << std::endl;
                }
            }
        }
    }
    print::setCursor(false);
    // Add 10% of the players current hp an 50% of their strength to maxHP
    // Arbitrary and needs to be replaced with actual value
    maxHealth += static_cast<int>((maxHealth * 0.1) + (mainStats[0] * 0.5));
    // Give the player back full HP when they level up because we're not savages
    currentHealth = maxHealth;

    // Print out the player so the user can see their changes
    std::cout << (*this);

    // Check if the player has enough experience to levelup again
    addExperience(0);
}

void player::addToStats(std::vector<int>toAdd) {
    // For all the stats the player has, add the given stats
    for(unsigned int i = 0; i < mainStats.size(); i++)
        mainStats[i] += toAdd[i];
    // Check to see if the stats added change the players bonuses
    checkStatBonuses();
}

void player::applyStatusEffect(std::vector<int> toApply, bool apply) {
    // This may need to be changed based off how we do atatus effects
    // Add the negative or positive effect
    if (apply) {
        statusEffect = toApply;
        for (unsigned int i = 0; i < 3; i++)
            mainStats[i] += statusEffect[i];
    }
    // Reverse the negative or positive effect
    else {
        for (unsigned int i = 0; i < 3; i++)
            mainStats[i] -= statusEffect[i];
    }
    // Check if the status effect changes the players stat bonuses
    checkStatBonuses();
}

void player::useConsumable(unsigned int index) {
    if(cInventory->getConsumables()[index].size() > 0) {
        std::vector<consumable*> tempC = cInventory->removeConsumables(index, 1);
        int stat = (tempC.front()->statsToAdd()[0]);
        int amount = (tempC.front()->statsToAdd()[1]);
        std::string s = "+" + std::to_string(amount);
        if(stat == 4 && !tempC.front()->getIsPerminant() && currentHealth >= maxHealth) {
            print::str("Sorry adventurer you are currently are topped up");
            std::cout << std::endl;
            cInventory->addConsumables(tempC);
        } else {
            if(tempC.front()->getIsPerminant()) {
                s += " permanently added to ";
                switch(stat) {
                case 0:
                    mainStats[0] += amount;
                    s += "strength";
                    break;
                case 1:
                    mainStats[1] += amount;
                    s += "dexterity";
                    break;
                case 2:
                    mainStats[2] += amount;
                    s += "intellect";
                    break;
                case 3:
                    mainStats[3] += amount;
                    s += "speed";
                    break;
                case 4:
                    maxHealth += amount;
                    currentHealth += amount;
                    s += "hp";
                    break;
                }
            } else {
                s += " added to ";
                switch(stat) {
                case 0:
                    statusEffect[0] += amount;
                    s += "strength";
                    break;
                case 1:
                    statusEffect[1] += amount;
                    s += "dexterity";
                    break;
                case 2:
                    statusEffect[2] += amount;
                    s += "intellect";
                    break;
                case 3:
                    statusEffect[3] += amount;
                    s += "speed";
                    break;
                case 4:
                    currentHealth += amount;
                    if(currentHealth > maxHealth)
                        currentHealth = maxHealth;
                    s += "hp";
                    break;
                }
            }
            print::str(s);
            delete tempC.front();
        }
        tempC.clear();
        std::cout << std::endl;
    } else {
        print::textColour(print::C_RED);
        print::str("Tried to use consumable index that is out of range");
        std::cout << std::endl;
        print::textColour(print::C_DEFAULT);
    }
    // Check if updating the players stats changes their damage
    updateDamagePower();
}

std::vector<int> player::getExperience() {
    // Return the experience in a vector to save time
    std::vector<int> temp;

    temp.push_back(currentExperience);
    temp.push_back(maxExperience);

    return temp;
}

bool player::checkAbilityReq(unsigned int inventoryIndex) {
    if(inventoryIndex < cInventory->getAbilities().size())
        return
            // get the stat amount required
            cInventory->getAbilities()[inventoryIndex]
            ->getStatRequirements()[1] <=
            // At the players main stats of the required stat
            mainStats[cInventory->getAbilities()[inventoryIndex]
                      ->getStatRequirements()[0]]
            // check the player is at the required level
            && cInventory->getAbilities()[inventoryIndex]
            ->getStatRequirements()[2] < level;
    else
        return false;
}

bool player::checkWeaponReq(unsigned int inventoryIndex) {
    if(inventoryIndex < cInventory->getWeapons().size())
        return
            cInventory->getWeapons()[inventoryIndex]->getStatRequirements()[1] <=
            mainStats[cInventory->getWeapons().
                      at(inventoryIndex)->getStatRequirements()[0]]
            && cInventory->getWeapons().at(inventoryIndex)->getStatRequirements()[2] <=
            level;
    else
        return false;
}

#define DIR_SAVE "../docs/DATA/Save_Player.csv"

void player::save() {
    // Delete the old save file
    remove(DIR_SAVE);

    std::ofstream toWrite;
    std::ifstream toRead;

    toWrite.open(DIR_SAVE);

    toWrite
    // Store all the players stats
            << name << ','
            << race << ','
            << currentHealth << ','
            << maxHealth << ','
            << level << ','
            << mainStats[0] << ','
            << mainStats[1] << ','
            << mainStats[2] << ','
            << mainStats[3] << ','
            << gold << ','
            << currentExperience << ','
            << maxExperience << ',';

    // Store all the equipped weapon stats
    if (equippedWeapon != nullptr) {
        toWrite
                << equippedWeapon->getName() << ','
                << equippedWeapon->getDiceRolls() << ','
                << equippedWeapon->getDiceSize() << ','
                << equippedWeapon->getStatRequirements()[0] << ','
                << equippedWeapon->getStatRequirements()[1] << ','
                << equippedWeapon->getStatRequirements()[2] << ','
                << equippedWeapon->getCost() << ','
                << equippedWeapon->getSellValue() << ',';
    }
    toWrite << "ABILITIES,";
    // Store all abilities
    if (!activeAbilities.empty()) {
        // Store the indicies of the 0th abilility
        toWrite << activeAbilities[0]->getIndex() << ',';

        if (activeAbilities.size() > 1) {
            // Store the indicies of the 1st abilility
            toWrite << activeAbilities[1]->getIndex() << ',';
        }
    }
    /** Store all items in the players inventory */
    // Store all weapons
    if (cInventory->getWeapons().empty()) {
        toWrite << "STORED_WEAPONS,";
        for (unsigned int i = 0; i < cInventory->getWeapons().size(); i++) {
            toWrite
                    << cInventory->getWeapons()[i]->getName() << ','
                    << cInventory->getWeapons()[i]->getDiceRolls() << ','
                    << cInventory->getWeapons()[i]->getDiceSize() << ','
                    << cInventory->getWeapons()[i]->getStatRequirements()[0] << ','
                    << cInventory->getWeapons()[i]->getStatRequirements()[1] << ','
                    << cInventory->getWeapons()[i]->getStatRequirements()[2] << ','
                    << cInventory->getWeapons()[i]->getCost() << ','
                    << cInventory->getWeapons()[i]->getSellValue() << ',';
        }
    }





    toWrite.close();
}

