#include "afd.hpp"
#include "common.hpp"

#include <cassert>
#include <cerrno>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>

std::chrono::time_point<std::chrono::utc_clock> getDeletetionTime(const std::string_view input)
{
    // Input should contain the time period (eg: "1h")
    if (input.size() < 2) {
        throw InvalidInputException("Invalid time period");
    }

    const auto countStr = input.substr(0, input.size() - 1);
    const auto unitStr = input.at(input.size() - 1);

    uint64_t count {};
    try {
        count = std::stoul(std::string(countStr.data(), countStr.length()));
        if (count > std::numeric_limits<int16_t>::max() || count == 0) {
            throw InvalidInputException("Integer overflow");
        }
    } catch (std::logic_error& e) {
        throw InvalidInputException(e.what());
    }
    const auto currentTime = std::chrono::utc_clock::now();

    switch (unitStr) {
    case 'd':
        return currentTime + std::chrono::hours(24 * count);
    case 'h':
        return currentTime + std::chrono::hours(count);
    case 'm':
        return currentTime + std::chrono::minutes(count);
    default:
        throw InvalidInputException("Invalid time unit");
    }
}
