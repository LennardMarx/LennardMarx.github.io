#ifndef LOOP_H
#define LOOP_H

#include "../include/UI.h"
#include "../include/boid.h"
#include <SDL2/SDL.h>
#include <array>
#include <cmath>
// #include <glm/gtc/constants.hpp>
#include "../include/glm/glm/glm.hpp"
#include <memory>
#include <random>
#include <unistd.h>
#include <vector>

class Loop {
public:
  Loop();
  ~Loop();

  void run();

private:
  void eventChecks();

private:
  UI *ui;

  bool quit = false;
  bool pause = false;

  const int FPS = 60;                // set FPS
  const int frameDelay = 1000 / FPS; // delay according to FPS
  Uint32 frameStart;                 // keeps track of time (?)
  int frameTime;

  SDL_Event event;
};

#endif
