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
	Point corners[4];
} Obstacle;


Node* nextPivot(Node* map[], int xMax, int yMax);
void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle);
void set_obstacle(Node* map[], Obstacle* obstacle, int xMax, int yMax);
int intersect(Point start, Node* stop, Obstacle* o);


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
		scanf("%i", &angle);
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

	for(int i = 0; i < nbObstacles; i++) {
		set_obstacle(map, &obstacles[i], xMax, yMax);
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
					if (x >= 0 && x < xMax && y >= 0 && y < yMax && map[x * yMax + y]->accessible) {
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
	return sin(angle * PI / 180);
}

int max(int a, int b) {
	if (a < b)
		return b;
	return a;
}

int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle) {
	obstacle->xPos = xPos;
	obstacle->yPos = yPos;
	obstacle->halfWidth = halfWidth;
	obstacle->halfHeight = halfHeight;
	obstacle->angle = angle;
	Point corner;
	int radius = 0;
	int margin = 0;
	//Top Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) - radius - margin;
	corner.y = yPos + (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) + radius + margin;
	obstacle->corners[0] = corner;
	//Top Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) + radius + margin;
	corner.y = yPos + (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) + radius + margin;
	obstacle->corners[1] = corner;
	//Bottom Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) + radius + margin;
	corner.y = yPos - (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) - radius - margin;
	obstacle->corners[2] = corner;
	//Bottom Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) - radius - margin;
	corner.y = yPos - (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) - radius - margin;
	obstacle->corners[3] = corner;
}

void set_obstacle(Node* map[], Obstacle* obstacle, int xMax, int yMax) {
	//Test uniquement les points qui ont une chance d'etre dans l'obstacle
	int half_diag = sqrt(obstacle->halfWidth * obstacle->halfWidth + obstacle->halfHeight * obstacle->halfHeight);
	Point origine = {0, 0};
	for (int i = max(0, obstacle->xPos - half_diag); i < min (xMax, obstacle->xPos + half_diag); i++) {
		for (int j = max(0, obstacle->yPos - half_diag); j < min (yMax, obstacle->yPos + half_diag); j++) {
			if(intersect(origine, map[i * yMax + j], obstacle) % 2) {
				//Nombre impair d'intersection -> point à l'intérieur
				map[i * yMax + j]->accessible = 0;
			}
		}
	}
}

/*
 * return 0 : pas d'intersection
 * return 1-4 : intersection
 * return 5 : erreur
 */

int intersect(Point start, Node* stop, Obstacle* o) {
	//Droite start-stop : a1 X + b1 = Y
	int intersection = 0;
	if (start.x != stop->x) {
		float a1 = (start.y - stop->y) / (start.x - stop->x);
		float b1 = start.y - a1 * start.x;
		for (int i = 0; i < 4; i++) {
		    Point c1 = o->corners[i%4];
		    Point c2 = o->corners[(i+1)%4];
			//printf("i = %i\n", i);
		    if (c1.x != c2.x) {
				/*printf("c1 ");
				c1.print();
				printf("c2 ");
				c2.print();*/
			    float a2 = (c1.y - c2.y) / (c1.x - c2.x);
			    if (a1 != a2) {
				    float b2 = c1.y - a2 * c1.x;
				    float x = (b2 - b1) / (a1 - a2);
					//printf("x = %f\n", x);
					/*printf("start ");
					start.print();
					printf("stop ");
					stop.print();
					printf("1.02 * x = %f 0.98 * x = %f\n", 1.02 * x, 0.98 * x);*/
				    if (((start.x < 0.98 * x && stop->x > 1.02 * x) || (start.x > 1.02 * x && stop->x < 0.98 * x))
						&& ((c1.x < 0.98 * x && c2.x > 1.02 * x) || (c1.x > 1.02 * x && c2.x < 0.98 * x))) {
					    //printf("return\n");
						intersection++;
				    }
			 	}
		    } else {
				if ((start.x < c1.x && stop->x > c1.x) || (start.x > c1.x && stop->x < c1.x)) {
			    	float y = a1 * c1.x + b1;
					//printf("y = %f c1.y = %f c2.y = %f\n", y, c1.y, c2.y);
			    	if ((c1.y < 0.98 * y && c2.y > 1.02 * y) || (c1.y > 1.02 * y && c2.y < 0.98 * y)) {
				   		intersection++;
			    	}
				}
		    }
		}
		return 0;
	} else {
		//printf("else");
		for (int i = 0; i < 4; i++) {
			Point c1 = o->corners[i%4];
			Point c2 = o->corners[(i+1)%4];
			if ((c1.x < start.x && c2.x > start.x) || (c1.x > start.x && c2.x < start.x)) {
				if (c1.x != c2.x) {
					float a2 = (c1.y - c2.y) / (c1.x - c2.x);
					float b2 = c1.y - a2 * c1.x;
					float y = a2 * start.x + b2;
					if ((start.y < y && stop->y > y) || (start.y > y && stop->y < y)) {
						intersection++;
					}
				}
			}
		}
		return 0;
	}
	//printf("error");
	return 5;
}

