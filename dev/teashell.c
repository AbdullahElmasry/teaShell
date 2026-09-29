#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>


// Signal Handler function , currenrly SIGINT, SIGTERM supported
void handler(int sig){

    if (sig == SIGINT) {
        char msg[] = "Recieved TERMINATION signal!\n";
        write(STDOUT_FILENO, msg, sizeof(msg));
    }

    else if(sig == SIGTERM) {
        char msg[] = "Recieved TERMINATION signal!\n";
        write(STDOUT_FILENO, msg, sizeof(msg));
    }
}


int main(/*int argc, char *argv[]*/){   // we dont need them as we are creating our own bellow

    struct sigaction action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    // in the case of CTRL + C
    sigaction(SIGINT, &action, NULL);

    // in the case of termination signal
    sigaction(SIGTERM, &action, NULL);


    while (1){
        // Prompt
        printf("$ ");

        // Getting the input from keyboard
        char buf[1024];


        
        // if CTRL+D detected then fgets returns NULL, in this case we break the whole loop and shell exits
        if(fgets(buf, 1024, stdin) == NULL){
            // feof checks if its EOF or not
            if(feof(stdin)){
                break;
            }

            // in the case of any termination signals, Clear the stream error state and try reading again
            if (errno == EINTR){ 
                clearerr(stdin);     
                continue;
            }

            perror("fgets: ");       // prints the error in a humand readable way
            break;
        }
        



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

        // Exit command 
        if(argv[0] == NULL) continue;
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


        int status;

        if (pid > 0){
            // this is parent :) then we should wiat for the child process to finish

            // wait(child status);
            waitpid(pid, &status, 0);
        }

        else if(pid < 0){
            // fork failed 
            // fprintf(stderr, "Fork FAILED!");
            perror("fork: ");
        }

        else{
            // this is child 
            execvp(argv[0], argv);
            /* execlp: exec, 'l' >> list of arguments, 'p' >> searches PATH for the needed binary
            execvp:       'v' >> vector of arguments, 'p' >> searches PATH for the needed binary
            */ 

            // exec didnt work
            // fprintf(stderr, "Could not exec %s\n", buf);

                perror("execvp: ");
                exit(EXIT_FAILURE);
        }


    } // while ends

}