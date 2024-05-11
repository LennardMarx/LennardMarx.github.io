#include "../include/player.h"

Player *new_player(float pos[3]) {
  Player *player = malloc(sizeof(Player));
  player->pos[0] = pos[0];
  player->pos[1] = pos[1];
  player->pos[2] = pos[2];
  player->rot[0] = 0;
  player->rot[1] = 0;
  player->rot[2] = 0;
  player_init(player);
  return player;
}
void destroy_player(Player *player) {
  free(player->plane);
  free(player);
}

void player_init(Player *player) {
  Projection_Plane *make_plane = malloc(sizeof(Projection_Plane));
  if (make_plane == NULL) {
    exit(EXIT_FAILURE);
  }
  make_plane->pos[0] = 0;
  make_plane->pos[1] = 0;
  make_plane->pos[2] = 65;
  make_plane->rot[0] = 0;
  make_plane->rot[1] = 0;
  make_plane->rot[2] = 0;
  make_plane->width = 80;
  make_plane->height = 60;

  init_screen(make_plane);
  player->plane = make_plane;

  player->update = player_update;
  player->clean_up = player_clean_up;
}

void player_update(Player *player) {
  player->plane->pos[0] = player->pos[0];
  player->plane->pos[1] = player->pos[1];
  player->plane->pos[2] = player->pos[2] + 65;
  player->plane->rot[0] = player->rot[0];
  player->plane->rot[1] = player->rot[1];
  player->plane->rot[2] = player->rot[2];

  player->plane->rotate(player->plane, player->pos);
  // player->plane->rotate_y(player->plane, player->pos);
  player->plane->calculate_centroid(player->plane);
  player->plane->calc_normal(player->plane, player->pos);
}

void player_clean_up(Player *player) {
  //
  free(player->plane);
}
