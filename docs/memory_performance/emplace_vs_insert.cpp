/*
Title: Emplace vs. Insert: Optimization and Temporary Objects
Category: Memory & Performance
File: emplace_vs_insert.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
To compare emplace_back vs push_back (and emplace vs insert) in STL containers.
This file explains how emplace functions perform direct initialization in-place,
avoiding unnecessary temporary objects and move/copy operations.

Compile:
g++ -std=c++23 emplace_vs_insert.cpp -o emplace_vs_insert

Run:
./emplace_vs_insert

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Direct Initialization vs. Copy/Move Initialization
- Temporary object creation and destruction
- perfect forwarding (std::forward)
- Why emplace is not always a "magic" optimization
- emplace and explicit constructors

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <string>
#include <print>

/**
 * @brief A class that logs its lifecycle events.
 */
class Item {
    std::string name;
    int value;

public:
    // Constructor
    Item(std::string n, int v) : name(std::move(n)), value(v) {
        std::println("  [Constructor] Item('{}', {})", name, value);
    }

    // Explicit constructor - can only be used with direct initialization (emplace)
    explicit Item(int v) : name("Explicit"), value(v) {
        std::println("  [Constructor] Item({}) (Explicit)", value);
    }

    // Copy Constructor
    Item(const Item& other) : name(other.name), value(other.value) {
        std::println("  [Copy Constructor] Item('{}')", name);
    }

    // Move Constructor
    Item(Item&& other) noexcept : name(std::move(other.name)), value(other.value) {
        std::println("  [Move Constructor] Item('{}')", name);
    }

    // Destructor
    ~Item() {
        // std::println("  [Destructor] Item('{}')", name);
    }
};

/**
 * @brief Demonstrates the difference between push_back and emplace_back.
 */
void demonstrate_push_vs_emplace() {
    std::println("\n--- 1. push_back vs emplace_back ---");
    
    std::vector<Item> vec;
    vec.reserve(10); // Reserve to avoid reallocations interfering with logs

    std::println("Using push_back (requires a temporary or existing object):");
    // 1. Create temporary Item
    // 2. Move temporary into vector
    // 3. Destroy temporary
    vec.push_back(Item("PushItem", 100));

    std::println("\nUsing emplace_back (constructs in-place):");
    // 1. Construct directly in the vector's memory
    // No temporary, no move.
    vec.emplace_back("EmplaceItem", 200);
}

/**
 * @brief Demonstrates emplace with explicit constructors.
 */
void demonstrate_explicit_constructors() {
    std::println("\n--- 2. Emplace and Explicit Constructors ---");
    
    std::vector<Item> vec;
    vec.reserve(5);

    // vec.push_back(42); // Error: Item(int) is explicit
    
    // emplace_back can call explicit constructors because it uses 
    // direct-initialization syntax under the hood.
    vec.emplace_back(42); 
    std::println("emplace_back successfully called the explicit constructor.");
}

/**
 * @brief Discusses why emplace isn't ALWAYS better.
 */
void demonstrate_emplace_pitfalls() {
    std::println("\n--- 3. When Emplace is NOT a win ---");

    std::vector<std::string> vec;
    vec.reserve(5);

    // If you already HAVE the object, emplace is no better than push_back (move).
    std::string s = "AlreadyExists";
    
    std::println("Passing an existing object to push_back:");
    vec.push_back(std::move(s));

    std::string s2 = "AlreadyExists2";
    std::println("Passing an existing object to emplace_back:");
    vec.emplace_back(std::move(s2));

    std::println("Note: Both call the move constructor. Emplace only wins when you pass constructor arguments.");
}

int main() {
    std::println("C++23 Memory & Performance: Emplace vs Insert");
    
    demonstrate_push_vs_emplace();
    demonstrate_explicit_constructors();
    demonstrate_emplace_pitfalls();

    return 0;
}

/*
Complexity Analysis:
- push_back: O(1) amortized. If no reallocation: 1 Construction (temporary) + 1 Move.
- emplace_back: O(1) amortized. If no reallocation: 1 Construction (in-place).
- Space Complexity: Identical for both.

Production Notes:
1. Prefer emplace_back when constructing a NEW object from arguments.
2. Prefer push_back when adding an EXISTING object (it's more readable and 
   sometimes safer with explicit constructors).
3. Be careful with 'emplace' in associative containers (like std::map). 
   'emplace' might construct the object even if the key already exists 
   (though it won't be inserted), which can be expensive.

Interview Pitfalls:
- Thinking emplace is ALWAYS faster. It's only faster if it avoids a temporary.
- Forgetting that emplace bypasses 'explicit' checks. This can lead to 
  accidental type conversions if the constructor arguments match something 
  unexpected.
- Reallocations: Both push_back and emplace_back trigger vector reallocations 
  if the capacity is exceeded, which is O(N).
*/
