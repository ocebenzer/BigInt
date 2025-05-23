#pragma once

#include <ostream>
#include <string>
#include <string_view>

namespace ocb {
    class BigInt {
        bool is_negative{};
        std::string value;

    public:
        BigInt(long long int);
        BigInt(const std::string& = "0");
        BigInt(std::string&&);

        [[nodiscard]] bool get_negative() const;
        void set_negative(bool);
        [[nodiscard]] std::string_view get_value() const;
        void set_value(std::string &&);
        [[nodiscard]] std::string to_string() const;
        void set(std::string &&);
        void set(long long int);

        // Unary operators

        BigInt operator+() const;
        BigInt operator-() const;
        BigInt &operator--();
        BigInt operator--(int);
        BigInt &operator++();
        BigInt operator++(int);

        // Binary Arithmetic Operators

        BigInt &operator+=(const BigInt &);
        BigInt &operator-=(const BigInt &);
        BigInt &operator*=(const BigInt &);
        BigInt &operator/=(const BigInt &);
        BigInt &operator%=(const BigInt &);


        // Binary Arithmetic Operator Overrides

        BigInt &operator+=(long long int);
        BigInt &operator-=(long long int);
        BigInt &operator*=(long long int);
        BigInt &operator/=(long long int);
        BigInt &operator%=(long long int);

        BigInt operator+(const BigInt &) const;
        BigInt operator-(const BigInt &) const;
        BigInt operator*(const BigInt &) const;
        BigInt operator/(const BigInt &) const;
        BigInt operator%(const BigInt &) const;

        BigInt operator+(long long int) const;
        BigInt operator-(long long int) const;
        BigInt operator*(long long int) const;
        BigInt operator/(long long int) const;
        BigInt operator%(long long int) const;

        bool operator<(const BigInt &) const;
        bool operator>(const BigInt &) const;
        bool operator<=(const BigInt &) const;
        bool operator>=(const BigInt &) const;
        bool operator==(const BigInt &) const;
        bool operator!=(const BigInt &) const;

        bool operator<(long long int) const;
        bool operator>(long long int) const;
        bool operator<=(long long int) const;
        bool operator>=(long long int) const;
        bool operator==(long long int) const;
        bool operator!=(long long int) const;

        friend BigInt operator+=(long long int, const BigInt &);
        friend BigInt operator-=(long long int, const BigInt &);
        friend BigInt operator*=(long long int, const BigInt &);
        friend BigInt operator/=(long long int, const BigInt &);
        friend BigInt operator%=(long long int, const BigInt &);
        friend BigInt operator+(long long int, const BigInt &);
        friend BigInt operator-(long long int, const BigInt &);
        friend BigInt operator*(long long int, const BigInt &);
        friend BigInt operator/(long long int, const BigInt &);
        friend BigInt operator%(long long int, const BigInt &);

        // Stream operators

        friend std::ostream &operator<<(std::ostream &, const BigInt &);
        friend std::istream &operator>>(std::istream &, BigInt &);

        // Misc

        [[nodiscard]] bool is_greater_than_int64_max() const;
        friend BigInt operator<<(const BigInt &, const BigInt &);
        friend BigInt operator>>(const BigInt &, const BigInt &);
        friend BigInt operator<<(const BigInt &, long long int);
        friend BigInt operator>>(const BigInt &, long long int);
    };

    BigInt operator""_BigInt (unsigned long long);

    BigInt factorial(unsigned long long int);
    BigInt fibonacci(unsigned long long int);
} // namespace ocb

template<>
struct std::hash<ocb::BigInt> {
    std::size_t operator()(const ocb::BigInt &num) const noexcept {
        return std::hash<std::string>()(num.to_string());
    }
};
