#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(/*int argc, char *argv[]*/){   // we dont need them as we are creating our own bellow

    while (1){
        // Prompt
        printf("$ ");

        // Getting the input from keyboard
        char buf[1024];
        fgets(buf, 1024, stdin);



        // Trim the newline from fgets output
        char *nl = strchr(buf, '\n');              // iterate through the buf and get that newline >> searches for the first occurrence of a character inside a string
        if (nl) *nl = '\0';                        // replace the newline with NULL

        // Tokenize the buf and turn it into argument vector which is a pointer to pointer to charachter 
        int argc = 0;
        char *argv[120];

        char *token = strtok(buf, " ");

        while(token != NULL){
            argv[argc] = token;
            argc++;

            token = strtok(NULL, " ");
        }

        argv[argc] = NULL;

        if(strcmp(argv[0], "exit") == 0){
            exit(0);
        }

        // ==========================================================

        // Execute the given line as a shell command.
        // system(buf); // Cheatinggggg

        // ==========================================================

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
            execvp(argv[0], &argv[0]);
            /* execlp: exec, 'l' >> list of arguments, 'p' >> searches PATH for the needed binary
            execvp:       'v' >> vector of arguments, 'p' >> searches PATH for the needed binary
            */ 

            // exec didnt work
            fprintf(stderr, "Could not exec %s\n", buf);
        }


    } // while ends

}