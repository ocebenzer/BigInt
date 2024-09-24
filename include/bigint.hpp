#pragma once

#include <string>
#include <string_view>

namespace ocb {

class BigInt {
private:
    bool is_negative;
    std::string value;

public:
    static BigInt factorial(int);

    BigInt(const std::string& = "0");
    BigInt(std::string&&);
    BigInt(const long long);

    const std::string_view get_value() const;
    const bool& get_negative() const;
    std::string get() const;
    void set_value(std::string&&);
    void set_negative(const bool);
    void set(std::string&&);
    void set(int number);

    bool is_greater_than_int64_max() const;

    BigInt operator+ () const;
    BigInt operator- () const;
    BigInt& operator+= (const BigInt&);
    BigInt& operator-= (const BigInt&);
    BigInt& operator*= (const BigInt&);
    BigInt& operator/= (const BigInt&);
    BigInt& operator%= (const BigInt&);
    BigInt& operator++ ();
    BigInt& operator-- ();
    BigInt operator++ (int);
    BigInt operator-- (int);
    friend BigInt operator+ (BigInt, const BigInt&);
    friend BigInt operator- (BigInt, const BigInt&);
    friend BigInt operator* (BigInt, const BigInt&);
    friend BigInt operator/ (BigInt, const BigInt&);
    friend BigInt operator% (BigInt, const BigInt&);
    friend BigInt operator<< (BigInt, const BigInt&);
    friend BigInt operator>> (BigInt, const BigInt&);
    friend bool operator< (const BigInt&, const BigInt&);
    friend bool operator> (const BigInt&, const BigInt&);
    friend bool operator<= (const BigInt&, const BigInt&);
    friend bool operator>= (const BigInt&, const BigInt&);
    friend bool operator== (const BigInt&, const BigInt&);
    friend bool operator!= (const BigInt&, const BigInt&);
};

std::ostream& operator<< (std::ostream&, const BigInt&);
std::istream& operator>> (std::istream&, BigInt&);

} // namespace ocb
