#include <string>

class DbValue {
public:
    DbValue()
        : value {}
        , isNull { true }
    { };

    explicit DbValue(std::string value)
        : value { std::move(value) }
        , isNull { false }
    { };

private:
    const std::string value;
    const bool isNull = true;
};

int main() {
    return 0;
}
