#ifndef AFDQ_HPP
#define AFDQ_HPP

#include <chrono>
#include <string_view>

void processFile(const std::string_view path, const std::chrono::time_point<std::chrono::system_clock>& currentTime);
void printDeletionTime(const std::string_view deletionTime, const std::string_view path,
    const std::chrono::time_point<std::chrono::system_clock> currentTime);

#endif // AFDQ_HPP
