#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv, char** envp) {
    int *x = (int*)malloc(10 * sizeof(int));
    char *y = (char*)malloc(107);
    short* z = (short*)malloc(2 * sizeof(short));

    *x = 125;
    *y = '!';
    *z = 34;
}
