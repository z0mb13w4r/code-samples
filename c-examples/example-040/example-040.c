#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN			(100)
#define MAXBUFFER			(1000)

enum { NAME, PARENS, BRACKETS };

int tokentype;								/* type of last token */
char token[MAXTOKEN];						/* last token string */
char name[MAXTOKEN];						/* identifier name */
char datatype[MAXTOKEN];					/* data type = char, int, etc. */
char out[MAXBUFFER];						/* output string */

/* dirdcl: parse a direct declarator */
void dirdcl(void);

/* dcl: parse a declarator */
void dcl(void);

/* return next token */
int gettoken(void)
{
	int c;
	char* p = token;

	while ((c = _getch()) == ' ' || c == '\t')
		;
	_putch(c);
	if (c == '(') {
		if ((c = _getch()) == ')') {
			_putch(c);
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			_ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = _getch()) != ']'; )
			;
		_putch(*(p - 1));
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = _getch()); ) {
			*p++ = c;
			_putch(c);
		}
		*p = '\0';
		_ungetch(c);
		return tokentype = NAME;
	}
	return tokentype = c;
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;

	if (tokentype == '(') {					/* ( dcl ) */
		dcl();
		if (tokentype != ')')
			printf("\nerror: missing )\n");
	} else if (tokentype == NAME)			/* variable name */
		strcpy(name, token);
	else
		printf("\nerror: expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )		/* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* convert declaration to words */
main()
{
	while (gettoken() != EOF) {		/* 1st token on line */
		strcpy(datatype, token);	/* is the datatype */
		out[0] = '\0';
		dcl();						/* parse rest of line */
		if (tokentype != '\n' && tokentype != ')')
			printf("\nsyntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
