#ifndef __GETCH_H_
#define __GETCH_H_

/* get a (possibly pushed back) character */
int getch();

/* push character back on input */
void ungetch(int c);

#endif
