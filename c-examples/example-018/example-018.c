#include <stdio.h>

/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];

	s[j] = '\0';
}

main()
{
	char string[] = "http://kylewickens.blogspot.co.uk/";

	printf("%s\n", string);
	squeeze(string, 'o');
	printf("%s\n", string);
	squeeze(string, 't');
	printf("%s\n", string);
	squeeze(string, 'k');
	printf("%s\n", string);
	squeeze(string, 'p');
	printf("%s\n", string);
	squeeze(string, 'l');
	printf("%s\n", string);

	return 0;
}
