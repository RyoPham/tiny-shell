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
	int
}

void dirFunc(int argc, char **argv) {
	printf("dir command\n");
}

void helpFunc(int argc, char **argv) {

}
