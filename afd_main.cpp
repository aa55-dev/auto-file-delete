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
#include "afd.hpp"
#include "common.hpp"

#include <cassert>
#include <cerrno>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/xattr.h>

[[noreturn]] static void printUsage(const std::string_view path)
{
    std::cout << path << " NUMBER[SUFFIX] FILES...\n"
              << "SUFFIX can be one of:\n"
              << "\t d: days\n"
              << "\t h: hours\n"
              << "\t m: minutes\n"
              << "Examples:\n"
              << "\t1. Mark file for deletion after 1 day\n"
              << "\t" << path << " 1d file.txt\n\n"
              << "\t2. Mark file for deletion after 30 minutes\n"
              << "\t" << path << " 30m file.txt";
    std::exit(1); // NOLINT(concurrency-mt-unsafe)
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        printUsage(argv[0]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    std::chrono::time_point<std::chrono::utc_clock> deletionTime;
    try {
        deletionTime = getDeletetionTime(argv[1]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << "\n"; // NOLINT(concurrency-mt-unsafe)
        printUsage(argv[0]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    const auto deletionTimeStr = std::to_string(deletionTime.time_since_epoch().count());

    assert(!deletionTimeStr.empty());

    for (int i = 2; i < argc; i++) {
        const auto& filename = argv[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        const auto result = setxattr(filename, ATTR_NAME, deletionTimeStr.c_str(), deletionTimeStr.size(), 0);
        if (result) {
            std::cerr << std::format("Failed to set xattr: {} {}\n", filename, strerror(errno)); // NOLINT(concurrency-mt-unsafe)
        }
    }

    return 0;
}
