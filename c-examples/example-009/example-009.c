#include <stdio.h>

/* count characters in input; 2st version */
main()
{
	long nc;

	nc = 0;
	for (nc = 0; getchar() != EOF; ++nc)
		;

	printf("%1d\n", nc);
}
