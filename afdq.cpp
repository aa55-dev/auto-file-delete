/*
auto-file-delete
Copyright (c) 2025, mail@aa55.dev

This file is part of auto-file-delete.

auto-file-delete is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

auto-file-delete is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
auto-file-delete. If not, see <https://www.gnu.org/licenses/>.
*/
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
