#include "ocb/bigint.hpp"

namespace ocb {

BigInt& BigInt::operator+= (const long long int rhs) { return *this += BigInt{rhs}; }
BigInt& BigInt::operator-= (const long long int rhs) { return *this -= BigInt{rhs}; }
BigInt& BigInt::operator*= (const long long int rhs) { return *this *= BigInt{rhs}; }
BigInt& BigInt::operator/= (const long long int rhs) { return *this /= BigInt{rhs}; }
BigInt& BigInt::operator%= (const long long int rhs) { return *this %= BigInt{rhs}; }
BigInt BigInt::operator+ (const BigInt& rhs) const { return BigInt{*this} += rhs; }
BigInt BigInt::operator- (const BigInt& rhs) const { return BigInt{*this} -= rhs; }
BigInt BigInt::operator* (const BigInt& rhs) const{ return BigInt{*this} *= rhs; }
BigInt BigInt::operator/ (const BigInt& rhs) const { return BigInt{*this} /= rhs; }
BigInt BigInt::operator% (const BigInt& rhs) const { return BigInt{*this} %= rhs; }
BigInt BigInt::operator+ (const long long int rhs) const { return BigInt{*this} += BigInt{rhs}; }
BigInt BigInt::operator- (const long long int rhs) const { return BigInt{*this} -= BigInt{rhs}; }
BigInt BigInt::operator* (const long long int rhs) const { return BigInt{*this} *= BigInt{rhs}; }
BigInt BigInt::operator/ (const long long int rhs) const { return BigInt{*this} /= BigInt{rhs}; }
BigInt BigInt::operator% (const long long int rhs) const { return BigInt{*this} %= BigInt{rhs}; }
BigInt operator+= (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} += rhs; }
BigInt operator-= (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} -= rhs; }
BigInt operator*= (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} *= rhs; }
BigInt operator/= (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} /= rhs; }
BigInt operator%= (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} %= rhs; }
BigInt operator+ (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} += rhs; }
BigInt operator- (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} -= rhs; }
BigInt operator* (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} *= rhs; }
BigInt operator/ (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} /= rhs; }
BigInt operator% (const long long int lhs, const BigInt& rhs) { return BigInt{lhs} %= rhs; }

} // namespace ocb