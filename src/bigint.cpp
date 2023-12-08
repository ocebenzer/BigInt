#include "bigint.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>

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
    return "";
};

const auto is_less_than = [] (const std::string& s1, const std::string& s2) {
    auto itr1{s1.rbegin()};
    auto itr2{s2.rbegin()};
    const auto& itr1_end{s1.rend()};
    const auto& itr2_end{s2.rend()};
    while (itr1 < itr1_end && itr2 < itr2_end) {
        if (*itr1 != *itr2) {
            return *itr1 < *itr2;
        }
    }
    const auto remaining1{itr1_end - itr1};
    const auto remaining2{itr2_end - itr2};
    return remaining1 < remaining2;
};

BigInt::BigInt(const std::string& value) : is_negative{*value.begin() == '-'} {
    const auto value_start{value.find_first_of("123456789")};
    if (value_start == std::string::npos) {
        this->set_value("0");
    }
    else {
        this->set_value(value.substr(value_start));
    }

    for (const char c : this->value) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument(std::to_string(c) + "(index " + std::to_string(this->value.find(c)) + ")");
        }
    }
};

BigInt::BigInt(const long long value) : BigInt(std::to_string(value)) {};

const std::string& BigInt::get_value() const { return this->value; }
const bool& BigInt::get_negative() const { return this->is_negative; }
void BigInt::set_value(std::string&& val) {
    this->value = std::move(val);
    if (this->value == "0") {
        this->set_negative(false);
    }
}
void BigInt::set_negative(bool&& val) { this->is_negative = std::move(val); }

std::string BigInt::get() const {
    if (this->get_negative()) {
        return "-" + this->get_value();
    }
    return this->get_value();
}

BigInt BigInt::operator+ () const { BigInt value{*this}; return value; }
BigInt BigInt::operator- () const { BigInt value{*this}; value.set_negative(std::move(!this->get_negative())); return value; }

BigInt& BigInt::operator+= (const BigInt& other) {
    if (this->get_negative()) {
        if (other.get_negative()) {
            this->set_value(add(this->value, other.value));
        }
        else {
            if (*this > other) {
                this->set_value(sub(this->value, other.value));
            }
            else {
                this->set_negative(std::move(false));
                this->set_value(sub(other.value, this->value));
            }
        }
    }
    else {
        if (other.get_negative()) {
            if (*this > other) {
                this->set_value(sub(this->value, other.value));
            }
            else {
                this->set_negative(std::move(true));
                this->set_value(sub(other.value, this->value));
            }
        }
        else {
            this->set_value(add(this->value, other.value));
        }
    }

    return *this;
};
BigInt& BigInt::operator-= (const BigInt& other) { const BigInt value{-other}; *this += value; return *this; }
BigInt& BigInt::operator*= (const BigInt& other) { return *this; }; // todo
BigInt& BigInt::operator/= (const BigInt& other) { return *this; }; // todo
BigInt& BigInt::operator%= (const BigInt& other) { return *this; }; // todo

BigInt& BigInt::operator++ () { *this += 1; return *this; };
BigInt& BigInt::operator-- () { *this -= 1; return *this; };

BigInt BigInt::operator++ (int) { BigInt old{*this}; *this += 1; return old; };
BigInt BigInt::operator-- (int) { BigInt old{*this}; *this -= 1; return old; };

BigInt BigInt::operator+ (const BigInt& other) const { BigInt value{*this}; value += other; return value; };
BigInt BigInt::operator- (const BigInt& other) const { BigInt value{*this}; value -= other; return value; };
BigInt BigInt::operator* (const BigInt& other) const { BigInt value{*this}; value *= other; return value; };
BigInt BigInt::operator/ (const BigInt& other) const { BigInt value{*this}; value /= other; return value; };
BigInt BigInt::operator% (const BigInt& other) const { BigInt value{*this}; value %= other; return value; };

BigInt& BigInt::operator<< (const BigInt& other) { *this /= 2; return *this; };
BigInt& BigInt::operator>> (const BigInt& other) { *this *= 2; return *this; };

bool BigInt::operator< (const BigInt& other) const {
    if (this->get_negative()) {
        if (other.get_negative()) {
            return is_less_than(this->get_value(), other.get_value());
        }
        else {
            return true;
        }
    }
    else {
        if (other.get_negative()) {
            return false;
        }
        else {
            return is_less_than(other.get_value(), this->get_value());
        }
    }
};
bool BigInt::operator> (const BigInt& other) const { return *this < other; };
bool BigInt::operator<= (const BigInt& other) const { return !(other > *this);};
bool BigInt::operator>= (const BigInt& other) const { return !(other < *this);};
bool BigInt::operator== (const BigInt& other) const { return this->value == other.value; };
bool BigInt::operator!= (const BigInt& other) const { return !(*this == other); };
