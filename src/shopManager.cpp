#include "shopManager.h"
shopManager::shopManager(const int& roomCount, player* myPlayer) {
    int level = (roomCount / 5);
    customer = myPlayer;

    if(level > 0)
        gold = 200 * level;
    else
        gold = 200;

    sinventory = new inventory;
    /// Give the shop 5 of the current level of healing consumable
    std::vector<consumable*> tempCon;
    for(int i = 0; i < 5; i++)
        tempCon.push_back(new consumable(level));

    sinventory->addConsumables(tempCon);
    tempCon.clear();
    /// Give the shop one of every book
    tempCon.push_back(new consumable(5));
    sinventory->addConsumables(tempCon);
    tempCon.clear();

    tempCon.push_back(new consumable(6));
    sinventory->addConsumables(tempCon);
    tempCon.clear();

    tempCon.push_back(new consumable(7));
    sinventory->addConsumables(tempCon);
    tempCon.clear();

    tempCon.push_back(new consumable(8));
    sinventory->addConsumables(tempCon);
    tempCon.clear();

    /// Give the shop a weapon of this level
    sinventory->addWeapon(new weapon(level));
    /// Give the player an option to buy a level for the next tier of rooms
    sinventory->addWeapon(new weapon(level + 2));
    /// give the Shop one ability from this level
    sinventory->addAbility(new ability(level));

    /// Hard coded indexes for the shop
    lastWeapon = 2;
    lastConsumable = 7;
    lastIndex = 8;
    hasAbility = true;
}

shopManager::~shopManager() {
    delete customer;
    delete sinventory;
}

