#include "bigint.hpp"

namespace ocb {

BigInt& BigInt::operator+= (const int64_t rhs) { return *this += BigInt{rhs}; }
BigInt& BigInt::operator-= (const int64_t rhs) { return *this -= BigInt{rhs}; }
BigInt& BigInt::operator*= (const int64_t rhs) { return *this *= BigInt{rhs}; }
BigInt& BigInt::operator/= (const int64_t rhs) { return *this /= BigInt{rhs}; }
BigInt& BigInt::operator%= (const int64_t rhs) { return *this %= BigInt{rhs}; }
BigInt BigInt::operator+ (const BigInt& rhs) const { return BigInt{*this} += rhs; }
BigInt BigInt::operator- (const BigInt& rhs) const { return BigInt{*this} -= rhs; }
BigInt BigInt::operator* (const BigInt& rhs) const{ return BigInt{*this} *= rhs; }
BigInt BigInt::operator/ (const BigInt& rhs) const { return BigInt{*this} /= rhs; }
BigInt BigInt::operator% (const BigInt& rhs) const { return BigInt{*this} %= rhs; }
BigInt BigInt::operator+ (const int64_t rhs) const { return BigInt{*this} += BigInt{rhs}; }
BigInt BigInt::operator- (const int64_t rhs) const { return BigInt{*this} -= BigInt{rhs}; }
BigInt BigInt::operator* (const int64_t rhs) const { return BigInt{*this} *= BigInt{rhs}; }
BigInt BigInt::operator/ (const int64_t rhs) const { return BigInt{*this} /= BigInt{rhs}; }
BigInt BigInt::operator% (const int64_t rhs) const { return BigInt{*this} %= BigInt{rhs}; }
BigInt operator+= (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} += rhs; }
BigInt operator-= (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} -= rhs; }
BigInt operator*= (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} *= rhs; }
BigInt operator/= (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} /= rhs; }
BigInt operator%= (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} %= rhs; }
BigInt operator+ (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} += rhs; }
BigInt operator- (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} -= rhs; }
BigInt operator* (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} *= rhs; }
BigInt operator/ (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} /= rhs; }
BigInt operator% (const int64_t lhs, const BigInt& rhs) { return BigInt{lhs} %= rhs; }

} // namespace ocb