#include "../include/cube.h"

void init_cube(Cube *cube) {
  // cube->corners = malloc(8 * sizeof(int *));
  // for (int i = 0; i < 8; i++)
  //   cube->corners[i] = malloc(3 * sizeof(int));
  update_corners(cube);
  cube->update = update_cube;
  cube->update_corners = update_corners;
  // cube->update_pos = update_pos;
  cube->rotate_x = rotate_x;
  cube->rotate_y = rotate_y;
  cube->rotate_z = rotate_z;
}
Cube *new_cube(float pos[3], float side_length) {
  Cube *cube = malloc(sizeof(Cube));
  cube->pos[0] = pos[0];
  cube->pos[1] = pos[1];
  cube->pos[2] = pos[2];
  cube->rot[0] = 0;
  cube->rot[1] = 0;
  cube->rot[2] = 0;
  cube->side_length = side_length;

  init_cube(cube);
  return cube;
}

void destroy_cube(Cube *cube) { free(cube); }

void update_cube(Cube *cube) {
  // cube->update_pos(cube, world);
  cube->update_corners(cube);
  cube->rotate_x(cube);
  cube->rotate_y(cube);
  cube->rotate_z(cube);
}

// Corner position relative to center.
void update_corners(Cube *cube) {

  cube->corners[0][0] = cube->pos[0] - cube->side_length / 2;
  cube->corners[0][1] = cube->pos[1] - cube->side_length / 2;
  cube->corners[0][2] = cube->pos[2] - cube->side_length / 2;

  cube->corners[1][0] = cube->pos[0] + cube->side_length / 2;
  cube->corners[1][1] = cube->pos[1] - cube->side_length / 2;
  cube->corners[1][2] = cube->pos[2] - cube->side_length / 2;

  cube->corners[2][0] = cube->pos[0] + cube->side_length / 2;
  cube->corners[2][1] = cube->pos[1] + cube->side_length / 2;
  cube->corners[2][2] = cube->pos[2] - cube->side_length / 2;

  cube->corners[3][0] = cube->pos[0] - cube->side_length / 2;
  cube->corners[3][1] = cube->pos[1] + cube->side_length / 2;
  cube->corners[3][2] = cube->pos[2] - cube->side_length / 2;

  cube->corners[4][0] = cube->pos[0] - cube->side_length / 2;
  cube->corners[4][1] = cube->pos[1] - cube->side_length / 2;
  cube->corners[4][2] = cube->pos[2] + cube->side_length / 2;

  cube->corners[5][0] = cube->pos[0] + cube->side_length / 2;
  cube->corners[5][1] = cube->pos[1] - cube->side_length / 2;
  cube->corners[5][2] = cube->pos[2] + cube->side_length / 2;

  cube->corners[6][0] = cube->pos[0] + cube->side_length / 2;
  cube->corners[6][1] = cube->pos[1] + cube->side_length / 2;
  cube->corners[6][2] = cube->pos[2] + cube->side_length / 2;

  cube->corners[7][0] = cube->pos[0] - cube->side_length / 2;
  cube->corners[7][1] = cube->pos[1] + cube->side_length / 2;
  cube->corners[7][2] = cube->pos[2] + cube->side_length / 2;
}

// Rotate about the x axis.
void rotate_x(Cube *cube) {

  // Convert degrees to radians.
  float ang = cube->rot[0] * M_PI / 180;
  float new_pos[3];
  for (int i = 0; i < 8; i++) {

    // Project cube to origin.
    cube->corners[i][0] = cube->corners[i][0] - cube->pos[0];
    cube->corners[i][1] = cube->corners[i][1] - cube->pos[1];
    cube->corners[i][2] = cube->corners[i][2] - cube->pos[2];

    // Matrix multiplication.
    new_pos[0] = cube->corners[i][0];
    new_pos[1] =
        cube->corners[i][1] * cosf(ang) - cube->corners[i][2] * sinf(ang);
    new_pos[2] =
        cube->corners[i][1] * sinf(ang) + cube->corners[i][2] * cosf(ang);

    cube->corners[i][0] = new_pos[0];
    cube->corners[i][1] = new_pos[1];
    cube->corners[i][2] = new_pos[2];

    // Set back to original position.
    cube->corners[i][0] = cube->corners[i][0] + cube->pos[0];
    cube->corners[i][1] = cube->corners[i][1] + cube->pos[1];
    cube->corners[i][2] = cube->corners[i][2] + cube->pos[2];
  }
}

void rotate_y(Cube *cube) {
  float ang = cube->rot[1] * M_PI / 180; // to radians
  float new_pos[3];
  for (int i = 0; i < 8; i++) {
    // Project cube to origin.
    cube->corners[i][0] = cube->corners[i][0] - cube->pos[0];
    cube->corners[i][1] = cube->corners[i][1] - cube->pos[1];
    cube->corners[i][2] = cube->corners[i][2] - cube->pos[2];
    // Matrix multiplication.
    new_pos[0] =
        cube->corners[i][0] * cosf(ang) + cube->corners[i][2] * sinf(ang);
    new_pos[1] = cube->corners[i][1];
    new_pos[2] =
        -cube->corners[i][0] * sinf(ang) + cube->corners[i][2] * cosf(ang);
    new_pos[2] = cube->corners[i][2];
    cube->corners[i][0] = new_pos[0];
    cube->corners[i][1] = new_pos[1];
    cube->corners[i][2] = new_pos[2];
    // Set back to original position.
    cube->corners[i][0] = cube->corners[i][0] + cube->pos[0];
    cube->corners[i][1] = cube->corners[i][1] + cube->pos[1];
    cube->corners[i][2] = cube->corners[i][2] + cube->pos[2];
  }
}
void rotate_z(Cube *cube) {
  float ang = cube->rot[2] * M_PI / 180; // to radians
  float new_pos[3];
  for (int i = 0; i < 8; i++) {
    // Project cube to origin.
    cube->corners[i][0] = cube->corners[i][0] - cube->pos[0];
    cube->corners[i][1] = cube->corners[i][1] - cube->pos[1];
    cube->corners[i][2] = cube->corners[i][2] - cube->pos[2];
    // Matrix multiplication.
    new_pos[0] =
        cube->corners[i][0] * cosf(ang) - cube->corners[i][1] * sinf(ang);
    new_pos[1] =
        cube->corners[i][0] * sinf(ang) + cube->corners[i][1] * cosf(ang);
    new_pos[2] = cube->corners[i][2];
    cube->corners[i][0] = new_pos[0];
    cube->corners[i][1] = new_pos[1];
    cube->corners[i][2] = new_pos[2];
    // Set back to original position.
    cube->corners[i][0] = cube->corners[i][0] + cube->pos[0];
    cube->corners[i][1] = cube->corners[i][1] + cube->pos[1];
    cube->corners[i][2] = cube->corners[i][2] + cube->pos[2];
  }
}
