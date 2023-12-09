#include "doctest/doctest.h"

#include "bigint.hpp"

using ocb::BigInt;

TEST_CASE("Less Than") {
    BigInt i;
    BigInt j;

    CHECK_FALSE(i < j);

    j += 1;
    CHECK(i < j);

    j = -2;

    CHECK_FALSE(i < j);
}

TEST_CASE("Greater Than") {

}

TEST_CASE("Less Than Equal") {

}

TEST_CASE("Greater Than Equal") {

}

TEST_CASE("Equal") {

}

TEST_CASE("Not Equal") {

}
