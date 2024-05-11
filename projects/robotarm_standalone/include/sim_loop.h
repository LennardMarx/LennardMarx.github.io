#ifndef SIM_LOOP_H
#define SIM_LOOP_H

#pragma once
#include "UI.h"
#include "event_checks.h"
#include "helper_variables.h"
#include "pendulum.h"
#include "pendulum_dynamics.h"
#include <cstdlib>
#include <emscripten.h>

#include <SDL2/SDL.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <ratio>

#include <list>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

struct context {
  const int FPS = 60;                // set FPS
  const int frameDelay = 1000 / FPS; // delay according to FPS
  Uint32 frameStart;                 // keeps track of time (?)
  int frameTime;

  int window_width = 1200;
  int window_height = 800;
  UI ui{window_width, window_height};

  Pendulum pendulum{0, 0};
  PendulumDynamics pendulumDynamics;
  HelperVars helperVars;
  EventChecks eventChecks;
  Uint32 mouseState;

  double pi = 3.141592653589793238462643383279502884197;
  double x0 = 0, y0 = 0, x1, y1, x2, y2; // link positions
  double x2_prev, y2_prev;               // previous endeffector position
  double l1 = 150, l2 = 150;             // pendulum length on screen

  int x, y;
  double x_conv;
  double y_conv;

  double qd1 = 0; // desired angle 1
  double qd2 = 0; // desired angle 2

  double xd = 0;  // desired x (when doing inverse kinematics) (!! in meters not
                  // pixels !!)
  double yd = -1; // desired y

  bool pause = false;
  bool controllerOff = false;

  int frameCount = 0;
};

class SimLoop {
public:
  Pendulum pendulum;
  SimLoop() : pendulum(Pendulum(0, 0)) {}
  ~SimLoop() {}
  context ctx;

  void run() { emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1); }

  // void run() {
private:
  static void mainloop(void *arg) {
    context *ctx = static_cast<context *>(arg);

    ctx->frameStart = SDL_GetTicks(); // limit framerate (see end of while loop)

    // check for Keyboard inputs;
    ctx->eventChecks.checkEvents(ctx->helperVars, ctx->pendulumDynamics);

    // pause the game
    if (ctx->pause) {
      // do nothing
    } else {
      // reset
      if (ctx->helperVars.getReset() == true) {
        ctx->pendulum.setStates({0, 0, 0, 0});
        ctx->helperVars.toggleReset();
        // reset = false;
        //  ALSO HAVE TO RESET TURN COUNT!!!
      }

      // mouse position
      ctx->mouseState = SDL_GetMouseState(&ctx->x, &ctx->y);
      // coordinates to window center
      ctx->x = ctx->x - ctx->window_width / 2;
      ctx->y = ctx->y - ctx->window_height / 2;
      // converting pixels to endeffector position in meters
      ctx->x_conv =
          ctx->x * 1 /
          (ctx->l1 +
           ctx->l2); // total length of robot arm over total length in pixels
      ctx->y_conv = -ctx->y * 1 / (ctx->l1 + ctx->l2);

      // checking if desired position is inside workspace
      if (sqrt(ctx->x_conv * ctx->x_conv + ctx->y_conv * ctx->y_conv) < 1) {
        ctx->xd = ctx->x_conv;
        ctx->yd = ctx->y_conv; // flipping y for IK assumptions
      }
      // when mouse is outside of workspace
      else if (sqrt(ctx->x_conv * ctx->x_conv + ctx->y_conv * ctx->y_conv) >=
               1) {
        // calculate position on unit circle (total robot length here = 1!!)
        // -> multiply by total length
        double th1 = atan(ctx->y_conv / ctx->x_conv);
        ctx->xd = 0.99999 * cos(th1); // can't handle exactly 1
        ctx->yd = 0.99999 * sin(th1);
        if (ctx->x_conv < 0) {
          ctx->xd = -ctx->xd;
          ctx->yd = -ctx->yd; // flipping for quadrant 2 and 3
        }
      }

      // integration// two integration steps per frame
      for (int i = 0; i < 10; ++i) {
        ctx->pendulumDynamics.setReceivedInputs(
            ctx->pendulumDynamics.inverseKinematics({ctx->xd, ctx->yd}));
        // seperate controller? (maybe seperate IK?)
        ctx->pendulumDynamics.setReceivedStates(ctx->pendulum.getStates());
        ctx->pendulumDynamics.rungeKutta();
        ctx->pendulum.setStates(ctx->pendulumDynamics.getUpdatedStates());
      }

      // calculate coordinates of links (relative angles)
      ctx->x1 = ctx->x0 + ctx->l1 * sin(ctx->pendulum.getStates().at(0));
      ctx->y1 = ctx->y0 + ctx->l1 * cos(ctx->pendulum.getStates().at(0));
      ctx->x2 = ctx->x1 + ctx->l2 * sin(ctx->pendulum.getStates().at(0) +
                                        ctx->pendulum.getStates().at(1));
      ctx->y2 = ctx->y1 + ctx->l2 * cos(ctx->pendulum.getStates().at(0) +
                                        ctx->pendulum.getStates().at(1));
    }

    ctx->helperVars.getTrajectory().push_back(
        {ctx->x2, ctx->y2}); // store endeffector position in trajectory

    // rendering screen
    ctx->ui.clear(); // clears screen

    int width = 10; // half width of the link
    // angles of the short side of the link to the origin (makes it a bit
    // easier to calculate)
    double ang1 = ctx->pi / 2 - ctx->pendulum.getStates().at(0);
    double ang2 = ctx->pi / 2 - (ctx->pendulum.getStates().at(0) +
                                 ctx->pendulum.getStates().at(1));

    // drawing the links
    ctx->ui.drawTiltedRectangle(ctx->x0, ctx->y0, ctx->x1, ctx->y1, ang1,
                                width);
    ctx->ui.drawTiltedRectangle(ctx->x1, ctx->y1, ctx->x2, ctx->y2, ang2,
                                width);

    // draw trajectory (intensity dependend on recency), define trajectory
    // length
    if (ctx->helperVars.getTrajOn()) {
      ctx->ui.drawTrajectory(ctx->helperVars.getTrajectory(), 200);
    }
    ctx->ui.present(); // shows rendered objects

    ctx->frameCount += 1; // count Frame

    // frame time to limit FPS
    ctx->frameTime = SDL_GetTicks() - ctx->frameStart;
    if (ctx->frameDelay > ctx->frameTime) {
      SDL_Delay(ctx->frameDelay - ctx->frameTime);
    }
  }

private:
};

#endif
