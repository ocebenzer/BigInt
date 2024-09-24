#include "bigint.hpp"
#include <cstdint>
#include <cmath>

namespace ocb {

BigInt BigInt::factorial(int n) {
    if (n < 2) {
        return 1;
    }

    return n * factorial(n-1);
}

BigInt BigInt::operator+ () const { BigInt i{*this}; return i; }
BigInt BigInt::operator- () const { BigInt i{*this}; i.set_negative(!this->get_negative()); return i; }

bool BigInt::is_greater_than_int64_max() const {
    return *this > INT64_MAX;
}

BigInt find_pow_of_2(const BigInt& pow) {
    if (pow < 64) {
        return std::pow(2, std::atoll(pow.get().c_str()));
    }

    const auto half_pow{find_pow_of_2(pow/2)};

    if (pow % 2 == 0) {
        return half_pow * half_pow;
    }

    return half_pow * half_pow * 2;
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
