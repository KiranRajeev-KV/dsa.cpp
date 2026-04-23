/*
Title: Copy vs. Move Semantics Complete Guide
Category: Memory & Performance
File: copy_vs_move.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
To master move semantics, lvalues, rvalues, and the performance benefits of moving
over copying. This file demonstrates how to implement move constructors/assignment
operators and explains compiler optimizations like RVO and NRVO.

Compile:
g++ -std=c++23 copy_vs_move.cpp -o copy_vs_move

Run:
./copy_vs_move

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- Lvalues vs. Rvalues (and Xvalues, Glvalues, Prvalues)
- Move Constructors and Move Assignment Operators
- std::move and its effect
- Return Value Optimization (RVO) and Mandatory Copy Elision
- Named Return Value Optimization (NRVO)
- C++23 auto(x) and auto{x} for explicit copies

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <vector>
#include <string>
#include <print>
#include <utility>
#include <algorithm>

/**
 * @brief A Resource-managing class to track copies and moves.
 */
class ResourceManager {
    std::string name;
    int* data;
    size_t size;

public:
    explicit ResourceManager(std::string n, size_t s) 
        : name(std::move(n)), size(s) {
        data = new int[size];
        std::println("[Constructor] Created {} at {:p}", name, (void*)data);
    }

    // Destructor
    ~ResourceManager() {
        if (data) {
            std::println("[Destructor] Deleting {} at {:p}", name, (void*)data);
            delete[] data;
        } else {
            std::println("[Destructor] Deleting {} (Already moved/null)", name);
        }
    }

    // 1. Copy Constructor (Deep Copy)
    ResourceManager(const ResourceManager& other) 
        : name(other.name + "_copy"), size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        std::println("[Copy Constructor] Copied {} to {}", other.name, name);
    }

    // 2. Move Constructor (Shallow Copy + Nulling other)
    ResourceManager(ResourceManager&& other) noexcept 
        : name(std::move(other.name) + "_moved"), data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::println("[Move Constructor] Moved resources from original to {}", name);
    }

    // 3. Move Assignment
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        std::println("[Move Assignment] Assigning to {}", name);
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            name = std::move(other.name) + "_assigned";
            
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void info() const {
        std::println("  Object: {}, Data Address: {:p}, Size: {}", name, (void*)data, size);
    }
};

/**
 * @brief Demonstrates the difference between copy and move.
 */
void demonstrate_move_vs_copy() {
    std::println("\n--- 1. Manual Copy vs. Move ---");
    
    ResourceManager res1("Source", 100);
    
    std::println("Performing Copy:");
    ResourceManager res2 = res1; // Calls Copy Constructor
    
    std::println("Performing Move:");
    ResourceManager res3 = std::move(res1); // Calls Move Constructor
    
    res1.info(); // res1 is now in a valid but unspecified (moved-from) state
    res2.info();
    res3.info();
}

/**
 * @brief Demonstrates RVO (Return Value Optimization).
 */
ResourceManager create_resource(const std::string& name) {
    // This is a prvalue (pure rvalue)
    return ResourceManager(name, 50);
}

void demonstrate_rvo() {
    std::println("\n--- 2. Return Value Optimization (RVO) ---");
    
    // In C++17/20/23, RVO is mandatory for prvalues.
    // No copy or move constructor is called here!
    ResourceManager res = create_resource("RVO_Target");
    res.info();
}

/**
 * @brief Demonstrates NRVO (Named Return Value Optimization).
 */
ResourceManager create_resource_named(const std::string& name) {
    ResourceManager local(name, 50);
    local.info();
    // This is a named object. NRVO is an optimization, not mandatory.
    return local; 
}

void demonstrate_nrvo() {
    std::println("\n--- 3. Named Return Value Optimization (NRVO) ---");
    ResourceManager res = create_resource_named("NRVO_Target");
    res.info();
}

/**
 * @brief C++23 auto(x) and auto{x} for explicit decay-copies.
 */
void demonstrate_cpp23_auto_copy() {
    std::println("\n--- 4. C++23 auto(x) / auto{{x}} ---");
    
    std::string s = "Hello C++23";
    
    // auto(s) creates a temporary copy of s. 
    // Useful when you want to pass a copy to a function that takes a reference 
    // or when you need to ensure a copy is made before a move.
    auto work = [](auto&& arg) {
        std::println("  Working on: {}", arg);
    };

    work(auto(s)); // Explicit copy
    std::println("  Original s is still: {}", s);
}

int main() {
    std::println("C++23 Memory & Performance: Copy vs Move Semantics");
    
    demonstrate_move_vs_copy();
    demonstrate_rvo();
    demonstrate_nrvo();
    demonstrate_cpp23_auto_copy();

    return 0;
}

/*
Complexity Analysis:
- Copy Constructor: O(N) where N is the size of the resource (deep copy).
- Move Constructor: O(1) (shallow copy of pointers).
- std::move: O(0) - It is just a static_cast to an rvalue reference.

Production Notes:
1. Use 'noexcept' on move constructors and move assignment operators. 
   Containers like std::vector will only move elements during reallocation 
   if the move constructor is marked 'noexcept'.
2. The "Rule of Five": If you define one of (Destructor, Copy-Constructor, 
   Copy-Assignment, Move-Constructor, Move-Assignment), you should likely 
   define all five.
3. Don't 'std::move' on return values unless you know what you're doing. 
   It can inhibit RVO/NRVO.

Interview Pitfalls:
- Thinking std::move actually moves data. It doesn't; it just enables 
  the use of the move constructor.
- Using a moved-from object. After std::move(x), x is in a "valid but 
  unspecified" state. You can re-assign to it, but don't read its value.
- Forgetting to null out pointers in the source object during a move 
  constructor (to avoid double-free).
*/
