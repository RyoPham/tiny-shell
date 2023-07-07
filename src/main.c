#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include "commands.h"
#include "process.h"

extern pid_t pid_running;
extern int is_running;

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
		if(buff[i] == '\"') {
			j = i + 1;
			while(buff[j] != '\0' && buff[j] != '\"') {
				++j;
			}
			if(buff[j] == '\"') {
				argv[argc++] = &buff[i + 1];
				buff[i] = buff[j] =  '\0';
				i = j + 1;
			}
			else {
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
		else {
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
	argv[argc] = NULL;
}	

void sigintHandler() {
	if(is_running) {
		kill(pid_running, 9);
		is_running = 0;
	}
	signal(SIGINT, sigintHandler);
	return;
}

int main(void) {
	prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);
	signal(SIGINT, sigintHandler);
	while(1) {
		getcwd(dir, SIZE);
		printf("(tiny shell) %s>", dir);
		fgets(buff, SIZE, stdin);
		getArgs();
		killZombies();
		run(argc, argv);
	}
}
