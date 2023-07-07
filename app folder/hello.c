/**
 * A simple program print "Hello" with its process id
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = getpid();
    printf("Hello from %u\n", pid);
}