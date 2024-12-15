#pragma once

#include <ostream>
#include <string>
#include <string_view>
#include <cstdint>

namespace ocb {
    class BigInt {
        bool is_negative{};
        std::string value;

    public:
        static BigInt factorial(int64_t);

        // Constructors

        BigInt(const std::string & = "0");

        BigInt(const std::string_view);

        BigInt(int64_t number);

        [[nodiscard]] bool get_negative() const;

        void set_negative(bool);

        [[nodiscard]] std::string_view get_value() const;

        void set_value(std::string &&);

        [[nodiscard]] std::string to_string() const;

        void set(std::string &&);

        void set(int64_t);


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

        BigInt &operator+=(int64_t);

        BigInt &operator-=(int64_t);

        BigInt &operator*=(int64_t);

        BigInt &operator/=(int64_t);

        BigInt &operator%=(int64_t);

        BigInt operator+(const BigInt &) const;

        BigInt operator-(const BigInt &) const;

        BigInt operator*(const BigInt &) const;

        BigInt operator/(const BigInt &) const;

        BigInt operator%(const BigInt &) const;

        BigInt operator+(int64_t) const;

        BigInt operator-(int64_t) const;

        BigInt operator*(int64_t) const;

        BigInt operator/(int64_t) const;

        BigInt operator%(int64_t) const;

        bool operator<(const BigInt &) const;

        bool operator>(const BigInt &) const;

        bool operator<=(const BigInt &) const;

        bool operator>=(const BigInt &) const;

        bool operator==(const BigInt &) const;

        bool operator!=(const BigInt &) const;

        bool operator<(int64_t) const;

        bool operator>(int64_t) const;

        bool operator<=(int64_t) const;

        bool operator>=(int64_t) const;

        bool operator==(int64_t) const;

        bool operator!=(int64_t) const;

        friend BigInt operator+=(int64_t, const BigInt &);

        friend BigInt operator-=(int64_t, const BigInt &);

        friend BigInt operator*=(int64_t, const BigInt &);

        friend BigInt operator/=(int64_t, const BigInt &);

        friend BigInt operator%=(int64_t, const BigInt &);

        friend BigInt operator+(int64_t, const BigInt &);

        friend BigInt operator-(int64_t, const BigInt &);

        friend BigInt operator*(int64_t, const BigInt &);

        friend BigInt operator/(int64_t, const BigInt &);

        friend BigInt operator%(int64_t, const BigInt &);


        // Stream operators

        friend std::ostream &operator<<(std::ostream &, const BigInt &);

        friend std::istream &operator>>(std::istream &, BigInt &);


        // Misc

        [[nodiscard]] bool is_greater_than_int64_max() const;

        friend BigInt operator<<(const BigInt &, const BigInt &);

        friend BigInt operator>>(const BigInt &, const BigInt &);

        friend BigInt operator<<(const BigInt &, int);

        friend BigInt operator>>(const BigInt &, int);
    };
} // namespace ocb

template<>
struct std::hash<ocb::BigInt> {
    std::size_t operator()(const ocb::BigInt &num) const noexcept {
        return std::hash<std::string>()(num.to_string());
    }
};
