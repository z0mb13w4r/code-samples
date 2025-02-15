/* shellsort: sort v[0]...v[n - 1] into increasing order */

#define COUNTOF(x)	(sizeof(x) / sizeof(x[0]))

void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
			}
}

main()
{
	int v[] = { 3, 54, 523, 2, 56, 12, 88, 9, 2 };
	shellsort(v, COUNTOF(v));
	return 0;
}
