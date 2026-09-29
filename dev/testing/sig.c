#include <signal.h>



void handler(int sig){
    printf("i wont die hehehehe suiii!\n");
}

int main(void){

    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    
    signal(SIGKILL, handler);  
    // unfortunately not gonna work :(


    while(1){
        printf("running... %d\n", getpid());
        sleep(1);
    }
}