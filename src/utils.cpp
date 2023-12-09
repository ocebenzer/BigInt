#include "utils.hpp"

#include <cassert>
#include <sstream>
#include <algorithm>

namespace ocb {

void trim_zeros (std::string& s) {
    const auto first_not_zero{s.find_first_not_of('0')};
    switch (first_not_zero) {
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

negativity calculate_negativity(bool v1, bool v2) {
    return static_cast<negativity>(v1 << 1 | v2);
}


std::string add (const std::string& s1, const std::string& s2){
    std::stringstream ss{""};
    int remainder{0};

    const auto add_digits = [&ss, &remainder] (int n1, int n2=0) {
        const auto sum{n1 + n2 + remainder};
        remainder = sum / 10;
        ss << std::to_string(sum % 10);
    };

    for (auto itr1{s1.rbegin()}, itr2{s2.rbegin()}; itr1 != s1.rend() && itr2 != s2.rend(); itr1++, itr2++) {
        add_digits(*itr1 - '0', *itr2 - '0');
    }

    {
        auto itr{s1.rbegin() + s2.size()};
        auto itr_end{s1.rend()};

        if (s2.size() > s1.size()) {
            itr = s2.rbegin() + s1.size();
            itr_end = s2.rend();
        }

        for (; itr != itr_end; itr++) {
            add_digits(*itr - '0');
        }
    }

    if (remainder) {
        ss << remainder;
    }

    auto result{ss.str()};

    std::reverse(result.begin(), result.end());
    return result;
}

std::string sub (const std::string& s1, const std::string& s2) {
    assert(s1.size() >= s2.size());

    std::stringstream ss{""};
    bool borrow{0};

    const auto sub_digits = [&ss, &borrow] (int n1, int n2=0) {
        auto sub{n1 - n2 - borrow};
        borrow = sub < 0;
        if (borrow) {
            sub += 10;
        }
        ss << std::to_string(sub);
    };

    for (auto itr1{s1.rbegin()}, itr2{s2.rbegin()}; itr1 != s1.rend() && itr2 != s2.rend(); itr1++, itr2++) {
        sub_digits(*itr1 - '0', *itr2 - '0');
    }

    {
        auto itr{s1.rbegin() + s2.size()};
        auto itr_end{s1.rend()};

        for (; itr != itr_end; itr++) {
            sub_digits(*itr - '0');
        }
    }

    auto result{ss.str()};
    std::reverse(result.begin(), result.end());

    trim_zeros(result);
    return result;
}

bool is_less_than (const std::string& s1, const std::string& s2) {
    if (s1.size() == s2.size()) {
        for (auto itr1{s1.begin()}, itr2{s2.begin()}; itr1 < s1.end(); itr1++, itr2++) {
            if (*itr1 != *itr2) {
                return *itr1 < *itr2;
            }
        }
    }
    return s1.size() < s2.size();
}

} // namespace ocb
