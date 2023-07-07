/**
 * Simple program get value of environment 
 * varibale named "MY_ENV_VAR"
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *my_env_var = getenv("MY_ENV_VAR");
    if(my_env_var) {
        printf("Var found: MY_ENV_VAR=%s\n", my_env_var);
    }
    else {
        printf("Var not found\n");
    }
}