#include "bigint.hpp"
#include "utils.hpp"

#include <sstream>
#include <stdexcept>

namespace ocb {

BigInt& BigInt::operator/= (const BigInt& other) {
    auto [quotient, remainder] = divide(this->get_value(), other.get_value());
    trim_zeros(quotient);

    this->set_value(std::move(quotient));
    this->set_negative(this->get_negative() ^ other.get_negative());

    return *this;
};

BigInt operator/ (BigInt lhs, const BigInt& rhs)  {
    lhs /= rhs;
    return lhs;
};

} // namespace ocb
