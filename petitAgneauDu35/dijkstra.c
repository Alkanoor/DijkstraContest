#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define INT_MAX 10000

typedef struct Node {
	int accessible;
	int A;
	int distance;
	int x;
	int y;
	struct Node* pere;
} Node;

typedef struct Point {
	int x;
	int y;
 } Point;

typedef struct Obstacle {
	int xPos;
	int yPos;
	int halfWidth;
	int halfHeight;
	int angle;
	Point topLeft;
	Point topRight;
	Point bottomLeft;
	Point bottomRight;
} Obstacle;


Node* nextPivot(Node* map[], int xMax, int yMax);
void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle);

int main(int argc, char* argv[]) {
	if (argc != 1) {
		printf("Syntax : %s\n", argv[0]);
		return 1;
	}
	int xMax, yMax, radius, xStart, yStart, xStop, yStop;

	scanf("%i[ \n]", &xMax);
	scanf("%i[ \n]", &yMax);
	scanf("%i[ \n]", &radius);
	scanf("%i[ \n]", &xStart);
	scanf("%i[ \n]", &yStart);
	scanf("%i[ \n]", &xStop);
	scanf("%i[ \n]", &yStop);
	//printf("%i %i %i %i %i %i %i\n", xMax, yMax, radius, xStart, yStart, xStop, yStop);

	//Recuperation des coordonnees des obstacles
	int nbObstacles = 0;
	Obstacle* obstacles = NULL;
	int xPos, yPos, halfWidth, halfHeight, angle;
	while(scanf("%i[ \n]", &xPos) != EOF) {
		if (feof(stdin))
			break;
		//Allocate space for a new obstacle
		obstacles = (Obstacle*)realloc(obstacles, (nbObstacles + 1) * sizeof(Obstacle));
		//Fill the data about the obstacle
		scanf("%i[ \n]", &halfWidth);
		scanf("%i[ \n]", &yPos);
		scanf("%i[ \n]", &halfHeight);
		scanf("%i", &.angle);
		init_obstacle(&obstacles[nbObstacles], xPos, yPos, halfWidth, halfHeight, angle);
		nbObstacles++;
	}
	
	Node* map[xMax * yMax];
	for (int i = 0; i < xMax; i++) {
		for (int j = 0; j < yMax; j++) {
			map[i * yMax + j] = (Node*)malloc(sizeof(Node));
			map[i * yMax + j]->accessible = 1;
			map[i * yMax + j]->A = 0;
			map[i * yMax + j]->distance = INT_MAX;
			map[i * yMax + j]->x = i;
			map[i * yMax + j]->y = j;
			map[i * yMax + j]->pere = map[i * yMax + j];
		}
	}
	//Initialisation du pivot initial (point de depart)
	map[xStart * yMax + yStart]->A = 1;
	map[xStart * yMax + yStart]->distance = 0;
	//TO DO : inclure les obstacles dans le tableau

	Node* pivot = map[xStart * yMax + yStart];
	int x, y;
	Node* cur;
	for (int i = 0; i < xMax * yMax - 1; i++) {
		//Pour l'ensemble des voisins de pivot
		for(int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				//Sans compter le pivot evidemment
				if (i != 0 || j != 0) {
					x = pivot->x + j;
					y = pivot->y + k;
					//printf("x = %i, y = %i\n", x, y);
					if (x >= 0 && x < xMax && y >= 0 && y < yMax) {
						cur = map[x * yMax + y];
						if(pivot->distance + 1 < cur->distance) {
							cur->distance = pivot->distance + 1;
							cur->pere = pivot;
						}
					}
				}
			}
		}
		pivot = nextPivot(map, xMax, yMax);
		pivot->A = 1;
	}
	
	//Recuperation du nombre de noeuds sur le chemin
	x = xStop;
	y = yStop;
	Node* pere;
	int nb = 1;
	while(x != xStart || y != yStart) {
		pere = map[x * yMax + y]->pere;
		x = pere->x;
		y = pere->y;
		nb++;
	}
	//Recuperation des coordonnees successives des noeuds sur le chemin
	x = xStop;
	y = yStop;
	int cnt = nb;
	int path[2 * nb];
	while (x != xStart || y != yStart) {
		path[2 * cnt - 1] = y;
		path[2 * cnt - 2] = x;
		pere = map[x * yMax + y]->pere;
		x = pere->x;
		y = pere->y;
		cnt--;
	}
	path[0] = xStart;
	path[1] = yStart;

	//Affichage du chemin
	for (int i = 0; i < 2* nb; i++) {
		printf("%i ", path[i]);
	}
	return 0;
}

Node* nextPivot(Node* map[], int xMax, int yMax) {
	//return the next pivot
	Node* pivot = (Node*)malloc(sizeof(Node));
	int freeMemory = 0;
	pivot->distance = INT_MAX;
	for (int i = 0; i < xMax * yMax; i++) {
		if(map[i]->A == 0 && map[i]->distance < pivot->distance) {
			if (!freeMemory) {
				//Release the memory allocated at the beginning
				free(pivot);
				freeMemory = 1;
			}
			pivot = map[i];
		}
	}
	return pivot;
}

int dcos (int angle) {
	return cos(angle * PI / 180);
}

int dsin (int angle) {
	return sin(angle * PI / 180):
}

void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle) {
	obstacle->xPos = xPos;
	obstacle->yPos = yPos;
	obstacle->halfWidth = halfWidth;
	obstacle->halfHeight = halfHeight;
	obstacle->angle = angle;
	Point corner;
	int radius = 0:
	int margin = 0;
	//Top Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) - radius - margin;
	corner.y = yPos + (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) + radius + margin;
	obstacle->topLeft = corner;
	//Top Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) + radius + margin;
	corner.y = yPos + (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) + radius + margin;
	obstacle->topRight = corner;
	//Bottom Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) + radius + margin;
	corner.y = yPos - (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) - radius - margin;
	obstacle->bottomRight = corner;
	//Bottom Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) - radius - margin;
	corner.y = yPos - (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) - radius - margin;
	obstacle->bottomLeft = corner;
}
