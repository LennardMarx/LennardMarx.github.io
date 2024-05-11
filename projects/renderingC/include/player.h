#ifndef PLAYER_H
#define PLAYER_H

#include "../include/projection_plane.h"

struct Player;

typedef struct Player {
  float pos[3];
  float rot[3];
  Projection_Plane *plane;
  void (*clean_up)(struct Player *player);
  void (*update)(struct Player *player);
} Player;

void player_init(Player *player);
Player *new_player(float pos[3]);
void destroy_player(Player *player);

void player_update(Player *player);

void player_clean_up(Player *player);

#endif
