#include "../include/matrices.h"
Matrix3x3 multiply_matrices(Matrix3x3 A, Matrix3x3 B) {
  Matrix3x3 result = {{{0}}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
        result.m[i][j] += A.m[i][k] * B.m[k][j];
      }
    }
  }
  return result;
}

// Define rotation matrices for X, Y, and Z axes
Matrix3x3 get_rotation_matrix(float thetaX, float thetaY, float thetaZ) {
  thetaX = thetaX * M_PI / 180;
  thetaY = thetaY * M_PI / 180;
  thetaZ = thetaZ * M_PI / 180;
  Matrix3x3 Rx = {{{1, 0, 0},
                   {0, cos(thetaX), -sin(thetaX)},
                   {0, sin(thetaX), cos(thetaX)}}};
  Matrix3x3 Ry = {{{cos(thetaY), 0, sin(thetaY)},
                   {0, 1, 0},
                   {-sin(thetaY), 0, cos(thetaY)}}};
  Matrix3x3 Rz = {{{cos(thetaZ), -sin(thetaZ), 0},
                   {sin(thetaZ), cos(thetaZ), 0},
                   {0, 0, 1}}};

  Matrix3x3 result = multiply_matrices(Ry, Rx);
  result = multiply_matrices(result, Rz);
  // result = Ry;
  return result;
}
