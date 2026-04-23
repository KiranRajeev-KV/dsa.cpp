#!/bin/bash
# Global Build Script for C++23 Reference Repository
# Compiles all .cpp files in the repository to ensure they are valid.
# Usage: ./build.sh [-c]  # -c to clean output files after compilation

set -e

CLEAN=false
while getopts "c" opt; do
    case $opt in
        c) CLEAN=true ;;
        *) echo "Usage: $0 [-c]" >&2; exit 1 ;;
    esac
done

CXX=${CXX:-g++}
CXXFLAGS="-std=c++23 -Wall -Wextra -Wpedantic"
MAX_JOBS=${MAX_JOBS:-8}

echo "Using compiler: $CXX"
echo "Flags: $CXXFLAGS"
echo "Max parallel jobs: $MAX_JOBS"

find . -name "*.cpp" | xargs -P $MAX_JOBS -I {} sh -c '
file="$1"
dir=$(dirname "$file")
base=$(basename "$file" .cpp)
out="$dir/$base.out"

echo "Compiling $file..."
'"$CXX"' '"$CXXFLAGS"' "$file" -o "$out"
' _ {}

echo "All files compiled successfully!"

if $CLEAN; then
    echo "Cleaning up output files..."
    find . -name "*.out" -delete
fi
