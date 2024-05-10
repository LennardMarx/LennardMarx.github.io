#ifndef INTERFACE_H
#define INTERFACE_H

#include "../include/cube.h"
#include <SDL2/SDL.h>

typedef struct {
  SDL_Window *window;
  SDL_Window *(*create_window)(char *name, int width, int height);
  SDL_Renderer *renderer;
  SDL_Renderer *(*create_renderer)(SDL_Window *window);
  void (*draw_rect_outline)(SDL_Renderer *renderer, SDL_Rect *r);
  void (*draw_cube)(SDL_Renderer *renderer, Cube *cube);
} Interface;

void init_interface(Interface *interface, int width, int height);
void destroy_interface(Interface *interface);

SDL_Window *create_window_function(char *name, int width, int height);
SDL_Renderer *create_renderer_function(SDL_Window *window);

void draw_rect_outline_function(SDL_Renderer *renderer, SDL_Rect *r);

void draw_cube_function(SDL_Renderer *renderer,
                        Cube *cube); // int screen_pos[8][2]);

#endif
