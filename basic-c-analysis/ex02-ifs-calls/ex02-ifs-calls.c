#include <stdio.h>

int global1 = 255;
int global2;

int main() {
	global2 = 128;
	int local = 17;
	printf("hello, world");
	scanf("%d", &global1);

	if (global1 > 0 && global1 < 72) {
		printf("Good Value");
		local = 23;
	} else {
		printf("Bad choice");
		local = 29;
	}

	puts("");
	printf("Local = %d Global%d", local, global1);
	puts("");
	return 0;
}
