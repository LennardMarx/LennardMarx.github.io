#ifndef MATRICES_H
#define MATRICES_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double m[3][3];
} Matrix3x3;

Matrix3x3 multiply_matrices(Matrix3x3 A, Matrix3x3 B);

Matrix3x3 get_rotation_matrix(float thetaX, float thetaY, float thetaZ);

#endif
