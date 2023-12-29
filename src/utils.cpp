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


std::string add (const std::string_view s1, const std::string_view s2){
    std::string final_value{s1};
    std::string_view added_value{s2};

    if (is_less_than(s1, s2)) {
        final_value = s2;
        added_value = s1;
    }

    auto itr1{final_value.rbegin()};
    auto itr2{added_value.rbegin()};

    int remainder{0};
    for (; itr2 < added_value.rend(); ++itr1, ++itr2) {
        remainder += *itr1 - '0' + *itr2 - '0';
        *itr1 = remainder % 10 + '0';
        remainder /= 10;
    }

    for (; itr1 < final_value.rend(); ++itr1) {
        remainder += *itr1 - '0';
        *itr1 = remainder % 10 + '0';
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
    auto itr2{s2.rbegin()};

    int borrow{0};
    bool borrowed{false};
    for (; itr2 < s2.rend(); ++itr1, ++itr2) {
        borrow = *itr1 - *itr2 + borrow;
        borrowed = borrow < 0;
        if (borrowed) {
            borrow += 10;
        }
        *itr1 = borrow % 10 + '0';
        borrow = borrowed ? -1 : 0;
    }

    for (; itr1 < final_value.rend(); ++itr1) {
        borrow = *itr1 - '0' + borrow;
        borrowed = borrow < 0;
        if (borrowed) {
            borrow += 10;
        }
        *itr1 = borrow % 10 + '0';
        borrow = borrowed ? -1 : 0;
    }

    assert(!borrowed);

    return final_value;
}

bool is_less_than (const std::string_view s1, const std::string_view s2) {
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
