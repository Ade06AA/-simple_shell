#include "main.h"

/**
* myitostr - func name
* @i: func arg 1
* @b: func arg 2
* @j: func arg 3
* Return: void
*/
void myitostr(unsigned int i, char *b, int *j)
{
	if (i == 0)
		return;
	myitostr(i / 10, b, j);
	b[(*j)++] = (i % 10) + '0';
}

/**
* mystrtoi - func arg 1
* @s: func arg 1
* @i: func arg 2
* @j: func arg 3
* Return: void
*/
void mystrtoi(char *s, int *i, int *j)
{
	int h;

	if (s[0] == '\0')
		return;
	for (h = 0; s[h] != '\0'; h++)
		;
	*i += (s[h - 1] - '0') * *j;
	*j = (*j * 10);
	s[h - 1] = '\0';
	mystrtoi(s, i, j);
}
