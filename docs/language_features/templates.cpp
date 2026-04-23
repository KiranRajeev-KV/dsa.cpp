/*
Title: Templates Complete Guide
Category: Language Features
File: templates.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive reference for C++ templates, ranging from basic function templates to C++23 features like explicit object parameters and static operator().

Compile:
g++ -std=c++23 templates.cpp -o templates

Run:
./templates

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Function and Class Templates
- Variable and Alias Templates
- Variadic Templates & Fold Expressions
- CRTP (Curiously Recurring Template Pattern)
- C++23 `static operator()`

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <string>
#include <vector>

// --- 1. Function Templates ---
template <typename T>
T add(T a, T b) {
    return a + b;
}

// --- 2. Class Templates ---
template <typename T, size_t Size>
class FixedArray {
private:
    T data[Size];
public:
    constexpr size_t size() const { return Size; }
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};

// --- 3. Variable Templates (C++14) ---
template <typename T>
constexpr T pi = T(3.1415926535897932385L);

// --- 4. Alias Templates (C++11) ---
template <typename T>
using StringMap = std::vector<std::pair<std::string, T>>;

// --- 5. Variadic Templates & Fold Expressions (C++17) ---
template<typename... Args>
auto sum_all(Args... args) {
    // Unary left fold
    return (... + args);
}

// --- 6. CRTP (Curiously Recurring Template Pattern) ---
// Used for static polymorphism (no vtable overhead)
template <typename Derived>
class Base {
public:
    void interface() {
        // Cast this to Derived* and call implementation
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived1 : public Base<Derived1> {
public:
    void implementation() { std::println("Derived1 Implementation"); }
};

// --- 7. C++23 static operator() ---
// Lambdas without captures and specific structs can now have a static operator().
// This is useful for passing stateless function objects around as simple function pointers.
struct StatefulFunctor {
    int state = 0;
    void operator()(int x) { std::println("State: {}", state + x); }
};

struct StatelessFunctor {
    // C++23 allows static operator()
    static void operator()(int x) {
        std::println("Stateless: {}", x);
    }
};

int main() {
    std::println("--- Templates in Modern C++ ---\n");

    // Basic usage
    std::println("add(5, 10) = {}", add(5, 10));
    std::println("add(2.5, 3.5) = {}", add(2.5, 3.5));

    // Class template
    FixedArray<int, 5> arr;
    arr[0] = 42;
    std::println("FixedArray size: {}, arr[0]: {}", arr.size(), arr[0]);

    // Variable template
    std::println("pi<float>: {}", pi<float>);
    std::println("pi<double>: {}", pi<double>);

    // Variadic templates
    std::println("sum_all(1, 2, 3, 4, 5) = {}", sum_all(1, 2, 3, 4, 5));

    // CRTP
    Derived1 d1;
    d1.interface();

    // C++23 static operator()
    StatelessFunctor::operator()(100);
    StatelessFunctor sf;
    sf(200); // Can still be called on instance

    auto stateless_lambda = [](int x) static {
        std::println("Static lambda: {}", x);
    };
    stateless_lambda(300);

    return 0;
}

/*
Complexity & Performance Notes:
- Templates implement "Duck Typing" at compile-time. There is NO runtime overhead; instead, there is a compile-time cost and potential executable bloat (code bloat) because a new function/class is instantiated for every unique set of template arguments.
- CRTP provides polymorphic behavior without the cost of virtual function calls (vtable lookups), making it extremely efficient for performance-critical code.

Interview Pitfalls:
- Understanding Two-Phase Name Lookup (dependent vs. independent names). Use `this->` or `Base<T>::` when accessing members of a dependent base class.
- Compile-time errors can be notoriously verbose. Concepts (C++20) solve this by constraining template arguments cleanly.
*/
