#ifndef PATH_H
#define PATH_H

typedef enum DIRECTION {DIAG_BAS_GAUCHE, VERT_BAS, DIAG_BAS_DROIT, X, HOR_GAUCHE, IMMOBILE,
  HOR_DROIT, Z, DIAG_HAUT_GAUCHE, VERT_HAUT, DIAG_HAUt_DROIT} DIRECTION;

void concat_path(int* points, int pointsNb);

#endif //PATH_H
