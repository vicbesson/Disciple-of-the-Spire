#include "monster.h"

monster::monster(std::string tName, std::string tRace, int tMaxHP,
                 std::vector<int> tMStats, int rl) {
    int spawnLevel = rl / 5;
    if(spawnLevel < 1)
        spawnLevel = 1;
    else if(spawnLevel > 5)
        spawnLevel = 5;
    level = spawnLevel;
    if (rl % 5 == 0)
        isBoss = true;
    else
        isBoss = false;
    name = tName;
    race = tRace;
    maxHealth = tMaxHP;
    currentHealth = maxHealth;
    mainStats = tMStats;
    initMonster();
}

monster::~monster() {

}

std::ostream& operator << (std::ostream& out, monster& toRender) {
    int nameSpacer = 20 - toRender.getName().length();
    int raceSpacer = 15 - toRender.getRace().length();
    int levelSpacer = 5;
    int hpSpacer = 4 - std::to_string(toRender.getCurrentHealth()).length();
    std::string strBonus;
    std::string dexBonus;
    std::string intBonus;

//    std::string dmgBonusSign;
//    // Change the operation after the weapon damage to +/- based on the players stats
//    if (toRender.getDamagePower() >= 0)
//        dmgBonusSign = " + ";
//    else
//        dmgBonusSign = " - ";

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

    out <<

        toRender.getName() << std::setw(nameSpacer) << toRender.getRace()
        << std::setw(raceSpacer)
        << "Level: " << toRender.getLevel() << std::setw(levelSpacer)
        << "HP: " << std::setw(hpSpacer) << toRender.getCurrentHealth() << " / "
        << toRender.getMaxHealth()
        << "\n" << std::setfill('.')
        // Print out the players stats
        << "0.Str" << std::setw(5) << toRender.getStats()[0] << strBonus
        << abs(toRender.getStatBonuses()[0]) << "\n"
        << "1.Dex" << std::setw(5) << toRender.getStats()[1] << dexBonus
        << abs(toRender.getStatBonuses()[1]) << "\n"
        << "2.Int" << std::setw(5) << toRender.getStats()[2] << intBonus
        << abs(toRender.getStatBonuses()[2]) << "\n"
        << "3.Spd" << std::setw(5) << toRender.getStats()[3]
        // reset the fill back to empty space
        << std::setfill(' ') << "\n";

    if(!toRender.getActiveAbilities().empty()) {
        int index = 0;
        out << "Active Abilities:\n";
        for(auto i : toRender.getActiveAbilities())
            out
                    << std::setw(4) << ++index
                    << std::setw(10 + i->getName().length() / 2)
                    << *i << std::endl;
    }

    out << std::endl;

    return out;
}

void monster::initMonster() {
    int tMainStat = 0;
    int tMainStatIndex = -1;

    // Check if str, dex, or int is highest for that race
    for (unsigned int i = 0; i < statBonuses.size(); i++) {
        if (mainStats[i] > tMainStat) {
            tMainStat = mainStats[i];
            tMainStatIndex = i;
        }
        if (i == 2 && mainStats[i] > tMainStat && mainStats[0] < mainStats[i]) {
            tMainStat = mainStats[i];
            tMainStatIndex = i;
        }
    }
    // Temp dice to be used for selecting which stats the monster gets
    // If it's a boss, increase its odds of getting good stat rolls (bigger die)
    // and double its level
    dice* lvlDice = new dice;

    if(isBoss) {
        delete lvlDice;
        lvlDice = new dice(10);
        level *= 2;
    }


    // Balancing comes into play here because the player gets 4 extra points at level 0
    // And the monsters points are all random
    for (int i = 0; i < level; i++) {
        int tIndex = lvlDice->roll();
        // Print out the dice roll for debugging
        // std::cout << tIndex << std::endl;
        // Roll 5 or 6, gain +2 to the main stat
        if (tIndex >= 5)
            mainStats[tMainStatIndex] += 2;
        // Roll 3 or 4, gain +1 to main stat, and + 1 to a random stat
        else if (tIndex >= 3) {
            mainStats[tMainStatIndex] += 1;
            mainStats[lvlDice->roll() % 3] += 1;
        }
        // Roll 2, gain 2 random stats
        else if (tIndex == 2) {
            mainStats[lvlDice->roll() % 3] += 1;
            mainStats[lvlDice->roll() % 3] += 1;
        }
        // Roll 1 gain +2 random stats, neither can be the monsters main stat
        // Ciritcal fail
        else {
            int availablePoints = 2;

            while (availablePoints != 0) {
                int rIndex = lvlDice->roll() % 3;
                if (rIndex != tMainStatIndex) {
                    mainStats[rIndex] += 1;
                    availablePoints -= 1;
                }
            }
        }
        // Add 10% of the monster current hp and
        //     50% of the monster strength to their maxHP
        maxHealth += (maxHealth * 0.1) + (mainStats[0] * 0.5);
        currentHealth = maxHealth;
    }

    delete lvlDice;

    if(isBoss) {
        std::vector<int> tempStatReq;
        tempStatReq.push_back(tMainStatIndex);
        tempStatReq.push_back(0);
        tempStatReq.push_back(level / 2);

        equippedWeapon = new weapon(tempStatReq);

        std::vector<ability*> tempAbil;
        tempAbil.push_back(new ability(level / 2, tMainStatIndex));

        // Give the player the monsters 0th ability
        cInventory->addAbility(tempAbil[0]);
        setActiveAbilities(tempAbil);
    }

    else {
        spawnWeapon(level);
        std::vector<ability*> tempAbil;
        tempAbil.push_back(new ability(level));
        setActiveAbilities(tempAbil);
    }

    checkStatBonuses();
    // Arbitrary amount of gold that the monster carries
    // NEEDS TO BE BALANCED
    setGold(dice(level * 10).roll());
}
