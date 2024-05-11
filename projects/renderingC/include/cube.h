#ifndef CUBE_H
#define CUBE_H

#include <math.h>
#include <stdlib.h>

struct Cube;

typedef struct Cube {
  float pos[3];
  float rot[3];
  float side_length;
  float corners[8][3];
  struct Cube *self;
  int screen_pos[8][2];
  void (*update)(struct Cube *cube);
  void (*update_corners)(struct Cube *cube);
  void (*rotate_x)(struct Cube *cube);
  void (*rotate_y)(struct Cube *cube);
  void (*rotate_z)(struct Cube *cube);
} Cube;

Cube *new_cube(float pos[3], float side_length);
void destroy_cube(Cube *cube);

void init_cube(Cube *cube);

void update_cube(Cube *cube);

void update_corners(Cube *cube);

void rotate_x(Cube *cube);
void rotate_y(Cube *cube);
void rotate_z(Cube *cube);

#endif
