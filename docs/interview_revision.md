# Interview Revision Handbook

## Top STL Interview Traps
1. **Iterator Invalidation**: Modifying a `std::vector` (like `push_back` or `erase`) can invalidate all iterators if reallocation occurs. See `containers/vector.cpp`.
2. **Erase-Remove Idiom**: Pre-C++20 required `v.erase(std::remove(v.begin(), v.end(), val), v.end())`. In C++20/23, prefer `std::erase(v, val)`.
3. **`std::map` vs `std::unordered_map`**: `std::map` is a Red-Black tree ($O(\log N)$). `std::unordered_map` is a hash table ($O(1)$ average, $O(N)$ worst-case). Don't use `map` just for $O(1)$ lookups.
4. **`operator[]` on Maps**: Using `map[key]` inserts a default-constructed value if the key doesn't exist. Use `map.contains(key)` (C++20) or `map.find(key)` instead for purely checking existence.
5. **String Concatenation**: Repeatedly doing `str += "a"` is $O(N)$, but `str = str + "a"` inside a loop can be $O(N^2)$ due to temporary allocations.

## Must-Know Interview Questions
- How is a `std::vector` implemented? What is its growth factor?
- Explain Move Semantics and `std::forward`. What problem does perfect forwarding solve?
- What is the difference between `std::shared_ptr` and `std::unique_ptr`? When would you use `std::weak_ptr`?
- How does `std::unordered_map` handle collisions?
- Implement a thread-safe Singleton (Meyers Singleton).

## Complexity Cheatsheet
| Data Structure / Algorithm | Search | Insert | Delete | Notes |
| :--- | :--- | :--- | :--- | :--- |
| `std::vector` | $O(N)$ | $O(1)$ amortized back | $O(1)$ back, $O(N)$ elsewhere | Best default container (cache-friendly). |
| `std::deque` | $O(N)$ | $O(1)$ front/back | $O(1)$ front/back | Not contiguous memory. |
| `std::list` | $O(N)$ | $O(1)$ (with iter) | $O(1)$ (with iter) | High cache miss rate. Avoid unless necessary. |
| `std::set` / `std::map` | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ | Ordered elements. |
| `std::unordered_map` | $O(1)$ avg | $O(1)$ avg | $O(1)$ avg | Worst case $O(N)$ on hash collisions. |
| `std::flat_map` (C++23) | $O(\log N)$ | $O(N)$ | $O(N)$ | Sorted vector-based. Better cache locality than `map`. |
| `std::priority_queue` | $O(1)$ top | $O(\log N)$ | $O(\log N)$ pop | Usually a max-heap. |

## C++23 Specific Interview Questions
- **Deducing `this`**: How does it replace the Curiously Recurring Template Pattern (CRTP)? (A: It allows the base class to access the derived class's members via an explicit object parameter without template inheritance overhead).
- **`std::expected`**: Why use it over exceptions? (A: For "expected" errors like parsing or timeouts, it's faster as it avoids stack unwinding and expresses the error state in the type system).
- **`std::println`**: How is it different from `std::cout`? (A: It uses the Python-like `{}` formatting, is type-safe, and generally faster as it doesn't involve heavy locale-dependent stream logic).
- **`std::move_only_function`**: What was wrong with `std::function`? (A: `std::function` required the wrapped lambda to be copyable, making it impossible to wrap lambdas capturing `std::unique_ptr`).
| `std::sort` | - | - | - | $O(N \log N)$ IntroSort (Quick + Heap + Insertion). |
| `std::stable_sort` | - | - | - | $O(N \log^2 N)$ or $O(N \log N)$ with extra memory. |

## Common Whiteboard Patterns
- **Sliding Window**: See `dsa_patterns/sliding_window.cpp`
- **Two Pointers**: See `dsa_patterns/two_pointers.cpp`
- **Monotonic Stack**: See `dsa_patterns/monotonic_stack.cpp`
- **Binary Search on Answer**: See `dsa_patterns/binary_search_pattern.cpp`
