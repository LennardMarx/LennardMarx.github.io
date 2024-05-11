#ifndef PROJECTION_PLANE_H
#define PROJECTION_PLANE_H

#include "../include/matrices.h"
#include <math.h>
#include <stdlib.h>

struct Projection_Plane;

typedef struct Projection_Plane {
  float pos[3];
  float pos_ref[3];
  float rot[3];
  float normal[3];
  int width;
  int height;
  float centroid[3];
  // float **corners;
  float corners[4][3];
  float corners_ref[4][3];
  float corners_ref_2[4][3];
  void (*rotate)(struct Projection_Plane *plane, float point[3]);
  void (*rotate_x)(struct Projection_Plane *plane, float point[3]);
  void (*rotate_y)(struct Projection_Plane *plane, float point[3]);
  void (*rotate_z)(struct Projection_Plane *plane, float point[3]);
  void (*calculate_centroid)(struct Projection_Plane *plane);
  void (*calc_normal)(struct Projection_Plane *plane, float point[3]);
} Projection_Plane;

void init_screen(Projection_Plane *plane);

// void projection_plane_update_pos(Projection_Plane *plane, float rot[3]);
void projection_plane_update_corners(Projection_Plane *plane);

void projection_plane_rotate(Projection_Plane *plane, float point[3]);
void projection_plane_rotate_x(Projection_Plane *plane, float point[3]);
void projection_plane_rotate_y(Projection_Plane *plane, float point[3]);
void projection_plane_rotate_z(Projection_Plane *plane, float point[3]);

void projection_plane_calculate_centroid(Projection_Plane *plane);

void projection_plane_calc_normal(Projection_Plane *plane, float point[3]);

#endif
