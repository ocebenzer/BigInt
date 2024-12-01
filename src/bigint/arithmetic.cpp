#include "bigint.hpp"
#include "utils.hpp"

#include <stdexcept>
#include <vector>
#include <numeric>

/*
 * https://en.cppreference.com/w/cpp/language/operators#Binary_arithmetic_operators
 */

namespace ocb {

BigInt& BigInt::operator+= (const BigInt& rhs) {
    switch (calculate_negativity(this->get_negative(), rhs.get_negative())) {
        case negativity::nn:
            this->set_value(add(this->value, rhs.get_value()));
            break;
        case negativity::np:
            if (is_less_than(rhs.get_value(), this->value)) {
                auto value{sub(this->value, rhs.get_value())};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            else {
                this->set_negative(false);
                auto value{sub(rhs.get_value(), this->value)};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            break;
        case negativity::pn:
            if (!is_less_than(this->value, rhs.get_value())) {
                auto value{sub(this->value, rhs.get_value())};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            else {
                this->set_negative(true);
                auto value{sub(rhs.get_value(), this->value)};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            break;
        case negativity::pp:
            this->set_value(add(this->value, rhs.get_value()));
            break;
        default:
            throw std::invalid_argument("");
    }

    return *this;
}

BigInt& BigInt::operator-= (const BigInt& rhs) {
    const BigInt i{-rhs};
    return *this += i;
}

BigInt& BigInt::operator*= (const BigInt& rhs) {
    if (*this == 0 || rhs == 0) {
        this->set(0);
        return *this;
    }
    std::vector<std::string> partial_values;
    const auto multiplied_value{rhs.get_value()};
    int padding{0};
    for (auto itr2{multiplied_value.rbegin()}; itr2 < multiplied_value.rend(); ++itr2) {
        const auto d2{*itr2 - '0'};
        std::string partial_value{this->get_value()};
        int remainder{0};
        for (auto itr1{partial_value.rbegin()}; itr1 < partial_value.rend(); ++itr1) {
            const auto d1{*itr1 - '0'};
            remainder = d1 * d2 + remainder;
            *itr1 = remainder % 10 + '0';
            remainder /= 10;
        }
        partial_values.push_back(std::to_string(remainder) + partial_value + std::string(padding, '0'));
        ++padding;
    }

    {
        auto result{std::reduce(partial_values.begin()+1, partial_values.end(), *partial_values.begin(), add)};
        trim_zeros(result);

        this->set_value(std::move(result));
        this->set_negative(this->get_negative() ^ rhs.get_negative());
    }

    return *this;
}

BigInt& BigInt::operator/= (const BigInt& rhs) {
    auto [quotient, remainder] = divide(this->get_value(), rhs.get_value());
    trim_zeros(quotient);

    this->set_value(std::move(quotient));
    this->set_negative(this->get_negative() ^ rhs.get_negative());

    return *this;
}

BigInt& BigInt::operator%= (const BigInt& rhs) {
    auto [quotient, remainder] = divide(this->get_value(), rhs.get_value());
    trim_zeros(remainder);

    this->set_value(std::move(remainder));

    return *this;
}

} // namespace ocb
