#include "doctest/doctest.h"

#include "bigint/bigint.hpp"

#include <random>

using ocb::BigInt;

TEST_CASE("Simple Constructor") {
    BigInt i;
    CHECK_EQ(i.get_value(), "0");
    CHECK_EQ(i.get_negative(), false);

    BigInt n{"e0"};
    CHECK_EQ(n.get_value(), "0");
    CHECK_EQ(n.get_negative(), false);
    CHECK_EQ(n.to_string(), "0");
}
TEST_CASE("Random Constructor Generation") {
    std::mt19937_64 rng;
    std::uniform_int_distribution<long long> distribution;

    for (int i{0}; i < 10; ++i) {
        const auto num{distribution(rng)};
        const auto str{std::to_string(num)};

        BigInt n{str};
        CHECK_EQ(n.get_value(), std::to_string(std::llabs(num)));
        CHECK_EQ(n.get_negative(), num < 0);
        CHECK_EQ(n.to_string(), str);
    }

    for (int i{0}; i < 10; ++i) {
        const auto num{distribution(rng)};
        const auto num_str{std::to_string(num)};
        const auto exp{static_cast<uint8_t>(distribution(rng))};
        const auto str{std::to_string(num) + "e" + std::to_string((exp))};

        BigInt n{str};
        const std::string n_get{n.to_string()};
        const std::string n_get_value{n.get_value()};

        CHECK_EQ(n_get_value.substr(0, num_str.size()), num_str);
        CHECK([&num_str, &n_get_value] () {
            const auto& zeros{n_get_value.substr(num_str.size())};
            for (const char c : zeros) {
                if (c != '0') {
                    return false;
                }
            }
            return true;
        }());

        CHECK_EQ(n.get_negative(), num < 0);

        if (num < 0) {
            CHECK_EQ(n_get[0], '-');
            CHECK_EQ(n_get.substr(1), n_get_value);
        }
        else {
            CHECK_EQ(n_get.size(), n_get_value.size());
            CHECK_EQ(n_get, n_get_value);
        }
    }
}
