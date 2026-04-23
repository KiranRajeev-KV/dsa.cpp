/*
Title: std::stacktrace Complete Guide
Category: Language Features
File: stacktrace_cpp23.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
Demonstrates the C++23 `std::stacktrace` library, which allows programs to capture and inspect the current call stack at runtime without external libraries.

Compile:
g++ -std=c++23 stacktrace_cpp23.cpp -lstdc++exp -o stacktrace_cpp23
(Note: Linking with -lstdc++exp is required for GCC implementations of <stacktrace>)

Run:
./stacktrace_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `std::stacktrace::current()`
- Iterating over stacktrace entries
- Source file and line number information
- Custom logging with stacktraces

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <print>

// std::stacktrace is a C++23 feature
#if __has_include(<stacktrace>)
#include <stacktrace>
#define HAS_STACKTRACE 1
#else
#define HAS_STACKTRACE 0
#endif

void function_c() {
    std::println("--- Capturing Stacktrace in function_c ---");

#if HAS_STACKTRACE
    // Captures the entire call stack at this point
    auto trace = std::stacktrace::current();
    
    // std::stacktrace has a built-in operator<< and formatter
    if (trace.empty()) {
        std::println("Stacktrace is empty (possibly missing debug symbols or compiler support).");
    } else {
        std::println("Captured {} entries:", trace.size());
        std::println("{}", trace);
        
        std::println("\n--- Detailed Entry Inspection ---");
        for (const auto& entry : trace) {
            std::println("Function: {:<30} | Line: {:<4} | File: {}", 
                         entry.description(), 
                         entry.source_line(), 
                         entry.source_file());
        }
    }
#else
    std::println("Error: <stacktrace> header not found. This compiler does not support std::stacktrace.");
#endif
}

void function_b() { function_c(); }
void function_a() { function_b(); }

int main() {
    std::println("--- C++23 std::stacktrace ---\n");

    function_a();

    return 0;
}

/*
Complexity & Performance Notes:
- Capturing a stacktrace is a relatively "heavy" operation. It involves querying the OS/debugging information. Use it for error logging and debugging, not in tight performance loops.
- `std::stacktrace` entries are lazily evaluated in some implementations to reduce cost if you only need the addresses.

Interview Pitfalls:
- Stacktrace information (like function names and line numbers) depends on debug symbols being present in the executable (use -g). Stripped binaries may only show memory addresses.
- It is NOT available in `constexpr` contexts.
- Linker Requirements: As of GCC 13/14, you MUST link with -lstdc++exp because the feature is part of the "experimental" C++23 library extensions.
*/
