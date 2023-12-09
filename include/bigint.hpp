#pragma once

#include <string>

class BigInt {
private:
    bool is_negative;
    std::string value;

public:
    BigInt(const std::string& = "");
    BigInt(std::string&&);
    BigInt(const long long);

    const std::string& get_value() const;
    const bool& get_negative() const;
    void set_value(std::string&&);
    void set_negative(const bool);

    std::string get() const;

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
    BigInt operator+ (const BigInt&) const;
    BigInt operator- (const BigInt&) const;
    BigInt operator* (const BigInt&) const;
    BigInt operator/ (const BigInt&) const;
    BigInt operator% (const BigInt&) const;
    BigInt& operator<< (const BigInt&);
    BigInt& operator>> (const BigInt&);
    bool operator< (const BigInt&) const;
    bool operator> (const BigInt&) const;
    bool operator<= (const BigInt&) const;
    bool operator>= (const BigInt&) const;
    bool operator== (const BigInt&) const;
    bool operator!= (const BigInt&) const;
};

std::ostream& operator<< (std::ostream&, const BigInt&);
std::istream& operator>> (std::istream&, BigInt&);