void shopManager::startTransaction() {
    bool stillShoping = true;
    /// Start the transaction with a clean terminal
    print::clearScreen();

    int lastPlayerWeapon;
    int lastPlayerConsumable;
    int lastPlayerIndex;
    while(stillShoping) {
        std::string command;
        // Temp
        int cost;
        // Input
        int itemIndex;
        print::clearScreen();
        std::cout << "So. Stuff to 'sell'? Need to 'buy' something?\n"
                  << "Manage what you have 'i'? Or are you done here? 'exit'\n"
                  << "What would you like to do adventurer: ";
        print::setCursor(true);
        command.clear();
        while(command[0] == '\n' || command.empty())
            getline(std::cin, command);
        print::setCursor(false);
        /** Main command switch */
        switch(formatCommand(command)) {
        /** Buy */
        case 1:
            print::str_time("Let me know if you see something you like.", 20);
            std::cout << std::endl << std::endl;
            displayGold();
            /// Show the user what's in the shop
            sinventory->viewInventory();
            std::cout << std::endl;

            /// Select an item to purchase
            print::str_time("What would you like to see?: ", 20);
            print::setCursor(true);
            command.clear();
            while(command[0] == '\n' || command.empty())
                getline(std::cin, command);
            print::setCursor(false);
            std::cout << std::endl;
            if(print::is_number(command)) {
                itemIndex = std::stoi(command);
                /// Decrement so that it starts counting at 0
                itemIndex--;

                /** If the selected item is a weapon */
                if(itemIndex < lastWeapon && lastWeapon != 0 && checkIndex(itemIndex)) {
                    /// Reusing the command variable for printing
                    command = "Are you use that you would like to purchase the " +
                              sinventory->getWeapons().at(itemIndex)->getName() + "?  (y/n)\nIt's only " +
                              std::to_string(sinventory->getWeapons().at(itemIndex)->getSellValue()) +
                              " gold!\nSpecial price for my special friend!!!";
                    print::str(command);
                    std::cout << std::endl;
                    /// Enter purchase confirmation
                    print::setCursor(true);
                    std::cout << ">>> ";
                    std::cin >> command;
                    print::setCursor(false);
                    switch(formatCommand(command)) {
                    case 1:
                        /// Set the cost as a dummy variable
                        cost = sinventory->getWeapons().at(itemIndex)->getSellValue();

                        if(playerAfford(cost)) {
                            /// Make the customer pay for their goods
                            customer->setGold(-cost);
                            /// Give the shop their money
                            gold += cost;
                            /// Add the purchased weapon to the players inventory
                            customer->getInventory()->
                            addWeapon(sinventory->removeWeapon(itemIndex));
                            /// Reduce the stock amount
                            lastWeapon--;
                            lastIndex--;
                            confirmPurchase();
                        } else
                            tooExpensive(cost);
                        break;

                    case 2:
                        somethingElse();
                        break;
                    }
                }
                /** If the selected item is a consumable */
                else if(itemIndex < lastConsumable && lastConsumable != 0
                        && checkIndex(itemIndex)) {
                    /// Adjust the index to account for the weapons
                    itemIndex -= lastWeapon;
                    /// Reusing the command variable for printing
                    command = "Are you use that you would like to purchase a " +
                              sinventory->getConsumables().at(itemIndex).front()->getName() +
                              "? (y/n)\nIt's only " +
                              std::to_string(sinventory->getConsumables().at(itemIndex).front()
                                             ->getSellValue()) + " gold!";

                    print::str(command);
                    std::cout << std::endl;
                    /// Enter purchase confirmation
                    std::cout << ">>> ";
                    print::setCursor(true);
                    std::cin >> command;
                    print::setCursor(false);

                    switch(formatCommand(command)) {
                    case 1:
                        /// Set the cost as a dummy variable
                        cost = sinventory->getConsumables().at(itemIndex).front()
                               ->getSellValue();
                        if(playerAfford(cost)) {
                            /// Make the customer pay for their goods
                            customer->setGold(-cost);
                            /// Give the shop their money
                            gold += cost;
                            /// Add the purchased weapon to the players inventory
                            customer->getInventory()->addConsumables(
                                sinventory->removeConsumables(itemIndex, 1));
                            /// Reduce the stock amount if there is no more left
                            if(sinventory->getConsumables().at(itemIndex).empty()) {
                                lastConsumable--;
                                lastIndex--;
                            }
                            confirmPurchase();
                        } else
                            tooExpensive(cost);
                        break;
                    /// Stop the transaction
                    case 2:
                        somethingElse();
                        break;
                    }

                }
                /** If the selected item is an ability */
                else if(checkIndex(itemIndex) && hasAbility) {

                    /// Reusing the command variable for printing
                    command = "Are you use that you would like to purchase a " +
                              sinventory->getAbilities().front()->getName() +
                              "? (y/n)\nIt's only " +
                              std::to_string(sinventory->getAbilities().front()->getSellValue())
                              + " gold!";

                    print::str(command);
                    std::cout << std::endl;
                    /// Enter purchase confirmation
                    std::cout << ">>> ";
                    print::setCursor(true);
                    std::cin >> command;
                    print::setCursor(false);

                    switch(formatCommand(command)) {
                    case 1:
                        /// Set the cost as a dummy variable
                        cost = sinventory->getAbilities().front()->getSellValue();
                        if(playerAfford(cost)) {
                            /// Make the customer pay for their goods
                            customer->setGold(-cost);
                            /// Give the shop their money
                            gold += cost;
                            /// Add the purchased weapon to the players inventory
                            customer->getInventory()->addAbility(sinventory->removeAbility(0));
                            /// Reduce the stock amount
                            lastIndex--;
                            hasAbility = false;
                            confirmPurchase();
                        } else
                            tooExpensive(cost);
                        break;
                    /// Stop the transaction
                    case 2:
                        somethingElse();
                        break;
                    }
                }
            }

            else {
                print::textColour(print::C_RED);
                print::str("Invalid Index");
                std::cout << std::endl;
                print::textColour(print::C_DEFAULT);
            }
            break;

        /** sell, s */
        case 2:
            /// If the players inventory is empty
            if(customer->getInventory()->isEmpty()) {
                print::str
                ("What do you want to sell me?! The lint in your pockets?!");
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "HA!" << std::endl;

                print::str
                (customer->getName() + "'s inventory is empty.\n");
                std::cout << std::endl;
                break;
            }
            /// Initialize the lastPlayer[inventory] index, this is cleaner
            lastPlayerWeapon = customer->getInventory()->getWeapons().size();
            lastPlayerConsumable = customer->getInventory()->getConsumables().size()
                                   + lastPlayerWeapon;

            if(!customer->getInventory()->getAbilities().empty()) {
                lastPlayerIndex = customer->getInventory()->getAbilities().size()
                                  + lastPlayerWeapon + lastPlayerConsumable;
            } else
                lastPlayerIndex = lastPlayerWeapon + lastPlayerConsumable;

            /// Show how much money then shop and player have
            displayGold();
            ///  Display the customers (players) inventory
            customer->getInventory()->viewInventory();
            std::cout << std::endl;
            /// Select an item to sell
            print::str_time("Alright, lets see what you got: ", 20);
            print::setCursor(true);
            command.clear();
            while(command[0] == '\n' || command.empty())
                getline(std::cin, command);
            std::cout << std::endl;
            print::setCursor(false);
            if(print::is_number(command)) {
                itemIndex = std::stoi(command);
                itemIndex--;
                /// Decrement so that it starts counting at 0


                /**  Sell Weapons */
                if(itemIndex < lastPlayerWeapon && lastPlayerWeapon != 0
                        && checkIndex(itemIndex)) {
                    command =
                        "Sure you want to let this sweet baby go?! (y/n)\nI haven't seen a "
                        + customer->getInventory()->getWeapons().at(itemIndex)->getName()
                        + " in a good while.";
                    /// Confirmation on selling message
                    print::str(command);
                    std::cout << std::endl;

                    print::setCursor(true);
                    /// Enter sale confirmation
                    std::cout << ">>> ";
                    std::cin >> command;
                    print::setCursor(false);

                    switch(formatCommand(command)) {
                    /// Sell item
                    case 1:
                        cost = customer->getInventory()
                               ->getWeapons().at(itemIndex)->getSellValue();
                        if(shopAfford(cost)) {
                            print::str("Sold " +
                                       customer->getInventory()->getWeapons().at(itemIndex)->getName()
                                       + " for " + std::to_string(cost));
                            std::cout << std::endl;
                            /// Remove the item from the player, and give it to the shop
                            sinventory->addWeapon
                            (customer->getInventory()->removeWeapon(itemIndex));
                            /// Give the player their money for the item
                            customer->setGold(cost);
                            /// Remove that gold from the shop
                            gold -= cost;
                            /// Adjust the shops stock numbers
                            lastWeapon++;
                            lastIndex++;
                        }
                        /// If the shop does not have enough money
                        else
                            shopCantAfford();
                        break;
                    /// Cancel sale
                    case 2:
                        somethingElse();
                        break;
                    }
                }

                /** Sell consumables */
                else if (itemIndex < lastPlayerConsumable && lastPlayerConsumable != 0
                         && checkIndex(itemIndex)) {
                    command = "I always to have extra of those kicking around! "
                              "I'll take it if you're sure. (y/n)";
                    print::str(command);
                    std::cout << std::endl;

                    /// Account for the weapons in the list
                    itemIndex -= lastPlayerWeapon;
                    /// Enter sale confirmation
                    std::cout << ">>> ";
                    print::setCursor(true);
                    std::cin >> command;
                    print::setCursor(false);
                    switch(formatCommand(command)) {
                    /// Sell item
                    case 1:
                        cost = customer->getInventory()
                               ->getConsumables().at(itemIndex).front()
                               ->getSellValue();

                        if(shopAfford(cost)) {
                            print::str("Sold " +
                                       customer->getInventory()->getConsumables().at(itemIndex).front()
                                       ->getName() + " for " + std::to_string(cost));
                            std::cout << std::endl;

                            /// Remove the item from the player, and give it to the shop
                            sinventory->addConsumables(customer->getInventory()
                                                       ->removeConsumables(itemIndex, 1));
                            /// Give the player their money for the item
                            customer->setGold(cost);
                            /// Remove that gold from the shop
                            gold -= cost;
                            /// Adjust the shops stock numbers
                            lastConsumable++;
                            lastIndex++;
                        }
                        /// If the shop does not have enough money
                        else
                            shopCantAfford();
                        break;
                    /// Cancel sale
                    case 2:
                        somethingElse();
                        break;
                    }
                }
                /** Sell abilities */
                else if (itemIndex < lastPlayerIndex && checkIndex(itemIndex)) {
                    /// Account for the weapons in the list
                    itemIndex -= lastPlayerConsumable;

                    command = "No way... You know how to use the " +
                              customer->getInventory()->getAbilities().at(itemIndex)->getName()
                              + " ability!\nAre you sure I can take that off your hands! (y/n)";
                    print::str(command);
                    std::cout << std::endl;

                    /// Enter sale confirmation
                    std::cout << ">>> ";
                    print::setCursor(true);
                    std::cin >> command;
                    print::setCursor(false);
                    switch(formatCommand(command)) {
                    /// Sell item
                    case 1:
                        cost = customer->getInventory()
                               ->getAbilities().at(itemIndex)->getSellValue();

                        if(shopAfford(cost)) {
                            print::str("Sold " +
                                       customer->getInventory()->getAbilities().at(itemIndex)->getName()
                                       + " for " + std::to_string(cost));
                            std::cout << std::endl;

                            /// Remove the item from the player, and give it to the shop
                            sinventory->addAbility(customer->getInventory()
                                                   ->removeAbility(itemIndex));
                            /// Give the player their money for the item
                            customer->setGold(cost);
                            /// Remove that gold from the shop
                            gold -= cost;
                            /// Adjust the shops stock numbers
                            lastIndex++;
                            hasAbility = true;
                        }
                        /// If the shop does not have enough money
                        else
                            shopCantAfford();

                        break;
                    /// Cancel sale
                    case 2:
                        somethingElse();
                        break;
                    }
                }
            }

            else {
                print::textColour(print::C_RED);
                print::str("Invalid Index");
                std::cout << std::endl;
                print::textColour(print::C_DEFAULT);
            }
            break;


        /** Exit and player management */
        /// vi, view the players inventory
        case 121:
            print::str(customer->getName() + " has " + std::to_string(customer->getGold()) + " gold.\n");
            customer->inventoryManagement();
            break;
        /// exit, ex
        case 0:
            print::str("Best of luck out there adventurer!");
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            /// Empty the screen when they leave the shop
            print::clearScreen();
            stillShoping = false;
            break;
        /** Debugging */
        /// Give the player 999 gold for testing
        case 99:
            customer->setGold(999);
            break;

        /// Invalid command
        default:
            print::textColour(print::C_RED);
            print::str("Invalid Command");
            std::cout << std::endl;
            print::textColour(print::C_DEFAULT);
            std::cout
                    << "Type 'buy' or 'sell' to access the different shop menus\n"
                    <<  "'inventory' ('i') or 'exit' ('e')"
                    << std::endl << std::endl;
            break;
        }
    }
}

