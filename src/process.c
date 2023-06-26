#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "list.h"
#include "process.h"

int isNumeric(char *s) {
	int i, n = strlen(s);
	for(i = 0; i < n; ++i) {
		if(!('0' <= s[i] && s[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}

pid_t getPPID(pid_t pid) {
	static char procname[64], comm[256];
	char status;
	pid_t ppid, unused;
	FILE* fp;
	snprintf(procname, sizeof(procname), "/proc/%u/stat", pid);
	fp = fopen(procname, "r");
	
	fscanf(fp, "%u %s %c %u", &unused, comm, &status, &ppid);

	fclose(fp);
	
	return ppid;
}

void getProcessInfo(pid_t pid, char *pname, char *status) {
	static char procname[64];
	pid_t unused;
	FILE* fp;
	snprintf(procname, sizeof(procname), "/proc/%u/stat", pid);
	fp = fopen(procname, "r");

	fscanf(fp, "%u %s %c", &unused, pname, status);

	fclose(fp);
}

int isChild(pid_t p_pid, pid_t c_pid, struct List* list_pid, struct List* list_ppid) {
	struct Node* u;
	struct Node* v;
	while(c_pid) {
		if(p_pid == c_pid) {
			return 1;
		}
		u = list_pid->head; 
		v = list_ppid->head;
		while(u != NULL) {
			if(u->value == c_pid) {
				break;
			}
			u = u->next;
			v = v->next;
		}
		if(v == NULL) {
			return 0;
		}
		c_pid = v->value;
	}
	return 0;
}

void getProcess(struct List* list_pid, struct List* list_ppid) {
    struct dirent *pDirent;
	DIR *pDir;
    pid_t tmp_pid;

    list_pid->head = list_pid->tail = NULL;
	list_ppid->head = list_ppid->tail = NULL;

    pDir = opendir("/proc");

	if(pDir == NULL) {
		printf("Cannot open directory /proc\n");
		return;
	}

	while((pDirent = readdir(pDir)) != NULL) {
		if(isNumeric(pDirent->d_name)) {
			tmp_pid = atoi(pDirent->d_name);
			add(list_pid, tmp_pid);
			add(list_ppid, getPPID(tmp_pid));
		}
	}
}

void getChildProcess(struct List* list_child_pid, struct List* list_child_ppid, pid_t pid, struct List list_pid, struct List list_ppid) {
    struct Node* cur_pid;
	struct Node* cur_ppid;

    list_child_pid->head = list_child_pid->tail= NULL;
	list_child_ppid->head = list_child_ppid->tail = NULL;    

    cur_pid = list_pid.head; 
	cur_ppid = list_ppid.head;

	while(cur_pid != NULL) {
		if(isChild(pid, cur_pid->value, &list_pid, &list_ppid)) {
			add(list_child_pid, cur_pid->value);
			add(list_child_ppid, cur_ppid->value);
		}
		cur_pid = cur_pid->next;
		cur_ppid = cur_ppid->next;
	}
    
}

void killZombies() {
	struct List list_pid, list_ppid;
	struct List list_child_pid, list_child_ppid;
	struct Node* cur_pid;
	struct Node* cur_ppid;
	pid_t pid = getpid();
	int ret;

	getProcess(&list_pid, &list_ppid);
	getChildProcess(&list_child_pid, &list_child_ppid, pid, list_pid, list_ppid);

	cur_pid = list_child_pid.head;
	cur_ppid = list_child_ppid.head;

	while(cur_pid != NULL) {
		if(cur_ppid->value == pid) {
			waitpid(cur_pid->value, &ret, WNOHANG);
		}
		cur_pid = cur_pid->next;
		cur_ppid = cur_ppid->next;
	}

	clear(&list_pid);
	clear(&list_ppid);
	clear(&list_child_pid);
	clear(&list_child_ppid);
}

int killChild() {
	struct List list_pid, list_ppid;
	struct List list_child_pid, list_child_ppid;
	struct Node* cur_pid;
	struct Node* cur_ppid;
	pid_t pid = getpid();
	int cnt = 0;

	getProcess(&list_pid, &list_ppid);
	getChildProcess(&list_child_pid, &list_child_ppid, pid, list_pid, list_ppid);

	cur_pid = list_child_pid.head;
	cur_ppid = list_child_ppid.head;

	while(cur_pid != NULL) {
		if(cur_pid->value != pid) {
			if(kill(cur_pid->value, 9) == 0) {
				++cnt;
			}
		}
		cur_pid = cur_pid->next;
		cur_ppid = cur_ppid->next;
	}

	clear(&list_pid);
	clear(&list_ppid);
	clear(&list_child_pid);
	clear(&list_child_ppid);

	return cnt;
}
