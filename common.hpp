#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdexcept>
#include <string_view>

inline constexpr const char* ATTR_NAME = "user.auto-file-delete.aa55.dev";
inline constexpr auto SKIP_DIRS = { "/proc", "/dev/", "/run" };
std::string readAttr(const std::string_view path);

class InvalidInputException : public std::runtime_error {
public:
    explicit InvalidInputException(const char* msg);
};

#endif // COMMON_HPP
