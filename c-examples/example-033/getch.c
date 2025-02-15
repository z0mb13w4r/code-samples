#include <stdio.h>

#define MAXSTACK	(100)		/* maximum depth of val stack */

char buff[MAXSTACK];			/* buffer for ungetch */
int  bufp = 0;					/* next free position in buff */

/* get a (possibly pushed back) character */
int getch()
{
	return (bufp > 0) ? buff[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
	if (bufp >= MAXSTACK)
		printf("ungetch: too many characters\n");
	else
		buff[bufp++] = c;
}
