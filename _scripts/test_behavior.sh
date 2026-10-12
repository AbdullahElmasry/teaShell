#!/usr/bin/env bash

set -u

PASS=0
FAIL=0

run_test() {
    local name="$1"
    local input="$2"
    local expected="$3"
    local output

    if output=$(printf '%s' "$input" | ./teashell 2>&1); then
        :
    else
        echo "FAIL: $name (shell exited unexpectedly)"
        FAIL=$((FAIL + 1))
        return
    fi

    if [[ "$output" == *"$expected"* ]]; then
        echo "PASS: $name"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $name"
        echo "  Expected output to contain: $expected"
        echo "  Actual output:"
        printf '    %s\n' "$output"
        FAIL=$((FAIL + 1))
    fi
}

run_test \
    "echo prints arguments" \
    $'echo hello world\nexit\n' \
    "hello world"

run_test \
    "multiple commands execute in order" \
    $'echo FIRST_MARKER\necho SECOND_MARKER\nexit\n' \
    "FIRST_MARKER"

echo
echo "Results: $PASS passed, $FAIL failed"

if (( FAIL > 0 )); then
    exit 1
fi
