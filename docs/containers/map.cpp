/*
Title: std::map Complete Guide
Category: Associative Containers
File: map.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::map, an ordered associative container of key-value pairs.
Covers tree-based mapping, lookup mechanics, and C++23 features.

Compile:
g++ -std=c++23 map.cpp -o map

Run:
./map

Key Topics:
- Red-Black Tree for Pairs
- O(log N) Lookup/Insert
- operator[] vs at() vs insert() vs emplace()
- C++23: std::ranges::to, formatted output, try_emplace
- Node handles and merging

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <map>
#include <print>
#include <ranges>
#include <string>

/**
 * @brief Demonstrates basic map operations and different insertion methods.
 */
void basic_operations() {
    std::println("--- Map Basics ---");
    std::map<std::string, int> ages;
    
    // 1. operator[] - convenient but has side effects (inserts default if key missing)
    ages["Alice"] = 30;
    
    // 2. insert() - returns pair<iterator, bool>
    auto [it, inserted] = ages.insert({"Bob", 25});
    std::println("Inserted Bob? {}", inserted);
    
    // 3. emplace() - constructs in-place
    ages.emplace("Charlie", 35);
    
    // 4. try_emplace (C++17/23) - better for complex values, doesn't construct if key exists
    ages.try_emplace("Alice", 40); // Alice remains 30
    
    std::println("Map contents: {}", ages);
}

/**
 * @brief Explains the difference between operator[] and at().
 */
void lookup_mechanics() {
    std::println("\n--- Lookup Mechanics ---");
    std::map<int, std::string> m = {{1, "One"}, {2, "Two"}};
    
    // at() is safe and const-friendly
    try {
        std::println("Key 1: {}", m.at(1));
        std::println("Key 3: {}", m.at(3)); // Throws
    } catch (const std::out_of_range& e) {
        std::println("at(3) failed: {}", e.what());
    }
    
    // operator[] is NOT const-friendly and will insert if missing
    std::println("Size before m[3]: {}", m.size());
    std::string val = m[3]; 
    std::println("Size after m[3]: {}", m.size());
}

/**
 * @brief Node manipulation and C++23 features.
 */
void advanced_features() {
    std::println("\n--- Advanced & C++23 Features ---");
    
    // C++23 ranges::to
    auto pairs = std::views::iota(1, 4) 
               | std::views::transform([](int n) { 
                   return std::make_pair(n, std::string(n, '*')); 
                 });
                 
    auto m = std::ranges::to<std::map<int, std::string>>(pairs);
    std::println("Map from range: {}", m);
    
    // Node handles: renaming a key without reallocation
    auto node = m.extract(2);
    if (!node.empty()) {
        node.key() = 20;
        m.insert(std::move(node));
    }
    std::println("Map after key rename: {}", m);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. operator[] Pitfall: If used in a loop to 'check' existence, it fills the map with default values. Use .contains() or .find() instead.");
    std::println("2. Sorting: Keys are always sorted. You can provide a custom comparator template argument.");
    std::println("3. Performance: Like std::set, high memory overhead per node. Log(N) is usually fast enough, but O(1) unordered_map is preferred if ordering doesn't matter.");
}

/**
 * @brief Complexity:
 * - Lookup/Insert/Delete: O(log N)
 * - Space: O(N)
 */
int main() {
    basic_operations();
    lookup_mechanics();
    advanced_features();
    interview_notes();
    return 0;
}
