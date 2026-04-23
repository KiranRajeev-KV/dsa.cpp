/*
Title: Concepts Complete Guide
Category: Language Features
File: concepts.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
A comprehensive guide to C++ Concepts, introducing compile-time constraints on template parameters. Concepts drastically improve error messages and API design.

Compile:
g++ -std=c++23 concepts.cpp -o concepts

Run:
./concepts

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `requires` clauses
- Custom concepts
- Standard library concepts (`<concepts>`)
- `requires` expressions (simple, type, compound, nested)
- Constraining `auto` variables

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <concepts>
#include <vector>

// --- 1. Basic Concepts & Requires Clause ---
// Using a standard concept.
template <typename T>
requires std::integral<T>
T add(T a, T b) {
    return a + b;
}

// Shorthand syntax
template <std::floating_point T>
T add(T a, T b) {
    return a + b;
}

// Terse syntax (C++20)
auto add(std::signed_integral auto a, std::signed_integral auto b) {
    return a + b;
}

// --- 2. Custom Concepts & Requires Expressions ---
template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>; // Compound requirement
};

// --- 3. Requires Expressions in depth ---
template <typename T>
concept Container = requires(T c) {
    // Simple requirement: expression must be valid
    c.size();
    c.empty();
    
    // Type requirement: nested type must exist
    typename T::value_type;
    typename T::iterator;
    
    // Compound requirement: return type must satisfy concept
    { c.begin() } -> std::same_as<typename T::iterator>;
    { c.end() } -> std::same_as<typename T::iterator>;
};

void print_container(const Container auto& c) {
    for (const auto& elem : c) {
        std::println("{} ", elem);
    }
    std::println("");
}

// --- 4. Constraining auto ---
void test_auto_constraints() {
    std::integral auto x = 10;
    // std::integral auto y = 3.14; // Compilation Error!
    std::println("Constrained auto x: {}", x);
}

// --- 5. Overload Resolution with Concepts ---
// The compiler prefers the most constrained template.
template<typename T>
void process(T) {
    std::println("Process generic");
}

template<std::integral T>
void process(T) {
    std::println("Process integral");
}

int main() {
    std::println("--- C++ Concepts ---\n");

    std::println("add(int): {}", add(5, 7));
    std::println("add(float): {}", add(5.5f, 7.2f));
    // add("A", "B"); // Compilation error: constraints not satisfied

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::println("Container print: ");
    print_container(vec);

    test_auto_constraints();

    process(3.14); // Calls generic
    process(42);   // Calls integral (more constrained)

    return 0;
}

/*
Complexity & Performance Notes:
- Concepts impose absolutely NO runtime overhead. They are purely compile-time checks used for SFINAE (Substitution Failure Is Not An Error) replacement and overload resolution.
- Concepts make compile times marginally slower due to constraint checking, but drastically improve the readability of compilation errors (no more 100-page template spews).

Interview Pitfalls:
- Understanding the difference between a `requires` clause and a `requires` expression.
  `template <typename T> requires std::integral<T>` (clause).
  `concept C = requires(T x) { x.foo(); };` (expression evaluating to bool).
- Overload resolution: the most specific concept wins. If concepts are not in a strict subsumption relationship, it causes an ambiguous overload error.
*/
