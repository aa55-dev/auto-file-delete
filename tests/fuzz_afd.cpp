#include "../afd.hpp"
#include "../common.hpp"

#include <cstring>
#include <iostream>
#include <string>
#include <syslog.h>

int main()
{
    std::string input;
    std::getline(std::cin, input);
    try {
        getDeletetionTime(input);
    } catch (InvalidInputException&) { // NOLINT(bugprone-empty-catch)
    }
}
