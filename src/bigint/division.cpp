#include "bigint.hpp"
#include "utils.hpp"

#include <sstream>

namespace ocb {

BigInt& BigInt::operator/= (const BigInt& other) {
    if (other == 0) {
        throw std::invalid_argument("divide by 0");
    }

    const auto& divisor{other.get_value()};
    int start_index{0};
    int end_index(1);

    if (is_less_than(this->get_value(), divisor)) {
        this->set_value("0");
        this->set_negative(false);
        return *this;
    }

    {
        auto reduced_this_value{this->get_value().substr(start_index, end_index)};
        while (is_less_than(reduced_this_value, divisor)) {
            ++end_index;
            reduced_this_value = this->get_value().substr(start_index, end_index);
        }
    }

    {
        std::string divident{this->get_value()};
        std::stringstream quotient;

        for (; end_index <= divident.size(); ++end_index) {
            const std::string_view partial_divident{divident.begin()+start_index, divident.begin()+end_index};

            if (!is_less_than(partial_divident, divisor)) {
                std::string partial_divisor{divisor};
                int partial_quotient{1};

                while (is_less_than(partial_divisor, partial_divident)) {
                    partial_divisor = add(partial_divisor, divisor);
                    ++partial_quotient;
                }
                // if remainder, undo last addition
                if (is_less_than(partial_divident, partial_divisor)) {
                    partial_divisor = sub(partial_divisor, divisor);
                    trim_zeros(partial_divisor);
                    --partial_quotient;
                }
                quotient << static_cast<char>(partial_quotient + '0');

                {
                    const std::string padding(divident.size()-end_index, '0');
                    const std::string padded_partial_divisor{partial_divisor + padding};

                    if (divident == padded_partial_divisor) {
                        quotient << padding;
                        break;
                    }

                    divident = sub(divident, padded_partial_divisor);
                    while (divident[start_index] == '0') {
                        ++start_index;
                    }
                }
            }
            else {
                quotient << static_cast<char>('0');
            }
        }

        {
            auto result{quotient.str()};
            trim_zeros(result);

            this->set_value(std::move(result));
            this->set_negative(this->get_negative() ^ other.get_negative());
        }
    }

    return *this;
};

BigInt BigInt::operator/ (const BigInt& other) const {
    BigInt i{*this};
    i /= other;
    return i;
};

} // namespace ocb
