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
#include "help.h"

pid_t pid_running;
int is_running = 0;

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

void clearFunc(int argc, char **argv) {
	if(argc > 1) {
		printf("Error: Too many arguments\n");
		return;
	}
	int pid = fork(), status;
	if(pid == 0) {
		execl("/bin/clear", "/bin/clear", (char *)NULL);
		return;
	}
	else {
		waitpid(pid, &status, 0);
	}
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
		setpgid(0, 0);
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
		argv[argc] = NULL;
		if(execv(argv[0], argv) == -1) {
			printf("Executation failed!\n");
		}
		exit(0);
	}
	else if(background_flag == 0) {
		pid_running = pid;
		is_running = 1;
		waitpid(pid, &status, 0);
		is_running = 0;
	}
}

void runbashFunc(int argc, char **argv) {
	static char BASH[10] = "/bin/bash";
	static char BCKG[3] = "-b";
	static char FREG[3] = "-f";
	static char TERG[3] = "-B";
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

	argc = shiftLeft(argc, argv, flag_count);
	argv[0] = BASH;
	argc = shiftRight(argc, argv, 1 + flag_count);
	if(flag_count) {
		if(background_flag) {
			if(new_terminal) {
				argv[1] = TERG;
			}
			else {
				argv[1] = BCKG;
			}
		}
		else {
			argv[1] = FREG;
		}
	}
	execFunc(argc, argv);
}

extern int getArgs(char *buff, char **argv);

void runbatFunc(int argc, char **argv) {
	if(argc == 1) {
		printf("Usage: runbat <file>\n");
		return;
	}
	if(argc > 2) {
		printf("Too many arguments\n");
		return;
	}

	char *file_name = argv[1];
	FILE *fp;
	static char buff[SIZE + 5];
	static char *sub_argv[SIZE + 5];
	int sub_argc;

	fp = fopen(file_name, "r");
	if(fp == NULL) {
		printf("%s: File does not exist\n", file_name);
		exit(0);
	}
	while(fgets(buff, SIZE, fp)) {
		sub_argc = getArgs(buff, sub_argv);
		// printf("argc = %d\n", argc);
		// for(int i = 0; i < argc; ++i) {
		// 	printf("argv[%d] = %s\n", i, argv[i]);
		// }
		// printf("===========================\n");
		run(sub_argc, sub_argv);
	}
}

void listFunc(int argc, char **argv) {
	int flag_all = 0, flag_find = 0;
	pid_t pid = getpid();
	struct List list_pid, list_ppid;
	struct List list_child_pid, list_child_ppid;
	struct Node* cur_pid;
	struct Node* cur_ppid;
	static char pname[256];
	char status;

	if(argc >= 2) {
		if(!strcmp(argv[1], "-all")) {
			flag_all = 1;
			if(argc > 2) {
				printf("Error: Too many arguments\n");
				return;
			}
		}
		else if(!strcmp(argv[1], "-f")) {
			flag_find = 1;
			flag_all = 1;
			if(argc < 3) {
				printf("Error: Too few arguments\n");
				return;
			}
			else if(argc > 3) {
				printf("Error: Too many arguments\n");
				return;
			}
		}
		else {
			printf("\nCannot recognize your arguments\n");
			listFuncHelp(argc, argv);
			return;
		}
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
	printf("%10s %10s %-6s %-20s\n", "PID", "PPID", "STATUS", "NAME");
	printf("=========================================================\n");
	while(cur_pid != NULL) {
		++process_count;
		getProcessInfo(cur_pid->value, pname, &status);
		// printf("%u %u\n", cur_pid->value, cur_ppid->value);
		if(!flag_find || strstr(pname, argv[2])) {
			printf("%10u %10u %-6c %-20s\n", cur_pid->value, cur_ppid->value, status, pname);
		}
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
		printf("Usage: kill <pid1> <pid2> ...\n");
		return;
	}
	int i;
	pid_t pid;
	for(i = 1; i < argc; ++i) {
		if(!isNumeric(argv[i])) {
			printf("\"%s\": arguments must be process IDs\n", argv[i]);
			continue;
		}
		pid = atoi(argv[i]);
		if(kill(pid, SIGKILL)) {
			printf("(%u) - No such process\n", pid);
		}
	}
}

void stopFunc(int argc, char **argv) {
	if(argc < 2) {
		printf("Usage: stop <pid1> <pid2> ...\n");
		return;
	}
	int i;
	pid_t pid;
	for(i = 1; i < argc; ++i) {
		if(!isNumeric(argv[i])) {
			printf("\"%s\": arguments must be process IDs\n", argv[i]);
			continue;
		}
		pid = atoi(argv[i]);
		if(kill(pid, SIGSTOP)) {
			printf("(%u) - No such process\n", pid);
		}
	}
}

void resumeFunc(int argc, char **argv) {
	if(argc < 2) {
		printf("Usage: resume <pid1> <pid2> ...\n");
		return;
	}
	int i;
	pid_t pid;
	for(i = 1; i < argc; ++i) {
		if(!isNumeric(argv[i])) {
			printf("\"%s\": arguments must be process IDs\n", argv[i]);
			continue;
		}
		pid = atoi(argv[i]);
		if(kill(pid, SIGCONT)) {
			printf("(%u) - No such process\n", pid);
		}
	}
}

