#include "baseCharacter.h"



baseCharacter::baseCharacter() {
    cInventory = new inventory();
    equippedWeapon = nullptr;
    mainStats.resize(4, 0);
    statBonuses.resize(4, 0);
    gold = 0;
    level = 0;
}

baseCharacter::~baseCharacter() {
    for(ability* i : activeAbilities) {
        delete i;
    }
    activeAbilities.clear();
    delete cInventory;
    delete equippedWeapon;
}

std::ostream& operator << (std::ostream& out, baseCharacter& toRender) {
    int nameSpacer = 18 - toRender.getName().length();
    int hpSpacer = 4 - std::to_string(toRender.getCurrentHealth()).length();
    int levelSpacer = 3 - std::to_string(toRender.getLevel()).length();

    // from using their current weapon based on their stats
    int dmgBonus = abs(toRender.getDamagePower());
    std::string dmgBonusSign;
    // Change the operation after the weapon damage to +/- based on the
    // players stats
    if (toRender.getDamagePower() >= 0)
        dmgBonusSign = " + ";
    else
        dmgBonusSign = " - ";

    out << "\n"
        << toRender.getName() << std::setw(nameSpacer)
        << "HP: " << std::setw(hpSpacer)
        << toRender.getCurrentHealth() << " / " << toRender.getMaxHealth()
        << std::setw(9)
        << "Level: " << toRender.getLevel() << std::setw(levelSpacer)
        << "\n" << toRender.getWeapon()->getName() << std::setw(3)
        << toRender.getWeapon()->getDiceRolls() << "d"
        << toRender.getWeapon()->getDiceSize()
        << dmgBonusSign << dmgBonus

        << std::endl;

    return out;
}

void baseCharacter::spawnWeapon(int level) {
    // If a weapon already exists, delete it
    if (equippedWeapon != nullptr)
        delete equippedWeapon;
    // Not sure if we still need this
    if (this != nullptr) {
        equippedWeapon = new weapon(level);
        // Check if this weapon gets a bonus from the characters stats
        updateDamagePower();
    }
}

void baseCharacter::checkStatBonuses() {
    // Reset statBonuses vector
    statBonuses.clear();
    statBonuses.resize(4);
    // Check Str, Dex, Int

    for (int i = 0; i < 3; i ++) {
        // Needs to work with odds (i.e. 7 should be - 2 not -1
        if((mainStats[i] - 10) / 2 >= 0)
            statBonuses[i] = (mainStats[i] - 10) / 2;
        else
            statBonuses[i] = 0;
        // Every 4 points of dexterity increases the players speed by 1
        // I figure this way dex grants a bonus to speed, but since it also
        // increases damage, it needs to have some balance
        if (i == 1 && statBonuses[1] > 0 && statBonuses[1] - mainStats[3] > 1) {
            mainStats[3] += 1;
        }
    }
    updateDamagePower();
}

void baseCharacter::updateDamagePower() {
    // If the character has a weapon, use that weapons main stat to determine
    // the players damage power
    if (equippedWeapon != nullptr)
        damagePower = statBonuses[equippedWeapon->getStatRequirements()[0]];

    // If no weapon is equipped, add the players str to their damagePower
    else
        damagePower = statBonuses[0];
}

int baseCharacter::useAbility(unsigned int index) {
    if(activeAbilities.size() > index) {
        // If the ability uses a stat that the player has a bonus with
        // add that bonus to the damage the ability deals
        return activeAbilities[index]->dealDamage() +
               statBonuses[activeAbilities[index]->getStatRequirements()[0]];
    }
    // Invalid Ability index
    else {
        return 0;
    }
}

int baseCharacter::dealDamage() {
    return equippedWeapon->dealDamage() + damagePower;
}

void baseCharacter::takeDamage(int damage) {
    currentHealth -= damage;
}




/** *****************  Getters *****************  */
std::string baseCharacter::getName() {
    return name;
}

std::string baseCharacter::getRace() {
    return race;
}

const int&  baseCharacter::getCurrentHealth() {
    return currentHealth;
}

const int&  baseCharacter::getMaxHealth() {
    return maxHealth;
}

const int&  baseCharacter::getLevel() {
    return level;
}

const int&  baseCharacter::getDamagePower() {
    return damagePower;
}

std::vector<int> baseCharacter::getStatBonuses() {
    return statBonuses;
}

bool baseCharacter::isDead() {
    if (currentHealth <= 0)
        return true;
    else
        return false;
}

inventory* baseCharacter::getInventory() {
    return cInventory;
}

std::vector<ability*> baseCharacter::getActiveAbilities() {
    return activeAbilities;
}

void baseCharacter::setGold(int g) {
    gold += g;
}

weapon* baseCharacter::getWeapon() {
    return equippedWeapon;
}

std::vector<int> baseCharacter::getStats() {
    return mainStats;
}

const int&  baseCharacter::getGold() {
    return gold;
}

/**     setters     */
void baseCharacter::setWeapon(weapon* toSet) {
    equippedWeapon = toSet;
    // Update the new weapons damage bonus depending on the main stat used
    // by the weapon, and the players stat bonus for that stat
    updateDamagePower();
}

void baseCharacter::setActiveAbilities(std::vector<ability*> toSet) {
    // Delete all the active abilities that the player has
    for(auto d : activeAbilities)
        delete d;

    // Set the active ablilities of the player to the given abilities
    activeAbilities = toSet;
}
