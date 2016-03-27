#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define INT_MAX 10000
#define MARGIN 0

typedef struct Point {
	int x;
	int y;
 } Point;

typedef struct Node {
	int accessible;
	int A;
	int distance;
	Point point;
	struct Node* pere;
} Node;

typedef struct Obstacle {
	int xPos;
	int yPos;
	int halfWidth;
	int halfHeight;
	int angle;
	Point corners[4];
} Obstacle;


Node* nextPivot(Node* map[], int xMax, int yMax, int margin);
void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle, int radius);
void set_obstacle(Node* map[], Obstacle* obstacle, int xMax, int yMax, int radius);
int isInside(Point, Obstacle*);
int signof(int);
int determinant(Point, Point, Point);

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

	//Recuperation des coordonnees des obstacles
	int nbObstacles = 0;
	Obstacle* obstacles = NULL;
	int xPos, yPos, halfWidth, halfHeight, angle;

	//Initialization of the map
	Node* map[xMax * yMax];
	for (int i = 0; i < xMax; i++) {
		for (int j = 0; j < yMax; j++) {
			map[i * yMax + j] = (Node*)malloc(sizeof(Node));
			map[i * yMax + j]->accessible = 1;
			map[i * yMax + j]->A = 0;
			map[i * yMax + j]->distance = INT_MAX;
			map[i * yMax + j]->point.x = i;
			map[i * yMax + j]->point.y = j;
			map[i * yMax + j]->pere = map[i * yMax + j];
		}
	}



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
		init_obstacle(&obstacles[nbObstacles], xPos, yPos, halfWidth, halfHeight, angle, radius);
		set_obstacle(map, &obstacles[nbObstacles], xMax, yMax, radius);
		nbObstacles++;
	}

	//Initialisation du pivot initial (point de depart)
	map[xStart * yMax + yStart]->A = 1;
	map[xStart * yMax + yStart]->distance = 0;
	Node* pivot = map[xStart * yMax + yStart];
	
	int x, y;
	Node* cur;
	int margin = radius + MARGIN;
	
	//Beginning of the algorithm
	for (int i = 0; i < xMax * yMax - 1; i++) {
		//Pour l'ensemble des voisins de pivot
		for(int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				//Sans compter le pivot evidemment
				if (j != 0 || k != 0) {
					x = pivot->point.x + j;
					y = pivot->point.y + k;
					if (map[x * yMax + y]->accessible && map[x * yMax + y]->A == 0) {
						cur = map[x * yMax + y];
						if(pivot->distance + 1 < cur->distance) {
							cur->distance = pivot->distance + 1;
							cur->pere = pivot;
						}
					}
				}
			}
		}
		pivot = nextPivot(map, xMax, yMax, margin);
		pivot->A = 1;
		//On s'arrete des qu'on a atteint la destination
		if(pivot->point.x == xStop && pivot->point.y == yStop) {
			break;
		}
	}
	
	//Recuperation du nombre de noeuds sur le chemin
	x = xStop;
	y = yStop;
	Node* pere;
	int nb = 1;
	while(x != xStart || y != yStart) {
		pere = map[x * yMax + y]->pere;
		x = pere->point.x;
		y = pere->point.y;
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
		x = pere->point.x;
		y = pere->point.y;
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

Node* nextPivot(Node* map[], int xMax, int yMax, int margin) {
	//return the next pivot
	Node* pivot = (Node*)malloc(sizeof(Node));
	//Keep track of the address of the space allocated to free it before returning
	Node* p = pivot;
	pivot->distance = INT_MAX;
	for (int x = margin; x <= xMax -margin; x++) {
		for (int y = margin; y <= yMax - margin; y++) {
			if(map[x * yMax + y]->accessible == 1 && map[x * yMax + y]->A == 0 && map[x * yMax + y]->distance < pivot->distance) {
				pivot = map[x * yMax + y];
			}
		}
	}
	free(p);
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

void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle, int radius) {
	obstacle->xPos = xPos;
	obstacle->yPos = yPos;
	obstacle->halfWidth = halfWidth;
	obstacle->halfHeight = halfHeight;
	obstacle->angle = angle;
	Point corner;
	//Top Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) - radius - MARGIN;
	corner.y = yPos + (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) + radius + MARGIN;
	obstacle->corners[0] = corner;
	//Top Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) + radius + MARGIN;
	corner.y = yPos + (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) + radius + MARGIN;
	obstacle->corners[1] = corner;
	//Bottom Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) + radius + MARGIN;
	corner.y = yPos - (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) - radius - MARGIN;
	obstacle->corners[2] = corner;
	//Bottom Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) - radius - MARGIN;
	corner.y = yPos - (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) - radius - MARGIN;
	obstacle->corners[3] = corner;
}

void set_obstacle(Node* map[], Obstacle* obstacle, int xMax, int yMax, int radius) {
	//Test uniquement les points qui ont une chance d'etre dans l'obstacle
	int half_diag = sqrt(obstacle->halfWidth * obstacle->halfWidth + obstacle->halfHeight * obstacle->halfHeight) + 2 * (radius + MARGIN);
	for (int i = max(0, obstacle->xPos - half_diag); i < min (xMax, obstacle->xPos + half_diag); i++) {
		for (int j = max(0, obstacle->yPos - half_diag); j < min (yMax, obstacle->yPos + half_diag); j++) {
			if(isInside(map[i * yMax + j]->point, obstacle)) {
				map[i * yMax + j]->accessible = 0;
			}
		}
	}
}

/*
 * return 0 : outside
 * return 1 : inside
 */
int isInside(Point point, Obstacle* obstacle) {
	int signe =signof(determinant(point, obstacle->corners[0], obstacle->corners[1]));
	for (int i = 1; i < 4; i++) {
		signe = signof(determinant(point, obstacle->corners[i], obstacle->corners[i%4]));
		if(signe != signof(determinant(point, obstacle->corners[i], obstacle->corners[i%4]))) {
			return 0;
		}
	}
	return 1;
}

//Donne le signe du paramètre
int signof(int x) {
	if(x >= 0)
		return 1;
	return -1;
}

//Calcul det(p1p, p1p2)
int determinant(Point p, Point p1, Point p2) {
	return (p.x - p1.x)*(p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
}
