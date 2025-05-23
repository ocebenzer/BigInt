#include "ocb/bigint.hpp"
#include "ocb/bigint/utils.hpp"

#include <regex>

namespace ocb {
    BigInt::BigInt(const long long int number)  { this->set(std::to_string(number)); }
    BigInt::BigInt(const std::string& number)   { this->set(std::string{number}); }
    BigInt::BigInt(std::string&& number)   { this->set(std::move(number)); }

    std::string BigInt::to_string() const {
        if (is_negative) {
            return "-" + value;
        }
        return value;
    }

    std::string_view BigInt::get_value() const {
        return std::string_view{value};
    }


    void BigInt::set_value(std::string&& number) {
        value = std::move(number);
    }

    bool BigInt::get_negative() const {
        return is_negative;
    }

    void BigInt::set_negative(const bool val) {
        is_negative = val;
    }

    void BigInt::set(std::string&& number) {
        static const std::regex regex{"([+-])?0*(\\d*)([eE][+]?(\\d+))?"};
        std::smatch matches;
        if (!std::regex_match(number, matches, regex)) {
            throw std::invalid_argument(number);
        }

        set_negative(matches[1] == "-");

        std::string new_value = matches[2].str();

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

    void BigInt::set(const long long int number) { this->set(std::to_string(number)); }

} // namespace ocb
