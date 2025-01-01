#ifndef AFD_HPP
#define AFD_HPP

#include <chrono>
#include <string_view>



std::chrono::time_point<std::chrono::utc_clock> getDeletetionTime(const std::string_view input);

#endif // AFD_HPP
