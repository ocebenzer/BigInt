#pragma once

#include <string>
#include <cstdint>

namespace ocb {

enum class negativity : uint8_t {
    pp = 0,
    pn = 1,
    np = 2,
    nn = 3
};

/**
 * return @enum negativity
 * very specific use case: switch-cases inside addition & subtraction operations
 */
negativity calculate_negativity (bool, bool);

/**
 * remove '0' characters before a number-string
 */
void trim_zeros (std::string&);

/**
 * add two number-strings
 */
std::string add (std::string_view, std::string_view);

/**
 * subtract two number-strings
 */
std::string sub (std::string_view, std::string_view);


/**
 * divide two number-strings
 * @returns [quotient, remainder]
 */
std::pair<std::string, std::string> divide (std::string_view, std::string_view);

/**
 * compare two number-strings
 */
bool is_less_than (std::string_view, std::string_view);

/**
 * find 2 ^ n
 */
BigInt find_pow_of_2(const BigInt&);

} // namespace ocb
