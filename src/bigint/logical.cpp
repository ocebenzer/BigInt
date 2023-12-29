#include "bigint.hpp"
#include "utils.hpp"

#include <stdexcept>

namespace ocb {

bool BigInt::operator< (const BigInt& other) const {
    switch (calculate_negativity(this->get_negative(), other.get_negative())) {
        case negativity::nn:
            return is_less_than(other.get_value(), this->get_value());
        case negativity::np:
            return true;
        case negativity::pn:
            return false;
        case negativity::pp:
            return is_less_than(this->get_value(), other.get_value());
        default:
            throw std::invalid_argument("");
    }
};

bool BigInt::operator> (const BigInt& other) const {
    return other < *this;
};

bool BigInt::operator<= (const BigInt& other) const {
    return !(*this > other);
};

bool BigInt::operator>= (const BigInt& other) const {
    return !(*this < other);
};

bool BigInt::operator== (const BigInt& other) const {
    return is_negative == other.is_negative && value == other.value;
};

bool BigInt::operator!= (const BigInt& other) const {
    return !(*this == other);
};

} // namespace ocb
