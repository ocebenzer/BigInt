#include "bigint.hpp"
#include "utils.hpp"

#include <vector>
#include <numeric>

namespace ocb {

BigInt& BigInt::operator*= (const BigInt& other) {
    if (*this == 0 || other == 0) {
        this->set(0);
        return *this;
    }

    std::vector<std::string> partial_values;
    const auto multiplied_value{other.get_value()};
    int padding{0};
    for (auto itr2{multiplied_value.rbegin()}; itr2 < multiplied_value.rend(); ++itr2) {
        const auto d2{*itr2 - '0'};
        std::string partial_value{this->get_value()};
        int remainder{0};
        for (auto itr1{partial_value.rbegin()}; itr1 < partial_value.rend(); ++itr1) {
            const auto d1{*itr1 - '0'};
            remainder = d1 * d2 + remainder;
            *itr1 = remainder % 10 + '0';
            remainder /= 10;
        }
        partial_values.push_back(std::to_string(remainder) + partial_value + std::string(padding, '0'));
        ++padding;
    }

{
    auto result{std::reduce(partial_values.begin()+1, partial_values.end(), *partial_values.begin(), add)};
    trim_zeros(result);

    this->set_value(std::move(result));
    this->set_negative(this->get_negative() ^ other.get_negative());
}

    return *this;
};

BigInt BigInt::operator* (const BigInt& other) const {
    BigInt i{*this};
    i *= other;
    return i;
};

} // namespace ocb
