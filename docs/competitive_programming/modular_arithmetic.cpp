/*
Title: Modular Arithmetic Guide in C++23
Category: Competitive Programming
File: modular_arithmetic.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
A comprehensive guide and implementation of modular arithmetic, 
including modular exponentiation, modular inverse (Fermat's Little Theorem 
and Extended Euclidean Algorithm), and a production-grade 'Modular' class.

Compile:
g++ -std=c++23 modular_arithmetic.cpp -o modular_arithmetic

Run:
./modular_arithmetic

Key Topics:
- Modular Addition, Subtraction, Multiplication
- Modular Exponentiation (Binary Exponentiation)
- Modular Inverse (using Extended GCD and Fermat's)
- Combination formula (nCr) with modular arithmetic
- Modular class with operator overloading

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <print>
#include <expected>

/**
 * Modular arithmetic is essential for problems involving large numbers
 * where the result needs to be modulo M (usually 10^9 + 7 or 998244353).
 */

namespace math_utils {

    template <typename T>
    constexpr T power(T a, long long b, T m) {
        T res = 1;
        a %= m;
        while (b > 0) {
            if (b % 2 == 1) res = (res * a) % m;
            a = (a * a) % m;
            b /= 2;
        }
        return res;
    }

    /**
     * Extended Euclidean Algorithm:
     * Finds x and y such that ax + by = gcd(a, b).
     * Time Complexity: O(log(min(a, b)))
     */
    template <typename T>
    constexpr T extended_gcd(T a, T b, T &x, T &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        T x1, y1;
        T d = extended_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

    /**
     * Modular Inverse using Extended GCD:
     * Works even if M is not prime, as long as gcd(a, M) = 1.
     */
    template <typename T>
    std::expected<T, std::string> mod_inverse(T a, T m) {
        T x, y;
        T g = extended_gcd(a, m, x, y);
        if (g != 1) return std::unexpected("Modular inverse does not exist");
        return (x % m + m) % m;
    }

    /**
     * Production-grade Modular Class for CP:
     * Automatically handles modulo operations.
     */
    template <int MOD>
    struct Modular {
        int val;
        constexpr Modular(long long v = 0) {
            val = (int)(v % MOD);
            if (val < 0) val += MOD;
        }

        Modular& operator+=(const Modular& other) {
            val += other.val;
            if (val >= MOD) val -= MOD;
            return *this;
        }
        Modular& operator-=(const Modular& other) {
            val -= other.val;
            if (val < 0) val += MOD;
            return *this;
        }
        Modular& operator*=(const Modular& other) {
            val = (int)((long long)val * other.val % MOD);
            return *this;
        }
        
        Modular operator+(const Modular& other) const { return Modular(*this) += other; }
        Modular operator-(const Modular& other) const { return Modular(*this) -= other; }
        Modular operator*(const Modular& other) const { return Modular(*this) *= other; }

        bool operator==(const Modular& other) const { return val == other.val; }
        bool operator!=(const Modular& other) const { return val != other.val; }

        Modular pow(long long b) const {
            Modular res = 1, a = *this;
            while (b > 0) {
                if (b % 2 == 1) res *= a;
                a *= a;
                b /= 2;
            }
            return res;
        }

        Modular inv() const {
            // Using Fermat's Little Theorem (requires MOD to be prime)
            return pow(MOD - 2);
        }

        Modular operator/(const Modular& other) const { return *this * other.inv(); }
    };

    using Mint = Modular<1000000007>;
}

/**
 * Precomputing Factorials for Combinations:
 * Often used in CP to calculate nCr in O(1) after O(N) precomputation.
 */
struct Combinatorics {
    int n;
    std::vector<math_utils::Mint> fact, invFact;

    Combinatorics(int _n) : n(_n), fact(_n + 1), invFact(_n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
        invFact[n] = fact[n].inv();
        for (int i = n - 1; i >= 0; i--) invFact[i] = invFact[i + 1] * (i + 1);
    }

    math_utils::Mint nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[r] * invFact[n - r];
    }
};

int main() {
    using namespace math_utils;

    std::println("--- Modular Arithmetic Demo ---");

    Mint a = 1000000000;
    Mint b = 10;
    std::println("a: {}, b: {}", a.val, b.val);
    std::println("a + b: {}", (a + b).val);
    std::println("a - b: {}", (a - b).val);
    std::println("a * b: {}", (a * b).val);
    std::println("a / b: {}", (a / b).val);

    std::println("\n--- Combinatorics (nCr) Demo ---");
    Combinatorics comb(100);
    std::println("10C3: {}", comb.nCr(10, 3).val);
    std::println("100C50 (mod 10^9+7): {}", comb.nCr(100, 50).val);

    std::println("\n--- Complexity Analysis ---");
    std::println("- Binary Exponentiation: O(log B)");
    std::println("- Modular Inverse: O(log M)");
    std::println("- nCr with precomputation: O(1) per query, O(N) precomputation.");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Forgetting to handle negative results in subtraction (a - b % M + M) % M.");
    std::println("- Integer overflow during multiplication before modulo: (a * b) % M fails if a*b > LLONG_MAX.");
    std::println("- Using Fermat's Little Theorem when M is not prime (use Extended GCD instead).");

    return 0;
}
