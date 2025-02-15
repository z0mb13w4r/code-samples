#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES		(5000)		/* max #lines to be sorted */
char* lineptr[MAXLINES];			/* pointers to text lines */

#define MAXLEN			(1000)		/* max length of any input line */

/* numcmp: compare s1 and s2 numerically */
int numcmp(char* s1, char* s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 < v2)
		return 1;
	return 0;
}

/* swap: interchange v[i] and v[j] */
void _swap(void* v[], int i, int j)
{
	void* temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* qsort: sort v[left]...v[right] into increasing order */
void _qsort(void* v[], int left, int right, int (*comp)(void*, void*))
{
	int i, last;

	if (left >= right)				/* do nothing if array contains */
		return;						/* fewer than two elements */
	_swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			_swap(v, ++last, i);
	_swap(v, left, last);
	_qsort(v, left, last - 1, comp);
	_qsort(v, last + 1, right, comp);
}

/* writelines: write output lines */
void writelines(char* lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* readlines: read input lines */
int readlines(char* lineptr[], int maxlines)
{
	int len, nlines;
	char* p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 1)
		if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';			/* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* sort input lines */
main(int argc, char* argv[])
{
	int nlines;				/* number of input lines read */
	int numeric = 0;		/* 1 if numeric sort */

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		_qsort((void**)lineptr, 0, nlines - 1, (int (*)(void*, void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	}

	printf("input: too big to sort\n");
	return 1;
}
