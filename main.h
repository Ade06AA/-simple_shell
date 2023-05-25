#ifndef _AA_
#define _AA_

#include <string.h> /* strtok */
#include <stdlib.h> /* free, malloc, NULL */
#include <stdbool.h> /* TRUE */
#include <unistd.h> /* write, fork, STDOUT_FILENO and the rest, */
#include <stdio.h> /* getline */
#include <sys/wait.h> /* wait */
#define ARG_MAX 100000
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

 /* get PATH from enviromental variable
* @e: func arg 1
 * enviromental variable
* Return: PATH (char *)
*/
/*char *getpath(char **e)
{
	int i;
	for (i = 0; e[i][0] != 'P' || e[i][1] != 'A' || e[i][2] != 'T' || e[i][3] != 'H'; i++)
		;
	return (e[i]);
}*/


/*	char *c;*/
/*	int i;*/

/*	for (i = 0; i != 100; i++)*/
/*		c[i] = a[i];*/
/*	c[i] = '\0';*/
/*	return (c);*/
/*}*/

/**
* mypathexec - func name
 * handels command that are found in PATH
* @tok: func arg 1
 * the tokenized input
* @a: func arg 2
 * the environment variables whic also contain PATH
* Return: 1 if the command is found in PATH else 0
*/
/*int mypathexec(char **tok, char **a)
{
	int i, j;
	char **token;
	char *path;

	path = malloc(200);
	path = getpath(a);
	for (i = 0; path[i] != '='; ++i)
		;
	i++;
	token = mystrtok(path + i, ':');
	for (i = 0; token[i] != NULL && (token[i][0] != 'P' && token[i][2] != 'O'); i++)
	{
		myjoin(&token[i], tok[0]);
		if (!(access(token[i], F_OK)))
		{
			j = fork();
			if (j == 0)
			{
				execve(token[i], tok, NULL);
				return (0);
			}
			else
			{
				wait(NULL);
				return (1);
			}
		}
	}
	return (0);
}*/
#endif
