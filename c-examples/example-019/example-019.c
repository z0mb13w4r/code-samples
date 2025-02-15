#include <stdio.h>

/* _strcat: contactenate t to end of s; s must be big enough */
void _strcat(char s[], char t[])
{
	int i, j;

	i = j = 0;
	while (s[i] != '\0')	/* find end of s */
		i++;

	while ((s[i++] = t[j ++]) != '\0')	/* copy t */
		;
}

main()
{
	char string1[100] = "http://";
	char string2[] = "kylewickens.blogspot.co.uk/";

	printf("%s\n", string1);
	printf("%s\n", string2);
	_strcat(string1, string2);
	printf("%s\n", string1);

	return 0;
}
