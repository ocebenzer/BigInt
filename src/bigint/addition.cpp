#include "bigint.hpp"
#include "utils.hpp"

#include <stdexcept>

namespace ocb {

BigInt& BigInt::operator+= (const BigInt& other) {
    switch (calculate_negativity(this->get_negative(), other.get_negative())) {
        case negativity::nn:
            this->set_value(add(this->value, other.get_value()));
            break;
        case negativity::np:
            if (is_less_than(other.get_value(), this->value)) {
                auto value{sub(this->value, other.get_value())};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            else {
                this->set_negative(false);
                auto value{sub(other.get_value(), this->value)};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            break;
        case negativity::pn:
            if (!is_less_than(this->value, other.get_value())) {
                auto value{sub(this->value, other.get_value())};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            else {
                this->set_negative(true);
                auto value{sub(other.get_value(), this->value)};
                trim_zeros(value);
                this->set_value(std::move(value));
            }
            break;
        case negativity::pp:
            this->set_value(add(this->value, other.get_value()));
            break;
        default:
            throw std::invalid_argument("");
    }

    return *this;
};

BigInt& BigInt::operator++ () {
    *this += 1;
    return *this;
};

BigInt BigInt::operator++ (int) {
    BigInt old{*this};
    *this += 1;
    return old;
};

BigInt operator+ (BigInt lhs, const BigInt& rhs)  {
    lhs += rhs;
    return lhs;
};

} // namespace ocb
