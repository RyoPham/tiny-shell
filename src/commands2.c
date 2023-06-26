#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "commands.h"
#include "list.h"
#include "process.h"

int shiftLeft(int argc, char **argv, int m) {
	int i;
	for(i = 0; i + m < argc; ++i) {
		argv[i] = argv[i + m];
	}
	argv[argc - m] = NULL;
	return argc - m;
}

int shiftRight(int argc, char **argv, int m) {
	int i;
	for(i = argc + m - 1; i >= m; --i) {
		argv[i] = argv[i - m];
	}
	argv[argc + m] = NULL;
	return argc + m;
}

void execFunc(int argc, char **argv) {
	if(argc < 2) {
		return;
	}
	static char gnome[20] = "/bin/gnome-terminal";
	static char q_flag[3] = "-q";
	static char dashdash[3] = "--";
	int background_flag = 0, flag_count = 0, new_terminal = 0;
	if(!strcmp(argv[1], "-b")) {
		background_flag = 1; //background mode
		flag_count = 1;
	}
	else if(!strcmp(argv[1], "-B")) {
		background_flag = 1; //background mode
		flag_count = 1;
		new_terminal = 1;
	}
	else if(!strcmp(argv[1], "-f")) {
		background_flag = 0; //foreground mode - default mode
		flag_count = 1;
	}

	if(access(argv[1 + flag_count], F_OK)) {
		printf("%s: No such file\n", argv[1 + flag_count]);
		return;
	}

	int pid = fork(), status;
	if(pid == 0) {
		argc = shiftLeft(argc, argv, 1 + flag_count);
		if(new_terminal) {
			argc = shiftRight(argc, argv, 3);
			argv[0] = gnome;
			argv[1] = q_flag;
			argv[2] = dashdash;
		}
		// printf("Pathname = %s\n", argv[1]);
		// printf("Args[] = ");
		// for(int i = 1; i < argc; ++i) {
		// 	printf("%s ", argv[i]);
		// }
		// printf("\n");
		if(execv(argv[0], argv) == -1) {
			printf("Executation failed!\n");
		}
		exit(0);
	}
	else if(background_flag == 0) {
		waitpid(pid, &status, 0);
	}
}

void listFunc(int argc, char **argv) {
	int flag_all = 0;
	pid_t pid = getpid();
	struct List list_pid, list_ppid;
	struct List list_child_pid, list_child_ppid;
	struct Node* cur_pid;
	struct Node* cur_ppid;
	static char pname[256];
	char status;

	if(argc >= 2 && !strcmp(argv[1], "-all")) {
		flag_all = 1;
	}

	getProcess(&list_pid, &list_ppid);
	getChildProcess(&list_child_pid, &list_child_ppid, pid, list_pid, list_ppid);

	if(!flag_all) {
		cur_pid = list_child_pid.head;
		cur_ppid = list_child_ppid.head;
	}
	else {
		cur_pid = list_pid.head;
		cur_ppid = list_ppid.head;
	}
	int process_count = 0;
	printf("%12s %12s %-6s %-20s\n", "PID", "PPID", "STATUS", "NAME");
	while(cur_pid != NULL) {
		++process_count;
		getProcessInfo(cur_pid->value, pname, &status);
		// printf("%u %u\n", cur_pid->value, cur_ppid->value);
		printf("%12u %12u %-6c %-20s\n", cur_pid->value, cur_ppid->value, status, pname);
		cur_pid = cur_pid->next;
		cur_ppid = cur_ppid->next;
	}
	// printf("Number of Process = %d\n", process_count);

	clear(&list_pid);
	clear(&list_ppid);
	clear(&list_child_pid);
	clear(&list_child_ppid);
}

void killFunc(int argc, char **argv) {
	if(argc < 2) {
		printf("Usage: kill <process id>\n");
		return;
	}
	pid_t pid = atoi(argv[1]);
	kill(pid, 9); //SIGKILL - 9
}

void stopFunc(int argc, char **argv) {
	if(argc < 2) {
		printf("Usage: resume <process id>\n");
		return;
	}
	pid_t pid = atoi(argv[1]);
	kill(pid, 19); //SIGSTOP - 19
}

void resumeFunc(int argc, char **argv) {
	if(argc < 2) {
		printf("Usage: resume <process id>\n");
		return;
	}
	pid_t pid = atoi(argv[1]);
	kill(pid, 18); //SIGCONT - 18
}

