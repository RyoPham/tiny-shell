#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "commands.h"

char buff[SIZE + 5], dir[SIZE + 5];
char *argv[SIZE + 5];
int argc;

void getArgs() {
	int i = 0, j, k = 0;
	argc = 0;
	while(buff[i] != '\0') {
		if(isspace(buff[i])) {
			++i;
			continue;
		}
		j = i + 1;
		while(!isspace(buff[j]) && buff[j] != '\0') {
			++j;
		}
		argv[argc++] = &buff[i];
		i = j;
		if(buff[i] != '\0') {
			buff[i] = '\0';
			++i;
		}
	}
}	

int main(void) {
	while(1) {
		getcwd(dir, SIZE);
		printf("(tiny shell) %s>", dir);
		fgets(buff, SIZE, stdin);
		getArgs();
		run(argc, argv);
	}
}
