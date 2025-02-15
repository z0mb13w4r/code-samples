#ifndef __CALC_H_
#define __CALC_H_

#define NUMBER		'0'			/* signal that a number was found */

/* push: push f onto the value stack */
void push(double f);

/* pop: pop and return top value from stack */
double pop();

/* getop: get next operator or numeric operand */
int getop(char s[]);

/* get a (possibly pushed back) character */
int getch();

/* push character back on input */
void ungetch(int c);

#endif
