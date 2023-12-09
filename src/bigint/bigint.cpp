#include "bigint.hpp"
#include "utils.hpp"

#include <regex>

namespace ocb {

BigInt::BigInt(const std::string& number) {
    this->set(std::string{number});
};

BigInt::BigInt(std::string&& number) {
    this->set(std::move(number));
};

BigInt::BigInt(const long long number) : BigInt(std::to_string(number)) { };

const std::string& BigInt::get_value() const {
    return this->value;
}

const bool& BigInt::get_negative() const {
    return this->is_negative;
}

std::string BigInt::get() const {
    if (this->get_negative()) {
        return "-" + this->get_value();
    }
    return this->get_value();
}

void BigInt::set_value(std::string&& number) {
    value = std::move(number);
}

void BigInt::set_negative(const bool val) {
    this->is_negative = val;
}

void BigInt::set(std::string&& number) {
    const std::regex regex{"([+-])?0*(\\d*)([eE][+]?(\\d+))?"};
    std::smatch matches;
    if (!std::regex_match(number, matches, regex)) {
            throw std::invalid_argument(number);
    }

    this->set_negative(matches[1] == "-");

    std::string new_value;

    new_value = matches[2].str();

    if (matches[3].matched) {
        const auto n{std::stoll(matches[4].str())};
        new_value += std::string(n, '0');
    }

    trim_zeros(new_value);

    if (new_value.empty()) {
        new_value = "0";
    }

    if (new_value == "0") {
        this->set_negative(false);
    }

    this->set_value(std::move(new_value));
}

} // namespace ocb
