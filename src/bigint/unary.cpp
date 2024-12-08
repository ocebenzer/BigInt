#include <bigint/bigint.hpp>

/*
 * https://en.cppreference.com/w/cpp/language/operators#Increment_and_decrement
 */

namespace ocb {

BigInt BigInt::operator+ () const { BigInt i{*this}; return i; }
BigInt BigInt::operator- () const { BigInt i{*this}; i.set_negative(!this->get_negative()); return i; }

BigInt& BigInt::operator++ () { return *this += 1; }
BigInt BigInt::operator++ (int) {
    BigInt old{*this};
    *this += 1;
    return old;
}

BigInt& BigInt::operator-- () { return *this += -1; }
BigInt BigInt::operator-- (int) {
    BigInt old{*this};
    *this += -1;
    return old;
}

} // namespace ocb
