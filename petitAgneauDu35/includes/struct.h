#ifndef STRUCT_H
#define STRUCT_H

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

#endif // STRUCT_H
