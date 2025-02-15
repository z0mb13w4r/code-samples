#include <stdio.h>
#include <string.h>

/* reverse: reverse string s in place */
char* reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}

	return s;
}

/* itoa: convert n to characters in a */
char* itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)			/* record sign. */
		n = -n;					/* make n positive */
	i = 0;
	do {						/* generate digits in reverse order */
		s[i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);		/* delete it */

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	return reverse(s);
}

main()
{
	char s[100];
	printf("%s\n", itoa(1, s));
	printf("%s\n", itoa(100, s));
	printf("%s\n", itoa(-200, s));
	return 0;
}
