/*
Title: Allocator Basics and Custom Allocators Complete Guide
Category: Memory & Performance
File: allocator_basics.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
To understand the abstraction layer between memory allocation and object construction in C++.
This file covers std::allocator, allocator_traits, and the implementation of a custom
logging allocator to demystify how STL containers manage memory.

Compile:
g++ -std=c++23 allocator_basics.cpp -o allocator_basics

Run:
./allocator_basics

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- The separation of allocation and construction
- std::allocator interface (C++20/23 updates)
- std::allocator_traits as the universal interface
- Implementing a Custom Logging Allocator
- Performance implications of allocation strategies

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <memory>
#include <vector>
#include <string>
#include <print>

/**
 * @brief A Custom Allocator that logs every allocation and deallocation.
 * 
 * In C++23, allocators are much simpler than in legacy C++ (pre-C++11).
 * Most of the boilerplate is handled by std::allocator_traits.
 */
template <typename T>
struct LoggingAllocator {
    using value_type = T;

    LoggingAllocator() noexcept = default;
    
    template <typename U>
    LoggingAllocator(const LoggingAllocator<U>&) noexcept {}

    /**
     * @brief Allocate raw memory for n objects of type T.
     * Note: This does NOT call constructors.
     */
    [[nodiscard]] T* allocate(std::size_t n) {
        if (n == 0) return nullptr;
        if (n > std::size_t(-1) / sizeof(T)) throw std::bad_array_new_length();
        
        void* pv = std::malloc(n * sizeof(T));
        if (!pv) throw std::bad_alloc();
        
        std::println("  [Allocating] {} items of size {} at {:p}", n, sizeof(T), pv);
        return static_cast<T*>(pv);
    }

    /**
     * @brief Deallocate memory.
     * Note: This does NOT call destructors.
     */
    void deallocate(T* p, std::size_t n) noexcept {
        std::println("  [Deallocating] {} items at {:p}", n, (void*)p);
        std::free(p);
    }

    // Comparison operators are required for allocators
    bool operator==(const LoggingAllocator&) const = default;
};

/**
 * @brief Demonstrates the manual use of std::allocator.
 * This shows the raw steps containers take under the hood.
 */
void demonstrate_raw_allocator() {
    std::println("\n--- 1. Manual std::allocator Usage ---");
    
    std::allocator<std::string> alloc;
    
    // Step 1: Allocate memory (no objects created yet)
    std::string* p = alloc.allocate(3);
    std::println("Memory allocated for 3 strings.");

    // Step 2: Construct objects in the allocated space (C++20/23 style)
    // std::allocator::construct is deprecated in C++17, removed in C++20.
    // Use std::allocator_traits instead.
    using traits = std::allocator_traits<std::allocator<std::string>>;
    
    traits::construct(alloc, p, "Hello");
    traits::construct(alloc, p + 1, "C++23");
    traits::construct(alloc, p + 2, "Allocators");

    std::println("Objects constructed: {}, {}, {}", p[0], p[1], p[2]);

    // Step 3: Destroy objects
    traits::destroy(alloc, p);
    traits::destroy(alloc, p + 1);
    traits::destroy(alloc, p + 2);
    std::println("Objects destroyed.");

    // Step 4: Deallocate memory
    alloc.deallocate(p, 3);
    std::println("Memory deallocated.");
}

/**
 * @brief Demonstrates using a custom allocator with a standard container.
 */
void demonstrate_custom_allocator() {
    std::println("\n--- 2. Custom Logging Allocator with std::vector ---");
    
    {
        // Vector will use our LoggingAllocator for all its memory needs
        std::vector<int, LoggingAllocator<int>> vec;
        
        std::println("Pushing elements...");
        vec.push_back(10); // Causes first allocation
        vec.push_back(20); // Might cause reallocation
        vec.push_back(30); // Might cause reallocation
        
        std::println("Vector contents: ");
        for (int i : vec) std::print("{} ", i);
        std::println("");
    } 
    // vec goes out of scope here, triggering deallocation
    std::println("Vector went out of scope.");
}

/**
 * @brief Deep Dive into std::allocator_traits
 */
void demonstrate_allocator_traits() {
    std::println("\n--- 3. Why std::allocator_traits Matters ---");
    
    using Alloc = LoggingAllocator<double>;
    using Traits = std::allocator_traits<Alloc>;

    std::println("Traits tell us about the allocator:");
    std::println("  - Max size: {}", Traits::max_size(Alloc{}));
    std::println("  - Propagate on copy: {}", Traits::propagate_on_container_copy_assignment::value);
    std::println("  - Propagate on move: {}", Traits::propagate_on_container_move_assignment::value);
    std::println("  - Propagate on swap: {}", Traits::propagate_on_container_swap::value);
}

int main() {
    std::println("C++23 Memory & Performance: Allocator Basics");
    
    demonstrate_raw_allocator();
    demonstrate_custom_allocator();
    demonstrate_allocator_traits();

    return 0;
}

/*
Complexity Analysis:
- Allocation (std::malloc): Usually O(1) or O(log N) depending on the heap manager.
- Construction: O(1) per object (calls the constructor).
- Deallocation (std::free): Usually O(1).
- Destruction: O(1) per object (calls the destructor).

Production Notes:
1. Prefer std::pmr::polymorphic_allocator (C++17+) for complex custom allocation 
   strategies as it avoids template bloat and allows runtime allocator switching.
2. Custom allocators are vital in embedded systems (fixed-size pools) or 
   high-frequency trading (latency-sensitive allocation).
3. In C++20/23, many member types of allocators (like pointer, reference) 
   are optional as allocator_traits provides defaults.

Interview Pitfalls:
- Mixing up 'allocate' (memory) with 'construct' (object).
- Forgetting to deallocate exactly what was allocated (same pointer, same size).
- Forgetting that an allocator must be "rebindable" to other types (though
  since C++11, allocator_traits handles the 'rebind' struct automatically).
- Neglecting the comparison operators (operator==). Containers may need to 
  check if one allocator can deallocate memory from another.
*/
