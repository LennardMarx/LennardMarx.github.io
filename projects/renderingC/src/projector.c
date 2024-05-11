#include "../include/projector.h"

void project_cube(Cube *cube, Player *player) {
  for (int i = 0; i < 8; i++) {

    // Direction of corner to focal point.
    float dir[3] = {cube->corners[i][0] - player->pos[0],
                    cube->corners[i][1] - player->pos[1],
                    cube->corners[i][2] - player->pos[2]};

    // Multiplier of where the plane intersects on the line. (ditance of
    // player
    // to plane to Distance of player to point)
    // float t = (player->plane->pos[2] - player->pos[2]) /
    //           (cube->corners[i][2] - player->pos[2]);
    float a = player->plane->normal[0];
    float b = player->plane->normal[1];
    float c = player->plane->normal[2];
    // float x0 = player->plane->centroid[0];
    // float y0 = player->plane->centroid[1];
    // float z0 = player->plane->centroid[2];
    float x0 = player->plane->corners_ref[0][0];
    float y0 = player->plane->corners_ref[0][1];
    float z0 = player->plane->corners_ref[0][2];
    float x1 = player->pos[0];
    float y1 = player->pos[1];
    float z1 = player->pos[2];
    float x2 = cube->corners[i][0];
    float y2 = cube->corners[i][1];
    float z2 = cube->corners[i][2];
    float t = (a * (x1 - x0) + b * (y1 - y0) + c * (z1 - z0)) /
              (a * (x1 - x2) + b * (y1 - y2) + c * (z1 - z2));

    // Intersection based on the Multiplier.
    float intersection[3] = {t * dir[0], t * dir[1], t * dir[2]};

    float p_a[3];
    p_a[0] = intersection[0] - player->plane->corners_ref[0][0];
    p_a[1] = intersection[1] - player->plane->corners_ref[0][1];
    p_a[2] = intersection[2] - player->plane->corners_ref[0][2];
    float AB[3];
    AB[0] = player->plane->corners_ref[1][0] - player->plane->corners_ref[0][0];
    AB[1] = player->plane->corners_ref[1][1] - player->plane->corners_ref[0][1];
    AB[2] = player->plane->corners_ref[1][2] - player->plane->corners_ref[0][2];
    float AB_len =
        sqrt((double)((AB[0] * AB[0]) + (AB[1] * AB[1]) + (AB[2] * AB[2])));
    // printf("AB len: %float\n", AB_len);
    AB[0] /= AB_len;
    AB[1] /= AB_len;
    AB[2] /= AB_len;

    float AD[3];
    AD[0] = player->plane->corners_ref[3][0] - player->plane->corners_ref[0][0];
    AD[1] = player->plane->corners_ref[3][1] - player->plane->corners_ref[0][1];
    AD[2] = player->plane->corners_ref[3][2] - player->plane->corners_ref[0][2];
    float AD_len = sqrt(((AD[0] * AD[0]) + (AD[1] * AD[1]) + (AD[2] * AD[2])));
    // printf("AD len: %float\n", AD_len);
    AD[0] /= AD_len;
    AD[1] /= AD_len;
    AD[2] /= AD_len;

    float p__x = p_a[0] * AB[0] + p_a[1] * AB[1] + p_a[2] * AB[2];
    float p__y = p_a[0] * AD[0] + p_a[1] * AD[1] + p_a[2] * AD[2];
    // p__x -= 40;
    // p__y -= 30;

    // printf("Point on Plane: %f, %f \n", p__x, p__y);

    // Conversion from plane to plane size.
    // cube->screen_pos[i][0] =
    //     (intersection[0] + (float)player->plane->width / 2) * WIDTH /
    //     player->plane->width;
    // cube->screen_pos[i][1] =
    //     (intersection[1] + (float)player->plane->height / 2) * HEIGHT /
    //     player->plane->height;
    // cube->screen_pos[i][0] =
    //     (p__x + (float)player->plane->width / 2) * WIDTH /
    //     player->plane->width;
    // cube->screen_pos[i][1] = (p__y + (float)player->plane->height / 2) *
    //                          HEIGHT / player->plane->height;
    cube->screen_pos[i][0] = p__x * WIDTH / player->plane->width;
    cube->screen_pos[i][1] = p__y * HEIGHT / player->plane->height;
  }
}

// void project_cube(Cube *cube, Player *player) {
//   // float test_dir[3] = {cube->pos[0] - focal->x, cube->pos[1] - focal->y,
//   //                      cube->pos[2] - focal->z};
//
//   // cube->t = player->plane->pos[2] / cube->pos[2];
//   // printf("Z Distance: %f\n", cube->pos[2]);
//   for (int i = 0; i < 8; i++) {
//
//     // Direction of corner to focal point.
//     float dir[3] = {cube->corners[i][0] - player->pos[0],
//                     cube->corners[i][1] - player->pos[1],
//                     cube->corners[i][2] - player->pos[2]};
//
//     // Multiplier of where the plane intersects on the line.
//     float t = player->plane->pos[2] / cube->corners[i][2];
//
//     // Intersection based on the Multiplier.
//     float intersection[2] = {t * dir[0], t * dir[1]}; //, t * dir[2]};
//
//     // Conversion from plane to plane size.
//     cube->screen_pos[i][0] =
//         (intersection[0] + (float)player->plane->width / 2) * WIDTH /
//         player->plane->width;
//     cube->screen_pos[i][1] =
//         (intersection[1] + (float)player->plane->height / 2) * HEIGHT /
//         player->plane->height;
//   }
// }
