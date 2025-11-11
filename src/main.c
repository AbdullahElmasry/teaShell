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
//-----------------------------------------------------------------



char *cell_read_line(void){
    char *buf;
    size_t bufsize;

  buf = NULL; // getline will take care of it

  if (getline(&buf, &bufsize) == -1){

    if (feof(stdin)){
        printf("[EOF]");
    }
    else{
        printf("Getline failed");
    }
    
  }
}


int main(int ac, char **av) // ac -> argument counter,  
{

    char *line;
    // REPL
    // READ - EVALUATE - PRINT/EXECUTE - LOOP

    while (0xCE77){

        // 1- get line
        // int getline();
        line = cell_read_line();



        /* 2- get tokens gettoke
                -> lexing > parsing EVALUATING


            3- Exec 
        */
    }



    // (void)ac;  // tells compiler that this wont be used
    // int status; 

    // // child process returns 0 so only child will enter the if.
    // if (fork() == 0){ // fork() creates new child process and return 0

    //     execvp(av[1], av + 1);

    //     // v for "vector" , p for "path"
    //     // takes an array of arguments and uses PATH to find the executable.
    //     // char **av = {"ls", "-la", NULL}

    // }

    /*  wait() -> system call that make parent process wait till child
    //     process finish and return anything like "return 0" or "exit(0)"
    //     that will be stored in -> status */
    wait(&status);

    return EXIT_SUCCESS;
}