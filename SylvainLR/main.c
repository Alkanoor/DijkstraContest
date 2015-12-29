#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])  {
    if (argc < 2) {
        return 1;
    }
	int xStart = atoi(argv[4]);
	int yStart = atoi(argv[5]);
	int xStop = atoi(argv[6]);
	int yStop = atoi(argv[7]);
    printf("%i %i", (xStart + xStop)/2, (yStart + yStop)/2);
    return 0;
}
