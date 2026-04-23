/*
Title: Ultimate C++23 Starter Template for Competitive Programming
Category: Competitive Programming
File: template_starter.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
A comprehensive, modern C++23 starter template for competitive programming 
contests. Includes fast I/O, common aliases, debugging tools, and 
modern language features.

Compile:
g++ -std=c++23 template_starter.cpp -o template_starter

Run:
./template_starter

Key Topics:
- Preprocessor directives for local vs judge
- C++23 I/O with std::println
- Recursive lambdas (deducing this)
- Modular solver structure
- Performance-oriented defaults

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <print>
#include <string>
#include <chrono>

/**
 * --- COMPETITIVE PROGRAMMING TEMPLATE (C++23) ---
 */

// Common Aliases
using ll = long long;
using ld = long double;
using vi = std::vector<int>;
using vll = std::vector<ll>;
using pii = std::pair<int, int>;

// Macros (Optional but helpful)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

// Debugger (Enabled only in local environment)
#ifdef LOCAL
#define debug(...) std::print(stderr, "[{}] : ", #__VA_ARGS__), debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

void debug_out() { std::println(stderr, ""); }
template <typename T, typename... Args>
void debug_out(T H, Args... T_args) { std::print(stderr, "{} ", H); debug_out(T_args...); }

/**
 * Problem Solver Class:
 * Keeps the logic encapsulated and clean.
 */
class Solver {
public:
    void solve() {
        // Read input
        int n;
        if (!(std::cin >> n)) return;

        std::vector<int> a(n);
        for (int& x : a) std::cin >> x;

        // C++23: Process with ranges
        std::ranges::sort(a);
        
        // C++23: Recursive lambda with 'deducing this'
        auto sum_digits = [](this auto self, int x) -> int {
            return x == 0 ? 0 : (x % 10) + self(x / 10);
        };
        (void)sum_digits;

        ll total_sum = 0;
        for (int x : a) total_sum += x;

        // Output results using std::println (faster and cleaner)
        std::println("Smallest: {}, Largest: {}, Total Sum: {}", a[0], a[n-1], total_sum);
    }
};

int main() {
    // Optimization for cin/cout
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Benchmarking start (Local only)
#ifdef LOCAL
    auto start_time = std::chrono::high_resolution_clock::now();
#endif

    int t = 1;
    // std::cin >> t; // Uncomment if there are multiple test cases
    while (t--) {
        Solver solver;
        solver.solve();
    }

#ifdef LOCAL
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    std::println(stderr, "\nExecution time: {:.4f} s", diff.count());
#endif

    return 0;
}

/**
 * Usage Instructions:
 * 1. Copy-paste this template into your contest environment.
 * 2. Implement the 'solve()' logic inside the Solver class.
 * 3. Use std::println for all output to leverage C++23 performance.
 * 4. Run with -DLOCAL to enable debugging and execution timers.
 */
