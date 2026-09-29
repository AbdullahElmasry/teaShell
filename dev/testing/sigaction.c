#include <signal.h>
#include <stdio.h>
#include <unistd.h>


void handler(int sig){
    printf("i wont die hehehehe suiii!\n");
}

int main(void){

    struct sigaction action;

    // kinda fixed setup 
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    // then use this instead of normal signal()
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGKILL, &action, NULL);



    // signal(SIGINT, handler);
    // signal(SIGTERM, handler);
    
    // signal(SIGKILL, handler);  
    // unfortunately not gonna work :(


    while(1){
        printf("running... %d\n", getpid());
        sleep(1);
    }
}