/*
Title: Ranges Algorithms & Views Guide
Category: Algorithms
File: ranges_algorithms.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
A deep dive into the modern C++20/23 Ranges library. Explains the shift from 
iterator-pairs to range-based composition, views, and functional pipelines.

Compile:
g++ -std=c++23 ranges_algorithms.cpp -o ranges_algorithms

Run:
./ranges_algorithms

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::ranges algorithms vs std algorithms
- Projections (Transforming data on-the-fly)
- Range Views (Lazy evaluation, piping)
- C++23: views::zip, views::chunk, views::slide
- C++23: std::ranges::to (Converting ranges back to containers)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <algorithm>
#include <ranges>
#include <print>
#include <string>
#include <list>
#include <map>

namespace rv = std::views;

void print_separator(std::string_view title) {
    std::println("\n--- {} ---", title);
}

int main() {
    // 1. Basic Ranges Algorithm (No more .begin(), .end())
    print_separator("Ranges Algorithms (Basic)");
    std::vector<int> nums = {5, 3, 9, 1, 7};
    std::ranges::sort(nums);
    std::print("Sorted: ");
    for (int n : nums) std::print("{} ", n);
    std::println("");

    // 2. Projections
    // Sort strings by length, not lexicographically, without a complex lambda
    print_separator("Projections");
    std::vector<std::string> names = {"John", "Alice", "Bob", "Charlie"};
    std::ranges::sort(names, {}, &std::string::size);
    std::print("Sorted by length: ");
    for (const auto& s : names) std::print("{} ", s);
    std::println("");

    // 3. Range Views & Pipelines
    // Views are lazy: they don't modify the source or allocate new memory.
    print_separator("Views & Pipelines");
    auto result = nums 
        | rv::filter([](int n) { return n % 2 != 0; }) // Take odds
        | rv::transform([](int n) { return n * n; });  // Square them
    
    std::print("Odd squares: ");
    for (int n : result) std::print("{} ", n);
    std::println("");

    // 4. C++23: views::zip
    // Iterate over multiple containers simultaneously
    print_separator("C++23: views::zip");
    std::vector<int> ids = {1, 2, 3};
    std::vector<std::string> items = {"Laptop", "Mouse", "Keyboard"};
    
    for (auto [id, item] : rv::zip(ids, items)) {
        std::println("Product ID {}: {}", id, item);
    }

    // 5. C++23: views::chunk and views::slide
    print_separator("C++23: views::chunk & views::slide");
    std::vector<int> data = {1, 2, 3, 4, 5, 6};
    
    std::print("Chunks of 2: ");
    for (auto chunk : data | rv::chunk(2)) {
        std::print("[");
        for (int x : chunk) std::print("{} ", x);
        std::print("] ");
    }
    std::println("");

    std::print("Sliding window of 3: ");
    for (auto window : data | rv::slide(3)) {
        std::print("[");
        for (int x : window) std::print("{} ", x);
        std::print("] ");
    }
    std::println("");

    // 6. C++23: std::ranges::to
    // Materialize a view back into a container.
    print_separator("C++23: std::ranges::to");
    auto even_list = data 
        | rv::filter([](int n) { return n % 2 == 0; })
        | std::ranges::to<std::list<int>>();
    
    std::print("Materialized even list: ");
    for (int n : even_list) std::print("{} ", n);
    std::println("");

    // 7. C++23: views::enumerate
    print_separator("C++23: views::enumerate");
    for (auto [idx, val] : names | rv::enumerate) {
        std::println("Index {}: {}", idx, val);
    }

    /*
    --- INTERVIEW PITFALLS ---
    1. Lazy Evaluation: Views are only computed when you iterate over them. 
       If the underlying container is destroyed, the view becomes invalid (dangling).
    2. Modification: Some views are read-only. Transforming a view usually 
       makes it read-only.
    3. Performance: While views are zero-overhead abstractions in many cases, 
       deeply nested pipelines can increase compile times and occasionally 
       affect runtime optimization.
    4. Ranges vs Iterators: Never mix them unless necessary. Ranges are 
       generally safer and prevent "iterator mismatch" errors.

    --- PRODUCTION NOTES ---
    - Use `std::ranges::to` to finish a pipeline and store results.
    - Projections are extremely powerful for cleaner code: 
      `std::ranges::find(employees, "id123", &Employee::id);`
    - C++23 views like `zip` and `enumerate` bring C++ on par with 
      Python and Rust for expressive iteration.
    */

    return 0;
}
