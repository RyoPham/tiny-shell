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
        listFuncHelp, 
        killFuncHelp, 
        stopFuncHelp, 
        resumeFuncHelp,
        clearFuncHelp
        };

void exitFuncHelp(int argc, char **argv) {

}

void cdFuncHelp(int argc, char **argv) {

}

void dateFuncHelp(int argc, char **argv) {

}

void dirFuncHelp(int argc, char **argv) {

}

void helpFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Brief details about commands supported in tiny-shell\n", "help");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: help [name of supported command]\n");
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
    printf("\nUsage: kill <process id>\n");
}

void stopFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Stop a running process\n", "stop");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: stop <process id>\n");
}

void resumeFuncHelp(int argc, char **argv) {
    printf("\n%-10s: Resume a suspended process\n", "resume");
    if(argc == 1) {
        return;
    }
    printf("\nUsage: resume <process id>\n");
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