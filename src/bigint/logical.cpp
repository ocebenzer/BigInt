#include "bigint.hpp"
#include "utils.hpp"

#include <stdexcept>

namespace ocb {

bool operator< (const BigInt& lhs, const BigInt& rhs)  {
    switch (calculate_negativity(lhs.get_negative(), rhs.get_negative())) {
        case negativity::nn:
            return is_less_than(rhs.get_value(), lhs.get_value());
        case negativity::np:
            return true;
        case negativity::pn:
            return false;
        case negativity::pp:
            return is_less_than(lhs.get_value(), rhs.get_value());
        default:
            throw std::invalid_argument("");
    }
};

bool operator> (const BigInt& lhs, const BigInt& rhs)  {
    return rhs < lhs;
};

bool operator<= (const BigInt& lhs, const BigInt& rhs)  {
    return !(rhs < lhs);
};

bool operator>= (const BigInt& lhs, const BigInt& rhs)  {
    return !(lhs < rhs);
};

bool operator== (const BigInt& lhs, const BigInt& rhs)  {
    return lhs.get_negative() == rhs.get_negative() && lhs.get_value() == rhs.get_value();
};

bool operator!= (const BigInt& lhs, const BigInt& rhs)  {
    return !(lhs == rhs);
};

} // namespace ocb
