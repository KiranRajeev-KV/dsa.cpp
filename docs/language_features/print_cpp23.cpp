/*
Title: C++23 std::print Complete Guide
Category: Language Features
File: print_cpp23.cpp
C++ Standard: C++23
Difficulty: Beginner

Purpose:
A guide to the C++23 `<print>` library (`std::print`, `std::println`). These provide a type-safe, fast, and modern alternative to `printf` and `std::cout`.

Compile:
g++ -std=c++23 print_cpp23.cpp -o print_cpp23

Run:
./print_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `std::print` and `std::println`
- Formatting basics (Python-like syntax)
- Printing to files and `stdout`
- Unicode support
- Comparison with `printf` and `iostream`

Authoring Rule:
This file must be independently runnable and production-grade.
*/

#include <string>
#include <vector>

// Note: std::print is in <print> header. 
// If not yet available, we fallback to std::format + std::cout.
#if __has_include(<print>)
#include <print>
#else
#include <format>
namespace std {
    template<typename... Args>
    void print(std::string_view fmt, Args&&... args) {
        std::println("{}", std::vformat(fmt, std::make_format_args(args...)));
    }
    template<typename... Args>
    void println(std::string_view fmt, Args&&... args) {
        std::print(fmt, std::forward<Args>(args)...);
        std::println("");
    }
}
#endif

int main() {
    // 1. Basic Printing
    std::println("Hello, C++23!");

    // 2. Formatting (Python-style { })
    std::string name = "Gemini";
    int year = 2023;
    std::println("System: {}, Version: {}.0", name, year);

    // 3. Positional Arguments
    std::println("Positional: {1} comes after {0}", "A", "B");

    // 4. Alignment and Precision
    std::println("Pi to 2 decimals: {:.2f}", 3.14159);
    std::println("Right aligned: {:>10}", "Hi");
    std::println("Padded: {:_<10}", "Start");

    // 5. Printing Containers (with Ranges)
    std::vector<int> nums = {1, 2, 3, 4, 5};
    // Note: C++23 print supports ranges directly!
    std::println("Numbers: {}", nums);

    // 6. Unicode support
    // std::print guarantees correct output to terminal regardless of locale/encoding.
    std::println("Unicode test: 🚀 🦀 ❄️");

    return 0;
}

/*
Complexity & Performance Notes:
- `std::print` is significantly faster than `std::cout` (no synchronization overhead with `printf` required) and safer than `printf` (compile-time type checking).
- It produces smaller binary code than `iostream` because it doesn't involve heavy template-based stream buffers for basic output.

Interview Pitfalls:
- **Synchronization**: `std::print` bypasses `std::cout`'s stream buffer. Mixing `std::print` and `std::cout` in the same program can lead to interleaved/garbled output. Stick to one.
- `std::print` does NOT automatically add a newline. Use `std::println` for that.
- Unlike `std::cout`, `std::print` does not flush the buffer automatically unless a newline is present (and even then, it depends on the implementation). Use `std::fflush(stdout)` if immediate visibility is critical.
- Formatting strings must generally be constant strings (literal strings) for the compiler to perform type checking. If you need dynamic formatting, use `std::vformat`.
*/
