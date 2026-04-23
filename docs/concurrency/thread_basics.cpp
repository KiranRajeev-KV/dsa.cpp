/*
Title: C++23 Threading Basics & jthread Guide
Category: Concurrency
File: thread_basics.cpp
C++ Standard: C++23
Difficulty: Beginner to Advanced

Purpose:
Comprehensive guide to basic threading in C++23. This file covers the transition from
legacy std::thread to modern std::jthread, passing arguments, hardware concurrency,
and cooperative interruption using stop_tokens.

Compile:
g++ -std=c++23 thread_basics.cpp -o thread_basics

Run:
./thread_basics

Key Topics:
- std::jthread (Joinable Thread) vs std::thread
- Argument passing and reference lifetimes
- Member function and lambda threading
- Cooperative interruption (std::stop_token)
- Thread identity and identification
- Hardware concurrency and oversubscription

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <thread>
#include <chrono>
#include <string>
#include <print>
#include <functional>
#include <stop_token>

using namespace std::chrono_literals;

/**
 * PRODUCTION NOTE:
 * Prefer std::jthread over std::thread.
 * std::jthread implements RAII: it automatically joins in its destructor.
 * std::thread will call std::terminate if destroyed while still joinable.
 */

// 1. Basic Function for Threading
void worker_function(const std::string& name, int count) {
    for (int i = 0; i < count; ++i) {
        std::println("Worker {}: iteration {}", name, i);
        std::this_thread::sleep_for(10ms);
    }
}

// 2. Class for Member Function Threading
class BackgroundTask {
public:
    void do_work(int id) {
        std::println("Member function worker {} started", id);
        std::this_thread::sleep_for(50ms);
    }
};

/**
 * INTERVIEW PITFALL: Reference Lifetimes
 * When passing arguments by reference to a thread, ensure the object
 * outlives the thread. std::ref() must be used explicitly.
 */
void increment_shared(int& val) {
    for (int i = 0; i < 1000; ++i) {
        val++;
    }
}

/**
 * ADVANCED: Cooperative Interruption
 * jthread supports stop_tokens, allowing a thread to check if it has been
 * requested to stop without using explicit flags or condition variables.
 */
void interruptible_worker(std::stop_token st, int id) {
    std::println("Interruptible worker {} started", id);
    while (!st.stop_requested()) {
        std::println("Worker {} is still working...", id);
        std::this_thread::sleep_for(20ms);
    }
    std::println("Worker {} received stop signal, cleaning up.", id);
}

int main() {
    std::println("=== C++23 Threading Basics ===");

    // --- 1. Basic jthread usage ---
    {
        std::println("\n[1] Basic jthread (RAII)");
        // No need to call .join() manually at the end of the scope.
        std::jthread t1(worker_function, "A", 3);
        std::jthread t2(worker_function, "B", 3);
        
        // Threads will be joined here as they go out of scope.
    }

    // --- 2. Lambda and Member Functions ---
    {
        std::println("\n[2] Lambda and Member Functions");
        
        // Lambda
        std::jthread t1([](int val) {
            std::println("Lambda thread: {}", val);
        }, 42);

        // Member Function
        BackgroundTask task;
        std::jthread t2(&BackgroundTask::do_work, &task, 101);
    }

    // --- 3. Passing by Reference ---
    {
        std::println("\n[3] Passing by Reference");
        int counter = 0;
        {
            // std::ref is mandatory to pass as reference
            std::jthread t(increment_shared, std::ref(counter));
        } // Thread joins here
        std::println("Counter value after thread: {}", counter);
    }

    // --- 4. Hardware Information ---
    {
        std::println("\n[4] System Metadata");
        unsigned int n = std::thread::hardware_concurrency();
        std::println("Hardware threads available: {}", n);
        std::println("Main thread ID: {}", std::this_thread::get_id());
    }

    // --- 5. Cooperative Interruption ---
    {
        std::println("\n[5] Cooperative Interruption with stop_token");
        std::jthread t(interruptible_worker, 7);
        
        std::this_thread::sleep_for(100ms);
        
        std::println("Main: requesting worker to stop");
        t.request_stop(); // Explicitly stop
        // Alternatively, the destructor of jthread would also request stop if not joined.
    }

    /**
     * COMPLEXITY ANALYSIS:
     * - Thread Creation: System-dependent, typically O(1) in terms of program logic,
     *   but high overhead due to kernel involvement.
     * - Context Switching: Cost is O(1) per switch but expensive in CPU cycles.
     *
     * INTERVIEW PITFALLS:
     * 1. Dangling References: Passing local variables to std::thread without joining.
     * 2. Exception Safety: If an exception is thrown before join(), std::thread terminates. 
     *    Use std::jthread or RAII wrappers.
     * 3. Oversubscription: Creating more threads than cores can lead to thrashing.
     */

    std::println("\n=== All threads finished execution ===");
    return 0;
}
