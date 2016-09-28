#include "utils.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#define WIDTH 200
#define LENGTH 300
#define MARGIN 0

static int fd;
static int map[WIDTH * LENGTH];
static Obstacle obstacle;
static int halfWidth, xPos, yPos, halfHeight, angle, ret;

void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle);
void set_obstacle(int map[], Obstacle* obstacle, int xMax, int yMax);
int isInside(int index, Obstacle* obstacle);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return -1;
    }

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRWXU);
    if (fd == -1) {
        printf("Error when opening file %s\n", argv[1]);
        return -2;
    }

    //Initialization of the map
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			map[i * LENGTH + j] = 1; // By default, each point can be reached.
		}
	}

    while(scanf("%i[ \n]", &xPos) != EOF) {
		if (feof(stdin))
			break;
		//Fill the data about the obstacle
		ret = 0;
		ret += scanf("%i[ \n]", &halfWidth);
		ret += scanf("%i[ \n]", &yPos);
		ret += scanf("%i[ \n]", &halfHeight);
		ret += scanf("%i", &angle);
		if (ret != 4)
			break;
		init_obstacle(&obstacle, xPos, yPos, halfWidth, halfHeight, angle);
		set_obstacle(map, &obstacle, WIDTH, LENGTH);
	}

    for (int i = 0; i < WIDTH * LENGTH; i++) {
        ret = write(fd, &map[i], sizeof(int));
    }
    return 0;
}


void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle) {
	obstacle->xPos = xPos;
	obstacle->yPos = yPos;
	obstacle->halfWidth = halfWidth;
	obstacle->halfHeight = halfHeight;
	obstacle->angle = angle;
	Point corner;
	//Top Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) - MARGIN;
	corner.y = yPos + (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) + MARGIN;
	obstacle->corners[0] = corner;
	//Top Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) + MARGIN;
	corner.y = yPos + (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) + MARGIN;
	obstacle->corners[1] = corner;
	//Bottom Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) + MARGIN;
	corner.y = yPos - (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) - MARGIN;
	obstacle->corners[2] = corner;
	//Bottom Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) - MARGIN;
	corner.y = yPos - (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) - MARGIN;
	obstacle->corners[3] = corner;
}

void set_obstacle(int map[], Obstacle* obstacle, int xMax, int yMax) {
	//Test uniquement les points qui ont une chance d'etre dans l'obstacle
	int half_diag = sqrt(obstacle->halfWidth * obstacle->halfWidth + obstacle->halfHeight * obstacle->halfHeight) + 2 * MARGIN;
	for (int i = max(0, obstacle->xPos - half_diag); i < min (xMax, obstacle->xPos + half_diag); i++) {
		for (int j = max(0, obstacle->yPos - half_diag); j < min (yMax, obstacle->yPos + half_diag); j++) {
			if(isInside(i * LENGTH + j, obstacle)) {
				//printf("map[%i][%i] obstacle\n", i, j);
				map[i * LENGTH + j] = 0;
			}
		}
	}
}

int isInside(int index, Obstacle* obstacle) {
    Point point;
    point.x = index % LENGTH;
    point.y = index / LENGTH;
	int signe = signof(determinant(point, obstacle->corners[0], obstacle->corners[1]));
	for (int i = 1; i < 4; i++) {
		if(signe != signof(determinant(point, obstacle->corners[i], obstacle->corners[(i + 1) % 4]))) {
			return 0;
		}
	}
	return 1;
}
