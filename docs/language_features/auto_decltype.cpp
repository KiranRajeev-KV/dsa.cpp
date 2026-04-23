/*
Title: Auto and Decltype Complete Guide
Category: Language Features
File: auto_decltype.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to type deduction in modern C++ using `auto`, `decltype`, `decltype(auto)`, and the C++23 `auto(x)` / `auto{x}` decay-copy features.

Compile:
g++ -std=c++23 auto_decltype.cpp -o auto_decltype

Run:
./auto_decltype

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `auto` and `const auto&`
- `decltype` vs `auto`
- `decltype(auto)` for perfect return types
- C++23 `auto(x)` / `auto{x}` (Decay-copy)
- Trailing return types

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <vector>
#include <string>
#include <type_traits>
#include <cassert>

// --- Helper for Type Display ---
template<typename T>
void print_type(const std::string& name) {
    std::println("Type of {} is correctly deduced.", name);
}

// --- decltype(auto) for Perfect Return Types ---
// Returns exactly the type of the expression (reference or value).
template<typename Container, typename Index>
decltype(auto) get_element(Container& c, Index i) {
    return c[i]; // If c[i] returns T&, decltype(auto) yields T&. If T, yields T.
}

int main() {
    std::println("--- Auto and Decltype (C++23) ---\n");

    // 1. Basic auto type deduction
    auto i = 42; // int
    auto d = 3.14; // double
    const auto p = &i; // int* const (const pointer to int)
    (void)d; (void)p;

    // auto strips top-level const and references by default
    const int ci = 10;
    auto val = ci; // int (copied)
    val = 20; // OK
    (void)val;

    // Explicitly add const/reference
    const auto& ref = ci; // const int&
    (void)ref;    
    // 2. decltype
    // decltype yields the EXACT type of the expression.
    int x = 5;
    int& rx = x;
    decltype(rx) exactly_rx = x; // int&
    exactly_rx = 10;
    assert(x == 10);
    
    // 3. decltype(auto)
    std::vector<int> vec = {1, 2, 3};
    get_element(vec, 1) = 99; // Returns int&, modifies the vector!
    assert(vec[1] == 99);
    
    // 4. C++23: auto(x) and auto{x} (Decay-Copy)
    // Sometimes you want to explicitly create a prvalue copy of an object,
    // decaying it (removing references, const, arrays to pointers, etc.)
    // auto(x) does exactly this, useful for passing a copy to a function
    // or mutating a local copy safely.
    
    std::string text = "Hello C++23";
    auto manipulate_copy = [](auto val) {
        val += " modified";
        std::println("Inside lambda: {}", val);
    };
    
    // We want to pass a copy of 'text' without modifying 'text'.
    // While pass-by-value does this, auto(x) explicitly requests a prvalue copy
    // right at the call site.
    manipulate_copy(auto(text)); 
    std::println("After lambda: {}", text);

    // Decay array to pointer using auto(x)
    int arr[5] = {1, 2, 3, 4, 5};
    auto ptr = auto(arr); // ptr is int*, decayed from int[5]
    static_assert(std::is_same_v<decltype(ptr), int*>);
    
    std::println("\nAll type deductions successfully demonstrated.");
    return 0;
}

/*
Complexity & Performance Notes:
- `auto` has ZERO runtime cost. Type deduction happens purely at compile-time.
- `auto(x)` is a clean way to force a copy/decay without explicitly spelling out the type. It avoids redundant type typing and prevents accidental reference binding.

Interview Pitfalls:
- Forgetting that `auto` strips references. `auto obj = get_singleton();` might make a full copy if `get_singleton()` returns a reference. Always use `auto&` or `const auto&` if you don't want a copy.
- Confusing `decltype(x)` (type of entity) and `decltype((x))` (type of expression). `decltype((x))` is `int&` if `x` is an lvalue of type `int`.
*/
