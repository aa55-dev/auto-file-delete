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

#include <cerrno>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string_view>

static void printUsage(const std::string_view path)
{
    std::cout << path << "  FILES...\n";
    std::exit(1); // NOLINT(concurrency-mt-unsafe)
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printUsage(argv[0]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    const auto currentTime = std::chrono::system_clock::now();

    for (int i = 1; i < argc; i++) {
        const auto& filename = argv[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (std::filesystem::is_directory(filename)) {
            for (const auto& p : std::filesystem::recursive_directory_iterator(filename, std::filesystem::directory_options::skip_permission_denied)) {

                processFile(p.path().string(), currentTime);
            }
        } else {
            processFile(filename, currentTime);
        }
    }

    return 0;
}
