#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Inside Child Process
        printf("Child process running...\n");
        exit(42); // Normal exit with a specific status code
    } else {
        // Inside Parent Process
        int status;
        waitpid(pid, &status, 0); // Wait for the child to finish

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Child ended normally with exit code: %d\n", exit_code);
        } else if (WIFSIGNALED(status)) {
            printf("Child was terminated by a signal.\n");
        }
    }
    return 0;
}
