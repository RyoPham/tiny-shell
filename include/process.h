#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "list.h"

int isNumeric(char *s);

pid_t getPPID(pid_t pid);

void getProcessInfo(pid_t pid, char *pname, char *status);

int isChild(pid_t p_pid, pid_t c_pid, struct List* list_pid, struct List* list_ppid);

void getProcess(struct List* list_pid, struct List* list_ppid);

void getChildProcess(struct List* list_child_pid, struct List* list_child_ppid, pid_t pid, struct List list_pid, struct List list_ppid);

void killZombies();

#endif