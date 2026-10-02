#include "expansion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expand_variables(char *argv[], int argc, int last_status){

    char status_str[20];

    snprintf(status_str, sizeof(status_str), "%d", last_status);

    for (int i=0; i < argc; i++){
        if (strcmp(argv[i], "$?") == 0){
            argv[i] = status_str;
        }

        // if the second argument's first letter is $ then we expand using getenv()
        else if (argv[i][0] == '$'){
            char *value = getenv(argv[i]+1); // because the first letter is $ so we start from the second letter
                    // the getenv() is returning NULL if the variable isnt there

            if (value != NULL){
                argv[i] = value;
            }
        }
    }

}