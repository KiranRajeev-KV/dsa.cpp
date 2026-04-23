# C++23 Complete Reference & Interview Handbook

Welcome to the ultimate C++23 reference repository. This project is a production-grade, fully executable knowledge base designed for mastering C++ from beginner concepts to senior backend engineering and competitive programming.

## Project Purpose
1. **Full Modern C++23 Reference**: Deep dives into the STL, language features, and modern paradigms.
2. **Interview Preparation**: Traps, patterns, and complexity analysis for technical interviews.
3. **Data Structures and Algorithms (DSA)**: Executable implementations of core algorithms.
4. **Competitive Programming Reference**: Templates, fast I/O, and advanced tree structures.
5. **Production Backend Engineering**: Best practices, memory performance, and concurrency.

## Folder Guide
- `containers/`: In-depth guides for every STL container (e.g., `vector`, `map`, `mdspan`).
- `algorithms/`: Standard algorithms, ranges, and custom implementations.
- `iterators/`: Categories, adapters, and custom iterator design.
- `functions/`: Callables, lambdas, `std::function`, and `std::move_only_function`.
- `language_features/`: Core C++23 additions, templates, concepts, and coroutines.
- `dsa_patterns/`: Common algorithmic patterns (Sliding Window, Prefix Sum, Monotonic Stack).
- `competitive_programming/`: Number theory, graph templates, segment trees, and Fast I/O.
- `concurrency/`: Multithreading, atomics, and condition variables.
- `memory_performance/`: Allocators, cache-friendliness, and move semantics.

## Learning Strategy
Every file in this repository is **independently executable**.
1. Read the frontmatter at the top of a file to understand the scope and compilation instructions.
2. Read the code and comments sequentially; they are designed to teach from beginner to advanced.
3. Compile and run the file to see the output.
4. Experiment by modifying the code.

## Compile Instructions
To compile any file in this repository, use a C++23 compatible compiler (GCC 13+ or Clang 16+ recommended):

```bash
g++ -std=c++23 path/to/file.cpp -o executable_name
./executable_name
```

## Best Study Order
Please refer to `learning_path.md` for structured roadmaps tailored to your goals.

- **Beginners**: Start with `learning_path.md` (Beginner Roadmap).
- **Interview Candidates**: Review `interview_revision.md` and `dsa_patterns/`.
- **Competitive Programmers**: Dive straight into `competitive_programming/` and `algorithms/`.
- **Senior Engineers**: Focus on `memory_performance/`, `concurrency/`, and `cpp23_features.md`.
