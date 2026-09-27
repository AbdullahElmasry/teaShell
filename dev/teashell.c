#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){

    // Prompt
    // printf("$ ");

    // Getting the input from keyboard
    // char buf[1024];
    // fgets(buf, 1024, stdin);



    // Trim the newline from fgets output
    // char *nl = strchr(buf, '\n');              // iterate through the buf and get that newline >> searches for the first occurrence of a character inside a string
    // if (nl) *nl = '\0';                        // replace the newline with NULL



    // Execute the given line as a shell command.
    // system(buf); // Cheatinggggg

    pid_t pid = fork();

    // extracting the command out of stdin
    // char command[400];
    // sscanf(buf, "%s", command);

    if (pid > 0){
        // this is parent :) then we should wiat for the child process to finish

        // wait(child status);
        wait(NULL);
    }

    else if(pid < 0){
        // fork failed 
        fprintf(stderr, "Fork FAILED!");
    }

    else{
        // this is child 
        execvp(argv[1], &argv[1]);  // execlp: exec, 'l' >> list of arguments, 'p' >> searches PATH for the needed binary

        // exec didnt work
        fprintf(stderr, "Could not exec %s\n", argv[1]);
    }

}