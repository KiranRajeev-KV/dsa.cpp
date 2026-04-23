/*
Title: std::set Complete Guide
Category: Associative Containers
File: set.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
A comprehensive guide to std::set, an ordered associative container typically implemented 
as a Red-Black Tree. Covers uniqueness, ordering, log(N) operations, and C++23 features.

Compile:
g++ -std=c++23 set.cpp -o set

Run:
./set

Key Topics:
- Red-Black Tree Mechanics
- O(log N) Insert/Erase/Find
- Custom Comparators
- Node handles (extract and merge)
- C++23: std::ranges::to, formatted output, ranges::contains

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <set>
#include <vector>
#include <algorithm>
#include <print>
#include <ranges>
#include <string>
#include <ostream>

/**
 * @brief Demonstrates basic set operations.
 */
void basic_operations() {
    std::println("--- Set Basics ---");
    std::set<int> s = {5, 2, 8, 1, 9, 2}; // Duplicates are ignored
    
    std::println("Set elements (sorted automatically): {}", s);
    
    // Insertion
    auto [it, inserted] = s.insert(7);
    std::println("Inserted 7? {}", inserted);
    
    auto [it2, inserted2] = s.insert(5);
    std::println("Inserted 5? {}", inserted2); // False, already exists
}

// Custom object set
struct Person {
    std::string name;
    int age;

    // Needed for formatted output
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.name << "(" << p.age << ")";
    }
};

/**
 * @brief Shows custom comparators to change ordering.
 */
void custom_comparator() {
    std::println("\n--- Custom Comparator ---");

    // Descending order set
    std::set<int, std::greater<int>> s_desc = {5, 2, 8, 1, 9};
    std::println("Descending set: {}", s_desc);    
    // Lambda comparator for C++20/23
    auto comp = [](const Person& a, const Person& b) {
        return a.age < b.age; // Sort by age
    };
    
    std::set<Person, decltype(comp)> people(comp);
    people.insert({"Alice", 30});
    people.insert({"Bob", 25});
    people.insert({"Charlie", 35});
    
    // Workaround for std::print not easily supporting sets with custom comparators implicitly
    // without specializing std::formatter. We iterate manually.
    std::print("People sorted by age: ");
    for (const auto& p : people) {
        std::print("{} ", p.name);
    }
    std::println("");
}

/**
 * @brief Modern node extraction and merging (C++17/C++23 context).
 */
void node_manipulation() {
    std::println("\n--- Node Extraction (Zero-copy move) ---");
    std::set<int> set1 = {1, 2, 3};
    std::set<int> set2 = {3, 4, 5};
    
    // Extract node '2' from set1
    auto node = set1.extract(2);
    node.value() = 10; // Modify value of the extracted node (safe because it's not in the tree)
    
    // Insert into set2
    set2.insert(std::move(node));
    
    std::println("Set 1 after extraction: {}", set1);
    std::println("Set 2 after insertion: {}", set2);
    
    // Merge all remaining nodes from set1 into set2 (efficient, no allocations)
    set2.merge(set1);
    std::println("Set 2 after merge: {}", set2);
}

/**
 * @brief C++23 features with set.
 */
void cpp23_set() {
    std::println("\n--- C++23 and Set ---");
    
    std::set<int> s = {10, 20, 30, 40};
    
    // C++23 ranges::contains (much cleaner than s.find(x) != s.end())
    bool has_20 = std::ranges::contains(s, 20);
    std::println("Contains 20? {}", has_20);
    
    auto range = std::views::iota(1, 10) 
               | std::views::filter([](int n) { return n % 3 == 0; });
               
    auto s_from_view = std::ranges::to<std::set<int>>(range);
    std::println("Set from range::to: {}", s_from_view);
}

/**
 * @brief Interview Pitfalls and Production Notes.
 */
void interview_notes() {
    std::println("\n--- Interview & Production Notes ---");
    std::println("1. Iterators are const: You cannot modify a set element directly via iterator (it breaks the tree ordering). You must erase and insert, or use node extract.");
    std::println("2. Performance: High memory overhead per node (color, parent, left, right). Poor cache locality. If elements don't change often, consider a sorted std::vector.");
    std::println("3. contains() vs find(): Prefer .contains() in C++20+ over .find() != .end() for readability.");
}

/**
 * @brief Complexity:
 * - Insert/Delete/Find: O(log N)
 * - Space: O(N) with heavy per-node overhead.
 */
int main() {
    basic_operations();
    custom_comparator();
    node_manipulation();
    cpp23_set();
    interview_notes();
    return 0;
}
