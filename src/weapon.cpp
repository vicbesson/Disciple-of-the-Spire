#include "weapon.h"



weapon::weapon() {
    weaponDice = nullptr;
    diceSize = 0;
    diceRolls = 0;
    name = "not initialized";

}

weapon::weapon(int l) {
    // Check in case we try and spawn a weapon an level 0
    if(l <= 0)
        l = 1;

    srand(time(NULL));

    weaponDice = new std::vector<dice>;
    generateWeapon(l);
}

weapon::weapon(std::vector<int> sReq) {
    // Check in case we try and spawn a weapon an level 0
    if(sReq[2] <= 0)
        sReq[2] = 1;

    srand(time(NULL));
    weaponDice = new std::vector<dice>;

    statRequirements = sReq;
    statRequirements.shrink_to_fit();

    int diceSize = statRequirements[2]/2 + 4 + (rand() % 5);
    // Add one dice of the randomly chosen size to the weaponDice vector
    for(int i = 0; i < statRequirements[2]; i++) {
        weaponDice->push_back(dice(diceSize));
    }
    // Optimize!
    weaponDice->shrink_to_fit();
    // If the weapon names dictionary was read in, select a random name
    // Then delete that name from the dictionary
    if(weapon::allNames != nullptr) {
        int tempIndex = rand() % allNames->size();
        std::copy_if(allNames->at(tempIndex).begin(), allNames->at(tempIndex).end(),
                     std::back_inserter(name),
        [] (char c) {
            return c != '\r' && c != '\n';
        });
        allNames->erase(allNames->begin() + tempIndex);
        name.append(addType(diceSize, statRequirements[0]));
    } else {
        name = "invalid name";
    }

    // Arbitrary. Kind of fun to have the value based on an attack
    // Sort of like trying it out in the shop.. idk
    cost = (statRequirements[2] * 50) + dealDamage();
    sellValue = (cost / 2);
}

weapon::weapon(std::string nam, int dSize, int dRolls, std::vector<int> sReq) {
    name = nam;
    diceSize = dSize;
    diceRolls = dRolls;
    statRequirements = sReq;
    weaponDice = new std::vector<dice>;

    for (int i = 0; i < diceRolls; i++) {
        weaponDice->push_back(diceSize);
    }

    weaponDice->shrink_to_fit();
}

weapon::~weapon() {
    delete weaponDice;
}

void weapon::generateWeapon(int level) {
    // Choose a random stat: [0] str, [1] dex, [2] int
    int statType = rand() % 3;
    int diceSize = level/2 + 4 + (rand() % 5);

    // Add one dice of the randomly chosen size to the weaponDice vector
    for(int i = 0; i < level; i++) {
        weaponDice->push_back(dice(diceSize));
    }
    // Optimize!
    weaponDice->shrink_to_fit();
    // If the weapon names dictionary was read in, select a random name
    // Then delete that name from the dictionary
    if(weapon::allNames != nullptr) {
        int tempIndex = rand() % allNames->size();
        std::copy_if(allNames->at(tempIndex).begin(), allNames->at(tempIndex).end(),
                     std::back_inserter(name),
        [] (char c) {
            return c != '\r' && c != '\n';
        });
        allNames->erase(allNames->begin() + tempIndex);
        name.append(addType(diceSize, statType));
    } else {
        name = "invalid";
    }
    // Add the stat requirement chosen above to the statRequirements
    statRequirements.push_back(statType);
    // Required amount of stats to use this weapon
    // NEEDS TO BE BALANCED
    statRequirements.push_back(level * 2);
    // If the weapon does max damage, increase the required level by 1
    if(diceSize >= 12) {
        statRequirements.push_back(level + 1);
    } else {
        statRequirements.push_back(level);
    }
    // Optimize
    statRequirements.shrink_to_fit();

    // Arbitrary. Kind of fun to have the value based on an attack
    // Sort of like trying it out in the shop.. idk
    cost = (level * 50) + dealDamage();
    sellValue = (cost / 2);

}

