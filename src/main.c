#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/prctl.h>
#include "commands.h"
#include "process.h"

char buff[SIZE + 5], dir[SIZE + 5];
char *argv[SIZE + 5];
int argc;

void getArgs() {
	int i = 0, j;
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
	argv[argc] = NULL;
}	

int main(void) {
	prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);
	while(1) {
		killZombies();
		getcwd(dir, SIZE);
		printf("(tiny shell) %s>", dir);
		fgets(buff, SIZE, stdin);
		getArgs();
		run(argc, argv);
	}
}
