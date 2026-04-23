/*
Title: std::optional, std::variant, and std::any Complete Guide
Category: Utilities / Vocabulary Types
File: optional_variant_any.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to C++ vocabulary types for handling optional values, 
type-safe unions, and type-erased containers.

Compile:
g++ -std=c++23 optional_variant_any.cpp -o optional_variant_any

Run:
./optional_variant_any

Key Topics:
- std::optional: Dealing with presence/absence
- std::variant: Type-safe sum types (unions)
- std::any: Type-erased storage
- std::visit and overload patterns
- C++23: std::optional monadic operations (and_then, transform, or_else)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <optional>
#include <variant>
#include <any>
#include <string>
#include <print>

/**
 * @brief Demonstrates std::optional and C++23 monadic operations.
 */
void optional_demonstration() {
    std::println("--- Optional & Monadic Operations ---");
    
    auto get_value = [](bool success) -> std::optional<int> {
        if (success) return 42;
        return std::nullopt;
    };
    
    auto opt = get_value(true);
    
    // C++23 Monadic operations
    auto result = opt.transform([](int n) { return n * 2; })
                     .transform([](int n) { return std::to_string(n); });
                     
    std::println("Transformed optional: {}", result.value_or("Nothing"));
    
    auto empty_opt = get_value(false).or_else([] { 
        std::println("Handling empty case..."); 
        return std::optional<int>(0); 
    });
    std::println("Empty opt with or_else: {}", *empty_opt);
}

/**
 * @brief Demonstrates std::variant and the visitor pattern.
 */
void variant_demonstration() {
    std::println("\n--- Variant & Visitor Pattern ---");
    
    using MyVariant = std::variant<int, double, std::string>;
    MyVariant v = 10;
    
    // std::visit
    std::visit([](auto&& arg) {
        std::println("Active variant type: {}", typeid(arg).name());
        std::println("Value: {}", arg);
    }, v);
    
    v = "Hello C++23";
    
    // Helper for multiple lambdas (Overload pattern)
    auto visitor = [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) std::println("Int: {}", arg);
        else if constexpr (std::is_same_v<T, std::string>) std::println("String: {}", arg);
        else std::println("Other type");
    };
    
    std::visit(visitor, v);
}

/**
 * @brief Demonstrates std::any.
 */
void any_demonstration() {
    std::println("\n--- Any (Type Erasure) ---");
    std::any a = 42;
    
    try {
        int val = std::any_cast<int>(a);
        std::println("Any contains int: {}", val);
        
        // This will throw
        // double d = std::any_cast<double>(a);
    } catch (const std::bad_any_cast& e) {
        std::println("Caught: {}", e.what());
    }
    
    if (a.has_value()) {
        std::println("Type of any: {}", a.type().name());
    }
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. optional vs null: optional is safer and more expressive than using magic values like -1 or nullptr.");
    std::println("2. variant vs union: variant is type-safe, calls destructors correctly, and knows its active type.");
    std::println("3. any vs void*: any manages lifetime and provides type safety via any_cast.");
    std::println("4. Performance: variant is generally very fast. any involves heap allocation for large types (Small Object Optimization applies to small types).");
}

int main() {
    optional_demonstration();
    variant_demonstration();
    any_demonstration();
    interview_notes();
    return 0;
}
