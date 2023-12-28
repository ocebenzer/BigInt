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
            if (!is_less_than(this->value, other.get_value())) {
                this->set_value(sub(this->value, other.get_value()));
            }
            else {
                this->set_negative(false);
                this->set_value(sub(other.get_value(), this->value));
            }
            break;
        case negativity::pn:
            if (!is_less_than(this->value, other.get_value())) {
                this->set_value(sub(this->value, other.get_value()));
            }
            else {
                this->set_negative(true);
                this->set_value(sub(other.get_value(), this->value));
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

BigInt BigInt::operator+ (const BigInt& other) const {
    BigInt i{*this};
    i += other;
    return i;
};

} // namespace ocb
