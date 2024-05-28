#include "../include/boid.h"

void draw_boid(struct UI *ui, struct Boid *boid) {
  vec2 dir;
  glm_vec2(boid->vel, dir);
  glm_vec2_normalize(dir);

  SDL_RenderDrawLine(ui->renderer, boid->pos[0], boid->pos[1],
                     boid->pos[0] + dir[0] * boid->length,
                     boid->pos[1] + dir[1] * boid->length);
  SDL_RenderDrawLine(ui->renderer, boid->pos[0] + dir[1] * boid->width / 2,
                     boid->pos[1] - dir[0] * boid->width / 2,
                     boid->pos[0] - dir[1] * boid->width / 2,
                     boid->pos[1] + dir[0] * boid->width / 2);
  SDL_RenderDrawLine(ui->renderer, boid->pos[0] + dir[1] * boid->width / 2,
                     boid->pos[1] - dir[0] * boid->width / 2,
                     boid->pos[0] + dir[0] * boid->length,
                     boid->pos[1] + dir[1] * boid->length);
  SDL_RenderDrawLine(ui->renderer, boid->pos[0] - dir[1] * boid->width / 2,
                     boid->pos[1] + dir[0] * boid->width / 2,
                     boid->pos[0] + dir[0] * boid->length,
                     boid->pos[1] + dir[1] * boid->length);
}
void draw_boid_red(struct UI *ui, struct Boid *boid) {
  vec2 dir;
  glm_vec2(boid->vel, dir);
  glm_vec2_normalize(dir);

  SDL_SetRenderDrawColor(ui->renderer, 230, 133, 136, 255); // some red

  SDL_RenderDrawLine(ui->renderer, boid->pos[0], boid->pos[1],
                     boid->pos[0] + dir[0] * boid->length,
                     boid->pos[1] + dir[1] * boid->length);
  SDL_RenderDrawLine(ui->renderer, boid->pos[0] + dir[1] * boid->width / 2,
                     boid->pos[1] - dir[0] * boid->width / 2,
                     boid->pos[0] - dir[1] * boid->width / 2,
                     boid->pos[1] + dir[0] * boid->width / 2);
  SDL_RenderDrawLine(ui->renderer, boid->pos[0] + dir[1] * boid->width / 2,
                     boid->pos[1] - dir[0] * boid->width / 2,
                     boid->pos[0] + dir[0] * boid->length,
                     boid->pos[1] + dir[1] * boid->length);
  SDL_RenderDrawLine(ui->renderer, boid->pos[0] - dir[1] * boid->width / 2,
                     boid->pos[1] + dir[0] * boid->width / 2,
                     boid->pos[0] + dir[0] * boid->length,
                     boid->pos[1] + dir[1] * boid->length);
  SDL_SetRenderDrawColor(ui->renderer, 249, 245, 215, 150); // gruv-light
}

void boid_continue_animation(struct Boid *boid, int *frameCount) {
  if (*frameCount % 4 == 0) {
    boid->animationFrame++;
  }
  if (boid->animationFrame >= 12) {
    boid->animationFrame = 0;
  }
}
