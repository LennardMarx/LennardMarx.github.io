#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
// #include <algorithm>
// #include <iostream>
// #include <set>
#include <string>
#include <unistd.h>
#include <vector>

#include "../include/UI.h"
// #include "../include/entity.h"
#include "../include/eventChecks.h"
#include "../include/movement.h"
#include "../include/raycaster.h"
// #include "../include/rectangle.h"
#include "../include/wall.h"
#include "../include/world_utils.h"

#include <emscripten.h>

struct context {

  const int WORLD_W = 800, WORLD_H = 800;
  const int SCREEN_W = 1200, SCREEN_H = 800;

  const int WALL_SIZE = 50;

  // UI ui{WORLD_W, WORLD_H, 0};
  // UI ui{SCREEN_W, SCREEN_H, 1800};
  UI ui{SCREEN_W, SCREEN_H, 0};

  const int FPS = 60;                // set FPS
  const int frameDelay = 1000 / FPS; // delay according to FPS
  Uint32 frameStart;                 // keeps track of time (?)
  int frameTime;

  // RayCaster player = RayCaster(WORLD_W / 2, WORLD_H / 2);
  // RayCaster player = RayCaster(0, 0);
  RayCaster player = RayCaster(-200, 300);

  // for one wall in direction of wall in square (u = up, d = down, l = left, r
  // = right) for corners: F = ┌, T = ┐, L = └, J = ┘ for corridors: H = ║, B =
  // ═
  int a = 10, b = 11, c = 12, d = 13, e = 14, f = 15; // wtf am i doing
  std::array<std::array<std::string, 16>, 16> worldMap2;

  std::vector<Wall *> walls;
  // walls = createWorld(worldMap, WORLD_W, WORLD_H, WALL_SIZE,
  // ui.getRenderer());
  WorldUtils world_utils;
  // walls = world_utils.createWorld2(worldMap2, WORLD_W, WORLD_H, WALL_SIZE,
  // ui.getRenderer());

  Uint32 mouseState;

  bool pause = false;
  bool quit = false;

  // SDL_Event event;
  EventChecks eventChecks;
};

static void mainloop(void *arg) {
  // chdir(SDL_GetBasePath());
  context *ctx = static_cast<context *>(arg);
  ctx->frameStart = SDL_GetTicks(); // limit framerate (see end of while loop)
  ctx->eventChecks.checkEvents(ctx->player, ctx->ui, ctx->frameStart);
  // pause the game
  ctx->ui.clear();

  if (ctx->eventChecks.getPause()) {
    SDL_SetRelativeMouseMode(SDL_FALSE); // getting mouse cursor again
    ctx->ui.drawBackground();
    ctx->ui.drawTexturedWalls(ctx->player.getDistances(),
                              ctx->player.getPositionOnWall(),
                              ctx->player.getTextureInfo());
    ctx->ui.drawMiniMap(ctx->walls, ctx->player.getRays());
    ctx->ui.printText("Game paused", 0, 0, {255, 255, 255, 150});

  } else {
    // SDL_SetRelativeMouseMode(SDL_TRUE);

    // SDL_PumpEvents();
    // mouseState = SDL_GetMouseState(&x, &y);
    // rayCaster.setPosition(ui, x, y);

    // check if the camera should rotate
    int direction = ctx->eventChecks.getRotationDirection();
    ctx->player.rotate(direction); // rotate camera
    // check which movements should be executed
    MovementFlag movement = ctx->eventChecks.getMovement();
    // move the camera accordingly

    // player.move(movement);
    // player.move2(eventChecks);

    ctx->player.emitLight(ctx->walls);

    ctx->player.checkCollision(ctx->walls);

    ctx->player.updatePreviousPosition();

    //============= 2D ===========================
    // ui.clear(); // render WORLD black
    // ui.drawWalls(walls);
    // ui.drawRays(player.getRays());
    // ui.present(); // render WORLD
    //================= 3D =====================

    ctx->ui.drawBackground();
    ctx->ui.drawTexturedWalls(ctx->player.getDistances(),
                              ctx->player.getPositionOnWall(),
                              ctx->player.getTextureInfo());
    ctx->ui.drawMiniMap(ctx->walls, ctx->player.getRays());

    ctx->ui.drawCrossHair();
  } // end else (pause game)
  ctx->ui.present();

  // frame time to limit FPS
  ctx->frameTime = SDL_GetTicks() - ctx->frameStart;
  if (ctx->frameDelay > ctx->frameTime) {
    SDL_Delay(ctx->frameDelay - ctx->frameTime);
  }
  // std::cout << frameStart << std::endl;
}

int main() {
  // chdir(SDL_GetBasePath());
  // srand((unsigned int)time(NULL));
  // 1080x1920

  context ctx;

  ctx.player.setOrientation(270);

  ctx.worldMap2[0] = {"O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[1] = {"O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[2] = {"O0", "O0", "O0", "d1", "O0", "O0", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[3] = {"O0", "O0", "O0", "H1", "O0", "O0", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[4] = {"O0", "F1", "B2", "O0", "B1", "T1", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[5] = {"O0", "H1", "O0", "H1", "O0", "H1", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[6] = {"O0", "H2", "O0", "u1", "O0", "H2", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[7] = {"O0", "O0", "O0", "O0", "O0", "H1", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[8] = {"O0", "O0", "O0", "O0", "O0", "H1", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[9] = {"O0", "O0", "O0", "O0", "O0", "H2", "O0", "O0",
                      "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[ctx.a] = {"O0", "O0", "O0", "O0", "O0", "H1", "O0", "O0",
                          "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[ctx.b] = {"O0", "O0", "O0", "O0", "O0", "H1", "O0", "O0",
                          "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[ctx.c] = {"O0", "O0", "O0", "O0", "O0", "H1", "O0", "O0",
                          "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[ctx.d] = {"O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0",
                          "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[ctx.e] = {"O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0",
                          "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};
  ctx.worldMap2[ctx.f] = {"O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0",
                          "O0", "O0", "O0", "O0", "O0", "O0", "O0", "O0"};

  ctx.walls =
      ctx.world_utils.createWorld2(ctx.worldMap2, ctx.WORLD_W, ctx.WORLD_H,
                                   ctx.WALL_SIZE, ctx.ui.getRenderer());

  emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);

  for (int i = 0; i < ctx.walls.size(); i++) {
    delete ctx.walls[i];
    // std::cout << "clean up!" << std::endl;
  }

  return 0;
}
