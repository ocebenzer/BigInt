#include "ocb/bigint.hpp"
#include "ocb/bigint/utils.hpp"

#include <stdexcept>

/*
 * https://en.cppreference.com/w/cpp/language/operators#Comparison_operators
 */

namespace ocb {

bool BigInt::operator< (const BigInt& rhs) const  {
    switch (calculate_negativity(get_negative(), rhs.get_negative())) {
        case negativity::nn:
            return is_less_than(rhs.get_value(), get_value());
        case negativity::np:
            return true;
        case negativity::pn:
            return false;
        case negativity::pp:
            return is_less_than(get_value(), rhs.get_value());
        default:
            throw std::invalid_argument("");
    }
}
bool BigInt::operator> (const BigInt& rhs) const { return rhs < *this; }
bool BigInt::operator<= (const BigInt& rhs) const { return !(rhs < *this); }
bool BigInt::operator>= (const BigInt& rhs) const { return !(*this < rhs); }

bool BigInt::operator== (const BigInt& rhs) const {
    return get_negative() == rhs.get_negative() && get_value() == rhs.get_value();
}
bool BigInt::operator!= (const BigInt& rhs) const { return !(*this == rhs); }

bool BigInt::operator< (const long long int rhs) const { return *this < BigInt{rhs}; }
bool BigInt::operator> (const long long int rhs) const { return *this > BigInt{rhs}; }
bool BigInt::operator<= (const long long int rhs) const { return *this <= BigInt{rhs}; }
bool BigInt::operator>= (const long long int rhs) const { return *this >= BigInt{rhs}; }
bool BigInt::operator== (const long long int rhs) const { return *this == BigInt{rhs}; }
bool BigInt::operator!= (const long long int rhs) const { return *this != BigInt{rhs}; }

} // namespace ocb
