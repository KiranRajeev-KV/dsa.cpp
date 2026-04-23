# Compile Commands Reference

This document provides specific compile commands for various scenarios.

## Standard Compilation
For standard execution and learning:
```bash
g++ -std=c++23 file.cpp -o file
```

## Strict Validation (Production / CI)
To ensure code meets production standards:
```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wshadow file.cpp -o file
```

## Optimization for Performance Testing
When testing `memory_performance/` or benchmarking:
```bash
g++ -std=c++23 -O3 -march=native -DNDEBUG file.cpp -o file
```

## Debugging and Sanitizers
To catch memory leaks and undefined behavior:
```bash
g++ -std=c++23 -g -O0 -fsanitize=address,undefined file.cpp -o file
```

## Competitive Programming
Common flags used in CP environments:
```bash
g++ -std=c++23 -O2 -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -D_GLIBCXX_DEBUG file.cpp -o file
```

## Clang Alternative
If using LLVM/Clang:
```bash
clang++ -std=c++23 -stdlib=libc++ file.cpp -o file
```
*(Note: Some C++23 features like `std::print` or `std::mdspan` may have different support status between libstdc++ and libc++).*
