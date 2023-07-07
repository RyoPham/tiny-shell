/**
 * Some simple functions working with process
*/

#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include "list.h"

/**
 * @brief: verify a string is a number
 * 
 * Verify a string is a number by checking if all its characters
 * are in range ascii value from '0' to '9'
 * 
 * @param: pointer to string
 * @return: 0/1 - NO/YES
*/
int isNumeric(char *s);

/**
 * @brief: get process id of parent
 * 
 * Get PPID of a process by reading file proc/[pid]/stat
 * 
 * @param: process id (pid)
 * @return: process id of parent;
*/
pid_t getPPID(pid_t pid);

/**
 * @brief: get info of a process
 * 
 * Get info of a process by reading file proc/[pid]/stat.
 * Info includes process's name and status (running/suspend/...)
 * 
 * @param: process id (pid)
 * @param: pointer to string storing process's name
 * @param: pointer to char storing process's status
 * 
 * @return: None
*/
void getProcessInfo(pid_t pid, char *pname, char *status);

/**
 * @brief: check if a process is in tiny-shell
 * 
 * With a linked-list of current pid, along with ppid, this function traces 
 * the tree upward from node pid.
 * 
 * @param: process id (p_pid)
 * @param: tiny-shell process id (c_pid)
 * @param: pointer to linked-list of PID
 * @param: pointer to linked-list of PPID
 * 
 * @return: 0/1 - NO/YES
*/
int isChild(pid_t p_pid, pid_t c_pid, struct List* list_pid, struct List* list_ppid);

/**
 * @brief: get all PID and PPID value
 * 
 * Read whole directories in /proc to get pid of all alive proces
 * Read file /proc/[pid]/stat to get ppid
 * 
 * @param: pointer to linked-list storing pid
 * @param: pointer to linked-list storing ppid
 * 
 * @return: None
*/
void getProcess(struct List* list_pid, struct List* list_ppid);

/**
 * @brief: extract process inside tiny-shell from linked-list
 * 
 * Double traverse linked-list storing pid and ppid to extract.
 * 
 * @param: pointer to linked-list storing pid of process inside tiny-shell
 * @param: pointer to linked-list storing ppid of process inside tiny-shell
 * @param: pid of tiny-shell
 * @param: linked-list storing pid of all process
 * @param: linked-list storing ppid of all process
 * 
 * @return: None
*/
void getChildProcess(struct List* list_child_pid, struct List* list_child_ppid, pid_t pid, struct List list_pid, struct List list_ppid);

/**
 * @brief: kill child processes which have zombie status
 * 
 * Get linked-list storing pid. 
 * Then wait pid which has ppid equal to tiny-shell's pid
 * 
 * @param: None
 * 
 * @return: None
*/
void killZombies();

/**
 * @brief: kill all processes inside tiny-shell
 * 
 * Get linked-list storing child process' pid.
 * Then send SIGKILL signal to all of them.
 * 
 * @param: None
 * 
 * @return: Number of successful signal sent
*/
int killChild();

#endif