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
