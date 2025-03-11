#include "ocb/bigint.hpp"
#include "ocb/bigint/utils.hpp"

/*
 * https://en.cppreference.com/w/cpp/language/operators#Bitwise_arithmetic_operators
 */

namespace ocb {

BigInt operator<< (const BigInt& lhs, const BigInt& rhs)  { return BigInt{lhs} *= find_pow_of_2(rhs); }
BigInt operator>> (const BigInt& lhs, const BigInt& rhs)  { return BigInt{lhs} /= find_pow_of_2(rhs); }
BigInt operator<< (const BigInt& lhs, const int64_t rhs)  { return lhs << BigInt{rhs}; }
BigInt operator>> (const BigInt& lhs, const int64_t rhs)  { return lhs >> BigInt{rhs}; }

} // namespace ocb
