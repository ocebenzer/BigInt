#include "bigint.hpp"

#include <cmath>

namespace ocb {

BigInt BigInt::operator+ () const { BigInt i{*this}; return i; }
BigInt BigInt::operator- () const { BigInt i{*this}; i.set_negative(!this->get_negative()); return i; }

bool BigInt::is_greater_than_int64_max() const {
    return *this > INT64_MAX;
}

/**
 * Only supports up to 2^63, too bad!
 */
BigInt find_pow_of_2(const BigInt& pow) {
    return std::pow(2, std::atoll(pow.get().c_str()));
}

BigInt operator<< (BigInt lhs, const BigInt& rhs)  {
    lhs *= find_pow_of_2(rhs);
    return lhs;
};

BigInt operator>> (BigInt lhs, const BigInt& rhs)  {
    lhs /= find_pow_of_2(rhs);
    return lhs;
};

} // namespace ocb
