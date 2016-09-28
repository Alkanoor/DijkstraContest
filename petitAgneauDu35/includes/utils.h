#ifndef UTILS_H
#define UTILS_H

#include "struct.h"
#define PI 3.14159265

/*
 * Return the cos of angle (given in degrees))
 */
int dcos(int angle);

/*
 * Return the sin of angle (given in degrees)
 */
int dsin(int angle);

/*
 * Return the max between a and b
 */
int max(int a, int b);

/*
 * Return the min between a and b
 */
int min(int a, int b);

/*
 * Return 1 if x >= 0, -1 otherwise
 */
int signof(int x);

/*
 * Return det(P1P, P1P2)
 */
int determinant(Point P, Point P1, Point P2);

#endif