int shopManager::formatCommand(std::string command) {
    for(unsigned int i = 0; i < command.length(); i++)
        command[i] = std::tolower(command[i]);

    if(command == "buy" || command == "b" || command == "yes" || command == "y")
        return 1;

    else if (command == "sell" || command == "s"
             || command == "no" || command == "n")
        return 2;
    else if (command == "inventory" || command == "i")
        return 121;
    // give the player money for testing
    else if(command == "ag")
        return 99;

    else if (command == "exit" || command == "leave" || command == "ex" || command == "e")
        return 0;

    return -1;
}

bool shopManager::playerAfford(const int& cost) {
    return (customer->getGold() >= cost);
}

bool shopManager::shopAfford(const int& cost) {
    return cost <= gold;
}

void shopManager::tooExpensive(const int& cost) {
    std::string toPrint;
    switch(rand() % 3) {
    case 0:
        toPrint = "Look. The price is the price kid. Maybe one day you'll have "
                  + std::to_string(cost - customer->getGold()) +
                  "\nmore gold and you can get this one.";
        print::str(toPrint);
        std::cout << std::endl;
        break;

    case 1:
        toPrint = "Some monster slayer... can't afford " + std::to_string(cost)
                  +" coins for some clearly needed supplies.\n" +
                  "\nMaybe there's something here you actually can afford...\n" +
                  "Take another look around kid.";
        print::str(toPrint);
        std::cout << std::endl;
        break;

    case 2:
        toPrint = "O.K. You have " + std::to_string(customer->getGold())
                  +" gold.\n"
                  "What you want costs " + std::to_string(cost) + " gold.\n" +
                  "See how that first number is smaller than the second one.\n" +
                  "That means you can't have it, until the first number is bigger.";
        print::str(toPrint);
        std::cout << std::endl;
        break;
    }
}

