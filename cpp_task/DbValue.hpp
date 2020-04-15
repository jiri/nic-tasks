//
// Created by Jiří Šebele on 15/04/2020.
//

#pragma once

#include <string>
#include <optional>

// NOTE: In a better world these would be in a utility header.
namespace detail {
    template <typename T>
    struct is_optional : std::false_type {};

    template <typename T>
    struct is_optional<std::optional<T>> : std::true_type {};
}

// NOTE: I used std::optional in lieu of boost::optional

class DbValue {
public:
    DbValue();
    explicit DbValue(std::string value);

    [[nodiscard]]
    bool is_null() const;

    // NOTE: Takes long to build, but elegant ¯\_(ツ)_/¯
    // NOTE: Build errors are cryptic and could be improved using concepts in C++20

    template <typename T>
    [[nodiscard]]
    auto as() const -> std::enable_if_t<detail::is_optional<std::decay_t<T>>::value, T> {
        if (!this->hasValue) {
            return std::nullopt;
        }
        return { this->as<typename T::value_type>() };
    };

    template <typename T>
    [[nodiscard]]
    auto as() const -> std::enable_if_t<!detail::is_optional<std::decay_t<T>>::value, T>;

    template <typename T>
    void into(T& out_value) const {
        out_value = this->as<T>();
    }

private:
    // NOTE: We probably don't ever want to modify these since it's not an ORM object.
    const std::string value;
    const bool hasValue = false;
};
