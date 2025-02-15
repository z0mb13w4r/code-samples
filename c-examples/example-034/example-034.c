#include <string.h>

#define ALLOCSIZE		(10000)		/* size of available space */

static char allocbuf[ALLOCSIZE];	/* storage for alloc */
static char* allocp = allocbuf;		/* next free position */

/* _alloc: return positer to n characters */
char* _alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {	/* it fits */
		allocp += n;
		return allocp - n;		/* old p */
	}
	else	/* not enough room */
		return 0;
}

/* _free: free storage pointed to by p */
void _free(char* p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/* _strlen: return length of string */
int _strlen(char* s)
{
	char* p = s;

	while (*p != '\0')
		p++;
	return p - s;
}

/* _strcpy1: copy t to s; pointer version 1 */
char *_strcpy1(char* s, char* t)
{
	char* p = s;

	while (*t != '\0')
		*p++ = *t++;
	return s;
}

/* _strcpy2: copy t to s; pointer version 2 */
char* _strcpy2(char* s, char* t)
{
	char* p = s;

	while ((*p++ = *t++) != '\0')
		;
	return s;
}

/* _strcpy3: copy t to s; pointer version 3 */
char* _strcpy3(char* s, char* t)
{
	char* p = s;

	while (*p++ = *t++)
		;
	return s;
}

main()
{
	char* x = _alloc(123);
	char* y = _alloc(234);
	char* z = _alloc(345);
	_strcpy1(x, "Hello World!");
	_strcpy2(y, "George of the Jungle!");
	_strcpy3(z, "Watch out for that tree!");
	int l = _strlen(x);
	_free(z);
	_free(y);
	_free(x);
}
