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
#define BOOST_TEST_MAIN

#include "../afdq.hpp"
#include "../common.hpp"

// NOLINTBEGIN(misc-include-cleaner)
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testPrintDeletionTime)
{

    const std::chrono::time_point<std::chrono::system_clock> testTime {};
    BOOST_CHECK_NO_THROW(printDeletionTime("123", "test", testTime));
    BOOST_CHECK_THROW(printDeletionTime("", "test", testTime), InvalidInputException);
    BOOST_CHECK_THROW(printDeletionTime("abcd", "test", testTime), InvalidInputException);
    // BOOST_CHECK_THROW(printDeletionTime("1111111111m", "test", testTime), InvalidInputException);

    // BOOST_CHECK_THROW(getDeletetionTime(""), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("1"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("h"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("h1"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("1111111111111111m"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("1111111111m"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("1h1"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("hh"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("0d"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("0h"), InvalidInputException);
    // BOOST_CHECK_THROW(getDeletetionTime("0m"), InvalidInputException);
    // BOOST_CHECK_NO_THROW(getDeletetionTime("1h"));
}

// NOLINTEND(misc-include-cleaner)
