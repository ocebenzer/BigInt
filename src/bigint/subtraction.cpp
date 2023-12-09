#include "bigint.hpp"

namespace ocb {

BigInt& BigInt::operator-= (const BigInt& other) {
    const BigInt i{-other};
    *this += i;
    return *this;
}

BigInt& BigInt::operator-- () {
    *this += -1;
    return *this;
};

BigInt BigInt::operator-- (int) {
    BigInt old{*this};
    *this += -1;
    return old;
};

BigInt BigInt::operator- (const BigInt& other) const {
    BigInt i{*this};
    i -= other;
    return i;
};

} // namespace ocb
