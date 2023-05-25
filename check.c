#include "main.h"

/**
* mycheck2 - func name
 * imppliment #
* @tokens: func arg 1
* Return: void
*/
void mycheck2(char **tokens)
{
	int i, j, f;

	if (tokens != NULL)
	{
		for (j = 0; tokens[j] != NULL; j++)
		{
			if (comp(tokens[j], "#"))
			{
				f = j;
				break;
			}
		}
		for (i = f; i < j; i++)
		{
			if (tokens[i] != NULL)
			{
				free(tokens[i]);
				tokens[i] = NULL;
			}
		}
		tokens[f] = NULL;
	}
}
