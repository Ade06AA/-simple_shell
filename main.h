#ifndef _AA_
#define _AA_

#include <string.h> /* strtok */
#include <stdlib.h> /* free, malloc, NULL */
#include <stdbool.h> /* TRUE */
#include <unistd.h> /* write, fork, STDOUT_FILENO and the rest, */
#include <stdio.h> /* getline */
#include <sys/wait.h> /* wait */
#define ARG_MAX 100000

extern char **environ;
/* sub1 */
int comp(char *, char *);
void mycopy(char **, char *);
void myfree(char **);
void fr(char *, char **);
char **mystrtok(char *, char);

/* sub2 */
size_t mywrite(char *, int);
int mybuiltin(char **, char **);
int mycheck(char **);

/* sub3 */
void myitostr(unsigned int, char *, int *);
void mystrtoi(char *, int *, int *);

/* sub 4 */
int myisnum(char *);
void myerror(char **, int);
void myjoin(char **, char *);

void mycheck2(char **);
void prompt(int);
int myexit2(char **, char *, int, int *, int *);
#endif
