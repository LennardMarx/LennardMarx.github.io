#include "../include/animated_sprite.h"
#include "../include/boid.h"
#include "../include/event_handler.h"
#include "../include/quad_tree.h"
#include "../include/ui.h"
#include <emscripten.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define PI 3.141592654

struct context {
  struct UI *ui;
  struct EventHandler *eventHandler;

  struct AnimatedSprite *animatedSprite;

  int boidCount;
  struct Boid **boids;

  int FPS;
  int FRAME_DELAY;
  Uint32 frameStart;
  int frameTime;

  vec2 mouse;
  int mouseX, mouseY;

  int frameCount;
};

static void mainloop(void *arg) {
  // chdir(SDL_GetBasePath());
  struct context *ctx = (struct context *)(arg);
  ctx->frameStart = SDL_GetTicks();

  SDL_GetMouseState(&ctx->mouseX, &ctx->mouseY);
  glm_vec2((vec2){ctx->mouseX, ctx->mouseY}, ctx->mouse);

  handle_events(ctx->eventHandler, ctx->ui, &ctx->mouse);

  clear_screen(ctx->ui);

  struct QuadTree *quadTree = quad_tree_create(
      (struct Rectangle){(float)ctx->ui->sizeX / 2, (float)ctx->ui->sizeY / 2,
                         (float)ctx->ui->sizeX, (float)ctx->ui->sizeY});

  for (int i = 0; i < ctx->boidCount; i++) {
    insert(quadTree, ctx->boids[i]);
  }

  for (int i = 0; i < ctx->boidCount; i++) {
    int mateCount;
    struct Boid **mates = query(quadTree, ctx->boids[i], &mateCount);
    find_flock(mates, mateCount, ctx->boids[i]);
    free(mates);

    separation(ctx->boids[i]);
    alignment(ctx->boids[i]);
    cohesion(ctx->boids[i]);

    avoid_border(ctx->ui, ctx->boids[i]);
    avoid_mouse(&ctx->mouse, ctx->boids[i]);

    fly(ctx->boids[i]);
    boid_continue_animation(ctx->boids[i], &ctx->frameCount);

    // draw_boid(ui, boids[i]);
    animated_sprite_draw(ctx->animatedSprite, ctx->boids[i]->pos[0] - 20,
                         ctx->boids[i]->pos[1] - 10, 40, 20);
    animated_sprite_play_frame(ctx->animatedSprite, 0, 0, 135, 65,
                               ctx->boids[i]->animationFrame);
    float angle =
        -atan2(ctx->boids[i]->vel[0], ctx->boids[i]->vel[1]) * 180 / PI + 180;
    // if (!eventHandler->pause)
    animated_sprite_render(ctx->animatedSprite, ctx->ui->renderer, &angle);
  }

  if (ctx->eventHandler->showQuadTree) {
    quad_tree_draw(quadTree, ctx->ui);
  }

  SDL_RenderPresent(ctx->ui->renderer);

  quad_tree_destroy(quadTree);

  ctx->frameTime = SDL_GetTicks() - ctx->frameStart;
  if (ctx->FRAME_DELAY > ctx->frameTime) {
    SDL_Delay(ctx->FRAME_DELAY - ctx->frameTime);
  }

  ctx->frameCount++;
}

int main(int argc, char *argv[]) {
  if (chdir(SDL_GetBasePath()) != 0) {
    perror("chdir failed");
  }

  srand(time(NULL));

  struct context ctx;

  ctx.ui = ui_create("Boids", 1800, 3000);
  ctx.eventHandler = event_handler_create();

  ctx.animatedSprite = animated_sprite_create(
      ctx.ui->renderer, "../resources/ducks_12_flap_outline.bmp");

  ctx.boidCount = 5000;
  ctx.boids = boids_create(ctx.ui, ctx.boidCount);

  ctx.FPS = 60;
  ctx.FRAME_DELAY = 1000 / ctx.FPS;

  ctx.frameCount = 0;

  emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);

  // Clean up.
  ui_destroy(ctx.ui);
  event_handler_destroy(ctx.eventHandler);
  boids_destroy(ctx.boids, ctx.boidCount);
  // textured_rectangle_destroy(texturedRectangle);
  animated_sprite_destroy(ctx.animatedSprite);

  SDL_Quit();

  return 0;
}
