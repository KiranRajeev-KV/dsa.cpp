# C++23 Features Guide

C++23 is focused on refining C++20, extending the standard library, and improving the developer experience. This document highlights the major additions.

## 1. `std::print` and `std::println`
**What:** Fast, type-safe, Python-like formatting directly to standard output.
**Why:** Replaces `std::cout` and `printf`. It uses `std::format` under the hood.
**Caveats:** Requires compiler support (GCC 14+, Clang 18+ for full support). Fallback to `std::cout` or `fmt::print` if unavailable.

## 2. `std::expected`
**What:** A vocabulary type representing either an expected value or an error.
**Why:** Replaces out-parameters, exceptions for control flow, and returning `std::pair<Result, bool>`.
**Usage:** `std::expected<int, std::string> parse_int(std::string_view s);`

## 3. `std::mdspan`
**What:** A non-owning multidimensional view over a contiguous sequence of elements.
**Why:** Essential for scientific computing and matrix operations without building custom matrix classes.

## 4. Deducing `this`
**What:** Explicit object parameter. Allows member functions to deduce the value category of the object they are called on.
**Why:** Eliminates the need to write separate `const`, non-`const`, lvalue, and rvalue overloads for member functions (e.g., CRTP simplification).

## 5. Standard Library Modules (`std` and `std.compat`)
**What:** `import std;`
**Why:** Dramatically reduces compile times compared to `#include <iostream>`, `#include <vector>`, etc.
**Caveats:** Build system support (CMake, Make) is still evolving.

## 6. `std::generator`
**What:** A synchronous coroutine generator yielding a sequence of values.
**Why:** Makes writing custom ranges and iterators trivial.

## 7. Ranges Improvements
- `ranges::to`: Convert ranges back to containers (e.g., `auto vec = views::iota(1, 10) | ranges::to<std::vector>();`).
- New views: `views::zip`, `views::chunk`, `views::slide`, `views::stride`, `views::enumerate`.

## 8. `std::move_only_function`
**What:** A version of `std::function` that can hold move-only closures (e.g., lambdas capturing `std::unique_ptr`).

## 9. `if consteval`
**What:** Evaluates a block of code only if executing in a constant-evaluation context.
**Why:** Fixes quirks with `std::is_constant_evaluated()`.

## 10. Multidimensional `operator[]`
**What:** `obj[x, y, z]` is now valid syntax.
**Why:** Makes mathematical and grid-based APIs cleaner.

## 11. `std::stacktrace`
**What:** A standard way to get a stacktrace for debugging and logging.
