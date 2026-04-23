/*
Title: std::bind and Placeholders Complete Guide
Category: Functional Programming
File: bind.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
Explores std::bind, partial function application, and placeholders. 
Discusses the transition from std::bind to modern Lambda expressions.

Compile:
g++ -std=c++23 bind.cpp -o bind

Run:
./bind

Key Topics:
- std::bind basic syntax
- std::placeholders (_1, _2, ...)
- Binding by value vs binding by reference (std::ref)
- Binding member functions
- Comparison with Lambdas (Modern C++ preference)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <functional>
#include <string>
#include <print>

using namespace std::placeholders; // For _1, _2, ...

int multiply(int a, int b) {
    return a * b;
}

void basic_bind() {
    std::println("--- Basic std::bind ---");

    // Bind 'b' to 10. 'a' remains a placeholder.
    auto multiply_by_10 = std::bind(multiply, _1, 10);
    std::println("10 * 10 = {}", multiply_by_10(10));
    std::println("5 * 10 = {}", multiply_by_10(5));

    // Reordering arguments
    auto divide = [](double a, double b) { return a / b; };
    auto reverse_divide = std::bind(divide, _2, _1);
    std::println("10 / 2 = {}", divide(10, 2));
    std::println("Bind reverse (10, 2) -> 2 / 10 = {}", reverse_divide(10, 2));
}

void bind_with_references() {
    std::println("\n--- Binding with References ---");

    int val = 0;
    auto increment = [](int& n) { n++; };

    // ERROR: std::bind copies arguments by default. 
    // This would increment a copy of 'val'.
    auto bad_inc = std::bind(increment, val);
    bad_inc();
    std::println("After bad_inc, val: {}", val); // Still 0

    // CORRECT: Use std::ref to pass a reference wrapper
    auto good_inc = std::bind(increment, std::ref(val));
    good_inc();
    std::println("After good_inc, val: {}", val); // 1
}

struct Logger {
    void log(const std::string& level, const std::string& msg) {
        std::println("[{}] {}", level, msg);
    }
};

void bind_member_functions() {
    std::println("\n--- Binding Member Functions ---");

    Logger logger;
    
    // Member functions require the object instance as the first argument
    auto info_log = std::bind(&Logger::log, &logger, "INFO", _1);
    info_log("Application started.");
    info_log("Memory usage: 15MB");

    auto error_log = std::bind(&Logger::log, &logger, "ERROR", _1);
    error_log("Connection failed.");
}

/**
 * Modern C++ Note:
 * std::bind is almost always inferior to Lambdas because:
 * 1. Lambdas are easier to read and maintain.
 * 2. Lambdas have better performance (easier for compilers to inline).
 * 3. std::bind requires std::ref/std::cref for references, which is error-prone.
 * 4. Lambdas handle move-only types better.
 */

void bind_vs_lambda() {
    std::println("\n--- std::bind vs Lambda ---");

    int factor = 5;

    // std::bind version
    auto b = std::bind(multiply, _1, factor);
    
    // Lambda version (Preferred)
    auto l = [factor](int x) { return multiply(x, factor); };

    std::println("Bind result: {}", b(10));
    std::println("Lambda result: {}", l(10));
}

int main() {
    try {
        basic_bind();
        bind_with_references();
        bind_member_functions();
        bind_vs_lambda();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Construction: O(N) where N is number of bound arguments (copies/moves them).
 * - Invocation: O(1) plus the cost of the wrapped function call.
 * - Space: sizeof(std::bind object) depends on the number and type of bound args.
 */
