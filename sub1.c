#include "main.h"

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
	if ((terminal_input[i] == '\0' || terminal_input[i] == '\n') && b[i] == '\0')
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
void mycopy(char **a, char *b, int h)
{
	int i;
	h = 0;
	(*a) = malloc(ARG_MAX);
	for (i = 0; b[i] != '\n' && b[i] != '\0'; h++, i++)
		(*a)[i] = b[i];
	(*a)[i] = '\0';
}


/**
* myfree - func name
 * free a pointer to pointer and its content
* @p: fuinc arg 1
 * number of sub pointer too be freed
* Return: void
*/
void myfree(char **p)
{
	int i = 0;

	if (p != NULL)
	{
		while (p[i] != NULL)
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
			x += 1;
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

