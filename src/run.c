#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

void (*func_list[])(int argc, char **argv) = {
        exitFunc, 
        cdFunc, 
        dateFunc, 
        dirFunc, 
        helpFunc, 
        execFunc, 
        runbashFunc,
        runbatFunc,
        listFunc, 
        killFunc, 
        stopFunc, 
        resumeFunc,
        clearFunc,
        pathFunc,
        addpathFunc
        };
const char *func_name_list[] = {
        "exit", 
        "cd", 
        "date", 
        "dir", 
        "help", 
        "exec", 
        "runbash",
        "runbat",
        "list", 
        "kill", 
        "stop", 
        "resume",
        "clear",
        "path",
        "addpath"
        };

void run(int argc, char **argv) {
        if(argc == 0) return;
        int i, n = sizeof(func_list) / sizeof(func_list[0]);
        for(i = 0; i < n; ++i) {
                if(!strcmp(argv[0], func_name_list[i])) {
                        (*func_list[i])(argc, argv);
                        return;
                }
        }
        printf("The tiny shell does not support \"%s\" command.\n", argv[0]);
        printf("Please use \"help\" command for help.\n");
}
