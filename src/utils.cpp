#include "ocb/bigint.hpp"
#include "ocb/bigint/utils.hpp"

#include <cassert>
#include <sstream>
#include <algorithm>

namespace ocb {

    void trim_zeros (std::string& s) {
        switch (const auto first_not_zero{s.find_first_not_of('0')}) {
            case 0:
                break;
            case std::string::npos:
                s = "0";
                break;
            default:
                s = s.substr(first_not_zero);
                break;
        }
    }

    negativity calculate_negativity(const bool v1, const bool v2) {
        uint8_t value{0};
        if (v1) value += 0b10;
        if (v2) value += 0b01;
        return static_cast<negativity>(value);
    }


    std::string add (const std::string_view s1, const std::string_view s2){
        std::string final_value{s1};
        std::string_view added_value{s2};

        if (is_less_than(s1, s2)) {
            final_value = s2;
            added_value = s1;
        }

        auto itr1{final_value.rbegin()};
        auto itr2{added_value.rbegin()};

        auto remainder{0};
        for (; itr2 < added_value.rend(); ++itr1, ++itr2) {
            remainder += *itr1 - '0' + *itr2 - '0';
            *itr1 = static_cast<char>(remainder % 10 + '0');
            remainder /= 10;
        }

        for (; itr1 < final_value.rend(); ++itr1) {
            remainder += *itr1 - '0';
            *itr1 = static_cast<char>(remainder % 10 + '0');
            remainder /= 10;
        }

        if (remainder) {
            return std::to_string(remainder) + final_value;
        }

        return final_value;
    }

    std::string sub (const std::string_view s1, const std::string_view s2) {
        assert(!is_less_than(s1, s2));

        std::string final_value{s1};

        auto itr1{final_value.rbegin()};
        auto borrow{0};
        bool borrowed{false};

        for (auto itr2{s2.rbegin()}; itr2 < s2.rend(); ++itr1, ++itr2) {
            borrow += *itr1 - *itr2;
            borrowed = borrow < 0;
            if (borrowed) {
                borrow += 10;
            }
            *itr1 = static_cast<char>(borrow % 10 + '0');
            borrow = borrowed ? -1 : 0;
        }

        for (; itr1 < final_value.rend(); ++itr1) {
            borrow += *itr1 - '0';
            borrowed = borrow < 0;
            if (borrowed) {
                borrow += 10;
            }
            *itr1 = static_cast<char>(borrow % 10 + '0');
            borrow = borrowed ? -1 : 0;
        }

        assert(!borrowed);

        return final_value;
    }

    std::pair<std::string, std::string> divide (const std::string_view s1, const std::string_view s2) {
        if (s2.find_first_not_of('0') == std::string::npos) {
            throw std::invalid_argument("divide by 0");
        }

        int start_index{0};
        int end_index(1);

        if (is_less_than(s1, s2)) {
            return {"0", std::string{s1}};
        }

        {
            auto reduced_this_value{s1.substr(start_index, end_index)};
            while (is_less_than(reduced_this_value, s2)) {
                ++end_index;
                reduced_this_value = s1.substr(start_index, end_index);
            }
        }

        std::string dividend{s1};
        std::stringstream quotient;

        for (; end_index <= dividend.size(); ++end_index) {
            const std::string_view partial_dividend{dividend.begin()+start_index, dividend.begin()+end_index};

            if (!is_less_than(partial_dividend, s2)) {
                std::string partial_divisor{s2};
                int partial_quotient{1};

                while (is_less_than(partial_divisor, partial_dividend)) {
                    partial_divisor = add(partial_divisor, s2);
                    ++partial_quotient;
                }
                // if remainder, undo last addition
                if (is_less_than(partial_dividend, partial_divisor)) {
                    partial_divisor = sub(partial_divisor, s2);
                    trim_zeros(partial_divisor);
                    --partial_quotient;
                }
                quotient << static_cast<char>(partial_quotient + '0');

                {
                    const std::string padding(dividend.size()-end_index, '0');
                    const std::string padded_partial_divisor{partial_divisor + padding};

                    if (dividend == padded_partial_divisor) {
                        quotient << padding;
                        dividend = "0";
                        break;
                    }

                    dividend = sub(dividend, padded_partial_divisor);
                    while (dividend[start_index] == '0') {
                        ++start_index;
                    }
                }
            }
            else {
                quotient << '0';
            }
        }

        return {quotient.str(), dividend};
    }

    bool is_less_than (const std::string_view s1, const std::string_view s2) {
        if (s1.size() == s2.size()) return s1 < s2;
        return s1.size() < s2.size();
    }

    BigInt find_pow_of_2 (const auto &pow) {
        const auto find_pow_of_2_impl = [](const auto &pow, const auto &find_pow_of_2_ref) {
            if (pow < 64) {
                long long int ll;
                std::stringstream ss{pow.to_string()};
                ss >> ll;
                return BigInt{ll};
            }

            const BigInt half_pow{find_pow_of_2_ref(pow / 2, find_pow_of_2_ref)};

            if (pow % 2 == 0) {
                return half_pow * half_pow;
            }

            return half_pow * half_pow * 2;
        };

        return find_pow_of_2_impl(pow, find_pow_of_2_impl);
    }

} // namespace ocb
