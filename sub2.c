#include "main.h"


/**
* mywrite - func name
* @s: func arg 1
* @fd: func arg2
* Return: size_t
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
* @env: func arg 2
* Return: 1 if  it is a builtin command and else 0
*/
int mybuiltin(char **t, char **env)
{
	int i;
	char buff[ARG_MAX / 2];

	if (comp(t[0], "echo"))
	{
		i = 1;
		while (t[i] != NULL)
		{
			mywrite(t[i++], STDOUT_FILENO);
			write(STDOUT_FILENO, " ", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	else if (comp(t[0], "pwd"))
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
	else if (comp(t[0], "env"))
	{
		for (i = 0; env[i] != NULL; i++)
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


