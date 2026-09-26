#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    // Prompt
    printf("$ ");

    // Getting the input from keyboard
    char buf[1024];
    fgets(buf, 1024, stdin);

    // Execute the given line as a shell command.
    // system(buf); // Cheatinggggg

}