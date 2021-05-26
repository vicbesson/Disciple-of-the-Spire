#include "item.h"

item::item() {
    //ctor
}

item::~item() {
    //dtor
}
const std::string& item::getName() {
    return name;
}

const int& item::getCost() {
    return cost;
}

const int& item::getSellValue() {
    return sellValue;
}
