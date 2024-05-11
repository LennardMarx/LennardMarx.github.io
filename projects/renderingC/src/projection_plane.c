#include "../include/projection_plane.h"

void init_screen(Projection_Plane *screen) {
  // screen->corners = malloc(4 * sizeof(int *));
  // for (int i = 0; i < 8; i++)
  //   screen->corners[i] = malloc(3 * sizeof(int));

  projection_plane_update_corners(screen);
  screen->rotate = projection_plane_rotate;
  screen->rotate_x = projection_plane_rotate_x;
  screen->rotate_y = projection_plane_rotate_y;
  screen->rotate_z = projection_plane_rotate_z;
  screen->calculate_centroid = projection_plane_calculate_centroid;
  screen->calc_normal = projection_plane_calc_normal;
}

void projection_plane_update_corners(Projection_Plane *screen) {

  screen->corners[0][0] = screen->pos[0] - (float)screen->width / 2;
  screen->corners[0][1] = screen->pos[1] - (float)screen->height / 2;
  screen->corners[0][2] = screen->pos[2];

  screen->corners[1][0] = screen->pos[0] + (float)screen->width / 2;
  screen->corners[1][1] = screen->pos[1] - (float)screen->height / 2;
  screen->corners[1][2] = screen->pos[2];

  screen->corners[2][0] = screen->pos[0] + (float)screen->width / 2;
  screen->corners[2][1] = screen->pos[1] + (float)screen->height / 2;
  screen->corners[2][2] = screen->pos[2];

  screen->corners[3][0] = screen->pos[0] - (float)screen->width / 2;
  screen->corners[3][1] = screen->pos[1] + (float)screen->height / 2;
  screen->corners[3][2] = screen->pos[2];
}

// void projection_plane_update_pos(Projection_Plane *plane, float rot[3])
// {
//   plane->pos[0] =
// }

// Hacky implementation.
void projection_plane_calc_normal(Projection_Plane *plane, float point[3]) {
  // 65 -> player plane distance
  plane->normal[0] = (plane->centroid[0] - point[0]) / 65;
  plane->normal[1] = (plane->centroid[1] - point[1]) / 65;
  plane->normal[2] = (plane->centroid[2] - point[2]) / 65;

  // printf("Normal Length: %f\n", sqrt(plane->normal[0] * plane->normal[0] +
  //                                    plane->normal[1] * plane->normal[1] +
  //                                    plane->normal[2] * plane->normal[2]));
}

void projection_plane_calculate_centroid(Projection_Plane *plane) {
  // Initialize sum of coordinates
  float sumX = 0, sumY = 0, sumZ = 0;

  // Calculate sum of coordinates
  for (int i = 0; i < 4; ++i) {
    sumX += plane->corners_ref[i][0];
    sumY += plane->corners_ref[i][1];
    sumZ += plane->corners_ref[i][2];
  }

  // Calculate mean coordinates (centroid)
  plane->centroid[0] = sumX / 4;
  plane->centroid[1] = sumY / 4;
  plane->centroid[2] = sumZ / 4;
}

// TODO: rotate acis of x rotation to first rotate around y and then rotate
// about the new x axis
void projection_plane_rotate(Projection_Plane *plane, float point[3]) {
  Matrix3x3 rot_mat =
      get_rotation_matrix(-plane->rot[0], -plane->rot[1], -plane->rot[2]);
  float new_pos[3];
  for (int i = 0; i < 4; i++) {

    // Project cube relative to point of rotation.
    // plane->corners_ref[i][0] = plane->corners[i][0] - point[0];
    // plane->corners_ref[i][1] = plane->corners[i][1] - point[1];
    // plane->corners_ref[i][2] = plane->corners[i][2] - point[2];

    // Matrix multiplication.
    new_pos[0] = plane->corners[i][0] * rot_mat.m[0][0] +
                 plane->corners[i][1] * rot_mat.m[0][1] +
                 plane->corners[i][2] * rot_mat.m[0][2];
    new_pos[1] = plane->corners[i][0] * rot_mat.m[1][0] +
                 plane->corners[i][1] * rot_mat.m[1][1] +
                 plane->corners[i][2] * rot_mat.m[1][2];
    new_pos[2] = plane->corners[i][0] * rot_mat.m[2][0] +
                 plane->corners[i][1] * rot_mat.m[2][1] +
                 plane->corners[i][2] * rot_mat.m[2][2];

    plane->corners_ref[i][0] = new_pos[0] + point[0];
    plane->corners_ref[i][1] = new_pos[1] + point[1];
    plane->corners_ref[i][2] = new_pos[2] + point[2];

    // Set back to original position.
    // plane->corners[i][0] = plane->corners[i][0] + point[0];
    // plane->corners[i][1] = plane->corners[i][1] + point[1];
    // plane->corners[i][2] = plane->corners[i][2] + point[2];
  }
}

