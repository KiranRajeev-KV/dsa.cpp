/*
Title: C++23 Atomics and Lock-Free Programming
Category: Concurrency
File: atomics.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
Deep dive into atomic operations, memory ordering, and lock-free programming.
Covers std::atomic, atomic flags, and C++20/23 atomic wait/notify features.

Compile:
g++ -std=c++23 atomics.cpp -o atomics

Run:
./atomics

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::atomic<T> (Integral and Pointer types)
- Read-Modify-Write operations (fetch_add, exchange)
- Compare and Swap (CAS): compare_exchange_weak / strong
- std::atomic_flag (Lock-free boolean flag)
- Memory Ordering (relaxed, acquire/release, seq_cst)
- C++20/23 atomic::wait and atomic::notify_one/all

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <atomic>
#include <thread>
#include <vector>
#include <print>
#include <chrono>

using namespace std::chrono_literals;

/**
 * PRODUCTION NOTE: Why Atomics?
 * Atomics provide a way to synchronize data without the overhead of mutexes
 * (locks). They are typically implemented using CPU-specific instructions 
 * like LOCK CMPXCHG.
 */

// 1. Basic Atomic Counter
std::atomic<int> shared_counter{0};

void increment_counter() {
    for (int i = 0; i < 1000; ++i) {
        // Atomic fetch_add
        shared_counter.fetch_add(1, std::memory_order_relaxed);
    }
}

// 2. Lock-free Flag using std::atomic_flag
std::atomic_flag spin_lock = ATOMIC_FLAG_INIT;

void critical_section(int id) {
    // Basic Spinlock implementation
    while (spin_lock.test_and_set(std::memory_order_acquire)) {
        // Spin...
    }
    
    std::println("Thread {} in critical section", id);
    std::this_thread::sleep_for(10ms);
    
    spin_lock.clear(std::memory_order_release);
}

// 3. Compare and Swap (CAS) - The heart of lock-free DS
void cas_demo() {
    std::atomic<int> value{10};
    int expected = 10;
    int desired = 20;

    // compare_exchange_strong: 
    // If value == expected, value = desired, return true.
    // If value != expected, expected = value, return false.
    bool success = value.compare_exchange_strong(expected, desired);
    
    std::println("CAS Success: {}, New Value: {}, Expected: {}", success, value.load(), expected);
}

// 4. C++20/23 Atomic Wait/Notify
// This allows a thread to wait for an atomic value change efficiently.
std::atomic<int> signal_flag{0};

void waiter() {
    std::println("Waiter: Waiting for signal...");
    // C++20/23: Efficiently blocks until value is no longer 0
    signal_flag.wait(0);
    std::println("Waiter: Signal received! Value is {}", signal_flag.load());
}

void notifier() {
    std::this_thread::sleep_for(200ms);
    std::println("Notifier: Sending signal...");
    signal_flag.store(1);
    signal_flag.notify_one();
}

int main() {
    std::println("=== C++23 Atomics Guide ===");

    // --- 1. Atomic Arithmetic ---
    {
        std::println("\n[1] Atomic Arithmetic Performance");
        std::vector<std::jthread> threads;
        for (int i = 0; i < 10; ++i) threads.emplace_back(increment_counter);
        
        threads.clear(); // Wait for all
        std::println("Final Atomic Counter: {}", shared_counter.load());
    }

    // --- 2. Spinlock using atomic_flag ---
    {
        std::println("\n[2] Spinlock with atomic_flag");
        std::jthread t1(critical_section, 1);
        std::jthread t2(critical_section, 2);
    }

    // --- 3. CAS Demo ---
    {
        std::println("\n[3] Compare and Swap (CAS)");
        cas_demo();
    }

    // --- 4. Atomic Wait/Notify ---
    {
        std::println("\n[4] Atomic Wait and Notify (C++20/23)");
        std::jthread t1(waiter);
        std::jthread t2(notifier);
    }

    /**
     * COMPLEXITY ANALYSIS:
     * - Atomic operations: O(1) CPU instruction.
     * - Contention: High contention on a single atomic variable leads to 
     *   "cache line bouncing" which degrades performance.
     *
     * INTERVIEW PITFALLS:
     * 1. ABA Problem: A value changes from A to B then back to A. A CAS might 
     *    succeed even though the state changed. Solved with versioning/tags.
     * 2. Weak vs Strong CAS: compare_exchange_weak can fail spuriously even if 
     *    values match. Use in a loop. Strong is safer for single checks.
     * 3. Memory Ordering: Default is memory_order_seq_cst (most restrictive). 
     *    Using relaxed incorrectly can lead to extremely subtle bugs.
     * 4. atomic_flag: Only provides test_and_set and clear. It's the only 
     *    type guaranteed to be lock-free on all platforms.
     * 
     * PRODUCTION NOTES:
     * - std::atomic<T>::is_lock_free() can be used to check if hardware supports 
     *   atomic operations for type T.
     * - Prefer std::atomic over mutexes for simple flags or counters.
     * - Lock-free data structures (queues, lists) are notoriously hard to implement; 
     *   use audited libraries when possible.
     */

    std::println("\n=== Atomics demonstration complete ===");
    return 0;
}