void shopManager::somethingElse() {
    switch(rand() % 3) {
    case 0:
        print::str("Something else perhaps?");
        std::cout << std::endl;
        break;
    case 1:
        print::str("I'm sure we can find you something more your style!");
        std::cout << std::endl;
        break;
    case 2:
        print::str("Yeah, no one ever wants that one");
        std::cout << std::endl;
        break;
    default:
        print::str("Not for you, that's fine. I got lots of good stuff around");
        std::cout << std::endl;
        break;
    }
}

bool shopManager::checkIndex(const int& index) {
    return (index >= 0 && index < lastIndex);
}

void shopManager::displayGold() {
    std::cout
            << "Shops Gold: " << gold << std::setw(40)
            << customer->getName() << " has " << customer->getGold() << " gold."
            << std::endl;
}

void shopManager::confirmPurchase() {
    switch(rand() % 6) {
    case 0:
        print::str("GREAT choice hero! This'll set you apart "
                   "from the rest of those\nchicken chasers out there!!!");
        std::cout << std::endl;
        break;
    case 1:
        print::str("Couldn't have picked a better one myself!");
        std::cout << std::endl;
        break;
    case 2:
        print::str("You'll be the talk of the spire with that!");
        std::cout << std::endl;
        break;
    case 3:
        print::str("Thanks. That things been sitting around here for eons...");
        std::cout << std::endl;
        break;
    case 4:
        print::str("Everyone deserves a little treat now and again!");
        std::cout << std::endl;
        break;
    case 5:
        print::str("That's one to bring home! Show it the folks!");
        std::cout << std::endl;
        break;
    }
}

void shopManager::shopCantAfford() {
    switch(rand() % 4) {
    case 0:
        print::str("That's too steep for what I can afford right now adventurer");
        std::cout << std::endl;
        break;
    case 1:
        print::str
        ("If my coin purse wasn't so light these days I would jump on that!");
        std::cout << std::endl;
        break;
    case 2:
        print::str
        ("It's just not in the cards for me right now. Maybe after my taxes!");
        std::cout << std::endl;
        break;
    case 3:
        print::str
        ("Oh sorry! Must have dropped my purse somewhere, I don't have enough!");
        std::cout << std::endl;
        break;
    }
}








