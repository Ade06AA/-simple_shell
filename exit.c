#include "main.h"

/**
* prompt - func name
* @i: func arg 1
 * for cheking if it is intaractive or not
* Return: void
*/
void prompt(int i)
{
	if (i)
	{
	write(STDOUT_FILENO, "┌─😑shell(•‿•)\n", 27);
	write(STDOUT_FILENO, "└─($)", 9);
	}
}

/**
* myexit2 - func name
* @tokens: func arg 1
* @buff: func arg 2
* @loopc: func arg 3
* @temp1: func arg 4
* @temp2: func arg 5
* Return: int
*/
int myexit2(char **tokens, char *buff, int loopc, int *temp1, int *temp2)
{
	if (comp(tokens[0], "exit"))
	{
		if (mycheck(tokens))
		{
			fr(buff, tokens);
			exit(0);
		}
		else
		{
			if (myisnum(tokens[1]))
			{
				mystrtoi(tokens[1], temp1, temp2);
				fr(buff, tokens);
				exit(*temp1);
			}
			myerror(tokens, loopc);
			fr(buff, tokens);
			return (1);
		}
	}
	return (0);
}
