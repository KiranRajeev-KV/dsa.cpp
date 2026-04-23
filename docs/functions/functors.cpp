/*
Title: Functors (Function Objects) Complete Guide
Category: Functional Programming
File: functors.cpp
C++ Standard: C++23
Difficulty: Beginner to Intermediate

Purpose:
Explains function objects (functors), their advantages over raw function pointers, 
and how they relate to Lambdas. Covers stateful functors and optimization.

Compile:
g++ -std=c++23 functors.cpp -o functors

Run:
./functors

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Basic Functor syntax (operator())
- Stateful Functors
- Generic Functors (Template operator())
- Optimization: Why Functors are faster than Function Pointers
- C++23: Static operator() in functors

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <print>

// 1. Simple Stateless Functor
struct Adder {
    int operator()(int a, int b) const {
        return a + b;
    }
};

// 2. Stateful Functor
struct SequenceGenerator {
    int current;
    int step;

    SequenceGenerator(int start = 0, int s = 1) : current(start), step(s) {}

    int operator()() {
        int val = current;
        current += step;
        return val;
    }
};

// 3. Generic Functor
struct TypePrinter {
    template <typename T>
    void operator()(const T& val) const {
        std::println("Value: {}", val);
    }
};

// 4. C++23 Static operator()
// Allows calling the functor without an instance, or allows the compiler 
// to optimize out the 'this' pointer.
struct StaticMultiplier {
    static int operator()(int a, int b) {
        return a * b;
    }
};

void basic_functors() {
    std::println("--- Basic Functors ---");
    
    Adder add;
    std::println("Adder(5, 10): {}", add(5, 10));

    SequenceGenerator gen(10, 5);
    std::println("Sequence: {}, {}, {}", gen(), gen(), gen());
}

void stl_integration() {
    std::println("\n--- STL Integration ---");
    
    std::vector<int> nums = {1, 2, 3, 4, 5};
    
    // Using a stateful functor with STL algorithm
    struct Accumulator {
        int sum = 0;
        void operator()(int x) { sum += x; }
    };

    Accumulator acc = std::for_each(nums.begin(), nums.end(), Accumulator{});
    std::println("Sum via Functor: {}", acc.sum);
}

/**
 * Performance Note:
 * Functors are generally faster than raw function pointers because:
 * 1. The compiler knows the exact type of the functor at compile time.
 * 2. This allows the compiler to inline the operator() call.
 * 3. Raw function pointers are opaque to the compiler, often preventing inlining.
 */

void advanced_functors() {
    std::println("\n--- Advanced Functors ---");

    TypePrinter printer;
    printer(42);
    printer("Hello Functors");

    // C++23 Static operator() usage
    std::println("Static Mult: {}", StaticMultiplier{}(6, 7));
    // Note: Even if it's static, you often need an instance for STL algorithms 
    // unless they take the type as a template parameter.
}

/**
 * Functors vs Lambdas:
 * - Lambdas are essentially syntactic sugar for functors.
 * - When you write a lambda, the compiler generates a unique, unnamed functor class.
 * - Manual functors are useful when:
 *   1. You need complex state or multiple methods.
 *   2. You want to name the type for reuse in multiple places.
 *   3. You need to provide custom constructors/destructors.
 */

int main() {
    try {
        basic_functors();
        stl_integration();
        advanced_functors();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
    return 0;
}

/**
 * Complexity Analysis:
 * - Call Overhead: O(1). Usually zero due to inlining.
 * - Space: sizeof(Functor) depends on its data members. Stateless functors 
 *   often have a size of 1 byte (empty base optimization).
 */
