
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "../include/cube.h"
#include "../include/definitions.h"
#include "../include/player.h"
#include <SDL2/SDL.h>
#include <math.h>

// typedef struct interface Interface;
typedef struct {
  void (*handle_events)(SDL_Event *event, int *quit, Player *player);
} EventHandler;

void handle_events_function(SDL_Event *event, int *quit, Player *player);

void init_event_handler(EventHandler *event_handler);

#endif
