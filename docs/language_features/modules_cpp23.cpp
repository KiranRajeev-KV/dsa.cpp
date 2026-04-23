/*
Title: C++23 Modules Guide
Category: Language Features
File: modules_cpp23.cpp
C++ Standard: C++23
Difficulty: Intermediate

Purpose:
Introduction to C++ Modules (`import`, `export module`). Modules provide faster compile times and better encapsulation than headers. Highlights C++23 `import std;`.

Compile:
g++ -std=c++23 -fmodules-ts modules_cpp23.cpp -o modules_cpp23
Note: Module support varies by compiler. C++23 `import std;` requires standard library modules to be pre-built.

Run:
./modules_cpp23

Note: C++23 std::print support for containers requires GCC 14+ or Clang 17+.

Key Topics:
- `export module`
- `import` vs `#include`
- C++23 `import std;` and `import std.compat;`
- Global module fragment

Authoring Rule:
This file must be independently runnable and production-grade.
*/

// --- 1. Global Module Fragment ---
// Used for legacy includes that don't support modules yet (commented out for standard compilation).
// module; 
// 
// --- 2. Module Declaration ---
// In a real project, this would be in a separate .ixx or .cppm file.
// export module MathLib;
// export int add(int a, int b) { return a + b; }

// --- 3. Main using Modules ---
// C++23 introduces 'import std;' which imports the entire standard library as a module.
// This is drastically faster than  + others.

#if defined(__cpp_lib_modules) && (__cpp_lib_modules >= 202207L)
import std;
#else
// Fallback for compilers without full 'import std;' support yet.
#include <print>
#include <vector>
#include <string>
#endif

int main() {
    std::println("--- C++23 Modules ---\n");

    // Standard library components are available via import std;
    std::vector<std::string> messages = {"Hello", "from", "C++23", "Modules"};
    
    for (const auto& msg : messages) {
        std::println("{} ", msg);
    }
    std::println("");

    std::println("\nNote: Modules replace the legacy header system.");
    std::println("- Faster compile times (O(1) instead of O(N) header processing).");
    // std::println("- No macro leakage (macros defined in a module don't leak out).");

    return 0;
}

/*
Complexity & Performance Notes:
- Modules are compiled into a Binary Module Interface (BMI). Importing a BMI is almost instantaneous compared to parsing a header file multiple times.
- Build times for large projects can improve by 5x-10x.

Interview Pitfalls:
- Macros are NOT exported by modules. If you need a macro from a legacy header, you must still `#include` it or use the Global Module Fragment.
- `import std;` vs `import std.compat;`: `std.compat` provides the same as `std` but also puts the C standard library functions (like `printf`) in the global namespace.
- You cannot mix `#include` and `import` for the same file easily without risk of ODR (One Definition Rule) violations in some compilers.
*/
