#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "help.h"

extern char *func_name_list[];
void (*help_list[])(int argc, char **argv) = {
        exitFuncHelp, 
        cdFuncHelp, 
        dateFuncHelp, 
        dirFuncHelp, 
        helpFuncHelp, 
        execFuncHelp, 
        runbashFuncHelp,
        listFuncHelp, 
        killFuncHelp, 
        stopFuncHelp, 
        resumeFuncHelp,
        clearFuncHelp,
        pathFuncHelp,
        addpathFuncHelp
        };

void exitFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Exit the tiny-shell\n", "exit");
    if(argc == 1){
        return;
    }
    printf("\nUsage: exit\n");
}

void cdFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Change the current working directory\n", "cd");
    if(argc == 1){
        return;
    }
    printf("\nUsage: cd [DIRECTORY]\n");
    printf("  %-10s Show the parent directory of the current directory\n", "..");
    printf("  %-10s Change the current directory to [DIRECTORY]\n", "[DIRECTORY]");
    printf("  %-10s Change the current directory to the home directory\n", "~");
}

void dateFuncHelp(int argc, char **argv) {
   printf("\n%-10s: Display the current date and time\n", "date");
    if (argc == 1) {
        return;
    }
    printf("\nUsage: date\n");
}

void dirFuncHelp(int argc, char **argv) {
printf("\n%-10s: List files in a specified directory (current directory by default)\n", "dir");
    if (argc == 1) {
        return;
    }
    printf("\nUsage: dir [path]\n");
    printf("  %-10s List files and directories in the current directory\n", "");
    printf("  %-10s List files and directories in the specified [DIRECTORY]\n", "[DIRECTORY]");
        
}

void helpFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Brief details about commands supported in tiny-shell\n", "help");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: help [name of supported command]\n");
}

void pathFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Display value of an environment variable (display all by default)\n", "path");
    if (argc == 1) {
        return;
    } 
    else {
        printf("\nUsage: path [var1] [var2] ...\n");
    }
}


void addpathFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Add a value to the specified environment variable\n", "addpath");
    if(argc == 1){
        return;
    }
    else{
        printf("\nUsage: addpath <VARIABLE> <PATH>\n");
        printf("  %-10s    Specify the environment variable\n", "<VARIABLE>");
        printf("  %-10s    Specify the value for variable\n", "<PATH>");
    }
}

void execFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Execute an executable file (in foreground mode by default)\n", "exec");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: exec [OPTION] <file> [arg1] [arg2] ...\n");
    printf("\nOptions:\n");
    printf("  %-10s foreground mode\n", "-f");
    printf("  %-10s background mode\n", "-b");
    printf("  %-10s create process in other terminal\n", "-B");
}

void runbashFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Run a bash file (in foreground mode by default)\n", "runbash");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: runbash [OPTION] <file> [arg1] [arg2] ...\n");
    printf("\nOptions:\n");
    printf("  %-10s foreground mode\n", "-f");
    printf("  %-10s background mode (not recommend)\n", "-b");
    printf("  %-10s create process in other terminal\n", "-B");
}

void listFuncHelp(int argc, char **argv) {
    printf("\n%-10s: List process (inside tiny-shell by default)\n", "list");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: list [OPTION1] [OPTION2]\n");
    printf("  %-10s all process in the OS\n", "-all");
    printf("  %-10s find process that has <TAR> in name\n", "-f <TAR>");
}

void killFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Kill a process\n", "kill");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: kill <pid1> <pid2> ...\n");
}

void stopFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Stop a running process\n", "stop");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: stop <pid1> <pid2> ...\n");
}

void resumeFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Resume a suspended process\n", "resume");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: resume <pid1> <pid2> ...\n");
}

void clearFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Clear termminal screen\n", "clear");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: clear\n");
}

void helpFunc(int argc, char **argv) {
    if(argc > 2) {
        printf("Error: Too many arguments\n");
        return;
    }
    if(argc == 2) {
        int n = sizeof(help_list) / sizeof(help_list[0]);
        int i;
        for(i = 0; i < n; ++i) {
            if(!strcmp(func_name_list[i], argv[1])) {
                (*help_list[i])(argc, argv);
                break;
            }
        }
    }
    else {
        int n = sizeof(help_list) / sizeof(help_list[0]);
        int i;
        printf("\n\nList of commands supported in tiny-shell\n");
        for(i = 0; i < n; ++i) {
            (*help_list[i])(argc, argv);
        }
        printf("\n\nTip: using \"help [name of supported command]\" for more details for each command\n");
        printf("\nNOTE:\n");
        printf("  <REQUIRE>  this is a required field\n");
        printf("  [OPTION]   this is an option field (not required)\n");
    }
    printf("\n");
}
