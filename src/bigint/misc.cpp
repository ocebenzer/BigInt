#include <cstdint>
#include <unordered_map>
#include "ocb/bigint.hpp"

namespace ocb {
    BigInt operator""_BigInt (const unsigned long long t) { return BigInt{std::to_string(t)}; }

    BigInt factorial(const unsigned long long n) {
        static std::unordered_map<long long int, BigInt> history;

        if (history.contains(n)) {
            return history[n];
        }

        if (n < 2) {
            const auto value = 1_BigInt;
            history[n] = value;
            return value;
        }

        const auto value = n * factorial(n - 1);
        history[n] = value;
        return value;
    }

    BigInt fibonacci(const unsigned long long n) {
        static std::unordered_map<unsigned long long, BigInt> history;

        if (history.contains(n)) {
            return history[n];
        }

        if (n < 3) {
            const auto value = 1_BigInt;
            history[n] = value;
            return value;
        }

        const auto n1 = fibonacci(n-1);
        const auto n2 = fibonacci(n-2);

        const auto value = n1 + n2;
        history[n] = value;
        return value;
    }

    bool BigInt::is_greater_than_int64_max() const {
        return *this > BigInt{INT64_MAX};
    }

} // namespace ocb
