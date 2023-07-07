/**
 * A simple program creates some non-stop processes (4 processes).
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(), t;
    int status;
    if(pid == 0) {
        pid = fork();
        if(pid == 0) {
            // while(1) {
            //     t = getpid();
            //     printf("Hello from %u\n", t);
            //     sleep(1);
            // }
            while(1);
        }
        else {
            // while(1) {
            //     t = getpid();
            //     printf("Hello from %u\n", t);
            //     sleep(1);
            // }
            while(1);
        }
    }
    else {
        pid = fork();
        if(pid == 0) {
            while(1);
        }
        else {
            while(1);
        }
    }
}