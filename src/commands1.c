#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "commands.h"

void exitFunc(int argc, char **argv) {
	exit(0);
}

void cdFunc(int argc, char **argv) {
	char * temp;
	temp = argv[1];
	if(argc > 3) {
		puts("\nError
			  \nToo many arguments");
	}

	else if(temp == "NULL" || temp == "~")
		chdir(home);
	
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
	
   const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

   printf("Year: %d\n", year);
   printf("Month: %s\n", months[month]);
   printf("Day: %d\n", day);
   printf("Time: %d:%d:%d\n", hour, min, sec);
	
}

void dirFunc(int argc, char **argv) {
	printf("dir command\n");
}

void helpFunc(int argc, char **argv) {

}
