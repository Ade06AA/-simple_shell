#include "main.h"


/**
* isnspace - func name
* @b: func arg 1
* Return: int
*/
int isnspace(char *b)
{
	int i;

	while (b[i] != '\0' && b[i] != '\n')
	{
		if (b[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

/**
* myisnum - func name
 *  chaeck if a string is a number
* @s: func name
 * str name
* Return: 1 if it is a num else 0
*/
int myisnum(char *s)
{
	int i;

	for (i = 0; (s[i] >= '0') && (s[i] <= '9'); i++)
		if (s[i + 1] == '\0')
			return (1);
	return (0);
}


/**
* myerror - func name
* @a: func arg 1
* @b: func arg 2
* Return: void
*/
void myerror(char **a, int b, char *av1)
{
	char d[20];
	int p = 0;

	myitostr(b, d, &p);
	mywrite(av1, STDERR_FILENO);
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


