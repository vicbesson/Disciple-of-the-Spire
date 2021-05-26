#include "consumable.h"

consumable::consumable() {
    srand(time(NULL));
    index = rand() % lastIndex;
    readInConsumableData();
}

consumable::consumable(int tid) {
    if (tid <= lastIndex && tid >= 0) {
        index = tid;

    } else
        index = 0;

    readInConsumableData();
}

consumable::~consumable() {

}

std::ostream& operator << (std::ostream& out, consumable& toRender) {
    std::string type = "";
    if(toRender.getIsPerminant())
        type = "book";
    else
        type = "potion";

    out
            << "|" << toRender.formatOutput(0, toRender.getName()) << "|"
            << toRender.formatOutput(1, type) << "|"
            << toRender.formatOutput(2, std::to_string(toRender.getSellValue()) + "g") << "|";

    return out;
}

std::string consumable::formatOutput(int type, std::string value) {
    switch(type) {
    case 0:
        while(value.length() < 23) {
            if(value.length() < 23)
                value = " " + value;
            if(value.length() < 23)
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

const int&  consumable::getID() {
    return index;
}

std::vector<int> consumable::statsToAdd() {
    return stats;
}

const bool& consumable::getIsPerminant() {
    return isPermanent;
}

void consumable::readInConsumableData() {
    std::ifstream toRead;

    toRead.open(DIR_CONSUMABLE);

    std::vector<std::string> tempData;
    std::string line;

    if (toRead.is_open()) {
        int lineCount = 0;
        while (getline(toRead, line)) {
            if (lineCount == index) {
                std::stringstream parsedText(line);
                while (getline(parsedText, line, ',')) {
                    tempData.push_back(line);
                }
                break;
            }
            lineCount++;
        }
        toRead.close();
    }

    index = std::stoi(tempData[0]);
    name = tempData[1];
    stats.push_back(std::stoi(tempData[2]));
    stats.push_back(std::stoi(tempData[3]));
    isPermanent = std::stoi(tempData[4]);
    cost = std::stoi(tempData[5]);
    sellValue = std::stoi(tempData[6]);
    description = tempData[7];
}