void projection_plane_rotate_x(Projection_Plane *plane, float point[3]) {

  // Convert degrees to radians.
  float ang = plane->rot[0] * M_PI / 180;
  float new_pos[3];
  for (int i = 0; i < 4; i++) {

    // Project cube relative to point of rotation.
    // plane->corners_ref[i][0] = plane->corners[i][0] - point[0];
    // plane->corners_ref[i][1] = plane->corners[i][1] - point[1];
    // plane->corners_ref[i][2] = plane->corners[i][2] - point[2];

    // Matrix multiplication.
    new_pos[0] = plane->corners_ref_2[i][0];
    new_pos[1] = plane->corners_ref_2[i][1] * cosf(ang) -
                 plane->corners_ref_2[i][2] * sinf(ang);
    new_pos[2] = plane->corners_ref_2[i][1] * sinf(ang) +
                 plane->corners_ref_2[i][2] * cosf(ang);

    plane->corners_ref[i][0] = new_pos[0] + point[0];
    plane->corners_ref[i][1] = new_pos[1] + point[1];
    plane->corners_ref[i][2] = new_pos[2] + point[2];

    // Set back to original position.
    // plane->corners[i][0] = plane->corners[i][0] + point[0];
    // plane->corners[i][1] = plane->corners[i][1] + point[1];
    // plane->corners[i][2] = plane->corners[i][2] + point[2];
  }
}

void projection_plane_rotate_y(Projection_Plane *plane, float point[3]) {

  // Convert degrees to radians.
  // TODO: Why is rotation inverted?
  float ang = -plane->rot[1] * M_PI / 180;
  float new_pos[3];
  for (int i = 0; i < 4; i++) {

    // Project cube relative to point of rotation.
    // plane->corners_ref[i][0] = plane->corners[i][0] - point[0];
    // plane->corners_ref[i][1] = plane->corners[i][1] - point[1];
    // plane->corners_ref[i][2] = plane->corners[i][2] - point[2];

    // Matrix multiplication.
    new_pos[0] =
        plane->corners[i][0] * cosf(ang) + plane->corners[i][2] * sinf(ang);
    new_pos[1] = plane->corners[i][1];
    new_pos[2] =
        -plane->corners[i][0] * sinf(ang) + plane->corners[i][2] * cosf(ang);

    plane->corners_ref[i][0] = new_pos[0]; // + point[0];
    plane->corners_ref[i][1] = new_pos[1]; // + point[1];
    plane->corners_ref[i][2] = new_pos[2]; // + point[2];

    // Set back to original position.
    // plane->corners[i][0] = plane->corners[i][0] + point[0];
    // plane->corners[i][1] = plane->corners[i][1] + point[1];
    // plane->corners[i][2] = plane->corners[i][2] + point[2];
  }
}
void projection_plane_rotate_z(Projection_Plane *plane, float point[3]) {

  // Convert degrees to radians.
  float ang = plane->rot[2] * M_PI / 180;
  float new_pos[3];
  for (int i = 0; i < 4; i++) {

    // Project cube relative to point of rotation.
    plane->corners[i][0] = plane->corners[i][0] - point[0];
    plane->corners[i][1] = plane->corners[i][1] - point[1];
    plane->corners[i][2] = plane->corners[i][2] - point[2];

    // Matrix multiplication.
    new_pos[0] =
        plane->corners[i][0] * cosf(ang) - plane->corners[i][1] * sinf(ang);
    new_pos[1] =
        plane->corners[i][0] * sinf(ang) + plane->corners[i][1] * cosf(ang);
    new_pos[2] = plane->corners[i][2];

    plane->corners_ref[i][0] = new_pos[0] + point[0];
    plane->corners_ref[i][1] = new_pos[1] + point[1];
    plane->corners_ref[i][2] = new_pos[2] + point[2];

    // Set back to original position.
    plane->corners[i][0] = plane->corners[i][0] + point[0];
    plane->corners[i][1] = plane->corners[i][1] + point[1];
    plane->corners[i][2] = plane->corners[i][2] + point[2];
  }
}
