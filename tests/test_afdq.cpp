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
