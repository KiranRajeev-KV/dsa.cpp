/*
Title: Ranges and Views Guide
Category: Iterators / Ranges
File: ranges_views.cpp
C++ Standard: C++23
Difficulty: Intermediate to Advanced

Purpose:
Covers the modern C++20/23 Ranges library which revolutionizes iterator usage.
Explains lazy evaluation, view composition (pipes), and C++23 specific views.

Compile:
g++ -std=c++23 ranges_views.cpp -o ranges_views

Run:
./ranges_views

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Ranges vs. Iterators
- View Composition (The Pipe Operator '|')
- Lazy Evaluation (Views don't own data)
- C++23 std::views::zip
- C++23 std::views::enumerate
- C++23 std::ranges::to (Converting views back to containers)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <ranges>
#include <print>
#include <string>
#include <map>

/**
 * 1. BASIC VIEW COMPOSITION
 * Transformation and Filtering without creating intermediate containers.
 */
void demo_view_pipes() {
    std::println("--- 1. View Composition (Pipes) ---");
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Filter even numbers, then square them
    auto result = nums 
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * n; });

    std::print("Squared Evens: ");
    for (int n : result) {
        std::print("{} ", n);
    }
    std::println("\n");
}

/**
 * 2. C++23 ZIP VIEW
 * Iterating over multiple containers simultaneously.
 */
void demo_zip_view() {
    std::println("--- 2. C++23 std::views::zip ---");
    std::vector<int> ids = {101, 102, 103};
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};

    for (auto const& [id, name] : std::views::zip(ids, names)) {
        std::println("ID: {}, Name: {}", id, name);
    }
    std::println("");
}

/**
 * 3. C++23 ENUMERATE VIEW
 * Getting both index and value in a loop.
 */
void demo_enumerate_view() {
    std::println("--- 3. C++23 std::views::enumerate ---");
    std::vector<std::string> fruits = {"Apple", "Banana", "Cherry"};

    for (auto [index, fruit] : fruits | std::views::enumerate) {
        std::println("Index: {}, Fruit: {}", index, fruit);
    }
    std::println("");
}

/**
 * 4. CONVERTING VIEWS (std::ranges::to)
 * C++23 utility to turn a lazy view back into a concrete container.
 */
void demo_ranges_to() {
    std::println("--- 4. C++23 std::ranges::to ---");
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Transform and collect into a new vector
    auto doubled_vec = nums 
        | std::views::transform([](int n) { return n * 2; })
        | std::ranges::to<std::vector<int>>();

    std::print("Collected Vector: ");
    for (int n : doubled_vec) std::print("{} ", n);
    std::println("\n");
}

/**
 * 5. PERFORMANCE: LAZY EVALUATION
 */
void demo_lazy_eval() {
    std::println("--- 5. Lazy Evaluation Logic ---");
    std::vector<int> v = {1, 2, 3};
    
    int call_count = 0;
    auto view = v | std::views::transform([&](int n) {
        call_count++;
        return n * 10;
    });

    std::println("View created. Call count: {}", call_count); // Should be 0
    
    auto it = view.begin();
    std::println("After accessing first element: {}", *it);
    std::println("Call count: {}\n", call_count); // Should be 1
}

int main() {
    std::println("C++23 Ranges and Views Mastery\n");

    demo_view_pipes();
    demo_zip_view();
    demo_enumerate_view();
    demo_ranges_to();
    demo_lazy_eval();

    std::println("--- Production Notes ---");
    std::println("1. Views are lightweight: They don't copy data, only store iterators/bounds.");
    std::println("2. Complexity: O(1) to create a view, evaluation happens O(N) during iteration.");
    std::println("3. Lifetime Safety: Be careful with 'dangling' views. If the underlying container is destroyed, the view becomes invalid.");
    std::println("4. Interview: Views follow functional-programming patterns (Lazy Evaluation). Mention that std::ranges::to (C++23) is used to 'materialize' a view back into a container.");

    return 0;
}
