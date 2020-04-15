//
// Created by Jiří Šebele on 15/04/2020.
//

#include "DbValue.hpp"

#include <charconv>
#include <exception>

#include <boost/date_time.hpp>

DbValue::DbValue() = default;

DbValue::DbValue(std::string value)
    : value { std::move(value) }
    , hasValue { true }
{ }

bool DbValue::is_null() const {
    return !this->hasValue;
}

// Specializations

// NOTE: Adding a specialization here should be the only thing needed to add support for a new type

template <>
int DbValue::as<int>() const {
    if (!this->hasValue) {
        throw std::invalid_argument { "DbValue is NULL" };
    }

    int result;
    auto begin = this->value.data();
    auto end = this->value.data() + this->value.size();

    if (auto [p, ec] = std::from_chars(begin, end, result); p != end) {
        throw std::invalid_argument { "Conversion error" };
    }

    return result;
}

template <>
std::string DbValue::as<std::string>() const {
    if (!this->hasValue) {
        throw std::invalid_argument { "DbValue is NULL" };
    }
    return this->value;
}

template <>
boost::posix_time::ptime DbValue::as<boost::posix_time::ptime>() const {
    if (!this->hasValue) {
        throw std::invalid_argument { "DbValue is NULL" };
    }
    return boost::posix_time::time_from_string(this->value);
}
