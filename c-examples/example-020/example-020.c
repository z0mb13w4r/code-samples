#include <stdio.h>

#define OFFSET(p, n)	((p) + 1 - (n))

/* getbits: get n bits from postion p */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> OFFSET(p, n)) & ~(~0 << n);
}

/* setbits: set n bits from position p */
unsigned setbits(unsigned x, int p, int n, int y)
{
	return (x & ~(getbits(~0, p, n) << OFFSET(p,n))) | (getbits(y, n - 1, n) << OFFSET(p, n));
}

/* invert: invert n bits from position p */
unsigned invert(unsigned x, int p, int n)
{
	return x ^ (getbits(~0, p, n) << OFFSET(p, n));
}

/* rotl: rotate left by n bit positions */
unsigned rotl(unsigned x, int n)
{
	return (x << n) | (x >> (sizeof(x) * 8 - n));
}

/* rotr: rotate right by n bit positions */
unsigned rotr(unsigned x, int n)
{
	return (x >> n) | (x << (sizeof(x) * 8 - n));
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x >>= 1)
		if (x & 1)
			b++;
	return b;
}

/* max: maximum of a and b */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

main()
{
	unsigned x = 0x12345678;
	printf("%08x\n", x);
	printf("%08x\n", getbits(x, 15, 8));
	printf("%08x\n", setbits(x, 15, 8, 0x18));
	printf("%08x\n", invert(x, 15, 8));
	printf("%08x\n", rotl(x, 8));
	printf("%08x\n", rotr(x, 8));
	printf("%d\n", bitcount(x));
	printf("%d\n", max(6, 8));
	return 0;
}
