#include "ocb/bigint.hpp"

#include <istream>

/*
 * https://en.cppreference.com/w/cpp/language/operators#Stream_extraction_and_insertion
 */

namespace ocb {

    std::ostream& operator<< (std::ostream& os, const BigInt& i) { return os << i.get_value(); }

    std::istream& operator>> (std::istream& is, BigInt& i) {
        std::string number;
        is >> number;
        i.set(std::move(number));
        return is;
    }

} // namespace ocb
