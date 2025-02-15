#include <stdio.h>

void doWhileLoop(void) {

	int x = 99;
	while (x > 0) {
		printf("%d\n", x);
		x--;
	}
}

int main() {

	size_t i;

	for (i = 0; i < 10; i++) {
		printf("%d\n", i);
	}

	doWhileLoop();

	return 0;
}
