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

#include <array>
#include <cerrno>
#include <cstdlib>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/xattr.h>

std::string readAttr(const std::string_view path)
{
    std::array<char, 128> value; // NOLINT(cppcoreguidelines-pro-type-member-init,hicpp-member-init,-warnings-as-errors)
    const auto result = getxattr(std::string(path.data(), path.length()).c_str(), "user.auto-file-delete.aa55.dev", value.data(), value.size());

    if (result <= 0) {
        // No xattr set on the file
        if (errno == ENODATA) {
            return {};
        }
        throw std::runtime_error(std::format("Failed to read attribute: {}, errno: {}\n", path, errno));
    }
    if (static_cast<size_t>(result) >= sizeof(value) - 1) {
        throw std::runtime_error(std::format("Attribute size too long: {}\n", result));
    }

    value.at(static_cast<size_t>(result)) = 0;

    return value.data();
}

InvalidInputException::InvalidInputException(const char* msg)
    : std::runtime_error(msg)
{
}
