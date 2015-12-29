#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
#include "point.h"

void path(int xStart, int yStart, int xStop, int yStop, int nbObstacles, Obstacle obstacles[]);

int main(int argc, char* argv[])  {
    if (argc < 2) {
        return 1;
    }
	int xStart = atoi(argv[4]);
	int yStart = atoi(argv[5]);
	int xStop = atoi(argv[6]);
	int yStop = atoi(argv[7]);
    printf("%i %i\n", (xStart + xStop)/2, (yStart + yStop)/2);
    return 0;
}

void path(int xStart, int yStart, int xStop, int yStop, int nbObstacles, Obstacle obstacles[]) {
	for (int i = 0; i < nbObstacles; i++) {
		Obstacle o = obstacles[i];
		Point out[4] {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
		o.getCorners(out);
		for (int j = 0; j < 4; j++)
		{
			Point c = out[j];
			if ((xStart < c.x && xStop > c.x) || (xStop < c.x && xStart > c.x)) {
				if ((yStart < c.y && yStop > c.y) || (yStop < c.x && yStart > c.y)) {
					path(xStart, yStart, c.x, c.y, nbObstacles, obstacles);
					path(c.x, c.y, xStop, yStop, nbObstacles, obstacles);
				}
			}
		}
	}
	printf("%i %i", xStop, yStop);
}
