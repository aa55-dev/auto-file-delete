#include "afdq.hpp"
#include "common.hpp"

#include <cerrno>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void printDeletionTime(const std::string_view deletionTime, const std::string_view path,
    const std::chrono::time_point<std::chrono::system_clock> currentTime)
{
    uint64_t deletionTimeInteger {};
    try {
        deletionTimeInteger = std::stoull(std::string(deletionTime.data(), deletionTime.length()));
    } catch (std::logic_error& e) {
        throw InvalidInputException(e.what());
    }
    const std::chrono::nanoseconds ns(deletionTimeInteger);
    const std::chrono::time_point<std::chrono::system_clock> tp(ns);

    const auto deletionLocalTime = std::chrono::zoned_time { std::chrono::current_zone(), tp };
    auto delta = tp - currentTime;

    const auto isExpired = delta.count() < 0;
    if (isExpired) {
        delta = abs(delta);
    }

    const auto deltaDays = std::chrono::duration_cast<std::chrono::days>(delta); // NOLINT(misc-include-cleaner)
    const auto deltaHours = std::chrono::duration_cast<std::chrono::hours>(delta - deltaDays);
    const auto deltaMinutes = std::chrono::duration_cast<std::chrono::minutes>(delta - deltaDays - deltaHours);

    std::cout << std::format("{} {} days, {} hours, {} minutes {}({}) {}\n",
        isExpired ? "Expired" : "Deletion in",
        deltaDays.count(), deltaHours.count(), deltaMinutes.count(),
        isExpired ? "ago " : "", deletionLocalTime, path);
}

void processFile(const std::string_view path, const std::chrono::time_point<std::chrono::system_clock>& currentTime)
{

    for (const auto& i : SKIP_DIRS) {
        if (path.starts_with(i)) {
            std::cerr << std::format("Skipped {}\n", path);
            return;
        }
    }

    std::string attr;
    try {
        attr = readAttr(path);
    } catch (std::runtime_error& e) {
        if (errno == ENOENT) {
            return;
        }
    }
    if (attr.empty()) {
        return;
    }

    printDeletionTime(attr, path, currentTime);
}
