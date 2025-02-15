#include <stdio.h>

int main() {

	struct {
		int x;
		int y;
		int z;
	} v;

	v.x = 10;
	v.y = 20;
	v.z = 30;

	printf("%d %d %d\n", v.x, v.y, v.z);
	return 0;
}
