#include "inventory.h"

inventory::inventory() {
    //inventorySize = 10;
}

inventory::~inventory() {
    for (unsigned int i = 0; i < consumableStacks.size(); i++) {
        for (consumable* j : consumableStacks[i]) {
            delete j;
        }
        consumableStacks[i].clear();
    }
    consumableStacks.clear();
    for (weapon* i : weapons) {
        delete i;
    }
    weapons.clear();
    for (ability* i : abilities) {
        delete i;
    }
    abilities.clear();
}

/*int inventory::getInventorySize() {
  return inventorySize;
}*/
std::string inventory::formatIndex(std::string index) {
    while (index.length() < 7) {
        if (index.length() < 7)
            index = " " + index;
        if (index.length() < 7)
            index = index + " ";
    }
    return index;
}

void inventory::viewInventory() {
    int index = 0;
    if (!weapons.empty()) {
        std::cout << "\nWeapon's\n"
                  << "| Index |             Name              |  Stat Req | "
                  << "Lvl Req | Damage | Price |\n"
                  << std::setw(80) << std::setfill('-') << ' ' << std::setfill(' ')
                  << std::endl;
        for (weapon* i : weapons) {
            index++;
            std::cout << "|" << formatIndex(std::to_string(index)) << *i << std::endl;
        }
    }
    if (!consumableStacks.empty()) {
        std::cout
                << "Consumable's\n"
                << "| Index |         Name          |  Type  | Price | Amount|\n"
                << std::setw(59) << std::setfill('-') << ' ' << std::setfill(' ')
                << std::endl;

        for (std::vector<consumable*> j : consumableStacks) {
            if (!j.empty()) {
                index++;
                consumable* c = j.front();
                std::cout << "|" << formatIndex(std::to_string(index)) << *c
                          << formatIndex(std::to_string(static_cast<int>(j.size())))
                          << "|" << std::endl;
            }
        }
    }
    if (!abilities.empty()) {
        std::cout
                << "Stored Abilities\n"
                << "| Index |        Name         |   CD   |  Stat Req | "
                << "Lvl Req | Damage | Price |\n"
                << std::setw(80) << std::setfill('-') << ' ' << std::setfill(' ')
                << std::endl;
        for (ability* k : abilities) {
            index++;
            std::cout << "|" << formatIndex(std::to_string(index)) << *k
                      << std::endl;
        }
    }

}

std::vector<std::vector<consumable*>> inventory::removeAllConsumables() {
    std::vector<std::vector <consumable*>> tempvector = consumableStacks;
    for (unsigned int i = 0; i < consumableStacks.size(); i++) {
        consumableStacks[i].clear();
    }
    consumableStacks.clear();
    return tempvector;
}

std::vector<weapon*> inventory::removeAllWeapons() {
    std::vector<weapon*> tmpvector = weapons;
    weapons.clear();
    return tmpvector;
}

/*bool inventory::checkForRoom(unsigned int amountToAdd) {
  int counter = amountToAdd;
  for (std::vector<consumable*> i : consumableStacks) {
    counter += i.size();
  }
  counter += weapons.size();
  if (counter > inventorySize) {
    return false;
  } else {
    return true;
  }
}*/

bool inventory::deleteConsumables(unsigned int index, unsigned int amount) {
    // to stop the compiler from giving warning
    if (consumableStacks.size() > index) {
        if (consumableStacks[index].size() < amount) {
            amount = consumableStacks[index].size();
        }
        for (int i = amount; i <= 0; i--) {
            delete consumableStacks[index].front();
            consumableStacks[index].erase(consumableStacks[index].begin());
        }
        if(consumableStacks[index].empty())
            consumableStacks.erase(consumableStacks.begin() + index);
        return true;
    }
    return false;
}

bool inventory::deleteWeapon(unsigned int index) {
    if (weapons.size() > index) {
        delete weapons[index];
        weapons.erase(weapons.begin() + index);
        return true;
    }
    /// temp
    return false;
}

void inventory::addConsumables(std::vector<consumable*> conStack) {
    if (conStack.size() > 0) {
        int index = conStack[0]->getID();
        bool found = false;
        for (unsigned int i = 0; i < consumableStacks.size(); i++) {
            if (consumableStacks[i].front()->getID() == index) {
                found = true;
                for (consumable* con : conStack) {
                    consumableStacks[i].push_back(con);
                }
            }
        }
        if (!found)
            consumableStacks.push_back(conStack);
    }
}


std::vector<consumable*> inventory::removeConsumables(unsigned int index,
        unsigned int amount) {
    std::vector<consumable*> tempvector;
    if (index < consumableStacks.size()) {
        if (consumableStacks[index].size() < amount) {
            amount = consumableStacks[index].size();
        }
        for (unsigned int i = 0; i < amount; i++) {
            tempvector.push_back(consumableStacks[index].front());
            consumableStacks[index].erase(consumableStacks[index].begin());
        }
        if(consumableStacks[index].empty())
            consumableStacks.erase(consumableStacks.begin() + index);
    }
    return tempvector;
}


weapon* inventory::removeWeapon(unsigned int index) {
    weapon* tempweapon = new weapon;
    if (weapons.size() > index) {
        tempweapon = weapons[index];
        weapons.erase(weapons.begin() + index);
    }
    return tempweapon;
}

void inventory::addWeapon(weapon* wpnToAdd) {
    if (wpnToAdd != nullptr) {
        weapons.push_back(wpnToAdd);
    }
}

void inventory::addAbility(ability* abilityToAdd) {
    if (abilityToAdd != nullptr) {
        abilities.push_back(abilityToAdd);
    }
}

ability* inventory::removeAbility(unsigned int index) {
    ability* tempability = new ability;
    if (abilities.size() > index) {
        tempability = abilities[index];
        abilities.erase(abilities.begin() + index);
    }
    return tempability;
}

std::vector<ability*> inventory::getAbilities() {
    return abilities;
}

std::vector<weapon*> inventory::getWeapons() {
    return weapons;
}

std::vector<std::vector<consumable*>> inventory::getConsumables() {
    return consumableStacks;
}

bool inventory::isEmpty() {
    return abilities.empty() && weapons.empty() && consumableStacks.empty();
}
