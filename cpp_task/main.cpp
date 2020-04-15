#include <optional>
#include <string>

#include <boost/date_time.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "DbValue.hpp"

// Tests

TEST_CASE("Provided usage examples") {
    SECTION("Basic access") {
        const auto v = DbValue { "42" };

        REQUIRE(!v.is_null());

        int c1 {};
        REQUIRE_NOTHROW(c1 = v.as<int>());
        REQUIRE(c1 == 42);

        int c2 {};
        REQUIRE_NOTHROW(v.into(c2));
        REQUIRE(c2 == 42);
    }

    SECTION("Conversion to optional") {
        const auto v = DbValue { "foo" };

        std::optional<std::string> c;
        INFO("TEST1")
        REQUIRE_NOTHROW(c = v.as<std::optional<std::string>>());
        INFO("TEST2")
        INFO(std::boolalpha << c.has_value());
        REQUIRE(*c == "foo");
        REQUIRE(static_cast<bool>(c));

        REQUIRE_THROWS(v.as<int>());
    }

    SECTION("Null value access") {
        const auto v = DbValue {};
        REQUIRE(v.is_null());

        std::optional<std::string> c;
        REQUIRE_NOTHROW(c = v.as<std::optional<std::string>>());
        REQUIRE(!static_cast<bool>(c));

        REQUIRE_THROWS(v.as<std::string>());
    }

// NOTE: Can't test for build errors
//    {
//        const auto v = DbValue { "1.1" };
//        const auto c = v.as<double>();  // build error (conversion not defined)
//    }
}

TEST_CASE("Custom tests") {
    SECTION("Int conversion") {
        REQUIRE_NOTHROW(DbValue { "42" }.as<int>());
        REQUIRE_NOTHROW(DbValue { "-33" }.as<int>());
        REQUIRE_NOTHROW(DbValue { "0" }.as<int>());

        REQUIRE_THROWS(DbValue { "foo" }.as<int>());
        REQUIRE_THROWS(DbValue { "13af" }.as<int>());
        REQUIRE_THROWS(DbValue { "5.8" }.as<int>());
    }

    SECTION("Time conversion") {
        const auto v1 = DbValue { "2002-01-20 23:41:59.000" }.as<boost::posix_time::ptime>();

        REQUIRE(v1.date().year() == 2002);
        REQUIRE(v1.date().month() == 1);
        REQUIRE(v1.date().day() == 20);

        REQUIRE(v1.time_of_day().hours() == 23);
        REQUIRE(v1.time_of_day().minutes() == 41);
        REQUIRE(v1.time_of_day().seconds() == 59);
    }
}