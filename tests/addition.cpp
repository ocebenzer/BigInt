#include "doctest/doctest.h"

#include "bigint.hpp"

TEST_CASE("Increment") {
    BigInt i;
    CHECK_EQ(i.get_value(), "0");
    CHECK_EQ(i.get_negative(), false);

    i++;
    CHECK_EQ(i.get_value(), "1");
    CHECK_EQ(i.get_negative(), false);
}
