#include <stdio.h>

#define min(x, y)		((x) < (y) ? (x) : (y))
#define max(x, y)		((x) > (y) ? (x) : (y))

struct point {
	int x;
	int y;
};

struct rect {
	struct point pt1;
	struct point pt2;
};

/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
	struct point temp;

	temp.x = x;
	temp.y = y;
	return temp;
}

/* makerect: make a rect from x1, x2, y1 and y2 components */
struct rect makerect(int x1, int x2, int y1, int y2)
{
	struct rect temp;

	temp.pt1 = makepoint(x1, y1);
	temp.pt2 = makepoint(x2, y2);
	return temp;
}

/* addpoint: add two points */
struct point addpoint(struct point p1, struct point p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
	return p.x >= r.pt1.x && p.x < r.pt2.x
		&& p.y >= r.pt1.y && p.y < r.pt2.y;
}

/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r)
{
	struct rect temp;

	temp.pt1.x = min(r.pt1.x, r.pt2.x);
	temp.pt1.y = min(r.pt1.y, r.pt2.y);
	temp.pt2.x = max(r.pt1.x, r.pt2.x);
	temp.pt2.y = max(r.pt1.y, r.pt2.y);
	return temp;
}

main()
{
	struct rect r1 = makerect(0, 100, 200, 300);
	struct rect r2 = makerect(50, 150, 100, 200);
	struct point p1 = makepoint(25, 250);
	struct point p2 = makepoint(35, 45);
	struct point p3 = addpoint(p1, p2);

	struct rect r3 = canonrect(r1);

	printf("addpoint: %d, %d\n", p3.x, p3.y);
	printf("canonrect: %d, %d, %d, %d\n", r3.pt1.x, r3.pt1.y, r3.pt2.x, r3.pt2.y);
	printf("ptinrect: %d\n", ptinrect(p1, r1));
}
