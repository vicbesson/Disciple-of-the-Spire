#include "ability.h"

ability::ability() {
    abilityDice = nullptr;
    cooldown = 0;
    currentCooldown = 0;
    onCooldown = false;
    diceRolls = 0;
    diceSize = 0;
    cost = 0;
    sellValue = 0;
}

ability::ability(int lev) {
    srand(time(NULL));
    if(lev > 5 || lev < 1)
        lev = 1;

    int rStat = rand() % ability::allAbilities->at(lev - 1).size();
    int rAbility = rand() % ability::allAbilities->at(lev - 1)[rStat].size();
    ability::abilityData ad = ability::allAbilities->at(lev - 1)[rStat][rAbility];

    name = ad.name;

    cooldown = ad.cooldown;
    currentCooldown = 0;

    diceRolls = ad.dRoll;
    diceSize = ad.dSize;

    description = ad.description;

    statRequirements.push_back(ad.aStats[0]);
    statRequirements.push_back(ad.aStats[1]);
    statRequirements.push_back(ad.aStats[2]);

    abilityDice = new std::vector<dice>;

    for(int i = 0; i < diceRolls; i++)
        abilityDice->push_back(dice(diceSize));

    cost = 50 * diceRolls;
    sellValue = cost / 2;
    /**
      Until something is in place to check if an ability exists, I've
      commented this out to prevent seg faults
    */
//  ability::allAbilities->at(lev - 1)[rStat].erase
//                (ability::allAbilities->at(lev - 1)[rStat].begin() + rAbility);
}

ability::ability(int lev, int sType) {
    if(lev > 5 || lev < 1)
        lev = ability::allAbilities->size() - 1;
    if(sType > 3 || sType < 0)
        sType = ability::allAbilities->at(lev).size() - 1;

    srand(time(NULL));
    int rAbility = rand() % ability::allAbilities->at(lev - 1)[sType].size();
    ability::abilityData ad = ability::allAbilities->at(lev - 1)[sType][rAbility];
    name = ad.name;
    cooldown = ad.cooldown;
    currentCooldown = 0;
    diceRolls = ad.dRoll;
    diceSize = ad.dSize;
    description = ad.description;
    statRequirements.push_back(ad.aStats[0]);
    statRequirements.push_back(ad.aStats[1]);
    statRequirements.push_back(ad.aStats[2]);
    abilityDice = new std::vector<dice>;
    for(int i = 0; i < diceRolls; i++)
        abilityDice->push_back(dice(diceSize));

    cost = 50 * diceRolls;
    sellValue = cost / 2;

    /**
      Until something is in place to check if an ability exists, I've
      commented this out to prevent seg faults
    */
//  ability::allAbilities->at(lev - 1)[sType].erase
//        (ability::allAbilities->at(lev - 1)[sType].begin() + rAbility);
}
// Testing : going to be deleted
ability::ability(int lev, int sType, int abil) {
    if(lev > 5 || lev < 1)
        lev = ability::allAbilities->size();
    if(sType > 3 || sType < 0)
        sType = ability::allAbilities->at(lev).size() - 1;
    if(abil > 3 || abil < 0)
        abil = ability::allAbilities->at(lev)[sType].size() -1;

    srand(time(NULL));
    ability::abilityData ad = ability::allAbilities->at(lev - 1)[sType][abil];
    name = ad.name;
    cooldown = ad.cooldown;
    currentCooldown = 0;
    diceRolls = ad.dRoll;
    diceSize = ad.dSize;
    description = ad.description;
    statRequirements.push_back(ad.aStats[0]);
    statRequirements.push_back(ad.aStats[1]);
    statRequirements.push_back(ad.aStats[2]);
    abilityDice = new std::vector<dice>;
    for(int i = 0; i < diceRolls; i++)
        abilityDice->push_back(dice(diceSize));
    ability::allAbilities->at(lev - 1)[sType].erase
    (ability::allAbilities->at(lev - 1)[sType].begin());

}

ability::~ability() {
    delete abilityDice;
}


std::ostream& operator << (std::ostream& out, ability& toRender) {
    std::string tempType = "";
    std::string aDamage = std::to_string(toRender.getDiceRolls()) + " * D" + std::to_string(toRender.getDiceSize());
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
    case 3:
        tempType = "Spd: " + std::to_string(toRender.getStatRequirements()[1]);
    }
    out << "|" << toRender.formatOutput(0, toRender.getName()) << "|"
        << toRender.formatOutput(1, std::to_string(toRender.getCooldown())) << "|"
        << toRender.formatOutput(2, tempType) << "|"
        << toRender.formatOutput(3, std::to_string(toRender.getStatRequirements()[2])) << "|"
        << toRender.formatOutput(4, aDamage) << "|"
        << toRender.formatOutput(5, std::to_string(toRender.getSellValue()) + "g") << "|";
    return out;
}

std::string ability::formatOutput(unsigned int type, std::string value) {
    switch(type) {
    case 0:
        while(value.length() < 21) {
            if(value.length() < 21)
                value = " " + value;
            if(value.length() < 21)
                value = value + " ";
        }
        break;
    case 1:
        while(value.length() < 8) {
            if(value.length() < 8)
                value = " " + value;
            if(value.length() < 8)
                value = value + " ";
        }
        break;
    case 2:
        while(value.length() < 11) {
            if(value.length() < 11)
                value = " " + value;
            if(value.length() < 11)
                value = value + " ";
        }
        break;
    case 3:
        while(value.length() < 9) {
            if(value.length() < 9)
                value = " " + value;
            if(value.length() < 9)
                value = value + " ";
        }
        break;
    case 4:
        while(value.length() < 8) {
            if(value.length() < 8)
                value = " " + value;
            if(value.length() < 8)
                value = value + " ";
        }
        break;
    case 5:
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

/**     GETTERS       */
std::string ability::getDescription() {
    return description;
}

int ability::getDiceRolls() {
    return abilityDice->size();
}

int ability::getDiceSize() {
    return abilityDice->front().getSides();
}

int ability::getCurrentCooldown() {
    return currentCooldown;
}

int ability::getCooldown() {
    return cooldown;
}

std::vector<int> ability::getStatRequirements() {
    return statRequirements;
}


void ability::reduceCooldown() {
    // Check if this ability is on cooldown
    // && if the remaining cooldown is > 0
    // Stops the currentCD from going negative for combat HUD
    if(onCooldown && currentCooldown > 0) {
        currentCooldown--;
        // Take this ability off cooldown
        if(currentCooldown <= 0) {
            onCooldown = false;
        }
    }
}

int ability::dealDamage() {
    if(!onCooldown) {
        onCooldown = true;
        currentCooldown = cooldown;
        int tempDamage = 0;
        for(dice i : *abilityDice) {
            tempDamage += i.roll();
        }
        return tempDamage;
    } else {
        return 0;
    }
}

int ability::getCost() {
    return cost;
}

int ability::getSellValue() {
    return sellValue;
}

int ability::getIndex() {
    return index;
}
