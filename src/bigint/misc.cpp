#include "bigint.hpp"
#include <cstdint>
#include <cmath>

namespace ocb {

BigInt BigInt::factorial(const int64_t n) {
    if (n < 2) {
       return BigInt{1};
    }
    return n * factorial(n - 1);
}

bool BigInt::is_greater_than_int64_max() const {
    return *this > BigInt{INT64_MAX};
}

} // namespace ocb
