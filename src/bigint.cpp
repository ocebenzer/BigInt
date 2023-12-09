#include "bigint.hpp"

#include <regex>
#include <cstdint>
#include <cassert>
#include <sstream>
#include <stdexcept>

enum class negativity : uint8_t {
    pp = 0,
    pn = 1,
    np = 2,
    nn = 3
};

const auto find_negativity = [] (bool v1, bool v2) { return static_cast<negativity>(v1 << 1 | v2); };

const auto trim_zeros = [] (std::string& s) {
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
};

const auto add = [] (const std::string& s1, const std::string& s2) {
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
};

const auto sub = [] (const std::string& s1, const std::string& s2) {
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
};

const auto is_less_than = [] (const std::string& s1, const std::string& s2) {
    if (s1.size() == s2.size()) {
        for (auto itr1{s1.begin()}, itr2{s2.begin()}; itr1 < s1.end(); itr1++, itr2++) {
            if (*itr1 != *itr2) {
                return *itr1 < *itr2;
            }
        }
    }
    return s1.size() < s2.size();
};

BigInt::BigInt(const std::string& number) { this->set(std::string{number}); };

BigInt::BigInt(std::string&& number) { this->set(std::move(number)); };

BigInt::BigInt(const long long number) : BigInt(std::to_string(number)) {};

const std::string& BigInt::get_value() const { return this->value; }

const bool& BigInt::get_negative() const { return this->is_negative; }

std::string BigInt::get() const {
    if (this->get_negative()) {
        return "-" + this->get_value();
    }
    return this->get_value();
}

void BigInt::set_value(std::string&& number) { value = std::move(number); }

void BigInt::set_negative(const bool val) { this->is_negative = val; }

void BigInt::set(std::string&& number) {
    const std::regex regex{"([+-])?0*(\\d*)([eE][+]?(\\d+))?"};
    std::smatch matches;
    if (!std::regex_match(number, matches, regex)) {
            throw std::invalid_argument(number);
    }
    
    this->set_negative(matches[1].matched && matches[1] == "-");

    std::string new_value;

    if (matches[2].str().empty()) {
        new_value = "0";
    }
    else {
        new_value = matches[2];
    }

    if (matches[3].matched) {
        const auto n{static_cast<char>(std::stoi(matches[4].str()))};
        new_value += std::string{n, '0'};
    }

    trim_zeros(new_value);
    if (new_value == "0") {
        this->set_negative(false);
    }

    this->set_value(std::move(new_value));
}

bool BigInt::is_greater_than_int64_max() const {
    return *this > INT64_MAX;
}

BigInt BigInt::operator+ () const { BigInt i{*this}; return i; }
BigInt BigInt::operator- () const { BigInt i{*this}; i.set_negative(!this->get_negative()); return i; }

BigInt& BigInt::operator+= (const BigInt& other) {
    switch (find_negativity(this->get_negative(), other.get_negative())) {
        case negativity::nn:
            this->set_value(add(this->get_value(), other.get_value()));
            break;
        case negativity::np:
            if (!is_less_than(this->get_value(), other.get_value())) {
                this->set_value(sub(this->get_value(), other.get_value()));
            }
            else {
                this->set_negative(false);
                this->set_value(sub(other.get_value(), this->get_value()));
            }
            break;
        case negativity::pn:
            if (!is_less_than(this->get_value(), other.get_value())) {
                this->set_value(sub(this->get_value(), other.get_value()));
            }
            else {
                this->set_negative(true);
                this->set_value(sub(other.get_value(), this->get_value()));
            }
            break;
        case negativity::pp:
            this->set_value(add(this->get_value(), other.get_value()));
            break;
        default:
            throw std::invalid_argument("");
    }

    return *this;
};
BigInt& BigInt::operator-= (const BigInt& other) { const BigInt i{-other}; *this += i; return *this; }
BigInt& BigInt::operator*= (const BigInt& other) { return *this; }; // todo
BigInt& BigInt::operator/= (const BigInt& other) { return *this; }; // todo
BigInt& BigInt::operator%= (const BigInt& other) { return *this; }; // todo

BigInt& BigInt::operator++ () { *this += 1; return *this; };
BigInt& BigInt::operator-- () { *this += -1; return *this; };

BigInt BigInt::operator++ (int) { BigInt old{*this}; *this += 1; return old; };
BigInt BigInt::operator-- (int) { BigInt old{*this}; *this += -1; return old; };

BigInt BigInt::operator+ (const BigInt& other) const { BigInt i{*this}; i += other; return i; };
BigInt BigInt::operator- (const BigInt& other) const { BigInt i{*this}; i -= other; return i; };
BigInt BigInt::operator* (const BigInt& other) const { BigInt i{*this}; i *= other; return i; };
BigInt BigInt::operator/ (const BigInt& other) const { BigInt i{*this}; i /= other; return i; };
BigInt BigInt::operator% (const BigInt& other) const { BigInt i{*this}; i %= other; return i; };

BigInt& BigInt::operator<< (const BigInt& other) { *this /= 2; return *this; };
BigInt& BigInt::operator>> (const BigInt& other) { *this *= 2; return *this; };

bool BigInt::operator< (const BigInt& other) const {
    switch (find_negativity(this->get_negative(), other.get_negative())) {
        case negativity::nn:
            return is_less_than(other.get_value(), this->get_value());
        case negativity::np:
            return true;
        case negativity::pn:
            return false;
        case negativity::pp:
            return is_less_than(this->get_value(), other.get_value());
        default:
            throw std::invalid_argument("");
    }
};
bool BigInt::operator> (const BigInt& other) const { return other < *this; };
bool BigInt::operator<= (const BigInt& other) const { return !(*this > other);};
bool BigInt::operator>= (const BigInt& other) const { return !(*this < other);};
bool BigInt::operator== (const BigInt& other) const { return value == other.value; };
bool BigInt::operator!= (const BigInt& other) const { return !(*this == other); };

std::ostream& operator<< (std::ostream& os, const BigInt& i) {
    return os << i.get();
}
std::istream& operator>> (std::istream& is, BigInt& i) {
    std::string number;
    is >> number;
    i.set(std::move(number));
    return is;
}
