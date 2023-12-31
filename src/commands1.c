#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "commands.h"
#include "process.h"

void exitFunc(int argc, char **argv) {
    while(killChild()) {
        sleep(1);
        killZombies();
    }
	exit(0);
}

void cdFunc(int argc, char **argv){
    char *temp = argv[1];

    if (argc > 2) {
        printf("Error: Too many arguments\n");
        return;
    }

    if (temp == NULL || *temp == '~') {
        if (chdir(getenv("HOME")) != 0) {
            printf("Failed to change directory\n");
            return;
        }
    } 
    
    else if (strcmp(temp, "..") == 0) {
        if (chdir("..") != 0) {
            printf("Failed to change directory\n");
            return;
        }
    } 
    
    else {
        if (chdir(temp) != 0) {
            printf("Directory does not exist\n");
            return;
        }
    }
}

void dateFunc(int argc, char **argv) {
    time_t now = time(0);
    struct tm *ltm = localtime(&now);

    int hour = ltm->tm_hour;
    int min = ltm->tm_min;
    int day = ltm->tm_mday;
    int month = ltm->tm_mon + 1;
    int year = 1900 + ltm->tm_year;

    const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    printf("%02d:%02d %s %02d/%02d/%d\n", hour, min, days[ltm->tm_wday], day, month, year);
}

void dirFunc(int argc, char **argv) {
    char *path;
    if (argc < 2) {
        path = ".";
    }
    else {
        path = argv[1];
    }

    DIR *dirp;
    struct dirent *entry;
    struct stat file_info;
    struct tm *time_info;
    char date[20];
    char time[20];

    dirp = opendir(path);
    if (dirp == NULL) {
        perror("Failed to open directory");
        return;
    }

    printf("%-15s%-15s%-15s%-15s%-15s\n", "Date", "Time", "Type", "Name", "Size (bytes)");
    printf("=========================================================================\n");

    while ((entry = readdir(dirp)) != NULL) {
        char full_path[512];
        snprintf(full_path, sizeof(full_path) - 2, "%s/%s", path, entry->d_name);

        if (lstat(full_path, &file_info) == -1) {
            perror("Failed to get file information");
            continue;
        }

        time_info = localtime(&file_info.st_mtime);
        strftime(date, sizeof(date), "%d/%m/%Y", time_info);
        strftime(time, sizeof(time), "%H:%M", time_info);

        if (S_ISREG(file_info.st_mode)) {
            printf("%-15s%-15s%-15s%-15s%-15lld\n", date, time, "<FILE>", entry->d_name, (long long)file_info.st_size);
        }
        else if (S_ISDIR(file_info.st_mode)) {
            printf("%-15s%-15s%-15s%-15s%-15lld\n", date, time, "<FOLDER>", entry->d_name, (long long)file_info.st_size);
        }
    }

    closedir(dirp);
}

extern char **environ;

void pathFunc(int argc, char **argv) {
    // if (argc > 1) {
    //     printf("Too many arguments.\n");
    // } else if (argv != NULL) {
    //     char *value = getenv(argv[0]);
    //     if (value != NULL) {
    //         printf("%s=%s\n", argv[0], value);
    //     } else {
    //         printf("The environment variable %s does not exist.\n", argv[0]);
    //     }
    // } else {
    //     printf("No argument provided.\n");
    // }
    if(argc == 1) {
        char **s = environ;
        for(; *s; ++s) {
            printf("%s\n", *s);
        }
    }
    else if (strcmp(argv[1],"-r") == 0){
        for(int i = 2; i < argc; i++){
            int result = unsetenv(argv[i]);
            if(result == -1){
                printf("%s: Error\n", argv[i]);
            }
        }
    }
    else {
        int i;
        char *value;
        for(i = 1; i < argc; ++i) {
            value = getenv(argv[i]);
            if(value != NULL) {
                printf("%s=%s\n", argv[i], value);
            }
            else {
                printf("The environment variable %s does not exist\n", argv[i]);
            }
        }
    }
}


void addpathFunc(int argc, char **argv) {
    if (argc != 3) {
        printf("Insufficient arguments. Usage: addpath <variable> <path>\n");
        return;
    }

    const char *variable = argv[1];
    const char *path = argv[2];

    int result = setenv(variable, path, 1);

    if (result == 0) {
        printf("Successfully set %s=%s\n", variable, path);
    } else {
        printf("Failed to set %s=%s\n", variable, path);
    }
}

