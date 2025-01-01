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
