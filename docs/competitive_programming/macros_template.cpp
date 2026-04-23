/*
Title: Modern C++23 Macros and Templates for Competitive Programming
Category: Competitive Programming
File: macros_template.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Demonstrates efficient macros, type aliases, and template utilities for 
speeding up coding in competitive programming while maintaining C++23 standards.
Focuses on std::ranges, views, and modern type deduction.

Compile:
g++ -std=c++23 macros_template.cpp -o macros_template

Run:
./macros_template

Key Topics:
- Type aliases (ll, vll, pii)
- Modern loops with std::ranges and views
- Debugging templates with std::print
- Lambda-based recursive functions (std::function vs deducing this)
- Universal min/max and utility functions

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <print>
#include <concepts>
#include <functional>

/**
 * Common CP Type Aliases:
 * Use 'using' instead of '#define' for type safety and better compiler errors.
 */
using ll = long long;
using ld = long double;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;
using vi = std::vector<int>;
using vll = std::vector<ll>;
using vvi = std::vector<vi>;

/**
 * Modern Loop Macros (Optional but common in CP):
 * In C++23, we prefer ranges and views.
 */
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())

namespace cp_utils {

    /**
     * C++23 Debug Print:
     * A powerful debug utility using std::print and concepts.
     */
    template <typename T>
    concept Container = requires(T t) {
        t.begin();
        t.end();
    } && !std::same_as<T, std::string>;

    void debug_out() { std::println(stderr, ""); }

    template <typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        if constexpr (Container<Head>) {
            std::print(stderr, "[ ");
            for (const auto& x : H) std::print(stderr, "{} ", x);
            std::print(stderr, "] ");
        } else {
            std::print(stderr, "{} ", H);
        }
        debug_out(T...);
    }

    #ifdef LOCAL
    #define debug(...) std::print(stderr, "[{}] : ", #__VA_ARGS__), debug_out(__VA_ARGS__)
    #else
    #define debug(...)
    #endif

    /**
     * C++23 Lambda Recursion (Deducing 'this'):
     * No more std::function overhead for recursive lambdas!
     */
    void demonstrate_recursion() {
        auto fib = [](this auto self, int n) -> ll {
            if (n <= 1) return n;
            return self(n - 1) + self(n - 2);
        };
        std::println("Fibonacci(10): {}", fib(10));
    }

    /**
     * Range-based operations:
     */
    void demonstrate_ranges() {
        vi v = {5, 2, 8, 1, 9};
        
        // Sorting using ranges
        std::ranges::sort(v);
        
        // Using views to filter and transform (C++23 views::zip is amazing)
        auto squared_even = v | std::views::filter([](int x) { return x % 2 == 0; })
                              | std::views::transform([](int x) { return x * x; });

        std::print("Squared even elements: ");
        for (int x : squared_even) std::print("{} ", x);
        std::println("");
    }
}

int main() {
    std::println("--- Modern C++23 CP Templates Demo ---");

    cp_utils::demonstrate_recursion();
    cp_utils::demonstrate_ranges();

    // Example of using the aliases
    vll large_data = {1000000000LL, 2000000000LL};
    std::println("Large data size: {}", sz(large_data));

    std::println("\n--- Production Notes ---");
    std::println("- Avoid #define for anything that can be a 'using' or 'constexpr'.");
    std::println("- 'deducing this' in lambdas is more efficient than std::function.");
    std::println("- Use std::ranges::sort instead of std::sort(all(v)) for cleaner code.");

    std::println("\n--- Interview Pitfalls ---");
    std::println("- Over-reliance on macros can make code unreadable to interviewers.");
    std::println("- Always explain why you use ll (long long) for potential overflows.");
    std::println("- Be careful with sz(x) macro if the container size is unsigned.");

    return 0;
}
