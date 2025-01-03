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
#include "common.hpp"

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <syslog.h>
#include <vector>

static void printUsage(const std::string_view path)
{
    std::cout << path << "  FILES...\n";
    std::exit(1); // NOLINT(concurrency-mt-unsafe)
}

static bool processPath(const std::filesystem::path& path, const std::chrono::milliseconds::rep currentTime)
{
    for (const auto& i : SKIP_DIRS) {
        if (path.string().starts_with(i)) {
            return false;
        }
    }

    try {
        const auto delTime = readAttr(path.string());
        if (delTime.empty()) {
            return false;
        }
        const std::chrono::nanoseconds ns(std::stoull(delTime));
        return currentTime > ns.count();
    } catch (std::runtime_error& e) {
        return false;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printUsage(argv[0]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    const auto currentTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::utc_clock::now().time_since_epoch()).count();

    std::vector<std::filesystem::path> filesTodelete;
    for (int i = 1; i < argc; i++) {
        const auto& path = argv[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (std::filesystem::is_directory(path)) {
            for (const auto& p : std::filesystem::recursive_directory_iterator(argv[1])) { // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                if (processPath(p.path(), currentTime)) {
                    filesTodelete.push_back(p.path());
                }
            }
        } else {
            if (processPath(path, currentTime)) {
                filesTodelete.emplace_back(path);
            }
        }
    }

    for (const auto& i : filesTodelete) {
        syslog(LOG_INFO, "%s", std::format("Deleting: {}", i.string()).c_str()); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg,misc-include-cleaner)
        std::filesystem::remove_all(i);
    }

    return 0;
}
