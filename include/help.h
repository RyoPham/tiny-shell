/**
 * This file contains functions print help
 * for commands supported in tiny-shell
 * 
 * Print brief or usage in addition
*/

#ifndef __HELP_H__
#define __HELP_H__

void exitFuncHelp(int argc, char **argv);
void cdFuncHelp(int argc, char **argv);
void dateFuncHelp(int argc, char **argv);
void dirFuncHelp(int argc, char **argv);
void helpFuncHelp(int argc, char **argv);
void pathFuncHelp(int argc, char **argv);
void addpathFuncHelp(int argc, char **argv);

void execFuncHelp(int argc, char **argv);
void runbashFuncHelp(int argc, char **argv);
void runbatFuncHelp(int argc, char **argv);
void listFuncHelp(int argc, char **argv);
void killFuncHelp(int argc, char **argv);
void stopFuncHelp(int argc, char **argv);
void resumeFuncHelp(int argc, char **argv);
void clearFuncHelp(int argc, char **argv);

void helpFunc(int argc, char **argv);

#endif