#include <ctype.h>
#include <stdio.h>
#include "getch.h"

/* getint: get next integer from input into *pn */
int getint(int* pn)
{
	int c, sign;

	while (isspace(c = getch()))		/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);		/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

main()
{
	int n;
	int i = getint(&n);
}
