#include "bigint.hpp"

namespace ocb {

std::ostream& operator<< (std::ostream& os, const BigInt& i) {
    return os << i.get();
}
std::istream& operator>> (std::istream& is, BigInt& i) {
    std::string number;
    is >> number;
    i.set(std::move(number));
    return is;
}

} // namespace ocb
