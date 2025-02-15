#include <stdio.h>

enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

/* _strlen: return length of s */
int _strlen(char s[])
{
	int i = 0;

	i = 0;

	while (s[i] != '\0')
		++i;

	return i;
}

/* atoi: converts s to integer */
int atoi(char s[])
{
	int i, n;

	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10 * n + (s[i] - '0');

	return n;
}

/* lower: convert c to lower case: ASCII only */
int lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}

main()
{
	printf("atoi = %d\n", atoi("123456789"));
	printf("strlen = %d\n", _strlen("http://kylewickens.blogspot.co.uk"));
	printf("lower = %c\n", lower('Y'));

	return 0;
}
