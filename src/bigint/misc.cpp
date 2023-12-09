#include "bigint.hpp"

namespace ocb {

BigInt BigInt::operator+ () const { BigInt i{*this}; return i; }
BigInt BigInt::operator- () const { BigInt i{*this}; i.set_negative(!this->get_negative()); return i; }

bool BigInt::is_greater_than_int64_max() const {
    return *this > INT64_MAX;
}

BigInt& BigInt::operator<< (const BigInt& other) {
    *this /= 2;
    return *this;
};

BigInt& BigInt::operator>> (const BigInt& other) {
    *this *= 2;
    return *this;
};

} // namespace ocb
