#!/usr/bin/env bash

set -u

PASS=0
FAIL=0
OUTPUT=""

# Run teaShell with a timeout and capture its output.
run_shell() {
    local input="$1"

    OUTPUT=$(printf '%s' "$input" | timeout 5s ./teashell 2>&1)
}

# Check whether the output contains the expected text.
run_test() {
    local name="$1"
    local input="$2"
    local expected="$3"

    if run_shell "$input"; then
        :
    else
        echo "FAIL: $name (shell exited unexpectedly or timed out)"
        FAIL=$((FAIL + 1))
        return
    fi

    if [[ "$OUTPUT" == *"$expected"* ]]; then
        echo "PASS: $name"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $name"
        echo "  Expected output to contain: $expected"
        printf '  Actual output:\n%s\n' "$OUTPUT"
        FAIL=$((FAIL + 1))
    fi
}

# Check that two markers appear in the correct order.
run_order_test() {
    local name="$1"
    local input="$2"
    local first="$3"
    local second="$4"

    if run_shell "$input"; then
        :
    else
        echo "FAIL: $name (shell exited unexpectedly or timed out)"
        FAIL=$((FAIL + 1))
        return
    fi

    if [[ "$OUTPUT" == *"$first"*"$second"* ]]; then
        echo "PASS: $name"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $name"
        echo "  Expected '$first' before '$second'"
        printf '  Actual output:\n%s\n' "$OUTPUT"
        FAIL=$((FAIL + 1))
    fi
}

# Check that a marker does not appear in the output.
run_absent_test() {
    local name="$1"
    local input="$2"
    local unexpected="$3"

    if run_shell "$input"; then
        :
    else
        echo "FAIL: $name (shell exited unexpectedly or timed out)"
        FAIL=$((FAIL + 1))
        return
    fi

    if [[ "$OUTPUT" != *"$unexpected"* ]]; then
        echo "PASS: $name"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $name"
        echo "  Unexpected output: $unexpected"
        printf '  Actual output:\n%s\n' "$OUTPUT"
        FAIL=$((FAIL + 1))
    fi
}

# 1. Command execution and arguments
run_test \
    "echo prints arguments" \
    $'echo hello world\nexit\n' \
    "hello world"

# 2. Multiple commands execute in order
run_order_test \
    "multiple commands execute in order" \
    $'echo FIRST_MARKER\necho SECOND_MARKER\nexit\n' \
    "FIRST_MARKER" \
    "SECOND_MARKER"

# 3. Empty input does not prevent subsequent commands
run_test \
    "empty input is handled" \
    $'\necho AFTER_EMPTY_MARKER\nexit\n' \
    "AFTER_EMPTY_MARKER"

# 4. Invalid commands do not prevent subsequent commands
run_test \
    "invalid command does not stop the shell" \
    $'teashell_command_that_does_not_exist\necho AFTER_ERROR_MARKER\nexit\n' \
    "AFTER_ERROR_MARKER"

# 5. Exit terminates the shell
run_test \
    "exit terminates the shell" \
    $'echo BEFORE_EXIT_MARKER\nexit\necho AFTER_EXIT_MARKER\n' \
    "BEFORE_EXIT_MARKER"

run_absent_test \
    "commands after exit are not executed" \
    $'exit\necho AFTER_EXIT_MARKER\n' \
    "AFTER_EXIT_MARKER"

# 6. EOF terminates the shell
run_test \
    "EOF exits cleanly" \
    'echo EOF_MARKER' \
    "EOF_MARKER"

# 7. An absolute executable path works
run_test \
    "absolute executable path works" \
    $'/usr/bin/printf ABSOLUTE_PATH_MARKER\nexit\n' \
    "ABSOLUTE_PATH_MARKER"

echo
echo "Results: $PASS passed, $FAIL failed"

if (( FAIL > 0 )); then
    exit 1
fi
