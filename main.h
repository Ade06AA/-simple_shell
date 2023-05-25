#ifndef _AA_
#define _AA_
#include <string.h> /* strtok */
#include <stdlib.h> /* free, malloc */
#include <stdbool.h> /* TRUE */
#include <unistd.h> /* write, fork */
#include <stdio.h> /* getline */
#include <sys/wait.h> /* wait */
#define ARG_MAX 32768
/**
* comp - func name
 * comp a string from stdin to a specified string
* @terminal_input: func arg 1
 * string from the terminal
* @b: func arg 2
 * string to be compierd with
* Return: 1 if equal else 0
*/
int comp(char *terminal_input, char *b)
{
	int i;
	for (i = 0; terminal_input[i] == b[i]; i++)
	{
	if ((terminal_input[i] == '\0'|| terminal_input[i] == '\n') && b[i] == '\0')
		return (1);
	}
	return (0);
}

/**
* mycopy - func name
 * copies string
* @a: func arg 1
* @b: func arg 2
* Return: void
*/
void mycopy(char **a, char *b)
{
	int i;
	(*a) = malloc(ARG_MAX);
	for (i = 0; b[i] != '\n' && b[i] != '\0'; i++)
		(*a)[i] = b[i];
	(*a)[i] = '\0';
}

/**
* myfree - func name
 * free a pointer to pointer and its content
* @p: fuinc arg 1
* @i: func arg 2
 * number of sub pointer too be freed
* Return: void
*/
void myfree(char **p)
{
	int i = 0;
	if (p != NULL)
	{
		while(p[i] != NULL)
		{
			free(p[i]);
			p[i] = NULL;
			i++;
		}
		free(p);
	}
}

/**
* fr - func name
 * free a char * and a char **
* @a: func arg 1
 * char * to be freed
* @b: func arg 2
 * char ** to be freed
* Return: void
*/
void fr(char *a, char **b)
{
	if (a != NULL)
		free(a);
	if (b != NULL)
		myfree(b);
}
/**
* mystrtok - func name
 * break a string into tokens
* @a: func arg 1
 * string to be broken
* @l: func arg 2
 * the expected seprator
* Return: a char ** containing the broken string
*/
char **mystrtok(char *a, char l)
{
	int i = 0, j = 0, x = 0;
	char **p = NULL;
	if (a == NULL || *a == '\0' || *a == '\n')
		return (p);
	p = malloc(ARG_MAX);
	while (a[x] != '\n' && a[x] != '\0')
	{
		if (a[x] == l)
		{
			x+=1;
			continue;
		}
		j = 0;
		p[i] = malloc(ARG_MAX);
		while (a[x] != l && a[x] != '\0' && a[x] != '\n')
		{
			p[i][j] = a[x];
			x++;
			j++;
		}
		p[i][j] = '\0';
		i++;
		x++;
	}
	p[i] = NULL;
	return (p);
}

/**
* mywrite - func name
 * a costumized write function
* @s: func arg 1
 * string to print
* Return: lengt of characters printed
*/
size_t mywrite(char *s, int fd)
{
	size_t i = 0;
	while (*s != '\0')
	{
		write(fd, s++, 1);
	}
	return (i);
}

/**
* mybuiltin - func name
 * check if a command is a built in if true the do the right thing
* @t: func arg 1
 * a char ** containing input broken into tokens
* Return: 1 if  it is a builtin command and else 0
*/
int mybuiltin(char **t, char **env)
{
	int i;
	char buff[ARG_MAX / 2];
	if (comp(t[0], "echo"))
	{
		i = 1;
		while(t[i] != NULL)
		{
			mywrite(t[i++], STDOUT_FILENO);
			write(STDOUT_FILENO, " ", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	else if(comp(t[0], "pwd"))
	{
		if (t[1] != NULL)
			write(STDERR_FILENO, "pwd: too many arguments\n", 24);
		else
		{
			getcwd(buff, ARG_MAX / 2);
			mywrite(buff, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	else if(comp(t[0], "ent"))
	{
		for(i = 0; env[i] != NULL; i++)
		{
			mywrite(env[i], STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	else
		return (0);
}

/**
* mycheck - func name
 * check if a perticular built in has the wright tag or arg
* @t: func arg 1
 * contains the command's tokens
* Return: 0 or 1
*/
int mycheck(char **t)
{
	if (comp(t[0], "exit"))
	{
		if (t[1] != NULL)
		{
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

void myitostr(unsigned int i, char *b, int *j)
{
	if (i == 0)
		return;
	myitostr(i / 10, b, j);
	b[(*j)++] = (i % 10) + '0';
}
void myerror(char **a, int b)
{
	char d[20];
	int p = 0;
	myitostr(b, d, &p);
	mywrite(a[0], STDERR_FILENO);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, d, p);
	write(STDERR_FILENO, ": ", 2);
	mywrite(a[0], STDERR_FILENO);
	if (comp(a[0], "exit"))
	{
		write(STDERR_FILENO, ": Illegal number: ", 18);
		mywrite(a[1], STDERR_FILENO);
	}
	else
		write(STDERR_FILENO, ": not found", 11);
	write(STDERR_FILENO, "\n", 1);
}

/**
* getpath - func name
 * get PATH from enviromental variable
* @e: func arg 1
 * enviromental variable
* Return: PATH (char *)
*/
char *getpath(char **e)
{
	int i;
	for (i = 0; e[i][0] != 'P' || e[i][1] != 'A' || e[i][2] != 'T' || e[i][3] != 'H'; i++)
		;
	return (e[i]);
}


/**
* myjoin - func name
 * add str b to str pointed to by a
* @a: func arg 1
 * pointer to the string to be appended
* @b: func arg 2
 * str to add to a
* Return: void
*/
void myjoin(char **a, char *b)
{
	int i, j;
	for (i = 0; (*a)[i] != '\0'; ++i)
		;
	(*a)[i++] = '/';
	for (j = 0; b[j] != '\0'; j++)
	{
		(*a)[i++] = b[j];
	}
	(*a)[i] = '\0';
}

/*char *mycopy2(char *a, char l)*/
/*{*/
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
int mypathexec(char **tok, char **a)
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
}
#endif
