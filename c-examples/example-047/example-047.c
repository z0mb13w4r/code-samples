#include <stdio.h>
#include <string.h>

#define MAXLINE			(100)

/* fgets: get at most n chars from iop */
char* _fgets(char* s, int n, FILE* iop)
{
	register int c;
	register char* cs;

	cs = s;
	while (--n > 0 && (c = getc(iop)) != EOF)
		if ((*cs++ = c) == '\n')
			break;
	*cs = '\0';
	return (c == EOF && cs == s) ? NULL : s;
}

/* fputs: put string s on file iop */
int _fputs(char* s, FILE* iop)
{
	int c;

	while (c = *s++)
		putc(c, iop);
	return ferror(iop) ? EOF : 0;
}

/* getline: read a line, return length */
int getline(char* line, int max)
{
	if (_fgets(line, max, stdin) == NULL)
		return 0;
	return strlen(line);
}

main()
{
	double sum;
	char line[MAXLINE];

	sum = 0;
	while (getline(line, MAXLINE) > 0)
		_fputs(line, stdout);

	return 0;
}