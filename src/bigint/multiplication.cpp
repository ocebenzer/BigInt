#include "bigint.hpp"

namespace ocb {

BigInt& BigInt::operator*= (const BigInt& other) {
    return *this;
};

BigInt BigInt::operator* (const BigInt& other) const {
    BigInt i{*this};
    i *= other;
    return i;
};

} // namespace ocb
