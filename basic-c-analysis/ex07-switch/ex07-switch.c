#include <stdio.h>

void largeSwitch(void) {

	int i = 3;

	switch (i) {
	case 0:
		puts("You entered 0");
		break;
	case 1:
		puts("You entered 1");
		break;
	case 2:
		puts("You entered 2");
		break;
	case 3:
		puts("You entered 3");
		break;
	default:
		puts("I guess I don't care what you entered!");
		break;
	}
}

int main() {
	int i = 0;

	puts("Enter a value:");
	scanf("%d", &i);

	switch (i) {
	case 0:
		puts("You entered 0");
		break;
	case 1:
		puts("You entered 1");
		break;
	case 2:
		puts("You entered 2");
		break;
	}

	largeSwitch();

	return 0;
}
