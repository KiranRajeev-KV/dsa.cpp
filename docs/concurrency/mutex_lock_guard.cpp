/*
Title: C++23 Mutex, Lock Guard, and Deadlock Prevention
Category: Concurrency
File: mutex_lock_guard.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Demonstrates thread synchronization using mutexes and modern RAII lock wrappers.
Covers std::mutex, std::recursive_mutex, std::lock_guard, std::unique_lock,
and the deadlock-preventing std::scoped_lock.

Compile:
g++ -std=c++23 mutex_lock_guard.cpp -o mutex_lock_guard

Run:
./mutex_lock_guard

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- std::mutex and std::lock_guard (Basic RAII)
- std::unique_lock (Flexibility: defer, try, timed)
- std::scoped_lock (C++17/20/23 solution for multiple locks)
- std::recursive_mutex (Re-entrant locking)
- Deadlock scenarios and prevention
- Thread-safe class design

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <thread>
#include <mutex>
#include <vector>
#include <print>
#include <chrono>

using namespace std::chrono_literals;

// 1. Thread-safe Counter using std::lock_guard
class SafeCounter {
    mutable std::mutex mtx; // 'mutable' allows locking in const member functions
    int value = 0;

public:
    void increment() {
        // RAII: Lock is acquired here and released when scope ends
        std::lock_guard<std::mutex> lock(mtx);
        value++;
    }

    int get() const {
        std::lock_guard<std::mutex> lock(mtx);
        return value;
    }
};

// 2. Demonstration of std::unique_lock flexibility
void unique_lock_demo() {
    std::mutex mtx;
    
    // Defer lock
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    
    // Do some work without lock...
    
    if (lock.try_lock()) {
        std::println("Acquired lock using try_lock");
        // ... work ...
        lock.unlock(); // Can manually unlock
    }
}

// 3. Deadlock Prevention with std::scoped_lock
struct Account {
    int balance;
    std::mutex mtx;
    explicit Account(int b) : balance(b) {}
};

void transfer(Account& from, Account& to, int amount) {
    // DON'T DO THIS (Risk of Deadlock):
    // std::lock_guard<std::mutex> lock1(from.mtx);
    // std::lock_guard<std::mutex> lock2(to.mtx);

    // DO THIS (C++17/20/23 pattern):
    // std::scoped_lock locks multiple mutexes using a deadlock avoidance algorithm.
    std::scoped_lock lock(from.mtx, to.mtx);
    
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        std::println("Transferred {} from Account A to B", amount);
    }
}

// 4. Recursive Mutex Example
class RecursiveWorker {
    std::recursive_mutex r_mtx;
public:
    void step1() {
        std::lock_guard<std::recursive_mutex> lock(r_mtx);
        std::println("In Step 1");
        step2(); // Re-entrant call: would deadlock with std::mutex
    }
    
    void step2() {
        std::lock_guard<std::recursive_mutex> lock(r_mtx);
        std::println("In Step 2");
    }
};

int main() {
    std::println("=== C++23 Mutex & Locking Mechanisms ===");

    // --- 1. Basic Synchronization ---
    {
        std::println("\n[1] Basic Mutex with std::lock_guard");
        SafeCounter sc;
        std::vector<std::jthread> threads;
        
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&sc]() {
                for (int j = 0; j < 1000; ++j) sc.increment();
            });
        }
        
        // jthreads join automatically
        threads.clear();
        std::println("Final Counter: {}", sc.get());
    }

    // --- 2. Multiple Mutexes & Deadlock Avoidance ---
    {
        std::println("\n[2] std::scoped_lock for Multiple Mutexes");
        Account accA(100), accB(100);
        
        std::jthread t1(transfer, std::ref(accA), std::ref(accB), 50);
        std::jthread t2(transfer, std::ref(accB), std::ref(accA), 20);
        
    // logic handled by jthread destructors
    }

    // --- 3. Recursive Locking ---
    {
        std::println("\n[3] std::recursive_mutex demo");
        RecursiveWorker worker;
        worker.step1();
    }

    /**
     * COMPLEXITY ANALYSIS:
     * - Mutex Lock/Unlock: O(1) in terms of code, but involves kernel transitions.
     * - Performance: Contention (multiple threads hitting the same lock) 
     *   dramatically slows down execution.
     *
     * INTERVIEW PITFALLS:
     * 1. Forgetting to Lock: Race conditions.
     * 2. Manual Lock/Unlock: Risk of not unlocking on exception/return. Use RAII.
     * 3. Deadlocks: T1 locks A then B, T2 locks B then A. Solution: std::scoped_lock.
     * 4. Over-locking: Locking a mutex for too long (e.g., during I/O) hurts concurrency.
     * 
     * PRODUCTION NOTES:
     * - Use 'mutable' for mutexes in classes to allow locking in const getters.
     * - Prefer std::scoped_lock even for single mutexes as it's cleaner and variadic.
     * - Avoid recursive_mutex unless necessary; it often indicates poor design.
     */

    std::println("\n=== Mutex demonstration complete ===");
    return 0;
}
