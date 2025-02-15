#include <stdio.h>

#define COUNTOF(x)	(sizeof(x) / sizeof(x[0]))

/* binsearch: find x in v[0] <= v[1] <= ... <=[n - 1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else	/* found match */
			return mid;
	}
	return -1; /* no match */
}

main()
{
	int v[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("%d\n", binsearch(3, v, COUNTOF(v)));
	printf("%d\n", binsearch(8, v, COUNTOF(v)));
	printf("%d\n", binsearch(100, v, COUNTOF(v)));
	return 0;
}
