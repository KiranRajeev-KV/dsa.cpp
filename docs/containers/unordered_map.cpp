/*
Title: std::unordered_map Complete Guide
Category: Associative Containers
File: unordered_map.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::unordered_map, the high-performance hash-map container.
Covers hashing, performance tuning, and C++23 enhancements.

Compile:
g++ -std=c++23 unordered_map.cpp -o unordered_map

Run:
./unordered_map

Key Topics:
- Hash Table Mechanics for Pairs
- Average O(1) performance
- Buckets and Load Factor
- Custom Hashers for keys
- C++23: std::ranges::to, try_emplace, contains

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <unordered_map>
#include <print>
#include <ranges>
#include <string>

/**
 * @brief Demonstrates basic unordered_map operations.
 */
void basic_operations() {
    std::println("--- Unordered Map Basics ---");
    std::unordered_map<std::string, std::string> capitals = {
        {"France", "Paris"}, {"Japan", "Tokyo"}, {"Egypt", "Cairo"}
    };
    
    capitals["India"] = "New Delhi";
    
    std::println("Capitals: {}", capitals);
    std::println("Bucket count: {}", capitals.bucket_count());
}

/**
 * @brief Performance tuning via reserve and load factor.
 */
void performance_tuning() {
    std::println("\n--- Performance Tuning ---");
    std::unordered_map<int, int> m;
    
    std::println("Default max_load_factor: {}", m.max_load_factor());
    
    // Prevent rehashes if we know the size
    m.reserve(1000);
    std::println("Bucket count after reserve(1000): {}", m.bucket_count());
}

/**
 * @brief C++23 and modern API usage.
 */
void modern_api() {
    std::println("\n--- Modern API & C++23 ---");
    std::unordered_map<int, std::string> m = {{1, "A"}, {2, "B"}};
    
    // C++20/23 contains
    if (m.contains(1)) std::println("Key 1 exists.");
    
    // C++17/23 try_emplace
    // Doesn't even construct the string if key exists (more efficient)
    m.try_emplace(1, "Already here");
    m.try_emplace(3, "New value");
    
    // C++23 ranges::to
    auto squares_view = std::views::iota(1, 6) 
                      | std::views::transform([](int n){ return std::make_pair(n, n*n); });
                      
    auto squares_map = std::ranges::to<std::unordered_map<int, int>>(squares_view);
    std::println("Squares Map: {}", squares_map);
}

/**
 * @brief Custom Hashing for complex keys.
 */
struct ConfigKey {
    int id;
    std::string section;
    bool operator==(const ConfigKey&) const = default; // C++20 defaulted comparison
};

// Specialized hasher
namespace std {
    template<> struct hash<ConfigKey> {
        size_t operator()(const ConfigKey& k) const {
            return hash<int>{}(k.id) ^ hash<string>{}(k.section);
        }
    };
}

void custom_hashing() {
    std::println("\n--- Custom Hashing ---");
    std::unordered_map<ConfigKey, std::string> configs;
    configs[{1, "Network"}] = "Enabled";
    
    std::println("Config found: {}", configs[{1, "Network"}]);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Iteration order: Unpredictable and changes after rehashing.");
    std::println("2. Pointer Stability: References to values and keys remain stable until the element is erased. Only iterators are invalidated by rehash.");
    std::println("3. Security: Beware of adversarial input causing O(N) lookup. Use a non-deterministic hasher if exposing to public web traffic.");
}

/**
 * @brief Complexity:
 * - Average: O(1)
 * - Worst: O(N)
 */
int main() {
    basic_operations();
    performance_tuning();
    modern_api();
    custom_hashing();
    interview_notes();
    return 0;
}
