#include "../include/cube.h"
#include "../include/definitions.h"
#include "../include/event_handler.h"
#include "../include/interface.h"
#include "../include/player.h"
#include "../include/projector.h"
#include <emscripten.h>

#include <SDL2/SDL.h>
#include <stdio.h>

struct context {
  Interface UI;

  EventHandler event_handler;

  SDL_Event event;
  int quit;

  Cube *cube;
  Cube *cube2;
  Cube *cube3;
  Cube *cube4;

  Player *player;
};

// void run() { emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1); }
//

static void mainloop(void *arg) {
  // chdir(SDL_GetBasePath());
  struct context *ctx = (struct context *)(arg);
  // while (!ctx.quit) {
  // Handle events
  ctx->event_handler.handle_events(&ctx->event, &ctx->quit, ctx->player);

  // Set render color to red ( background will be rendered in this color )
  SDL_SetRenderDrawColor(ctx->UI.renderer, 69, 133, 136, 255);

  // Clear winow
  SDL_RenderClear(ctx->UI.renderer);

  // Set render color to blue ( rect will be rendered in this color )
  // SDL_SetRenderDrawColor(ctx->UI.renderer, 255, 255, 255, 255);
  SDL_SetRenderDrawColor(ctx->UI.renderer, 249, 245, 215, 255);
  ctx->player->update(ctx->player);

  ctx->cube2->rot[0] -= 1;
  ctx->cube2->rot[2] -= 1;

  // Upate corner position of cube and rotate them.
  ctx->cube->update(ctx->cube);
  ctx->cube2->update(ctx->cube2);
  ctx->cube3->update(ctx->cube3);
  ctx->cube4->update(ctx->cube4);

  // Project cube to the screen plane.
  project_cube(ctx->cube, ctx->player);
  project_cube(ctx->cube2, ctx->player);
  project_cube(ctx->cube3, ctx->player);
  project_cube(ctx->cube4, ctx->player);

  // Draw the projected cube on the screen.
  ctx->UI.draw_cube(ctx->UI.renderer, ctx->cube);
  ctx->UI.draw_cube(ctx->UI.renderer, ctx->cube2);
  ctx->UI.draw_cube(ctx->UI.renderer, ctx->cube3);
  ctx->UI.draw_cube(ctx->UI.renderer, ctx->cube4);

  // printf("Player Rotation: %f\n", player->rot[1]);
  // printf("Player Position: %f, %f, %f\n", player->pos[0], player->pos[1],
  //        player->pos[2]);
  // printf("Plane centroid: %f, %f, %f\n", player->plane->centroid[0],
  //        player->plane->centroid[1], player->plane->centroid[2]);
  // printf("Player Posish: %f, %f, %f\n", player->pos[0], player->pos[1],
  //        player->pos[2]);
  // printf("Player rotish: %f, %f, %f\n", player->rot[0], player->rot[1],
  //        player->rot[2]);
  // printf("Plane Norm: %f, %f, %f\n", player->plane->normal[0],
  //        player->plane->normal[1], player->plane->normal[2]);
  // for (int i = 0; i < 4; i++) {
  //
  //   printf("Plane Corner [%d]: %f, %f, %f\n", i,
  //          player->plane->corners_ref[i][0],
  //          player->plane->corners_ref[i][1],
  //          player->plane->corners_ref[i][2]);
  // }
  // printf("Plane centroid: %f, %f, %f\n", player->plane->centroid[0],
  //        player->plane->centroid[1], player->plane->centroid[2]);

  // Update the screen
  SDL_RenderPresent(ctx->UI.renderer);

  // Add a small del  ay to control the frame rate (optional)
  SDL_Delay(16);
}

// void run() { emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1); }

int main(int argc, char **argv) {
  struct context ctx;

  // Interface UI;
  init_interface(&ctx.UI, WIDTH, HEIGHT);

  // EventHandler event_handler;
  init_event_handler(&ctx.event_handler);

  ctx.quit = 0;

  ctx.cube = new_cube((float[]){30, 0, 80}, 30);
  ctx.cube2 = new_cube((float[]){30, 0, 80}, 15);
  ctx.cube3 = new_cube((float[]){-30, 0, 80}, 30);
  ctx.cube4 = new_cube((float[]){60, 0, 80}, 30);

  ctx.player = new_player((float[]){0, 0, 0});

  // run();
  // void run() { emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1); }
  emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);

  SDL_DestroyWindow(ctx.UI.window);
  SDL_Quit();

  // Clean up
  destroy_player(ctx.player);

  destroy_cube(ctx.cube);
  destroy_cube(ctx.cube2);
  destroy_cube(ctx.cube3);
  destroy_cube(ctx.cube4);
  // destroy_interface(&UI);

  return 0;
}
