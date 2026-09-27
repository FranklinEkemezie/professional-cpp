#!/usr/bin/env bash

set -u

PROJECT="$1"
PROJECT_DIR="$PROJECT"
TEST_DIR="$PROJECT_DIR/bin/tests/unit"

if [ ! -d "$PROJECT_DIR" ]; then
    echo "Error: project '$PROJECT' does not exist."
    exit 1
fi
 
if [ ! -d "$TEST_DIR" ]; then
    echo "No test binaries found."
    exit 1
fi

tests=$(find "$TEST_DIR" -type f -perm -111 | sort)

if [ -z "$tests" ]; then
    echo "No test binaries found."
    exit 1
fi

echo "========================================"
echo " Running tests"
echo "========================================"

for test in $tests; do
    name="$(basename "$test")"

    echo
    echo ">>> $name"

    if "$test"; then
        echo "    ✓ $name passed"
    else
        echo "    ✗ $name failed"
        echo
        echo "Test suite failed."
        exit 1
    fi
done

echo
echo "All tests passed."