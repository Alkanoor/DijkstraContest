#ifndef DIJKSTRA_H
#define DIJKSTRA_H

/*
 * Initial distance of every point (except the starting point)
 */
#define INT_MAX 20000

/*
 * This value is used as the extra-space that must be left between an obstacle and the robot
 */
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

/*
 * Return the node that must be used as the next pivot
 * Warning : this function doesn't modify the node
 * In particular, it's A field is not set by this function
 */
Node* nextPivot(Node* map[], int xMax, int yMax, int margin, int distMin);

/*
 * Initialize the Obstacle variable provided with the given values
 */
void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle, int radius);

/*
 * Place the obstacle on the map
 * Set the 'accessible' field of the nodes which are inside the obstacle
 * or too close to it to be accessible by the center of the robot
 * (according to it's radius)
 */
void set_obstacle(Node* map[], Obstacle* obstacle, int xMax, int yMax, int radius);

/*
 * Return 1 if the Point is inside the obstacle or too close to be accessible
 * by the center of the robot
 */
int isInside(Point, Obstacle*);

/*
 * Display the distance of every node in the map
 * A value of -1 means that the distance to this point
 * has not been calculated :
 *	- this point is not accessible
 *  - the destination has been reached before updating
 *		the distance value of this point
 */
void printCost(Node* map[], int xMax, int yMax);

#endif
