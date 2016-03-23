#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Point {
	int accessible;
	int A;
	int distance;
	int x;
	int y;
	struct Point* pere;
} Point;

Point* nextPivot(Point* map[], int xMax, int yMax);

int main(int argc, char* argv[]) {
	if (argc != 1) {
		printf("Syntax : %s\n", argv[0]);
		return 1;
	}
	int xMax, yMax, radius, xStart, yStart, xStop, yStop;

	scanf("%i\n", &xMax);
	scanf("%i\n", &yMax);
	scanf("%i\n", &radius);
	scanf("%i\n", &xStart);
	scanf("%i\n", &yStart);
	scanf("%i\n", &xStop);
	scanf("%i\n", &yStop);

	//TO DO : Recuperation des coordonnees des obstacles

	Point* map[xMax * yMax];
	for (int i = 0; i < xMax; i++) {
		for (int j = 0; j < yMax; j++) {
			map[i * yMax + j] = (Point*)malloc(sizeof(Point));
			map[i * yMax + j]->accessible = 1;
			map[i * yMax + j]->A = 0;
			map[i * yMax + j]->distance = INT_MAX;
			map[i * yMax + j]->x = i;
			map[i * yMax + j]->y = j;
			map[i * yMax + j]->pere = map[i * yMax + j];
		}
	}

	//Initialisation du pivot initial (point de depart)
	map[xStart * yMax + yStop]->A = 1;
	map[xStart * yMax + yStop]->distance = 0;

	//TO DO : inclure les obstacles dans le tableau

	Point* pivot = map[xStart * yMax + yStop];
	int x, y;
	Point* cur;
	for (int i = 0; i < xMax * yMax - 1; i++) {
		//Pour l'ensemble des voisins de pivot
		for(int j = -1; j <= 1; j++) {
			for (int k = -1; j <= 1; j++) {
				//Sans compter le pivot evidemment
				if (i != 0 || j != 0) {
					x = pivot->x + j;
					y = pivot->y + k;
					cur = map[x * yMax + y];
					if(pivot->distance + 1 < cur->distance) {
						cur->distance = pivot->distance + 1;
						cur->pere = pivot;
					}
				}
			}
		}
		pivot = nextPivot(map, xMax, yMax);
		pivot->A = 1;
	}
	//TO DO : remonter les parents depuis l'arrivee jusqu'au depart
	return 0;
}

Point* nextPivot(Point* map[], int xMax, int yMax) {
	//return the next pivot
	Point* pivot = (Point*)malloc(sizeof(Point));
	pivot->distance = INT_MAX;
	for (int i = 0; i < xMax * yMax; i++) {
		if(map[i]->A == 0 && map[i]->distance < pivot->distance)
			pivot = map[i];
	}
	return pivot;
}
