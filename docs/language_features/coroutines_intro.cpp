/*
Title: Coroutines Introduction Guide
Category: Language Features
File: coroutines_intro.cpp
C++ Standard: C++23
Difficulty: Advanced

Purpose:
A foundational look at C++20/23 Coroutines. Explains the "Magic Triangle" of Coroutines: the Promise object, the Coroutine Handle, and the Awaitable.

Compile:
g++ -std=c++23 coroutines_intro.cpp -o coroutines_intro

Run:
./coroutines_intro

Key Topics:
- `co_await`, `co_yield`, `co_return`
- The `promise_type` structure
- Coroutine state and handles
- Custom awaitables (suspend_always, suspend_never)

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>
#include <coroutine>
#include <exception>

// --- A Simple Coroutine Task Type ---
// This is the "return type" of the coroutine.
struct SimpleTask {
    struct promise_type {
        SimpleTask get_return_object() {
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}
    };

    std::coroutine_handle<promise_type> handle;

    SimpleTask(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~SimpleTask() { if (handle) handle.destroy(); }

    void resume() {
        if (handle && !handle.done()) {
            handle.resume();
        }
    }
};

// --- Coroutine Definition ---
SimpleTask my_first_coroutine() {
    std::println("  [Coroutine] Started");
    co_await std::suspend_always{}; // Suspend point
    std::println("  [Coroutine] Resumed after first suspend");
    co_await std::suspend_always{}; // Suspend point
    std::println("  [Coroutine] Finished");
}

int main() {
    std::println("--- C++ Coroutines Intro ---\n");

    std::println("Main: Calling coroutine...");
    SimpleTask task = my_first_coroutine();

    std::println("Main: Coroutine created and suspended at start.");
    
    std::println("Main: Resuming 1...");
    task.resume();

    std::println("Main: Resuming 2...");
    task.resume();

    std::println("Main: Resuming 3 (Final)...");
    task.resume();

    std::println("Main: Coroutine complete.");

    return 0;
}

/*
Complexity & Performance Notes:
- Coroutines usually involve a heap allocation for the "coroutine frame" (state). However, compilers (like Clang/GCC) can often perform HALO (Heap Allocation Elision Optimization) if the coroutine lifetime is strictly nested.
- Suspending and resuming a coroutine is extremely fast, roughly equivalent to two function calls/context switches, far cheaper than thread context switching.

Interview Pitfalls:
- Coroutines are NOT threads. They are cooperative multitasking primitives. They run on the same thread that resumes them unless you explicitly dispatch them to a thread pool.
- Forgetting to `destroy()` the coroutine handle in the task's destructor leads to a memory leak of the coroutine frame.
- `co_await`, `co_yield`, and `co_return` cannot be used in `main()`.
*/
