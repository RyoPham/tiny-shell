#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define SIZE	(105)

void exitFunc(int argc, char **argv);
void cdFunc(int argc, char **argv);
void dateFunc(int argc, char **argv);
void dirFunc(int argc, char **argv);
void helpFunc(int argc, char **argv);

void execFunc(int argc, char **argv);
void listFunc(int argc, char **argv);
void killFunc(int argc, char **argv);
void stopFunc(int argc, char **argv);
void resumeFunc(int argc, char **argv);

void run(int argc, char **argv);

#endif
