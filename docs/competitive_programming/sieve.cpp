/*
Title: Sieve of Eratosthenes and Number Theory in C++23
Category: Competitive Programming
File: sieve.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Covers efficient prime number generation, linear sieve (O(N)), 
prime factorization in O(log N) using smallest prime factor (SPF), 
and divisor counting.

Compile:
g++ -std=c++23 sieve.cpp -o sieve

Run:
./sieve

Key Topics:
- Classic Sieve of Eratosthenes (O(N log log N))
- Linear Sieve (O(N))
- Smallest Prime Factor (SPF) for fast factorization
- Divisor counting and Euler's Totient Function (Phi)
- C++23 std::views for filtering primes

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <print>
#include <ranges>
#include <map>

namespace number_theory {

    /**
     * Linear Sieve:
     * Computes primes and Smallest Prime Factor (SPF) in O(N).
     * Every composite number is visited exactly once by its smallest prime factor.
     */
    struct Sieve {
        int n;
        std::vector<int> min_prime;
        std::vector<int> primes;

        Sieve(int _n) : n(_n), min_prime(_n + 1, 0) {
            for (int i = 2; i <= n; i++) {
                if (min_prime[i] == 0) {
                    min_prime[i] = i;
                    primes.push_back(i);
                }
                for (int p : primes) {
                    if (p > min_prime[i] || (long long)i * p > n) break;
                    min_prime[i * p] = p;
                }
            }
        }

        bool is_prime(int x) const {
            if (x < 2) return false;
            return min_prime[x] == x;
        }

        /**
         * Fast Prime Factorization:
         * Using SPF, factorization takes O(log X).
         */
        std::map<int, int> get_factors(int x) const {
            std::map<int, int> factors;
            while (x > 1) {
                factors[min_prime[x]]++;
                x /= min_prime[x];
            }
            return factors;
        }

        /**
         * Euler's Totient Function (Phi):
         * Number of integers 1 <= k <= x such that gcd(k, x) = 1.
         */
        int phi(int x) const {
            int res = x;
            while (x > 1) {
                int p = min_prime[x];
                res -= res / p;
                while (x % p == 0) x /= p;
            }
            return res;
        }
    };

}

int main() {
    using namespace number_theory;

    int limit = 100;
    Sieve sieve(limit);

    std::println("--- Linear Sieve Demo (up to {}) ---", limit);
    std::print("Primes: ");
    for (int p : sieve.primes) {
        std::print("{} ", p);
    }
    std::println("");

    int num = 84;
    std::println("\n--- Factorization of {} ---", num);
    auto factors = sieve.get_factors(num);
    for (auto [p, count] : factors) {
        std::println("{} ^ {}", p, count);
    }

    std::println("\n--- Euler's Totient Function ---");
    std::println("phi(84) = {}", sieve.phi(84));
    std::println("phi(13) = {} (13 is prime)", sieve.phi(13));

    std::println("\n--- C++23 Ranges + Sieve ---");
    auto prime_squares = sieve.primes 
                        | std::views::transform([](int p) { return p * p; })
                        | std::views::take(5);
    
    std::print("Squares of first 5 primes: ");
    for (int ps : prime_squares) std::print("{} ", ps);
    std::println("");

    std::println("\n--- Complexity Analysis ---");
    std::println("- Linear Sieve construction: O(N)");
    std::println("- Prime Factorization (with SPF): O(log X)");
    std::println("- Euler's Totient: O(log X)");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Forgetting to handle 1 and 0 as non-primes.");
    std::println("- Sieve of Eratosthenes memory limit (use bitset for O(N) bits instead of ints).");
    std::println("- Integer overflow when computing i * i in classic sieve.");

    return 0;
}
