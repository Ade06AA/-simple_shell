#include "main.h"
/*   costomized function located in main */
/* -------------------------------------- */
/* check the file manual for easy navigation on the costomized functions */
/* -------------------------------------- */



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

	for (i = 0; e[i][0] != 'P' || e[i][1] != 'A'; i++)
	{
		if (e[i][2] != 'T' || e[i][3] != 'H')
			continue;
		else
			break;
	}
	return (e[i]);
}



/**
* myexec - func name
 * execute comands if given full path
* @tokens: func arg 1
 * token of comand
* @buff: func arg 2
* Return: void
*/
void myexec(char **tokens, char *buff)
{
	int j;

	j = fork();
	if (j == 0)
	{
		execve(tokens[0], tokens, NULL);
		exit(1);
	}
	else
	{
		wait(NULL);
		fr(buff, tokens);
	}
}



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
	int i, j = 0;
	char **to;
	char *path = NULL;

	path = getpath(a);
	for (i = 0; path[i] != '='; ++i)
		;
	i++;
	to = mystrtok(path + i, ':');
	for (i = 0; to[i] != NULL && (to[i][0] != 'P' && to[i][2] != 'O'); i++)
	{
		myjoin(&to[i], tok[0]);
		if (!(access(to[i], F_OK)))
		{
			j = fork();
			if (j == 0)
			{
				execve(to[i], tok, NULL);
				return (0);
			}
			else
			{
				wait(NULL);
				myfree(to);
				free(tok[i]);
				return (1);
			}
		}
	}
	myfree(to);
	free(tok[i]);
	return (0);
}

/**
* mygetinput - func name
* @b: func arg 1
 * buffer to store input
* @t: func arg 2
* @l: func arg 3
* Return: void
*/
size_t mygetinput(char **b, int t, size_t *l)
{
	size_t i;

	if (t)
	{
		i = getline(b, l, stdin);
		if (i == -1)
		{
			free(*b);
			write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
	}
	else
	{
		i = read(STDIN_FILENO, *b, ARG_MAX);
		if (i == -1 || i == 0)
		{
			free(*b);
			exit(0);
		}
	}
	return (i);
}

/**
* main - func name
 * the main function
 * the whole program tries to impliment a typical shell
* @argc: func arg 1
* @argv: func arg 2
* @envp: func arg 3
 * enviromental variable
* Return: 0 if no problem was encounterd
*/
int main(int argc, char **argv, char **envp)
{
	int i, interractive, loopc = 0, temp1 = 0, temp2 = 1;
	char *buff;
	char **tokens;
	size_t len = 0;

	interractive = isatty(STDIN_FILENO);
	while (true)
	{
		++loopc;
		prompt(interractive);
		buff = malloc(ARG_MAX);
		i = mygetinput(&buff, interractive, &len);
		if (i == 1)
		{
			free(buff);
			continue;
		}
		buff[i - 1] = '\0';
		tokens = mystrtok(buff, ' ');
		if (myexit2(tokens, buff, loopc, &temp1, &temp2))
			continue;
		if (mybuiltin(tokens, envp))
		{
			fr(buff, tokens);
			continue;
		}
		if (mypathexec(tokens, envp))
		{
			fr(buff, tokens);
			continue;
		}
		if (access(tokens[0], F_OK))
		{
			myerror(tokens, loopc);
			fr(buff, tokens);
		}
		else
			myexec(tokens, buff);
	}
	return (0);
}
