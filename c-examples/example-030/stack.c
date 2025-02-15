#include <stdio.h>

#define MAXSTACK	(100)		/* maximum depth of val stack */

int sp = 0;						/* next free stack position */
double stack[MAXSTACK];			/* value stack */

/* push: push f onto the value stack */
void push(double f)
{
	if (sp < MAXSTACK)
		stack[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop()
{
	if (sp > 0)
		return stack[--sp];

	printf("error: stack empty\n");
	return 0.0;
}
