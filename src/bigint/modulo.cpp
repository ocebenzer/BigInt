#include "bigint.hpp"
#include "utils.hpp"

#include <sstream>
#include <stdexcept>

namespace ocb {

BigInt& BigInt::operator%= (const BigInt& other) {
    auto [quotient, remainder] = divide(this->get_value(), other.get_value());
    trim_zeros(remainder);

    this->set_value(std::move(remainder));

    return *this;
};

BigInt operator% (BigInt lhs, const BigInt& rhs)  {
    lhs %= rhs;
    return lhs;
};

} // namespace ocb
