#include "print.h"

int print::C_WHITE [3] = {255, 255, 255};
int print::C_BLACK [3] = {0, 0, 0};
int print::C_RED [3] = {255, 0, 0};
int print::C_GREEN [3] = {0, 255, 0};
int print::C_GREEN_D [3] = {0, 175, 0};
int print::C_BLUE [3] = {75, 75, 255};
int print::C_PURPLE [3] = {150, 75, 255};
int print::C_BROWN [3] = {153, 76, 0};
int print::C_PINK [3] = {255, 102, 255};

int print::C_DEFAULT [3] = {200, 200, 200};

void print::str(const std::string& toPrint) {
    for(auto c : toPrint) {
        std::cout << c;
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % DEFAULT_MOD));
    }
}

void print::str_time(const std::string& toPrint, const int& maxMillis) {
    for(auto c : toPrint) {
        std::cout.flush() << c;

        std::this_thread::sleep_for(std::chrono::milliseconds(maxMillis));
    }
}


void print::vec(const std::vector<std::string>& toPrint) {
    for(auto l : toPrint) {
        for(auto c : l) {
            std::cout << c;
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % DEFAULT_MOD));
        }
        std::cout << std::endl;
    }
}

void print::vec_faster(const std::vector<std::string>& toPrint) {
    int mod = DEFAULT_MOD;
    int lineCounter = -1;
    for(auto l : toPrint) {
        lineCounter++;
        if(lineCounter % (toPrint.size() /5) == 0)
            mod *= 0.8;
        for(auto c : l) {
            std::cout.flush() << c;
            if(c != ' ')
                std::this_thread::sleep_for(std::chrono::milliseconds(rand() % mod));
        }
        std::cout << std::endl;
    }
}

void print::vec_time(const std::vector<std::string>& toPrint,
                     const int& maxMillis) {
    for(auto l : toPrint) {
        std::cout << l << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % maxMillis));
    }
}

void print::initScreen() {
    // Resize the terminal, and clear the terminal of text before game begins
    system("resize -s 32 80;");
    // Set the background to black
    system("printf '\e[48;2;0;0;0m';");
    // Set the cursor to light grey
    print::textColour(C_DEFAULT);

    system("clear;");
    setCursor(false);
}
void print::textColour(const int colour[3]) {
    std::string bgColour = "printf '\e[38;2;";
    bgColour.append(std::to_string(colour[0]) + ";");
    bgColour.append(std::to_string(colour[1]) + ";");
    bgColour.append(std::to_string(colour[2]) + "m'");

    char textColour[bgColour.length()];
    strcpy(textColour, bgColour.c_str());
    system(textColour);
    std::cout.flush();
}

void print::setCursor(const bool& box) {
    if(box)
        system("printf '\e[0 q';");
    else
        system("printf '\e[4 q';");

    std::cout.flush();
}

bool print::is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
    s.end(), [](unsigned char c) {
        return !std::isdigit(c);
    }) == s.end();
}

void print::deathScreen() {
    for(int i = 0; i < 255; i += 2) {
        std::string bgColour = "printf '\e[48;2;";
        bgColour.append(std::to_string(i) + ";");
        bgColour.append(std::to_string(0) + ";");
        bgColour.append(std::to_string(0) + "m';");

        char sysCommand[bgColour.length()];
        strcpy(sysCommand, bgColour.c_str());
        system(sysCommand);

        for(int f = 0; f < 31; f++)
            std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::microseconds(2000));
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));

    for(int i = 255; i > 0 ; i -= 2) {
        std::string bgColour = "printf '\e[48;2;";
        bgColour.append(std::to_string(i) + ";");
        bgColour.append(std::to_string(0) + ";");
        bgColour.append(std::to_string(0) + "m';");

        char sysCommand[bgColour.length()];
        strcpy(sysCommand, bgColour.c_str());
        system(sysCommand);

        for(int f = 0; f < 31; f++)
            std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::microseconds(2000));
    }

}

void print::clearScreen() {
    system(SYS_CLEAR);
}

std::string print::toLower(std::string input) {
    // convert string to upper case
    std::for_each(input.begin(), input.end(), [](char & c) {
        c = ::tolower(c);
    });
    return input;
}
