
/**
  DEBUGGING MAIN CURRENTLY IN USE BY TYLER FOR TESTING THINGS


*/

#include "gameManager.h"

#include <iostream>

int main()
{

  gameManager* myManager = new gameManager;

  myManager->startGame();

	return 0;
}
/**

    // Print functions are prefixed with 1
    if (tempCommand[0] == "prace" || tempCommand[0] == "pr")
        temp.push_back(10);

    else if (tempCommand[0] == "pplayer" || tempCommand[0] == "pp")
        temp.push_back(12);
    // Print the players weapon
    else if (tempCommand[0] == "pplayerweapon" || tempCommand[0] == "ppw")
        temp.push_back(120);
        //print view inventory
    else if (tempCommand[0] == "viewinventory" || tempCommand[0] == "vi")
        temp.push_back(121);

    // Print the monsters detailed stats
    else if (tempCommand[0] == "pmonster" || tempCommand[0] == "pm")
        temp.push_back(13);
    // Print the monsters weapon
    else if (tempCommand[0] == "pmonsterweapon" || tempCommand[0] == "pmw")
        temp.push_back(130);
    // Print the monsters gold
    else if (tempCommand[0] == "pmonstergold" || tempCommand[0] == "pmg")
        temp.push_back(131);
    // Print all the consumables in the csv
    else if (tempCommand[0] == "pconsumables" || tempCommand[0] == "pcon")
        temp.push_back(14);
    //Print all items in chest inventory
    else if(tempCommand[0] == "viewChest" || tempCommand[0] == "vc")
        temp.push_back(15);
         // Prints all the abilities in the csv
    else if (tempCommand[0] == "pabilities" || tempCommand[0] == "pa")
        temp.push_back(16);
    // Create object prefixed with 2std::vector<consumable*> t
    else if (tempCommand[0] == "makweapon" || tempCommand[0] == "mw")
        temp.push_back(20);
    // Make a player with a chosen race
    else if (tempCommand[0] == "makeplayer" || tempCommand[0] == "mp")
        temp.push_back(21);
    // Increase the players level by 1
    else if (tempCommand[0] == "levelup" || tempCommand[0] == "lvl")
        temp.push_back(210);

    else if (tempCommand[0] == "makemonster" || tempCommand[0] == "mm")
        temp.push_back(22);
    // Start combat
    else if (tempCommand[0] == "makecombat" || tempCommand[0] == "mc")
        temp.push_back(23);

    // Make a consumable, also needs an index.
    else if (tempCommand[0] == "makeconsumable" || tempCommand[0] == "mcon")
        temp.push_back(24);

    // debugging gets a prefix of 9
    else if (tempCommand[0] == "clear")
        temp.push_back(90);
    // add x to the players current experience
    else if (tempCommand[0] == "addexperience" || tempCommand[0] == "xp")
        temp.push_back(91);
    // print the damage done from a normal weapon attack by the player
    else if (tempCommand[0] == "atk")
        temp.push_back(92);

    else if(tempCommand[0] == "mainmenu" || tempCommand[0] == "mmenu")
      temp.push_back(93);
    // GTFO
    else if (tempCommand[0] == "exit" || tempCommand[0] == "quit"
          || tempCommand[0] == "e")
          temp.push_back(0);

}
*/







