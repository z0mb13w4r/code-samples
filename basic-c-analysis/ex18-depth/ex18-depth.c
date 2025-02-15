#include <stdio.h>

void depth_2_1() {
	printf("inside depth_2_1\n");
}

void depth_2_2() {
	printf("inside depth_2_2\n");
}

void depth_1() {
	depth_2_1();
	depth_2_2();
	printf("inside depth_1\n");
}

int main(void) {
	depth_1();
}
