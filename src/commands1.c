#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "commands.h"

void exitFunc(int argc, char **argv) {
	exit(0);
}

void cdFunc(int argc, char **argv) {
	char * temp;
	temp = argv[1];
	if(argc > 3) {
		printf("Error\n");
		printf("Too many arguments\n");
	}

	else if(temp == NULL || *temp == '~')
		chdir("/home");
	
	else {
		int change = chdir(temp);
		if(change < 1)
			printf("Directory does not exist :'(");
	}
}

void dateFunc(int argc, char **argv) {
   time_t now = time(0);

   struct tm *ltm = localtime(&now);

   int year = 1900 + ltm->tm_year;
   int month = ltm->tm_mon;
   int day = ltm->tm_mday;
   int hour = 1 + ltm->tm_hour;
   int min = 1 + ltm->tm_min;
   int sec = 1 + ltm->tm_sec;

   // Mảng chứa tên các tháng
   const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

   printf("Year: %d\n", year);
   printf("Month: %s\n", months[month]);
   printf("Day: %d\n", day);
   printf("Time: %d:%d:%d\n", hour, min, sec);

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

    printf("%-15s%-15s%-15s%-15s\n", "Date", "Time", "Type", "Name");
    printf("=========================================================================\n");

    while ((entry = readdir(dirp)) != NULL) {
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (lstat(full_path, &file_info) == -1) {
            perror("Failed to get file information");
            continue;
        }

        time_info = localtime(&file_info.st_mtime);
        strftime(date, sizeof(date), "%d/%m/%Y", time_info);
        strftime(time, sizeof(time), "%H:%M", time_info);

        if (S_ISREG(file_info.st_mode)) {
            printf("%-15s%-15s%-15s%-15s\n", date, time, "<FILE>", entry->d_name);
        }
        else if (S_ISDIR(file_info.st_mode)) {
            printf("%-15s%-15s%-15s%-15s\n", date, time, "<FOLDER>", entry->d_name);
        }
    }

    closedir(dirp);
}

void helpFunc(int argc, char **argv) {

}
