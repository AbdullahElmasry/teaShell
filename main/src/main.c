#include "../include/main.h"

/*  by default the os is looking for a main function and the first
    argument will the counter and the second will store those arguments
    to iterate through them later using the argument vector.
*/

/*
./runner ls -l
ac = 3

av →   ┌───────────────┐
       │ av[0] ──► "./runner\0"
       │ av[1] ──► "ls\0"
       │ av[2] ──► "-l\0"
       │ av[3] ──► NULL
       └───────────────┘ 
*/

int main(int ac, char **av) // ac -> argument counter,  
{
    (void)ac;  // tells compiler that this wont be used
    int status;

    // child process
    if (fork() == 0){ // fork() creates new child process and return 0, and returns child PID > 0 
        execvp(av[1], av + 1);
    }

    /*  wait() -> system call that make parent process wait till child
        process finish and return anything like "return 0" or "exit(0)"
        that will be stored in -> status */
    wait(&status); 

    return EXIT_SUCCESS;
}