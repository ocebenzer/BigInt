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
std::string add (const std::string_view, const std::string_view);

/**
 * subtract two number-strings
 */
std::string sub (const std::string_view, const std::string_view);


/**
 * divide two number-strings
 * @returns [quotient, remainder]
 */
std::pair<std::string, std::string> divide (const std::string_view, const std::string_view);

/**
 * compare two number-strings
 */
bool is_less_than (const std::string_view, const std::string_view);

} // namespace ocb