std::string weapon::addType(int dSize, int sType) {
    switch(sType) {
    //  Strength
    case 0:
        if(dSize == 4)
            return " Club";
        else if (dSize == 5)
            return " Spiked-Club";
        else if (dSize == 6)
            return " Sword";
        else if (dSize == 7)
            return " Broad-Sword";
        else if (dSize == 8)
            return " Two-Handed Axe";
        else if (dSize == 9)
            return " Battle-Axe";
        else if (dSize == 10)
            return " Halberd";
        else if (dSize == 11)
            return " Maul";
        else if (dSize >= 12)
            return " Scythe";

        break;
    //  Dexterity
    case 1:
        if(dSize == 4)
            return " Dagger";
        else if (dSize == 5)
            return " Scimitar";
        else if (dSize == 6)
            return " Rapier";
        else if (dSize == 7)
            return " Flail";
        else if (dSize == 8)
            return " Glaive";
        else if (dSize == 9)
            return " Whip";
        else if (dSize == 10)
            return " Falchion";
        else if (dSize == 11)
            return " Morning-Star";
        else if (dSize >= 12)
            return " Bat'leth";

        break;
    // Int
    case 2:
        if(dSize == 4)
            return " Magic-Rock";
        else if (dSize < 7)
            return " Wand";
        else if (dSize < 11)
            return " Staff";
        else if (dSize == 11)
            return " Wizards Staff";
        else if (dSize >= 12)
            return " Grand-Staff";
        break;

    default:
        break;
    }
    return " Invalid Stat Requirement";
}

std::ostream& operator << (std::ostream &out, weapon &toRender) {
    std::string tempType = "";
    std::string wDamage = std::to_string(toRender.getDiceRolls()) + " * D" + std::to_string(toRender.getDiceSize());
    switch(toRender.getStatRequirements()[0]) {
    case 0:
        tempType = "Str: " + std::to_string(toRender.getStatRequirements()[1]);
        break;
    case 1:
        tempType = "Dex: " + std::to_string(toRender.getStatRequirements()[1]);
        break;
    case 2:
        tempType = "Int: " + std::to_string(toRender.getStatRequirements()[1]);
        break;
    }
    out << "|" << toRender.formatOutput(0, toRender.getName()) << "|" << toRender.formatOutput(1, tempType) << "|"
        << toRender.formatOutput(2, std::to_string(toRender.getStatRequirements()[2])) << "|" << toRender.formatOutput(3, wDamage) << "|"
        << toRender.formatOutput(4, std::to_string(toRender.getSellValue()) + "g") << "|";
    return out;
}

std::string weapon::formatOutput(int type, std::string value) {
    switch(type) {
    case 0:
        while(value.length() < 31) {
            if(value.length() < 31)
                value = " " + value;
            if(value.length() < 31)
                value = value + " ";
        }
        break;
    case 1:
        while(value.length() < 11) {
            if(value.length() < 11)
                value = " " + value;
            if(value.length() < 11)
                value = value + " ";
        }
        break;
    case 2:
        while(value.length() < 9) {
            if(value.length() < 9)
                value = " " + value;
            if(value.length() < 9)
                value = value + " ";
        }
        break;
    case 3:
        while(value.length() < 8) {
            if(value.length() < 8)
                value = " " + value;
            if(value.length() < 8)
                value = value + " ";
        }
        break;
    case 4:
        while(value.length() < 7) {
            if(value.length() < 7)
                value = " " + value;
            if(value.length() < 7)
                value = value + " ";
        }
        break;
    }
    return value;
}

int weapon::dealDamage() {
    int tempDamage = 0;
    for(auto i : *weaponDice) {
        tempDamage += i.roll();
    }

    return tempDamage;
}


/** *****************  Getters *****************  */
int weapon::getDiceRolls() {
    return weaponDice->size();
}

int weapon::getDiceSize() {
    return weaponDice->front().getSides();
}

std::vector<int> weapon::getStatRequirements() {
    return statRequirements;
}

std::string weapon::getName() {
    return name;
}



